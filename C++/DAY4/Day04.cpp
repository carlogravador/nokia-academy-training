#include <iostream>
#include <cstring>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct pDetails
{
	string _name;
	float money;
	string cards[2];
	int score[2];
	string status[2];
	bool isStand[2];
	float bet[2];
	bool split;
	bool isOut;
};



string shuffle(string &card);
bool blackJack(int sum);
int score(string cards);
int cardScore(char single);

void printDealerCards(struct pDetails dealer){
	int length = dealer.cards[0].length();
	for(int i = 0; i < length; i++){
		if(i == 0){
			cout << dealer.cards[0][0];
		} else {
			cout << "?";
		}
	}

}


int main()
{

    int rnd=1,_dealIndex;
	const string origDeck = "A23456789XJKQA23456789XJKQA23456789XJKQA23456789XJKQ";
	string card;
	string &crd = card;
	int playerCount;
	int deckCount;

	while(1){
		cout << "Enter number of players:";
		cin >> playerCount;
		if(playerCount <= 10 && playerCount >= 1) break;	
		cout << "Invalid input \n";
	}

	playerCount++;		//for dealer;
	while(1){
		cout << "Enter number of decks:";
		cin >> deckCount;
		if(deckCount <= 10 && deckCount >= 1) break;	
		cout << "Invalid input \n";
	}

	for(int i = 0; i < deckCount; i++){
		card += origDeck;		//add deck
	}

	struct pDetails _player[playerCount];

	for(int i = 1; i < playerCount; ++i)
	{
		cout << "Enter name for player " << i << ": ";
		cin >>_player[i]._name;
		while(1){		
			cout << "Enter initial money: ";
			cin >> _player[i].money;
			if(_player[i].money <= 10000 && _player[i].money >= 0){
				break;
			}
			cout << "Invalid input\n";
		}		
	}
	//shuffling cards

while(1)
{
	cout<<"\t\t\n\n>>>>Round " << rnd << "<<<<\n\n";
	for(int i = 1; i < playerCount; i++){
		while(1){
			cout << "Player: " << _player[i]._name << endl;
			cout << "Enter your bet on this round: ";
			cin >> _player[i].bet[0];
			if(_player[i].bet[0] <= _player[i].money && _player[i].bet[0] >= 0) break;
			cout << "Insufficient funds\n";
		}
	}

	
	int activeCtr = 0;
	for(int i=0;i<playerCount;i++)			//reset players every round
	{
		_player[i].split = false;
		_player[i].isStand[0] = false;
		_player[i].isStand[1] = false;
		_player[i].score[0] = 0;
		_player[i].score[1] = 0;
		_player[i].cards[0] = "";
		_player[i].cards[1] = "";
		if(_player[i].isOut) continue;
		_player[i].status[0] = " ";
		_player[i].status[1] = " ";
		activeCtr++;
		
	}
	activeCtr--;
	_dealIndex = 0;
	
	string newCards = shuffle(crd);
		
//	give 2 cards each
	for(int y = 0; y < 2; ++y)
	{
		for(int i = 0; i < playerCount; ++i)
		{
			if(_player[i].money >=1)
			{
				_player[i].cards[0] += newCards[_dealIndex];
			_dealIndex++;	
			}
		}
	}
	int standCount = 0;
	int handCtr = 0;
	_player[1].cards[0] = "JQ";
	for(;;)
	{
		//dealer
		standCount = 0;
		bool isHit = false;
		_player[0].score[0] = score(_player[0].cards[0]);
		for(int i = 1; i < playerCount; ++i)
		{
			handCtr = 0;
			if(_player[i].isOut) continue;
			_player[i].score[0] = score(_player[i].cards[0]); 		//compute score
			
			if(blackJack(_player[i].score[0]))			//check blackjack
			{		
					_player[i].status[0] = "WIN";
			}	
			else
			{
				
				printDealerCards(_player[0]);								
				cout << endl << "PLAYER " << _player[i]._name << "'s TURN!" << endl;								
				while(1){			//loop for hand
					if(_player[i].isStand[handCtr] == false && _player[i].status[handCtr] != "WIN")
					{   	
						cout << "HAND CTR: " << handCtr;
						cout << "Current bet: " << _player[i].bet[handCtr] << endl;
						char opt;
						if(_player[i].score[handCtr] < 21)
						{
							//skip if already split
							if(cardScore(_player[i].cards[0][0]) == cardScore(_player[i].cards[0][1]) &&
									 !_player[i].split){		//splitable
								if(_player[i].bet[0] * 2 <= _player[i].money){
									int temp;
									cout << "Press 1 to split: ";
									cin >> temp;
									if(temp == 1){
										activeCtr++;
										string temp = _player[i].cards[0];
										_player[i].cards[0] = temp[0];
										_player[i].cards[1] = temp[1];
										_player[i].cards[0] += newCards[_dealIndex];
										_player[i].score[0] = score(_player[i].cards[0]);
										_player[i].bet[0] = _player[i].bet[0];
										_player[i].bet[1] = _player[i].bet[0];
										if(blackJack(_player[i].score[0]))			//check blackjack
										{		
											_player[i].status[0] = "WIN";
										}
										_dealIndex++;
										
										_player[i].cards[1] += newCards[_dealIndex];
										_player[i].score[1] = score(_player[i].cards[1]);	
										if(blackJack(_player[i].score[1]))			//check blackjack
										{		
											_player[i].status[1] = "WIN";
										}
										_dealIndex++;
										_player[i].split = true;
									}
								}
							}

							cout << "Cards on HAND: " << _player[i].cards[handCtr] << endl << "Current Value: " << _player[i].score[handCtr] << endl << "Stand or Hit? (S / H): ";	
							cin >> opt;
							cin.ignore();
							if(tolower(opt) == tolower('s'))
							{
								_player[i].isStand[handCtr] = true;
								standCount++;
							}
							if(tolower(opt) == tolower('h'))
							{
								cout << "Current Value: " << _player[i].score[handCtr] << endl << "Current Cards: " << _player[i].cards[handCtr] ;
								_player[i].cards[handCtr] += newCards[_dealIndex];		//concat character
								cout << endl << "New set of Cards: " << _player[i].cards[handCtr];
								_player[i].score[handCtr] = score(_player[i].cards[handCtr]);		//compute score
								cout << endl << "New Value: " << _player[i].score[handCtr] << endl;
								_dealIndex++;
								isHit = true;
							}
						}
						else	//busted	
						{
							_player[i].isStand[handCtr] = true;
							standCount++;
							
						}
					} 
				//----------------loop-----------------
					if(_player[i].split){
						handCtr++;
						if(handCtr == 2){
							break;
						}
					} else {
						break;					
					}
				}
				
			}
		}
		
		if(blackJack(_player[0].score[0]))
		{
				_player[0].status[0] = "WIN";
		}
		else
		{
			if(_player[0].score[0] < 17)
			{
				_player[0].score[0] = score(_player[0].cards[0] + newCards[_dealIndex]);
				_player[0].cards[0] +=newCards[_dealIndex];
				_dealIndex++;
			}
		}
		
		if(_player[0].score[0] >= 17 )
		{
			_player[0].isStand[0] = true;
		}
		
		if((!isHit || standCount == activeCtr) && _player[0].isStand[0])
		{
			system("clear");
			cout << "\n\n\n\t\t\tGame Ends!!"<<endl;
			break;
			
		}
	}


	//compare
	
	system("clear");
	for(int i = 1; i < playerCount; ++i)
	{
		handCtr = 0;
		if(_player[i].isOut) continue;
		while(1){
			cout << "INFINITE\n";
			if(_player[i].score[handCtr] > 21)
			{
				_player[i].money -= _player[i].bet[handCtr];
			}
			else
			{
				if(_player[i].status[handCtr] == "WIN" && _player[0].status[0] != "WIN")
				{
					_player[i].money += _player[i].bet[handCtr] * 1.5;
				}
				else if(_player[i].score[handCtr] > _player[0].score[0])
				{
					_player[i].money += _player[i].bet[handCtr];
				}
				else if(_player[0].score[0] > 21)
				{
					_player[i].money += _player[i].bet[handCtr];
				}
				else if(_player[i].status[handCtr] != "WIN" && _player[0].status[0] == "WIN")
				{
					_player[i].money -= _player[i].bet[handCtr];
				}
				else if(_player[i].score[handCtr] < _player[0].score[0])
				{
					_player[i].money -= _player[i].bet[handCtr];
				}
			
			}
				if(_player[i].split){
					handCtr++;
					if(handCtr == 2){
						break;				
					}
				} else {
					break;
				}
	
		
		}
		if(_player[i].money <= 0) {
			_player[i].isOut = true;
		}
		
		handCtr = 0;
		cout << "DEALER' S CARD: " << _player[0].cards[0] << "   CARD VALUE: " << _player[0].score[0] << endl;
		cout << "Player: " << _player[i]._name << endl;
		cout << "CURRENT MONEY: " << _player[i].money << endl;
		while(1){
			cout << "CARDS: " << _player[i].cards[handCtr] << "   VALUE: " << _player[i].score[handCtr] << endl;
			if(_player[i].split){
					handCtr++;
					if(handCtr == 2){
						break;				
					}
			} else {
				break;
			}
		}
		cout << "TEST REACH i: " << i << "PlayerCount: " << playerCount << endl;	
		continue;
	}
	rnd++;
	
	if(_player[1].money<1 && _player[2].money<1&& _player[3].money<1 &&_player[4].money<1)
	{
		break;
	}

}
	return 0;
}


int cardScore(char single){
	if(single == 'X' || single == 'J' || single == 'Q' || single == 'K')
		{
			return 10;	
		}
		else if(single == 'A')
		{
			return 11;
		}
		else
		{
			return (int)(single - 48);
		}
}

int score(string cards)
{
	int sum = 0;
	int length = cards.length();
	for(int len = 0; len < length; ++len)
	{
		if(cards[len] == 'X' || cards[len] == 'J' || cards[len] == 'Q' || cards[len] == 'K')
		{
			sum += 10;	
		}
		else if(cards[len] == 'A')
		{
			if(sum <=10)
			{
				sum += 11;
			}
			else
			{
				sum += 1;
			}
		}
		else
		{
			sum += ((int)(cards[len]) - 48);
		}
	}
	return sum;
}

string shuffle(string& card)
{
	int deckSize = card.length();
	srand(time(0));
	char temp;
	for(int i = 0; i < deckSize; ++i)
	{
		int r = rand() % deckSize;
		temp = card[r];
		card[i] = card[r];
		card[r] = temp;
	}
	return card;
}


bool blackJack(int sum)
{
	if(sum == 21)
	{
		return true;
	}
	return false;
}
