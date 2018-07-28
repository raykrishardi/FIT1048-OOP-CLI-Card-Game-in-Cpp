#include "Player.h"
#include <sstream>

//-------------------------------------
//				Constructors
//-------------------------------------
//default constructor that initialises the player name to "computer"
Player::Player(){
	setName("Computer");
}

//2-parameter constructor that initialises the player name and deck
//name will be validated in the setName() function
//player's deck will be initialised from the full/whole deck
Player::Player(std::string initName, Deck& fullDeck){
	setName(initName);
	fillDeckInHand(fullDeck);
}


//-------------------------------------
//				Accessors
//-------------------------------------
int Player::getNumberOfCardsInDeck(){ return numberOfCardsInDeck; }
Card Player::getTopCard(){ return deckInHand[numberOfCardsInDeck - 1]; }
//return the 'n'th card from the top of player's deck ('n' could be 4,8,etc)
//this function is used when "war" occurs
//multiplier is used to get the appropriate 'n'th number of card when multiple "war" occurs
//multiplier starts with 1 and will be incremented appropriately if multiple "war" occurs
Card Player::getNTopCard(int multiplier){ return deckInHand[numberOfCardsInDeck - 1 - (4 * multiplier)]; }

//-------------------------------------
//				Mutator
//-------------------------------------
//attempt to set the player name
//return true and assign the name if the given name is valid
bool Player::setName(std::string newName){
	bool success = false;

	if (validateName(newName)){
		name = newName;
		success = true;
	}
		
	return success;
}


//---------------------------------------
//		Helper and Utility functions
//---------------------------------------
//check whether the player name is valid or not (must consist of either upper/lower case alphabet letter)
//return false if it is not either combination of upper/lower case alphabet letter
bool Player::validateName(std::string newName){
	bool valid = true;
	char chr;

	if (newName.length() > 0){
		for (int i = 0; i < newName.length(); i++){
			chr = newName[i];
			if (!(chr >= 65 && chr <= 90 || chr >= 97 && chr <= 122)){
				valid = false;
				break;
			}
		}
	}
	else
		valid = false;

	return valid;
}

//add a card to the player's deck (represented by vector)
//increment the number of cards in deck for a particular player accordingly
void Player::addCardToDeck(Card newCard){
	deckInHand.push_back(newCard);
	numberOfCardsInDeck++;
}

//fill the player's deck with 26 unique cards from the full/whole deck
void Player::fillDeckInHand(Deck& fullDeck){
	for (int i = 1; i <= STARTING_NUMBER_OF_CARDS; i++){
		addCardToDeck(fullDeck.deal());
	}
}

//insert cards to the end of winner's deck
//used in "battle" and "war"
void Player::insertCardToEndDeck(Card oldCard, Card newCard){
	//insert the old card to the end of the deck and remove the old card from the top of the deck
	deckInHand.insert(deckInHand.begin(), oldCard); deckInHand.pop_back();
	//insert the loser card to the end of the winner's deck
	deckInHand.insert(deckInHand.begin(), newCard);
	//increment the number of cards in player deck appropriately
	numberOfCardsInDeck++;
}

//remove card from the loser's deck
//appropriately decrement the number of cards
void Player::removeCardFromDeck(){
	deckInHand.pop_back();
	numberOfCardsInDeck--;
}

//return the player name and number of cards with appropriate formatting
std::string Player::toString(){
	std::stringstream retVal;

	retVal << "Name: " << name << std::endl;
	retVal << "Number Of Cards: " << numberOfCardsInDeck << std::endl;

	//NOTE: you can return all cards within the player's deck by uncommenting the for loop construct below
	//-------------------------------------------------------
	//				For testing purpose
	//-------------------------------------------------------
	//get the translated value and suit for each card in hand
	//for (int i = 0; i < deckInHand.size(); i++){
	//	retVal << deckInHand[i].toString() << std::endl;
	//}
	//-------------------------------------------------------

	return retVal.str();
}