#include "Card.h"

//lookup array to get the translated value and suit
const std::string VALUE_TRANSLATOR[] = { "", "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
const std::string SUIT_TRANSLATOR[] = { "", "Diamonds", "Clubs", "Hearts", "Spades" };

//-------------------------------------
//				Constructors
//-------------------------------------
Card::Card(){
	value = 0;
	suit = 0;
}
Card::Card(int initValue, int initSuit){
	setValue(initValue);
	setSuit(initSuit);
}

//-------------------------------------
//				Accessors
//-------------------------------------
int Card::getValue(){ return value; }
int Card::getSuit(){ return suit; }
std::string Card::getTranslatedValue(){ return VALUE_TRANSLATOR[value]; }
std::string Card::getTranslatedSuit(){ return SUIT_TRANSLATOR[suit]; }

//-------------------------------------
//				Mutators
//-------------------------------------

//attempt to set the value of a card
//return true and assign the value if the given parameter is between 1 and 13
bool Card::setValue(int newValue){
	bool success = false;

	if (newValue >= 1 && newValue <= 13){
		value = newValue;
		success = true;
	}

	return success;
}

//attempt to set the suit of a card
//return true and assign the suit if the given parameter is between 1 and 4
bool Card::setSuit(int newSuit){
	bool success = false;

	if (newSuit >= 1 && newSuit <= 4){
		suit = newSuit;
		success = true;
	}

	return success;
}

//-------------------------------------
//			Utility function
//-------------------------------------

//return the translated value and suit for a card with appropriate formatting
std::string Card::toString(){ return "The " + getTranslatedValue() + " of " + getTranslatedSuit(); }