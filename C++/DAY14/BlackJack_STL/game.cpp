#include <iostream>
#include "game.h"

using namespace std;

Game::Game(){
	round = 1;
	pCount = 0;
	dCount = 0;
	endOfGame = false;
	endOfRound = false;
	dealer = new DealerPlayer();
}

void Game::setUpPhase(){
	cout << "---------WELCOME TO BLACKJACK GAME!---------\n\n";

	while(1){
		cout << "Enter number of players: ";
		cin >> pCount;
		if(pCount <= 10 && pCount >= 1){
			break;
		}
		cout << "Invalid number of players.\n";
	}

	while(1){
		cout << "Enter number of Decks: ";
		cin >> dCount;
		if(dCount <= 10 && dCount >= 1){
			break;
		}
		cout << "Invalid number of Decks.\n";
	}
	deck = new Deck(dCount);
	deck->shuffle();

	for(int i = 0; i < pCount; i++){
		float money;
		cout << "Enter starting money for Player " << i + 1 << ": ";
		cin >> money;
		if(money <= 10000 && money >= 0) {
			players[i] = new NormalPlayer(money);
			players.push_back(new NormalPlayer(money));
		} else {
			cout << "Invalid starting money.\n";
			i--;
		}
	}
}

void Game::start(){
	while(!isEndOfGame()){
		resetForNewRound();
		bettingPhase();
		distributePhase();
		surrenderPhase();
		blackJackCheckingPhase();
		printTable();
		if(isEndOfRound()){
			if(isEndOfGame()){
				break;
			}
		}
		playerDecisionPhase();
		dealerDecisionPhase();
		checkPayouts();
		printTable();
	}
}


//private
void Game::resetForNewRound(){
	endOfRound = false;
	dealer->reset();
	deck->reset();
	//reset player variabes
	for(auto &p : players){
		p->reset();
	}
}

void Game::bettingPhase(){
	//betting phase
	cout << "-----BETTING PHASE-----\n\n";
	for(auto &p : players){
		float bet;
		cout << "Player " << p->getId() << " - Money: " << p->getMoney() << endl;
		cout << "Enter bet: ";
		cin >> bet;
		if(bet > p->getMoney() || bet < 0) {
			cout << "Invalid bet amount.\n";
			i--;
			continue;
		}
		p->getPrimaryHand()->setBet(bet);
	}
}

void Game::distributePhase(){
	//distribute phase
	cout << "\n-----DISTRIBUTE PHASE------\n";
	for(int i = 0; i < pCount + 1; i++){
		for(int j = 0; j < 2; j++){
			Card *cardFromDeck;
			if(i == pCount) {
				cardFromDeck = deck->getCard();
				dealer->getPrimaryHand()->putCard(cardFromDeck);
			} else {
				cardFromDeck = deck->getCard();
				cardFromDeck->show();
				players[i]->getPrimaryHand()->putCard(cardFromDeck);
			}
		}
	}
}

void Game::surrenderPhase(){
	//surrender phase
	cout << "\n-----SURRENDER PHASE------\n";
	dealer->getPrimaryHand()->getCardAt(0)->show();	
	for(auto &p : players){
		int choice;
		cout << "---------DEALER CARDS-------\n";
		dealer->getPrimaryHand()->printAllCards();
		cout << "---------Player " << p->getId() << "--------\n";
		p->getPrimaryHand()->printHandInfo();
		cout << "------------------------------\n";
		cout << "Press 1 to surrender: ";
		cin >> choice;
		if(choice == 1) {
			p->getPrimaryHand()->surrender();
			p->payOut(p->getPrimaryHand()->getBet() / 2);
		}
	}
}

void Game::blackJackCheckingPhase(){
	//BlackJack Checking
	for(auto &p : players){
		if(p->getPrimaryHand()->getStatus() == Hand::STATUS_SURRENDER) continue;
		if(p->getPrimaryHand()->isBlackJack()){
			p->getPrimaryHand()->setStatus(Hand::STATUS_BLACKJACK);
			if(!dealer->getPrimaryHand()->isBlackJack()) {
				float bet = p->getPrimaryHand()->getBet() * 1.5;
				p->addWinnings(bet);
			}
		}
	}

	//dealer is blackJack, find if other players are blackjack
	if(dealer->getPrimaryHand()->isBlackJack()){		
		dealer->getPrimaryHand()->setStatus(Hand::STATUS_BLACKJACK);
		dealer->getPrimaryHand()->getCardAt(1)->show();
		endOfRound = true;
		for(auto &p : players) {
			if(p->getPrimaryHand()->getStatus() == Hand::STATUS_SURRENDER) continue;
			
			if(p->getPrimaryHand()->isBlackJack()){
				p->getPrimaryHand()->setStatus(Hand::STATUS_BLACKJACK + " TIE!");
			} else {
				//payout
				p->getPrimaryHand()->setStatus(Hand::STATUS_LOSE);
				p->payOut(p->getPrimaryHand()->getBet());
			}
		}
	}
}

void Game::printTable(){
	//print table
	cout << "\n-------PLAYER CARDS--------\n\n";
	for(int i = 0; i < pCount + 1; i++) {
		if(i == pCount) {			
			if(endOfRound) {
				dealer->printInfo();
			} else {
				cout << "--------DEALER--------\n";
				dealer->getPrimaryHand()->printAllCards();
			}
		} else {	
			cout << "---------Player " << players[i]->getId() << "--------\n";
			players[i]->printInfo();
			if(players[i]->isBankrupt()) players.erase(players[i]);
		}
	}
}

bool Game::isEndOfRound(){
	return endOfRound;
}

bool Game::isEndOfGame(){

	endOfGame = true;
	for(auto &p : players){
		if(!p->isBankrupt()) {
			endOfGame = false;
			break;
		} else {
			players.erase(p);
		}
	}
	
	return endOfGame;
}

