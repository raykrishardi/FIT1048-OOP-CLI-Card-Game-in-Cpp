# "Total War" Card game in C++

# About the project:
This game is one of the three assignments for my FIT1048 (Foundations of C++) unit. The game is designed using object-oriented paradigm, has a command-line interface, and written using Microsoft Visual Studio 2013 IDE. Below contains the game overview and rules which are directly taken from the assignment brief.

# Game Overview:
You are to implement a computer-based variant of the card game War. This is a two-player card game played with a standard deck of cards in which the aim of the game is to capture all cards in the deck. When one player has all 52 cards, the game is over.

# Basic Play:
To begin, all 52 cards from a standard deck of cards are evenly split randomly between two players.
The game plays as follows:

• Each player turns over the top card in their deck. This is called a “Battle”.

• Whichever player has the highest card claims both cards and puts them at the end of their
collection. The value of the card is based on the number value, with 2 being the lowest and
Ace being highest. “Picture” cards are ordered lowest to highest Jack, Queen, King, Ace.

• If both cards have the same value, “War” breaks out (detailed below)

• This continues until one player has all 52 cards, in which the game ends

# War:
If the value of both cards is the same, “War” takes place. It has the following rules:

• Each player takes the top 4 cards from their deck. The 4th card is revealed. Whoever has the
highest value on that 4th card claims all cards. If it is a draw again, this process is repeated.

# Game Modes:
Your game should have two modes that can be chosen at the beginning of your program:
1. Versus Computer Mode – In this mode one player can play against a computer opponent
2. Simulation Mode – In this mode you simulate a complete game with no human players. At
the end of the game, you must report on who won, how many “battles” and how many
“wars” occurred in the game

# Extra Functionality:
1. Changing how a draw in “war” is handled
  
  - In this application, if “war” is not possible because of the lack of cards then alternate “war” will occur.
  
  - the winner of the alternate “war” will be decided based on the top card suit
  
For example, player1 only has four cards left and the top card is the same as player2 in which “war” should have occurred.       However, because you cannot get the fourth card then the winner will be decided by comparing the suit of the top card (order from lowest to highest: Diamonds, Clubs, Hearts, Spades). Please refer to the Sample alternate “war” result scenarios in README.pdf file.
  
2. Making a particular type of card have special powers in a “battle” or “war”

  - Implemented in “war”
  
    - When “war” is not possible because of the lack of cards, the top card suit will be used to determine the winner/loser of the “war”.
