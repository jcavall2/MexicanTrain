#pragma once

#include <string>
#include <iostream>
#include "Human.h"
#include "Computer.h"
#include "Round.h"

using namespace std;

class Game {

public:

	Game();

	Game(int, int, int);

	void startRound();
	void continuePlay();
	void playRound(Round);

	void loadSave();

	void getNumbers(vector<Tile>&, string, bool&);


private:

	//The humans total score for the game
	int humanScore;
	//The computers total score for the game
	int compScore;
	//The round number for the current round
	int roundNum;

};