void Game::playerDecisionPhase() {
//decision phase
	cout << "----------DECISION PHASE-----------\n\n";
	while(1){
		bool hit = false;
		for(auto &p : players){
			//player will split
			splittingPhase(p);		
			playersTurn(p, hit);
			
		}//End of for loop for ever players
			
		if(!hit) break;		//break the infinite loop for decision phase

	}//End of while loop for decision phase
}

void Game::dealerDecisionPhase(){
	//Dealer decision
	cout << "-------Dealers decision------\n";
	dealer->getPrimaryHand()->printAllCards();
	while(1){
		Card *cardFromDeck;
		if(dealer->decide() == Hand::DECISION_HIT){
			cardFromDeck = deck->getCard();
			cout << "HIT -> ";
			cardFromDeck->print();
			dealer->getPrimaryHand()->hit(cardFromDeck);
			if(dealer->getPrimaryHand()->isBusted()){
				dealer->getPrimaryHand()->setStatus(Hand::STATUS_BUST);
			}
		} else {
			dealer->getPrimaryHand()->stand();
			cout << "STAND\n";
			break;
		}
	}
}

void Game::playersTurn(NormalPlayer *p, bool &hit){
//loop for player hands
	int mode;
	vector<Hand *> playerHands = p->getAllHands();
	for(auto &currentHand : playerHands) {
		
		if(!currentHand->canPlay()) continue;
			
		cout << "---------Player " << p->getId() << " turn------------\n";
		cout << "Money: " << p->getMoney() << endl;
		cout << "----Cards on Hand " << j + 1 << "----\n";
		currentHand->printHandInfo();
					
		while(1){
			cout << "1. Hit" << endl << "2. Stand" << endl << "3. Double" << endl;
			cout << "Enter mode:";
			cin >> mode;
			if(mode == Hand::DECISION_DOUBLE){
				float money = p->getMoney();
				if(!currentHand->canDouble(money)){
					cout << "Insufficient Funds! Try another mode\n";
					continue;
				}
			} 
			break;
		}
		
		Card *cardFromDeck;
		switch(mode){
			case Hand::DECISION_HIT:
				cardFromDeck = deck->getCard();
				cardFromDeck->show();
				currentHand->hit(cardFromDeck);
				hit = true;
				if(currentHand->isBusted()) {
					currentHand->setStatus(Hand::STATUS_BUST);
				}
				cout << "------New Cards on Hand-------\n";
				currentHand->printHandInfo();
				break;
			case Hand::DECISION_STAND:
				currentHand->stand();
				break;
			case Hand::DECISION_DOUBLE:
				cardFromDeck = deck->getCard();
				cardFromDeck->show();
				currentHand->doubleMove(cardFromDeck);
				if(p->getHandAt(j)->isBusted()) {
					currentHand->setStatus(Hand::STATUS_BUST);
				}
				cout << "------New Cards on Hand-------\n";
				currentHand->printHandInfo();
				break;
		}
				
	}// End of for loop for player hands
}

void Game::splittingPhase(NormalPlayer *p){
	int mode;
	if(p->isHandSplited()) return;
	if(p->getSplitStatus() == NormalPlayer::SPLIT_REFUSE) return;
	if(!p->getPrimaryHand()->isSplitable()) return;
	
	if(p->canSplit()){		
		cout << "---------Player " << p->getId() << " turn------------\n";
		cout << "----Cards on Hand----\n";
		p->getPrimaryHand()->printHandInfo();
		cout << "Press 1 to split: ";
		cin >> mode;
		if(mode == 1){
			p->split();
			for(int k = 0; k < 2; k++){
				float bet = p->getPrimaryHand()->getBet();
				Card *cardFromDeck;
				cardFromDeck = deck->getCard();
				cardFromDeck->show();
				p->getHandAt(k)->putCard(cardFromDeck);
				p->getHandAt(k)->setBet(bet);
				cout << "----New Cards on Hand----" << k + 1 << endl;
				p->getHandAt(k)->printAllCards();
			}
		} else {
			p->setSplitStatus(NormalPlayer::SPLIT_REFUSE);
		}
	}

}


void Game::handPayOut(NormalPlayer *p, Hand *hand){
	Hand *dealerHand = dealer->getPrimaryHand();
	float bet = hand->getBet();
	if(dealerHand->isBusted() && !hand->isBusted()){
		hand->setStatus(Hand::STATUS_WIN);
		p->addWinnings(bet);
	} else if(hand->getStatus() == Hand::STATUS_BUST && !dealerHand->isBusted()){
		p->payOut(bet);
	} else if(hand->getScore() > dealerHand->getScore() && !hand->isBusted()){
		hand->setStatus(Hand::STATUS_WIN);
		p->addWinnings(bet);
	} else if(hand->getScore() < dealerHand->getScore() && !dealerHand->isBusted()) {
		hand->setStatus(Hand::STATUS_LOSE);
		p->payOut(bet);
	} else if(hand->getScore() == dealerHand->getScore() && !hand->isBusted() ){
		hand->setStatus("TIED!");
	} 
}

void Game::checkPayouts(){
	//Check Payouts
	endOfRound = true;
	for(auto &currPlayer : players){
		for(int j = 0; j < currPlayer->getHandCount(); j++){
			Hand *currentHand = currPlayer->getHandAt(j);
			if(currPlayer->isBankrupt() && currentHand->getCardCount() == 0) {
				continue;
			}
			if(!currentHand->hasPayout()) continue;			
			handPayOut(currPlayer, currentHand);
		}
	}
}

Game::~Game(){
	for(auto &currPlayer : players){
		delete currPlayer;
	}
	delete players;
	delete deck;
	delete dealer;

}
