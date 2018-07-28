#include "GameController.h"
#include <iostream>


//-------------------------------------
//				Constructor
//-------------------------------------
//default game controller constructor that performs these functionalities: 
//1. create a new full deck object and shuffle the newly created full deck object
//2. create two player objects with appropriate actual parameters (name and the reference to the full deck object)
//	 the reference to the full deck object will be used to initialised the individual player's deck
//3. assign the player objects to variable "player1" and "player2"
GameController::GameController(){
	Deck fullDeck;
	fullDeck.shuffle();
	player1 = Player("ComputerOne", fullDeck);
	player2 = Player("ComputerTwo", fullDeck);
}

//---------------------------------------
//				Helper functions
//---------------------------------------

//function that prompts for game mode and return the selected game mode as string
string GameController::promptAndGetGameMode(){
	bool validGameMode = false;

	//keep asking for valid game mode if it is not valid
	//game mode must be either "1" or "2"
	//"1" refers to versus computer mode and "2" refers to simulation mode
	while (!validGameMode){
		cout << "Total War!" << endl;
		cout << "Select Mode:" << endl;
		cout << "1. Versus Computer Mode" << endl;
		cout << "2. Simulation Mode" << endl;
		cout << "Select option: ";
		getline(cin, gameMode);
		if (gameMode == "1" || gameMode == "2")
			validGameMode = true;
		else {
			cout << "Invalid game mode option! Try again...";
			system("timeout 3"); system("cls");
		}
	}

	return gameMode;
}

//function that prompts and sets player1 name when versus computer mode is selected
void GameController::promptAndSetPlayer1Name(){
	bool validPlayer1Name = false;
	string tmpName;

	//keep asking for valid name if it is not valid (name must consist of either upper/lower case alphabet letter)
	while (!validPlayer1Name){
		cout << "Enter Player1 Name: ";
		getline(cin, tmpName);
		if (player1.setName(tmpName))
			validPlayer1Name = true;
		else
			cout << "Invalid player name! Try again..." << endl;
	}
}

//function that performs the "battle" result logic
void GameController::battleResult(Player& winner, Player& loser){
	//insert the winner's and loser's top card to the end of the winner's deck
	winner.insertCardToEndDeck(winner.getTopCard(), loser.getTopCard());
	//remove loser's top card from the loser's deck 
	loser.removeCardFromDeck();
}

//function that performs the "war" result logic
void GameController::warResult(Player& winner, Player& loser){
	//insert the appropriate amount of cards to the end of the winner's deck depending on the warMultiplier value
	//remove the appropriate amount of cards from the loser's deck depending on the warMultiplier value
	//warMultiplier starts with 1 and will be incremented appropriately if multiple "war" occurs
	for (int i = 1; i <= (1 + (warMultiplier * 4)); i++)
		battleResult(winner, loser);
}

//function that performs the alternate "war" result logic
//this function will be called if "war" is not possible because of the lack of cards 
//the logic:
//1. determine player that has the least amount of cards and store the value
//2. insert the appropriate amount of cards to the end of the winner's deck depending on the value
//3. remove the appropriate amount of cards from the loser's deck depending on the value
void GameController::warAlternateResult(Player& winner, Player& loser){
	int leastNumberOfCards;

	if (winner.getNumberOfCardsInDeck() < loser.getNumberOfCardsInDeck())
		leastNumberOfCards = winner.getNumberOfCardsInDeck();
	else
		leastNumberOfCards = loser.getNumberOfCardsInDeck();

	for (int i = 1; i <= leastNumberOfCards; i++)
		battleResult(winner, loser);
}

//function that performs the "war" logic
void GameController::war(Player& player1, Player& player2){
	while (!warStop){
		//determine whether there are still enough cards to perform "war"
		bool cardsWithinRange = player1.getNumberOfCardsInDeck() - 1 - (4 * warMultiplier) >= 0 &&
			player2.getNumberOfCardsInDeck() - 1 - (4 * warMultiplier) >= 0;

		//if there are still enough cards to perform "war"
		if (cardsWithinRange){
			//get the 'n'th card from both player's deck depending on the warMultiplier value
			Card player1NTopCard = player1.getNTopCard(warMultiplier), player2NTopCard = player2.getNTopCard(warMultiplier);
			//get the value of the 'n'th card from both players
			int player1NTopCardValue = player1NTopCard.getValue(), player2NTopCardValue = player2NTopCard.getValue();

			//display the value and suit of the player's 'n'th card
			cout << "Player1 " << to_string(4 * warMultiplier) << "th Card: " << player1NTopCard.toString() << endl;
			cout << "Player2 " << to_string(4 * warMultiplier) << "th Card: " << player2NTopCard.toString() << "\n\n";

			//if the value of the 'n'th card from both players are identical
			if (player1NTopCardValue == player2NTopCardValue){
				warMultiplier++; //increment the warMultiplier to accomodate for the next 'n'th number of card (e.g. 8th card)
				war(player1, player2); //perform "war" again
				numberOfWar++; //increment the number of "war" accordingly
			}
			//if the value of the 'n'th card contains "Ace" card
			else if (player1NTopCardValue == 1 && player2NTopCardValue > 1 ||
				player2NTopCardValue == 1 && player1NTopCardValue > 1){

				//if player1 has the "Ace" card and player2 has other card then player1 wins the "war"
				if (player1NTopCardValue == 1)
					warResult(player1, player2);
				//if player2 has the "Ace" card and player1 has other card then player2 wins the "war"
				else if (player2NTopCardValue == 1)
					warResult(player2, player1);

				warStop = true; //stop "war" because winner has been decided
			}
			//if the value of player1's 'n'th card is greater than player2's then player1 wins the "war"
			else if (player1NTopCardValue > player2NTopCardValue){
				warResult(player1, player2);
				warStop = true; //stop "war" because winner has been decided
			}
			//if the value of player2's 'n'th card is greater than player1's then player2 wins the "war"
			else if (player2NTopCardValue > player1NTopCardValue){
				warResult(player2, player1);
				warStop = true; //stop "war" because winner has been decided
			}
		}
		//if there are NOT enough cards to perform "war" then perform ALTERNATE "war"
		else{
			//get the SUIT of the TOP CARD from both players
			int player1TopCardSuit = player1.getTopCard().getSuit();
			int player2TopCardSuit = player2.getTopCard().getSuit();

			//determine the winner of ALTERNATE "war" based on the TOP CARD SUIT (lowest-highest: diamonds, clubs, hearts, spades)
			if (player1TopCardSuit > player2TopCardSuit)
				warAlternateResult(player1, player2);
			else if (player2TopCardSuit > player1TopCardSuit)
				warAlternateResult(player2, player1);

			warStop = true; //stop "war" because winner has been decided
		}
	}

}

