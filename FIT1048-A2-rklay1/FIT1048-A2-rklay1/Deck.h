#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck{
private:
	Card deckOfCards[53]; //array of card objects (deck) that contains 52 unique cards (index zero is not used)
	int numberOfCards; //variable that contains the number of cards in deck
public:
	//constructor
	Deck(); //default deck constructor

	//accessor
	int getNumberOfCards(); //return the number of cards in deck

	//utility functions
	void fill(); //fill the empty deck with cards
	void shuffle(); //shuffle the deck
	Card deal(); //return a card from top of the deck
};

#endif