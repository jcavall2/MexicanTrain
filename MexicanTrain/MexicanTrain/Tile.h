#pragma once

#include <string>
#include <iostream>

class Tile {

public:

	Tile();

	Tile(int, int);
	
	int getSide1();
	int getSide2();

	int getTotalPips();

	void Display();
	void swapSides();

private:
	//The number of pips on the first side of the Tile
	int side1;
	//The number of pips on the second side of the tile
	int side2;

};