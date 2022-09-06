#pragma once

#include "Tile.h"
#include <vector>

using namespace std;

class Player {

public:

	Player() {}

	//Draws the tiles into the players hand
	virtual void drawToHand(Tile) = 0;
	//Gets the size of the players hand
	virtual int getHandSize() = 0;
	//Gets the certain number in the players hand
	virtual Tile getTile(int) = 0;
	//Removes the certain number tile from players hand
	virtual void removeTile(int) = 0;
	//The computer tile picking algorithm
	virtual void makeDecision(vector<Tile>&, bool, vector<Tile>&, bool, vector<Tile>&, bool, bool&, bool&, bool&, bool&, bool&, bool&, Tile) = 0;

private:


};