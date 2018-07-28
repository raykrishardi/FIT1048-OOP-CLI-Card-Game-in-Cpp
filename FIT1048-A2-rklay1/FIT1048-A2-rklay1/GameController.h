#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Player.h"

using namespace std;

class GameController{
private:
	Player player1; //variable that represents player1
	Player player2; //variable that represents player2
	string gameMode; //variable that contains the selected game mode from the user
	bool gameOver; //variable that determines when the game is over
	int warMultiplier = 1; //variable that is used to get the appropriate 'n'th number of card when multiple "war" occurs
	bool warStop = false; //variable that determines when "war" is over
	int numberOfBattle = 0; //variable that keeps track of the number of "battle"
	int numberOfWar = 0; //variable that keeps track of the number of "war"

	//helper functions
	string promptAndGetGameMode(); //prompt for game mode and return the selected game mode as string
	void promptAndSetPlayer1Name(); //prompt and set player1 name when versus computer mode is selected
	void playGameMode(string selectedGameMode); //play the game based on the selected game mode
	void battle(Player& player1, Player& player2); //function that contains the "battle" logic
	void battleResult(Player& winner, Player& loser); //function that contains the "battle" result logic
	void war(Player& player1, Player& player2); //function that contains the "war" logic
	void warResult(Player& winner, Player& loser); //function that contains the "war" result logic
	void warAlternateResult(Player& winner, Player& loser); //function that contains the alternate "war" result logic
	void gameWinner(Player& winner); //function that displays the winner of the game and the total number of "war" and "battle" occurrences
	
public:
	GameController(); //default game controller constructor
	void playGame(); //function that starts the game
};

#endif