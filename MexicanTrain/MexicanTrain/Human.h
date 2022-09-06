	#pragma once

#include "Tile.h"
#include <vector>
#include "Player.h"

using namespace std;

class Human : public Player {

public:

	Human();

	void drawToHand(Tile);

	int getHandSize();

	Tile getTile(int);

	void removeTile(int);

	void makeDecision(vector<Tile>&, bool, vector<Tile>&, bool, vector<Tile>&, bool, bool&, bool&, bool&, bool&, bool&, bool&, Tile);

private:
	vector<Tile> humanHand;

};