#pragma once

#include "Game.h"
#include "Deck.h"
#include "Human.h"
#include "Computer.h"
#include "Player.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Round {

public:

	Round();

	Round(int);

	Round(int, int, vector<Tile>, vector<Tile>, bool, int, vector<Tile>, vector<Tile>, bool, vector<Tile>, vector<Tile>, bool, bool, bool, bool);

	void humanDeal();
	void computerDeal();

	Tile engine();

	void coinFlip();
	void setIsHumanTurn(bool);
	void addEngine(Tile);
	void displayTable();
	void play();
	
	void setHumanScore(int);
	void setCompScore(int);

	void setEligibility();
	void showEligibility();

	void updateConnectingPips();

	bool hasPlayableTile();

	int getWinner();

	int getHumanPips();
	int getComputerPips();

	void saveGame();

private:
	//True if its the human players turn, false if its the computer players turn
	bool isHumanTurn;
	//True if the mexican train has been started
	bool isMexicanTrainStarted;

	//True if the human train is marked
	bool isHumanTrainMarked;
	//True if the computer train is marked
	bool isComputerTrainMarked;

	//True if the human train is eligible
	bool isHumanEligible;
	//True if the computer train is eligible
	bool isComputerEligible;
	//True if the Mexican train is eligible
	bool isMexicanEligible;

	//True if the Human train has an orphan double
	bool isHumanOrphan;
	//True if the computer train has an orphan double
	bool isComputerOrphan;
	//True if the mexican train has an orphan double
	bool isMexicanOrphan;

	//True if the Human player's last played tile was a double and needs to play again
	bool doublePlayed;
	//True if the computer player needs to draw a tile from the boneyard
	bool needDraw;

	//The number of pips at the end of the human train
	int humanConnectingPip;
	//The number of pips at the end of the computer train
	int computerConnectingPip;
	//The number of pips at the end of the mexican train
	int mexicanConnectingPip;

	//The number of tiles the human player has placed so far that turn
	int tilesPlaced;

	//The round number
	int roundNum;

	//The total number of pips in the humans hand
	int totalHumanPips;
	//The total number of pips in the computers hand
	int totalComputerPips;

	//The vector holding the tiles that are in the human train
	vector<Tile> humanTrain;
	//The vector holding the tiles that are in the computer train
	vector<Tile> computerTrain;
	//The vector holding the tiles that are in the mexican train
	vector<Tile> mexicanTrain;

	//The Deck object that holds all the tiles not on the board or in either players hand
	Deck boneyard;

	//The human object for the human player
	Human humanPlayer;
	//The human object for the computer player
	Computer computerPlayer;

	//Pointer to the player class, the parent of the Human and Computer classes
	Player* player;

	//The human players current score
	int humanScore;
	//The computer players current score
	int compScore;

	//The number declaring who the winner is, 1 is the human, 2 is the computer, 3 is a tie if the boneyard is empty and no one can play, 0 if no winner yet
	int winner;

};