//function that performs the "battle" logic
void GameController::battle(Player& player1, Player& player2){
	//get the top card from both player's deck
	Card player1TopCard = player1.getTopCard(), player2TopCard = player2.getTopCard();
	//get the value of the top card from both players
	int player1TopCardValue = player1TopCard.getValue(), player2TopCardValue = player2TopCard.getValue();

	//if the value of the top card from both players are identical
	if (player1TopCardValue == player2TopCardValue){
		warMultiplier = 1; //initialised the warMultiplier back to 1 for each "war" occurrences
		war(player1, player2); //start a "war"
		numberOfWar++; //increment the number of "war" accordingly
		warStop = false; //accomodate for next "war" by initialising the value back to false
	}
	//if the value of the top card contains "Ace" card
	else if (player1TopCardValue == 1 && player2TopCardValue > 1 ||
		player2TopCardValue == 1 && player1TopCardValue > 1){

		//if player1 has the "Ace" card and player2 has other card then player1 wins the "battle"
		if (player1TopCardValue == 1){
			battleResult(player1, player2);
		}
		//if player2 has the "Ace" card and player1 has other card then player2 wins the "battle"
		else if (player2TopCardValue == 1){
			battleResult(player2, player1);
		}

	}
	//if the value of player1's top card is greater than player2's then player1 wins the "battle"
	else if (player1TopCardValue > player2TopCardValue){
		battleResult(player1, player2);
	}
	//if the value of player2's top card is greater than player1's then player2 wins the "battle"
	else if (player2TopCardValue > player1TopCardValue){
		battleResult(player2, player1);
	}


}

//function that displays:
//1. the winner's name and number of cards
//2. the total number of "battle" and "war"
void GameController::gameWinner(Player& winner){
	cout << "Game Winner:" << endl;
	cout << winner.toString();
	cout << "Number of Battle: " << numberOfBattle << endl;
	cout << "Number of War: " << numberOfWar << endl;
	system("pause");
}

//play the game based on the selected game mode
void GameController::playGameMode(string selectedGameMode){
	system("cls");
	cout << "Total War!" << "\n\n";
	//if versus computer mode is selected
	if (selectedGameMode == "1"){
		//prompt and set player1 name
		promptAndSetPlayer1Name(); cout << endl;
	}

	//keep looping until one of the players has 52 cards
	while (!gameOver){
		//display the number of "battle" and "war"
		cout << "Number of Battle: " << numberOfBattle << endl;
		cout << "Number of War: " << numberOfWar << "\n\n";

		//display the player's name and number of cards
		//display the player's top card suit and value 
		cout << player1.toString();
		cout << "Top Card: " << player1.getTopCard().toString() << "\n\n";

		cout << player2.toString();
		cout << "Top Card: " << player2.getTopCard().toString() << "\n\n";

		battle(player1, player2); //start a "battle"
		numberOfBattle++; //increment the number of "battle" accordingly

		//if one of the players has no cards left then the game is over
		if (player1.getNumberOfCardsInDeck() == 0 || player2.getNumberOfCardsInDeck() == 0)
			gameOver = true;

		if (selectedGameMode == "1"){
			system("pause"); system("cls"); cout << "Total War!" << "\n\n";
		}
	}

	//check which player has all 52 cards and display the winner of the game
	if (player1.getNumberOfCardsInDeck() == 52)
		gameWinner(player1);
	else if (player2.getNumberOfCardsInDeck() == 52)
		gameWinner(player2);


}

//starts the game
void GameController::playGame(){
	//prompt for game mode and play the game based on the selected game mode
	playGameMode(promptAndGetGameMode());
}