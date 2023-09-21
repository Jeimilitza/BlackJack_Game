//============================================================================
// Author      : Jeimilitza Sainz Lopez
//============================================================================

// Preprocessor to use and manipulate strings
#include <string>
// Preprocessor to use and manipulate vectors
#include <vector>
// Preprocessor to generate random number
#include <cstdlib>
// Preprocessor to set time seed
#include <ctime>
// Preprocessor for input/output manipulation
#include <iostream>
using namespace std;

// Class for the validations
class validations
{
public:
	int wantToPlay();	// Prototype of member function wantToPlay
	int option1(int choice);	// Prototype of member function option1
};
// Class for the game
class game
{
public:
	void play(validations val, vector<string> &count);	// Prototype of member function play
	void playing1(int i, int *cards, int *dealerCards, int &stack, int &dealerStack, int choice, validations val, vector<string> &count);// Prototype of member function playing1
	void playing2(int i, int *cards, int *dealerCards, int &stack, int &dealerStack, validations val, vector<string> &count);	// Prototype of member function playing2
	void dealerPlays(int i, int *dealerCards, int &dealerStack, validations val, vector<string> &count);	// Prototype of member function dealerPlays
	string symbols(int card, vector<string> &count);
	int getCard(vector<string> &count, string &symbol);	// Prototype of member function getCard
	int cardA(int card, string symbol);	// Prototype of member function cardA
	int cardJoker(int card, string symbol);	// Prototype of member function cardJoker
	int cardValue(int card, string symbol);	// Prototype of member function cardValue
	int dealerCardValue(int card, int dealerStack, string symbol);	// Prototype of member function dealerCardValue
	int drawOrStay(validations val);	// Prototype of member function drawOrStay
};
/****************************************************************
                         * Main Function *
****************************************************************/
int main() {

	// Setting the time seed
	srand (time(0));

	// Creating objects for the two classes
	validations val;
	game game;

	// Variable for the player's choice
	int choice;

	// Calling the wantToPlay member function
	choice = val.wantToPlay();

	vector<string> count;

	// If choice is yes the game starts
	if (choice == 1)
	{
		game.play(val, count);
	}

	// End of program
	cout << endl;
	cout << "End of game.\n";

	return 0;
}
/****************************************************************
                    * validations::wantToPlay *
 * This member function asks the user if they want to play a *
  * game of BlackJack and calls the member function option1 *
****************************************************************/
int validations::wantToPlay()
{
	int choice;

	cout << "Do you want to play a game of BlackJack?\n";
	cout << "Yes: 1  or  No: 0\n";
	cin >> choice;

	return validations::option1(choice);
}
/****************************************************************
                    * validations::option1 *
   * This member function validates that the option chosen *
                     * by user is correct *
****************************************************************/
int validations::option1(int choice)
{
	while (choice < 0 || choice > 1)
	{
		cout << "You must enter 1 for YES  or 0 for NO.\n";
		cout << "Please enter your choice again:\n";
		cin >> choice;
	}
	return choice;
}
/****************************************************************
                        * game::play *
     * This member function starts the game of BlackJack *
  * by drawing two cards for both, the player and the dealer *
****************************************************************/
void game::play(validations val, vector<string> &count)
{
	int cards[21], dealerCards[21];
	int stack = 0, dealerStack = 0;
	int i = 0;
	string symbol;

	// This function shows the first moves of the game
	// the first two cards drawn by the player and the dealer
	// one of the dealer's card is not revealed to the player

	cout << "Your first two cards are: \n";

	cards[i] = game::getCard(count, symbol);
	cards[i] = game::cardValue(cards[i], symbol);

	dealerCards[i] = game::getCard(count, symbol);
	dealerCards[i] = game::dealerCardValue(dealerCards[i], dealerStack, symbol);

	i++;

	cards[i] = game::getCard(count, symbol);
	cards[i] = game::cardValue(cards[i], symbol);
	stack +=  cards[i] + cards[i-1];

	dealerCards[i] = game::getCard(count, symbol);
	dealerCards[i] = game::dealerCardValue(dealerCards[i], dealerStack, symbol);
	dealerStack +=  dealerCards[i] + dealerCards[i-1];

	cout << endl;
	cout << "The dealer has drawn for himself a(n) " << dealerCards[i] << " of " << symbol << "\n";
	cout << "The other card remains hidden.\n";

	i++;

	// The game continues by calling the playing2 function
	game::playing2(i, cards, dealerCards, stack, dealerStack, val, count);

}
/****************************************************************
                        * game::playing1 *
     * This member function continues the game of BlackJack *
* when the dealer already stands and the player wants to keep going *
****************************************************************/
void game::playing1(int i, int *cards, int *dealerCards, int &stack, int &dealerStack, int choice, validations val, vector<string> &count)
{
	string symbol;

// If player wants to keep playing and dealer already stands
	if (choice == 1)
		{
		// player draws another card
			cards[i] = game::getCard(count, symbol);
			cards[i] = game::cardValue(cards[i], symbol);
			stack += cards[i];
// Possible ends of game after this move
			if (stack == 21)
			{
				cout << endl;
				cout << "Your stack has reached 21.\n";
				cout << "You win the game of blackJack\n";
			}
			else if (stack > 21)
			{
				cout << endl;
				cout << "Your stack has surpassed 21.\n";
				cout << "The dealer wins\n";
			}
			else
			{
				i++;
				cout << endl;
				cout << "Your stack has a total of " << stack << ".\n";
				choice = game::drawOrStay(val);
				game::playing1(i, cards, dealerCards, stack, dealerStack, choice, val, count);
			}
		}
// If player decides to stay
	else
	{
		cout << "You have decided to stay.\n";
// Possible ends of game after this move
		if ((dealerStack > stack) && (dealerStack <= 21))
		{
			cout << endl;
			cout << "The dealer wins the game with a stack of " << dealerStack << " in total.\n";
		}
		else if ((stack > dealerStack) && (stack <= 21))
		{
			cout << endl;
			cout << "You win the game with a stack of " << stack << " in total.\n";
		}
		else if (stack == dealerStack)
		{
			cout << endl;
			cout << "No one wins, both the player and the dealer ended up with ";
			cout << dealerStack << " cards in total.\n";
		}
	}
}
/****************************************************************
                        * game::playing2 *
     * This member function continues the game of BlackJack *
    * when both the dealer and the player want to keep going *
****************************************************************/
void game::playing2(int i, int *cards, int *dealerCards, int &stack, int &dealerStack, validations val, vector<string> &count)
{
	string symbol;
	int choice;
// When the dealer's stack has reached 17 or higher the dealer decides to stay
// and the player can continue playing until they want to stay
	if (dealerStack > 16)
	{
		cout << "The dealer has decided to stay.\n";
		cout << endl;
		cout << "Your stack has a total of " << stack << ".\n";
		choice = game::drawOrStay(val);

// if the player wants to keep playing after the dealer stayed
// they draw another card
		if (choice == 1)
		{
			cards[i] = game::getCard(count, symbol);
			cards[i] = game::cardValue(cards[i], symbol);
			stack += cards[i];

// Possibles ends of game after this move
			if (stack == 21)
			{
				cout << endl;
				cout << "Your stack has reached 21.\n";
				cout << "You win the game of blackJack\n";
			}
			else if (stack > 21)
			{
				cout << endl;
				cout << "Your stack has surpassed 21.\n";
				cout << "The dealer wins\n";
			}
			else
			{
				// The playing1 function gets called when the player wants to keep going
				// but the dealer stands
				i++;
				cout << endl;
				cout << "Your stack has a total of " << stack << ".\n";
				choice = game::drawOrStay(val);
				game::playing1(i, cards, dealerCards, stack, dealerStack, choice, val, count);
			}
	    }
// if the player does not want to keep playing after the dealer stayed
		else
		{
			cout << "You have decided to stay.\n";

			// Now that both dealer and player stand wins who ever has more card while not exceeding 21
			// and it could also be a tie
			if ((dealerStack > stack) && (dealerStack <= 21))
			{
				cout << endl;
				cout << "The dealer wins the game with a stack of " << dealerStack << " in total.\n";
			}
			else if ((stack > dealerStack) && (stack <= 21))
			{
				cout << endl;
				cout << "You win the game with a stack of " << stack << " in total.\n";
			}
			else if (stack == dealerStack)
			{
				cout << endl;
				cout << "No one wins, both the player and the dealer ended up with ";
				cout << dealerStack << " cards in total.\n";
			}
	    }
	}
	// if the dealer does not stay
	else
	{
		// Asking if player wants to keep playing
		cout << endl;
		cout << "Your stack has a total of " << stack << ".\n";
		choice = game::drawOrStay(val);
// if the player wants to keep playing
		if (choice == 1)
			{
			// they draw another card
				cards[i] = game::getCard(count, symbol);
				cards[i] = game::cardValue(cards[i], symbol);
				stack += cards[i];

// Possible ends of game after this move
				if (stack == 21)
				{
					cout << endl;
					cout << "Your stack has reached 21.\n";
					cout << "You win the game of blackJack\n";
				}
				else if (stack > 21)
				{
					cout << endl;
					cout << "Your stack has surpassed 21.\n";
					cout << "The dealer wins\n";
				}
				else
				{
			// If the game does not end, it is the dealer's turn to draw a card
					cout << endl;
					dealerCards[i] = game::getCard(count, symbol);
					dealerCards[i] = game::dealerCardValue(dealerCards[i], dealerStack, symbol);
					dealerStack += dealerCards[i];
					cout << "The dealer has drawn for himself a " << dealerCards[i] << " of " << symbol << "\n";
					cout << "the dealer's stack has a total of " << dealerStack << ".\n";
// Possible ends of game after this move
					if (dealerStack == 21)
					{
						cout << endl;
						cout << "The dealer wins with a stack of 21\n";
					}
					else if (dealerStack > 21)
					{
						cout << endl;
						cout << "The dealers stack has surpassed 21.\n";
						cout << "You win the game of blackJack\n";
					}
					else
					{
						// if the game does not end call this function again for dealer and player to keep playing
						i++;
						game::playing2(i, cards, dealerCards, stack, dealerStack, val, count);
					}
				}
			}
// If the player does not want to continue
		else
		{
			cout << "You have decided to stay.\n";
			// The dealer keeps playing until they want to stand
			while (dealerStack < 17)
			{
			game::dealerPlays(i, dealerCards, dealerStack, val, count);
			}
// Possible ends of game after this move
			if ((dealerStack > stack) && (dealerStack <= 21))
			{
				cout << endl;
				cout << "The dealer wins the game with a stack of " << dealerStack << " in total.\n";
			}
			else if ((stack > dealerStack) && (stack <= 21))
			{
				cout << endl;
				cout << "You win the game with a stack of " << stack << " in total.\n";
			}
			else if (stack == dealerStack)
			{
				cout << endl;
				cout << "No one wins, both the player and the dealer ended up with ";
				cout << dealerStack << " cards in total.\n";
			}
		}
	}
}
/****************************************************************
                      * game::getCard *
   * This member function takes a random card from the deck *
    * and it has a 4 in 52 probability of getting a Joker *
****************************************************************/
int game::getCard(vector<string> &count, string &symbol)
{

	int card, possibility;
	// Draws a random card
	card = rand() % 14 + 1;
	// There is a 2 in 26 (or 4 in 52) chance that it is a 14(Joker)
	if (card == 14)
	{
		possibility = rand() % 26 + 1;
		if (possibility == 1 || possibility == 26)
		{
			// Calling the symbols function and returning the card
		    symbol = game::symbols(card, count);
			return card;
		}
		else
		{
			// If the possibility of being a joker does not meet calls the function again
			return game::getCard(count, symbol);
		}
	}
	else
	{
		// Calling the symbols function and returning the card
	    symbol = game::symbols(card, count);
		return card;
	}
}
string game::symbols(int card, vector<string> &count)
{
	string symbol;
    int s;
    string sym;

// Getting a random number
    s = rand() % 4 + 1;

    // Assigning the numbers to the symbols
    if (s == 1)
    {
        sym = "hearts";
    }
    else if (s == 2)
    {
        sym = "diamonds";
    }
    else if (s == 3)
    {
        sym = "spades";
    }
    else
    {
        sym = "clubs";
    }

    // Storing the number of the card and symbol as a whole in a vector
    string c = sym;
    c.append(to_string(card));
    count.push_back(c);

    int size = count.size();
     int iteration, j;
// Checking if that card with that same symbol has appeared in the game before
    for(iteration = 0; iteration < size; iteration++)
    {
        for(j = iteration + 1; j < size; j++)
        {
// if it has appeared before call the function getCard again for a new card
            if(count[iteration] == count[j])
             {
                game::getCard(count, symbol);
             }
        }
    }
// Returning the symbol of the card
   return sym;

}
/****************************************************************
                       * game::cardValue *
  * This member function gives the corresponding value to each *
             * card according to the BlackJack rules *
****************************************************************/
int game::cardValue(int card, string symbol)
{
	// If an Ace is drawn it gives option to he user to choose the value between 1 and 11
	if (card == 1)
	{
	cout << "your card is an Ace of " << symbol << "\n";
	card = game::cardA(card, symbol);
	}
	// if a Joker is drawn option to he user to choose the value from 1 to 11
	else if (card == 14)
	{
		cout << "Your card is a Joker.\n";
		card = game::cardJoker(card, symbol);
	}
	// if a face card is drawn its value is 10
	else if ((card == 11) || (card == 12) || (card == 13))
	{
		card = 10;
		cout << "Your card is a face of " << symbol;
	    cout << " which is worth 10.\n";
	}
	// if a card from 2 to 10 is drawn the value is its number
	else
	{
		cout << "Your card is a(n) " << card << " of " << symbol << "\n";
	}
	return card;
}
/****************************************************************
                         * game::cardA *
  * This member function asks the user if they want their A card *
                 * to have a value of 1 or 11 *
****************************************************************/
int game::cardA(int card, string symbol)
{
	// Asking the user what they want their Ace to be
	cout << "Do you want it to be a 1 or 11?\n";
	cin >> card;

	if (card == 1 || card == 11)
	{
		return card;
	}
	else
	{
		cout << "That is an invalid entry.\n";
		return game::cardA(card, symbol);
	}
}
/****************************************************************
                       * game::cardJoker *
  * This member function asks the user what value they want *
                      * their Joker to have  *
****************************************************************/
int game::cardJoker(int card, string symbol)
{
	// Asking the user what they want their Joker to be
	cout << "What card do you want the joker to be?\n";
	cin >> card;

	if (card < 1 || card > 11)
	{
		cout << "That is an invalid entry.\n";
		cout << "It must be a number from 1 to 11.\n";
		return game::cardJoker(card, symbol);
	}
	else
	{
		card = game::cardValue(card, symbol);
		return card;
	}

}
/****************************************************************
                    * game::dealerCardValue *
     * This member function decides what value should the *
                     *  dealer's card have *
****************************************************************/
int game::dealerCardValue(int card, int dealerStack, string symbol)
{
	// When the dealer draws an Ace they choose the value to be one that their stack does not exceed 21
	if (card == 1)
	{
		if (dealerStack > 10)
		{
			card = 1;
		}
		else
		{
			card = 11;
		}
	// When the dealer draws a Joker they choose the value to be one that gets them the closest to 21 possible
	// 11 being the maximum value
	}
	else if (card == 14)
	{
		if (dealerStack > 10)
		{
			card = 21 - dealerStack;
		}
		else
		{
			card = 11;
		}
	}
	// If it is a face card the value is 10
	else if ((card == 11) || (card == 12) || (card == 13))
	{
		card = 10;
	}

	return card;
}
/****************************************************************
                     * game::drawOrStay *
  * This member function asks the user if they want to draw *
                   * another card or stay *
****************************************************************/
int game::drawOrStay(validations val)
{
	int choice;

	cout << "Do you want to draw another?\n";
	cout << "Yes: 1  or  No: 0\n";
	cin >> choice;
	val.option1(choice);

	return choice;
}
/****************************************************************
                        * game::dealerPlays *
     * This member function continues the game of BlackJack *
   * when the player stands but the dealer wants to keep going *
****************************************************************/
void game::dealerPlays(int i, int *dealerCards, int &dealerStack, validations val, vector<string> &count)
{

	   string symbol;
	// If the player already stands but the dealer wants to keep playing
	// this are their plays
		cout << endl;
		dealerCards[i] = game::getCard(count, symbol);
		dealerCards[i] = game::dealerCardValue(dealerCards[i], dealerStack, symbol);
		dealerStack += dealerCards[i];
		cout << "The dealer has drawn for himself a(n) " << dealerCards[i] << " of " << symbol << "\n";
		cout << "the dealer's stack has a total of " << dealerStack << ".\n";

		if (dealerStack == 21)
		{
			cout << endl;
			cout << "The dealer's stack has reached 21.\n";
			cout << "The dealer wins\n";
		}
		else if (dealerStack > 21)
		{
			cout << endl;
			cout << "The dealers stack has surpassed 21.\n";
			cout << "You win the game of blackJack\n";
		}
		else if (dealerStack > 16)
		{
			cout << "The dealer has decided to stay.\n";
		}
}
