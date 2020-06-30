#include<iostream>
#include<cstring>
#include<cstdlib>

#define FLAGS_DEALER 1
#define FLAGS_ALL 0

using std::cout;
using std::cin;
using std::endl;

typedef struct s_card {
	char symbol[10];
	int num;
	int value;
} Card;

typedef struct s_deck {
	Card cards[52];
} Deck;

typedef struct s_player {
	float money;
	Card cards[13];
	int cardCount;	
	int cardScore;
	int status;
} Player;

enum Mode {
	HIT = 1,
	STAND = 2,
	BLACKJACK = 3
};

//constructor for cards
Card createCard(const char symbol[], int number, int value){
	Card c;
	
	strcpy(c.symbol, symbol);
	c.num = number;
	c.value = value;
	
	return c;
}

//constructor for deck
Deck createDeck(){
	Deck d;
	
	char symbols[4][10] = {
		"\u2666",	//diamond
		"\u2665",	//heart
		"\u2663",	//clubs
		"\u2660"	//spades
	};
	
	int values[13] = {11, 2, 3, 4, 5 ,6 ,7 ,8 ,9 ,10, 10, 10 ,10};
	
	for(int i = 0; i < 52; i++){
		d.cards[i] = createCard(symbols[i % 4] , (i % 13) + 1 , values[i % 13]);
	}
		
	return d;
}


//search if you have an ace
int aceCounter(Player p){
	int ctr = 0;
	for(int i = 0; i < p.cardCount; i++){
		if(p.cards[i].num == 1){
			ctr++;
		}
	}
	
	return ctr;
}


int bestScore(Player p){
	int score1 = 0;
	int aceCtr = aceCounter(p);
	
	for(int i = 0; i < p.cardCount; i++){
		score1 += p.cards[i].value;
	}
	
	while(aceCtr > 0 && score1 > 21){
		score1 -= 10;
		aceCtr--;
	}
	
	return score1;
}

void drawCard(Deck &d, Player *p){
	Card drawn;
	int index;
	
	srand(time(0));
	
	while(1) {	
		index = rand() % 52;
		drawn = d.cards[index];	
		if(drawn.value != -1){
			break;
		}
	}
	
	d.cards[index].value = -1;
	p->cards[p->cardCount] = drawn;
	p->cardCount++;
	p->cardScore = bestScore(*p);
	
	
}

bool isStand(Player p){
	return p.status == STAND;
}

bool isBust(Player p){
	return p.cardScore > 21;
}

bool isBlackJack(Player p){
	return p.cardScore == 21;
}

void printCard(Card c){	
	bool flags = false;
	char nameEquiv[10];
	int value = c.num;
	switch(value){
		case 1:
			flags = true;
			strcpy(nameEquiv, "ACE");
			break;
		case 11:
			flags = true;
			strcpy(nameEquiv, "JACK");
			break;
		case 12:
			flags = true;
			strcpy(nameEquiv, "QUEEN");
			break;
		case 13:
			flags = true;
			strcpy(nameEquiv, "KING");
			break;
	
	}
	
	if(flags){
		cout << nameEquiv << " of " << c.symbol << endl;
	} else {
		cout << c.num << " of " << c.symbol << endl;
	}
}

void printPlayerCards(Player p, int flags){
	for(int i = 0; i < p.cardCount; i++){
		
		//printCard(p.cards[i]);
		if(flags == FLAGS_DEALER){
			if(i == 0){
				printCard(p.cards[i]);
			} else {
				cout << "?\n";
			}
		} else {
			printCard(p.cards[i]);
		}
	}
	
	if(flags == FLAGS_ALL)
		cout << "Score: " << p.cardScore << endl;			
}

bool isEndOfGame(Player player[]){
	int moneyCtr = 0;
	
	for(int i = 0; i < 4; i++){
		if(player[i].money < 1) moneyCtr++;
	}
		
	
	
	return moneyCtr == 4;
}




