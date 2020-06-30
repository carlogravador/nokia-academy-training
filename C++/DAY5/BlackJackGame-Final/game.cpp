/**
 *	Driver Class for the game BlackJack 
 */

#include<iostream>

using std::cin;
using std::cout;
using std::endl;

#include "deck.h"
#include "normalplayer.h"
#include "dealerplayer.h"

int main(){
	int pCount;
	int dCount;
	int round = 1;
	bool endOfRound = false;
	bool endOfGame = false;
	
	DealerPlayer *dealer = new DealerPlayer();
	Deck *deck;
	NormalPlayer **players;

	cout << "---------WELCOME TO BLACKJACK GAME!---------\n\n";

	while(1){
		cout << "Enter number of players: ";
		cin >> pCount;
		if(pCount <= 10 && pCount >= 1){
			break;
		}
		cout << "Invalid number of players.\n";
	}
	players = new NormalPlayer* [pCount];

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
		} else {
			cout << "Invalid starting money.\n";
			i--;
		}
	}

	while(1){
		//start of round
		cout << "\n------ROUND " << round << "--------\n\n";
		
		endOfRound = false;
		dealer->reset();
		deck->reset();
		//reset player variabes
		for(int i = 0; i < pCount; i++){
			players[i]->reset();
		}
		
		//betting phase
		cout << "-----BETTING PHASE-----\n\n";
		for(int i = 0; i < pCount; i++){
			if(players[i]->isBankrupt()) continue;
			float bet;
			cout << "Player " << i + 1 << " - Money: " << players[i]->getMoney() << endl;
			cout << "Enter bet: ";
			cin >> bet;
			if(bet > players[i]->getMoney() || bet < 0) {
				cout << "Invalid bet amount.\n";
				i--;
				continue;
			}
			players[i]->getPrimaryHand()->setBet(bet);
		}
		
		//distribute phase
		cout << "\n-----DISTRIBUTE PHASE------\n";
		for(int i = 0; i < pCount + 1; i++){
			for(int j = 0; j < 2; j++){
				Card *cardFromDeck;
				if(i == pCount) {
					cardFromDeck = deck->getCard();
					dealer->getPrimaryHand()->putCard(cardFromDeck);
				} else {
					if(players[i]->isBankrupt()) continue;
					cardFromDeck = deck->getCard();
					cardFromDeck->show();
					players[i]->getPrimaryHand()->putCard(cardFromDeck);
				}
			}
		}

		//surrender phase
		cout << "\n-----SURRENDER PHASE------\n";
		dealer->getPrimaryHand()->getCardAt(0)->show();	
		for(int i = 0; i < pCount; i++){
			if(players[i]->isBankrupt()) continue;
			int choice;
			cout << "---------DEALER CARDS-------\n";
			dealer->getPrimaryHand()->printAllCards();
			cout << "---------Player " << players[i]->getId() << "--------\n";
			players[i]->getPrimaryHand()->printHandInfo();
			cout << "------------------------------\n";
			cout << "Press 1 to surrender: ";
			cin >> choice;
			if(choice == 1) {
				players[i]->getPrimaryHand()->surrender();
				players[i]->payOut(players[i]->getPrimaryHand()->getBet() / 2);
			}
		}
		
		//BlackJack Checking
		for(int i = 0; i < pCount; i++){
			if(players[i]->isBankrupt()) continue;
			if(players[i]->getPrimaryHand()->getStatus() == Hand::STATUS_SURRENDER) continue;
			if(players[i]->getPrimaryHand()->isBlackJack()){
				players[i]->getPrimaryHand()->setStatus(Hand::STATUS_BLACKJACK);
				if(!dealer->getPrimaryHand()->isBlackJack()) {
					float bet = players[i]->getPrimaryHand()->getBet() * 1.5;
					players[i]->addWinnings(bet);
				}
			}
		}

		//dealer is blackJack, find if other players are blackjack
		if(dealer->getPrimaryHand()->isBlackJack()){		
			dealer->getPrimaryHand()->setStatus(Hand::STATUS_BLACKJACK);
			dealer->getPrimaryHand()->getCardAt(1)->show();
			endOfRound = true;
			for(int i = 0; i < pCount; i++) {
				if(players[i]->isBankrupt()) continue;
				if(players[i]->getPrimaryHand()->getStatus() == Hand::STATUS_SURRENDER) continue;
				
				if(players[i]->getPrimaryHand()->isBlackJack()){
					players[i]->getPrimaryHand()->setStatus(Hand::STATUS_BLACKJACK + " TIE!");
				} else {
					//payout
					players[i]->getPrimaryHand()->setStatus(Hand::STATUS_LOSE);
					players[i]->payOut(players[i]->getPrimaryHand()->getBet());
				}
			}
		}

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
				if(players[i]->isBankrupt() && players[i]->getPrimaryHand()->getCardCount() == 0) {
					continue;
				}	
				cout << "---------Player " << players[i]->getId() << "--------\n";
				players[i]->printInfo();
			}
		}

		if(endOfRound){
			
			endOfGame = true;
			for(int i = 0; i < pCount; i++ ){
				if(!players[i]->isBankrupt()) {
					endOfGame = false;
					break;
				}
			}

			cout << "Press enter to continue: ";
			cin.get();
			cin.ignore();
			round++;
		
			if(endOfGame) break;
			
			continue;
		}

		//decision phase
		cout << "----------DECISION PHASE-----------\n\n";
		while(1){
			bool hit = false;
			for(int i = 0; i < pCount; i++){
				if(players[i]->isBankrupt()) continue;
				
				for(int j = 0; j < 2; j++) {
					int mode;
					Card *cardFromDeck;
					
					if(!players[i]->isHandSplited() && 
							players[i]->getSplitStatus() != NormalPlayer::SPLIT_REFUSE) {
						if(players[i]->getPrimaryHand()->isSplitable()) {
							//check if money is capable of splitting depending on bet
							if(players[i]->canSplit()){		
								cout << "---------Player " << i + 1 << " turn------------\n";
								cout << "----Cards on Hand----\n";
								players[i]->getPrimaryHand()->printHandInfo();
								cout << "Press 1 to split: ";
								cin >> mode;
								if(mode == 1){
									players[i]->split();
									for(int k = 0; k < 2; k++){
										float bet = players[i]->getPrimaryHand()->getBet();
										cardFromDeck = deck->getCard();
										cardFromDeck->show();
										players[i]->getHandAt(k)->putCard(cardFromDeck);
										players[i]->getHandAt(k)->setBet(bet);
										cout << "----New Cards on Hand----" << k + 1 << endl;
										players[i]->getHandAt(k)->printAllCards();
									}
								} else {
									players[i]->setSplitStatus(NormalPlayer::SPLIT_REFUSE);
								}
							}
						}
					}
					//Blockers
					if(players[i]->getHandAt(j)->getDecision() == Hand::DECISION_STAND) {
						if(players[i]->isHandSplited()) continue;
						else break;
					}
					if(players[i]->getHandAt(j)->getStatus() == Hand::STATUS_BLACKJACK) {
						if(players[i]->isHandSplited()) continue;
						else break;
					}
					if(players[i]->getHandAt(j)->getStatus() == Hand::STATUS_SURRENDER) {
						if(players[i]->isHandSplited()) continue;
						else break;
					}
					if(players[i]->getHandAt(j)->getStatus() == Hand::STATUS_BUST) {
						if(players[i]->isHandSplited()) continue;
						else break;
					}
					if(players[i]->getHandAt(j)->getDecision() == Hand::DECISION_STAND) {
						if(players[i]->isHandSplited()) continue;
						else break;
					}

					cout << "---------Player " << i + 1 << " turn------------\n";
					cout << "----Cards on Hand " << j + 1 << "----\n";
					players[i]->getHandAt(j)->printHandInfo();

					cout << "1. Hit" << endl << "2. Stand" << endl << "3. Double" << endl;
					cout << "Enter mode:";
					cin >> mode;
					switch(mode){
						case Hand::DECISION_HIT:
							cardFromDeck = deck->getCard();
							cardFromDeck->show();
							players[i]->getHandAt(j)->hit(cardFromDeck);
							hit = true;
							if(players[i]->getHandAt(j)->isBusted()) {
								players[i]->getHandAt(j)->setStatus(Hand::STATUS_BUST);
							}
							cout << "------New Cards on Hand-------\n";
							players[i]->getHandAt(j)->printHandInfo();
							break;
						case Hand::DECISION_STAND:
							players[i]->getHandAt(j)->stand();
							break;
						case Hand::DECISION_DOUBLE:
							cardFromDeck = deck->getCard();
							cardFromDeck->show();
							players[i]->getHandAt(j)->doubleMove(cardFromDeck);
							if(players[i]->getHandAt(j)->isBusted()) {
								players[i]->getHandAt(j)->setStatus(Hand::STATUS_BUST);
							}
							cout << "------New Cards on Hand-------\n";
							players[i]->getHandAt(j)->printHandInfo();
							break;
					}
					
					if(!players[i]->isHandSplited()) break;
					
				}// End of for loop for player hands

			}//End of for loop for ever players
			
			if(!hit) break;		//break the infinite loop for decision phase

		}//End of while loop for decision phase

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

		//Check Payouts
		for(int i = 0; i < pCount; i++){
			for(int j = 0; j < 2; j++){
				
				if(players[i]->isBankrupt() && players[i]->getHandAt(j)->getCardCount() == 0) {
					if(players[i]->isHandSplited()) continue;
					else break;
				}
				if(players[i]->getHandAt(j)->getStatus() == Hand::STATUS_BLACKJACK) {
					if(players[i]->isHandSplited()) continue;
					else break;
				}
				if(players[i]->getHandAt(j)->getStatus() == Hand::STATUS_SURRENDER) {
					if(players[i]->isHandSplited()) continue;
					else break;
				}

				float bet = players[i]->getHandAt(j)->getBet();
				if(dealer->getPrimaryHand()->isBusted() && !players[i]->getHandAt(j)->isBusted()){
					players[i]->getHandAt(j)->setStatus(Hand::STATUS_WIN);
					players[i]->addWinnings(bet);
				} else if(players[i]->getHandAt(j)->getStatus() == Hand::STATUS_BUST
						&& !dealer->getPrimaryHand()->isBusted()){
					players[i]->payOut(bet);
				} else if(players[i]->getHandAt(j)->getScore() > 
						dealer->getPrimaryHand()->getScore() && 
								!players[i]->getHandAt(j)->isBusted()){
					players[i]->getHandAt(j)->setStatus(Hand::STATUS_WIN);
					players[i]->addWinnings(bet);
				} else if(players[i]->getHandAt(j)->getScore() < 
						dealer->getPrimaryHand()->getScore() && 
							!dealer->getPrimaryHand()->isBusted()) {
					players[i]->getHandAt(j)->setStatus(Hand::STATUS_LOSE);
					players[i]->payOut(bet);
				} else if(players[i]->getHandAt(j)->getScore() == 
						dealer->getPrimaryHand()->getScore() &&
							 !players[i]->getHandAt(j)->isBusted() ){
					players[i]->getHandAt(j)->setStatus("TIED!");
				} 

				if(!players[i]->isHandSplited()) break;
			}
		}

		//print table
		cout << "\n-------PLAYER CARDS--------\n\n";
		for(int i = 0; i < pCount + 1; i++) {	
			if(i == pCount) {			
				dealer->printInfo();
			} else {
				if(players[i]->isBankrupt() && players[i]->getPrimaryHand()->getCardCount() == 0) {
					continue;
				}	
				cout << "---------Player " << players[i]->getId() << "--------\n";
				players[i]->printInfo();
			}
		}

		endOfGame = true;
		for(int i = 0; i < pCount; i++ ){
			if(!players[i]->isBankrupt()) {
				endOfGame = false;
				break;
			}
		}

		cout << "Press enter to continue: ";
		cin.get();
		cin.ignore();
		round++;
		
		if(endOfGame) break;

	}//End of infinite loop game
	cout << "-------------END OF GAME---------------\n";
	for(int i = pCount - 1; i > 0; i--){
		delete players[i];
	}
	delete deck;
	delete players;
	delete dealer;

	return 0;
}
