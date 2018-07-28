#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Deck.h"

class Player{
private:
	std::string name; //variable that contains the player name
	std::vector<Card> deckInHand; //vector of card objects that represents the player's deck
	int numberOfCardsInDeck = 0; //variable that contains the number of cards in the player's deck

	//constant
	static const int STARTING_NUMBER_OF_CARDS = 26; //constant that stores the starting number of cards (26 cards for each player's deck) 

	//helper functions
	bool validateName(std::string newName); //validate the name given by the user
	void fillDeckInHand(Deck& fullDeck); //fill the player's deck from the full/whole deck
public:
	//constructors
	Player(); //default player constructor
	Player(std::string initName, Deck& fullDeck); //2-parameter constructor that initialises the player name and deck


	//accessors
	int getNumberOfCardsInDeck(); //return the number of cards in the player's deck
	Card getTopCard(); //return the top card from player's deck
	Card getNTopCard(int multiplier); //return the 'n'th card from the top of player's deck


	//mutator
	bool setName(std::string newName); //attempt to set the player name


	//utility functions
	void addCardToDeck(Card newCard); //add card from the full/whole deck to the player's deck
	void insertCardToEndDeck(Card oldCard, Card newCard); //insert cards to the end of the player's deck
	void removeCardFromDeck(); //remove a card from the player's deck
	//return the player name and number of cards with appropriate formatting
	//NOTE: you can return all cards within the player's deck by uncommenting the for loop construct (used for testing purpose)
	std::string toString(); 
};

#endif