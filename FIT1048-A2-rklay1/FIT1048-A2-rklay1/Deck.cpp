#include "Deck.h"
#include <iostream> //for rand()
#include <time.h> //for srand(time(NULL))

//-------------------------------------
//				Constructor
//-------------------------------------
//fill the newly created deck object with unique 52 cards
Deck::Deck(){
	fill();
}

//-------------------------------------
//				Accessor
//-------------------------------------
int Deck::getNumberOfCards(){ return numberOfCards; }

//-------------------------------------
//			Utility functions
//-------------------------------------

//fill the deck with unique 52 cards
void Deck::fill(){
	for (int suit = 1; suit <= 4; suit++){
		for (int value = 1; value <= 13; value++){
			Card tmpCard(value, suit);
			deckOfCards[(suit - 1) * 13 + value] = tmpCard;
		}
	}

	numberOfCards = 52;
}
//shuffle the deck of cards for 7000 times
void Deck::shuffle(){
	int randomCard1, randomCard2;
	Card tmpCard;

	srand(time(NULL));

	for (int i = 1; i <= 7000; i++){
		randomCard1 = 1 + rand() % 52;
		randomCard2 = 1 + rand() % 52;

		tmpCard = deckOfCards[randomCard1];
		deckOfCards[randomCard1] = deckOfCards[randomCard2];
		deckOfCards[randomCard2] = tmpCard;
	}
}
//deal or return a card from the top of the deck if there are still cards in the deck
Card Deck::deal(){
	Card tmpCard;

	if (numberOfCards >= 1){
		tmpCard = deckOfCards[numberOfCards];
		numberOfCards--;
	}

	return tmpCard;
}