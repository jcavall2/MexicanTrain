#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Tile.h"

using namespace std;

class Deck {

public:

	Deck();

	void createDeck();
	void shuffle();

	Tile draw();

	void removeEngine(Tile);

	Tile getNextTile();
	bool isBoneyardEmpty();

	int getBoneyardSize();
	Tile getTileAt(int);

	void addToDeck(Tile);

private:
	//The vector that holds the tiles in the boneyard
	vector <Tile>boneyard;

};