int main(void){

	int round = 1;
	int mode;

	Player dealer;
	Player player[4];
	Deck deck;
	
	//char block;
	
	for(int i = 0; i < 4; i++){
		player[i].money = 10;	//set initial value
	}
	
	while(1){
		//work here
		deck = createDeck();
		
		//start of round	
		cout << "-----------------Round " << round << "-------------------" << endl;		
		
		//distribute for players
		cout << "DISTRIBUTE PHASE\n\n";
		for(int i = 0; i < 4; i++){
			player[i].cardScore = 0;
			player[i].cardCount = 0;
			if(player[i].money < 1) continue;		//ignnore player with money less than 1
			player[i].status = HIT;
			for(int j = 0; j < 2; j++){
				drawCard(deck, &player[i]);
			}
		}
	
		
		for(int i = 0; i < 4; i++){
			if(player[i].money < 1) continue;		//ignnore player with money less than 1
			cout << "Player " << i + 1 << endl;
			cout << "Money: " << player[i].money << endl;
			cout << "Number of cards: " << player[i].cardCount << endl;
			printPlayerCards(player[i], FLAGS_ALL);
			cout << endl;
		}
				
		//draw dealer
		dealer.cardCount = 0;
		for(int j = 0; j < 2; j++){
			drawCard(deck, &dealer);
		}
				
		cout << "\nDealer cards\n";
		printPlayerCards(dealer, FLAGS_DEALER);
	
			
		//black jack checking
		for(int i = 0; i < 4; i++){
			if(player[i].money < 1) continue;		//ignnore player with money less than 1
			if(isBlackJack(player[i])){
				cout << "\nPlayer " << i + 1 << " BlackJack\n";
				player[i].status = BLACKJACK;
				if(!isBlackJack(dealer)){
					player[i].money += 1.5;
				} 
				//cout << "Player " << i + 1 << " money: " << player[i].money << endl << endl;
			} else if(isBlackJack(dealer)){	
				if(!isBlackJack(player[i])){
					player[i].money--;
				//	cout << "Player " << i + 1 << " money: " << player[i].money << endl << endl;
				}
			} 
		}
		
		//print dealer cards if blackjack
		if(isBlackJack(dealer)){
			cout << "\nDealer " <<  " BlackJack\n";
			printPlayerCards(dealer, 0);
				
			//end of round, print
			for(int i = 0; i < 4; i++){
				if(player[i].money < 1 && player[i].cardCount == 0 ) continue;
				cout << "--------------Player " << i + 1 << "---------------" << endl;
				printPlayerCards(player[i], FLAGS_ALL);
				cout << "Money: " << player[i].money << endl;
			}
		
			if(isEndOfGame(player)){
				break;
			}
			
			cout << "Press enter to continue: ";
			cin.get();
			cin.ignore();
			round++;
			continue;
		}
		
		//next phase
		while(1){
			bool hit = false;
			for(int i = 0; i < 4; i++){
				
				//blockers
				if(player[i].money < 1) continue;
				if(player[i].status == BLACKJACK) continue;
				if(isBust(player[i])) continue;
				if(isStand(player[i])) continue;
			
				cout << "\n-----------Player " << i + 1 << " turn------------\n";
				cout << "Your cards\n";
				printPlayerCards(player[i], FLAGS_ALL);
				cout << "\n1. HIT \n2. STAND\n";
				cout << "Enter mode: ";	
				cin >> mode;
			
				switch(mode){
					case HIT:
						drawCard(deck, &player[i]);	
						cout << "\nYour new set of cards \n";
						printPlayerCards(player[i], FLAGS_ALL);
						if(isBust(player[i])){
							cout << "BUSTED!\n";
						}
						hit = true;
						break;
					case STAND:
						cout << "STAND\n";
						player[i].status = STAND;
						continue;
						break;
				}
			}
				
				
			if(!hit) break;	
		}
			
		//next phase dealer
		cout << "--------Dealer------\n";
		while(dealer.cardScore < 17){
			drawCard(deck, &dealer);
			printPlayerCards(dealer, FLAGS_DEALER);
			cout << "-----------------------\n";
		}
			
		//dealer is busted
		if(isBust(dealer)){
			cout << "BUSTED!\n";
			for(int i = 0; i < 4; i++){
				if(player[i].money < 1) continue;
				if(player[i].status == BLACKJACK){	//ignore blackJack already added money
					continue;
				} else if(!isBust(player[i])){
					player[i].money++;
				} 
			}
		} else {
			for(int i = 0; i < 4; i++){
				if(player[i].money < 1) continue;
				if(player[i].status == BLACKJACK){	//ignore blackJack already added money
					continue;			
				} else {		//compare cards of dealer and every player with no black jack	
					if(dealer.cardScore > player[i].cardScore ||
							 isBust(player[i])) {
						player[i].money--;
					} else if(dealer.cardScore < player[i].cardScore) {
						player[i].money++;
					}
				}
			}
		}
		printPlayerCards(dealer, FLAGS_ALL);
		
		//end of round, print
		for(int i = 0; i < 4; i++){
			if(player[i].money < 1 && player[i].cardCount == 0 ) continue;
			cout << "--------------Player " << i + 1 << "---------------" << endl;
			printPlayerCards(player[i], FLAGS_ALL);
			cout << "Money: " << player[i].money << endl;
		}
		
		
		if(isEndOfGame(player)){
			break;
		}

		cout << "Press enter to continue: ";
		cin.get();
		cin.ignore();
		round++;			
	}
		
		
	cout << "The game will end\n";
	
	return 0;
}
