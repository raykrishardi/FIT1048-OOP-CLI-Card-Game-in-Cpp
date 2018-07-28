#ifndef CARD_H
#define CARD_H

#include <string>

class Card{
private:
	int value; //variable that contains card value
	int suit; //variable that contains card suit
public:
	//constructors
	Card(); //default card constructor
	Card(int initValue, int initSuit); //2-parameter card constructor that initialises the value and suit

	//accessors
	int getValue(); //return an integer value
	int getSuit(); //return an integer suit
	std::string getTranslatedValue(); //return the value as string
	std::string getTranslatedSuit(); //return the suit as string

	//mutators
	bool setValue(int newValue); //attempt to set the value of a card
	bool setSuit(int newSuit); //attempt to set the suit of a card

	//utility function
	std::string toString(); //return the translated value and suit with appropriate formatting
};

#endif