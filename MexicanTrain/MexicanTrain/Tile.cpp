#include "Tile.h"
#include <string>
#include <iostream>

using namespace std;

//Default constructor
Tile::Tile()
{
	side1 = 0;
	side2 = 0;
}

//parameterized constructor
Tile::Tile(int S1, int S2)
{
	side1 = S1;
	side2 = S2;
}

/* *********************************************************************
Function Name: getSide1
Purpose: Gets the first side of a tile
Parameters:
			none
Return Value: The value of side1 in tile, an int
Algorithm: 
			1) Returns value to side1
Assistance Received: none
********************************************************************* */
int Tile::getSide1()
{
	return side1;
}

/* *********************************************************************
Function Name: getSide2
Purpose: Gets the second side of a tile
Parameters:
			none
Return Value: The value of side2 in tile, an int
Algorithm:
			1) Returns value to side2
Assistance Received: none
********************************************************************* */
int Tile::getSide2()
{
	return side2;
}

/* *********************************************************************
Function Name: Display
Purpose: Prints the tile as "side1-side2" for when they're in the train or in hand
Parameters:
			none
Return Value: none
Algorithm:
			1) Prints out the first side then a dash then the second side
Assistance Received: none
********************************************************************* */
void Tile::Display()
{
	cout << side1;
	cout << "-";
	cout << side2;
}

/* *********************************************************************
Function Name: swapSides
Purpose: To swap the sides of the tile if it needs to be turned around to connect to a train
Parameters:
			none
Return Value: none
Algorithm:
			1) Creates a temp value to hold the value of side1
			2) Sets the value in side2 to side1
			3) Sets the value of temp to side2
Assistance Received: none
********************************************************************* */
void Tile::swapSides()
{
	int temp = side1;
	side1 = side2;
	side2 = temp;
}

/* *********************************************************************
Function Name: getTotalPips
Purpose: Gets the total pips of side1 and side2 for finding the size of the tile
Parameters:
			none
Return Value: The value of side1 and side2 added together, an int
Algorithm:
			1)Adds together side1 and side2 and returns the value
Assistance Received: none
********************************************************************* */
int Tile::getTotalPips()
{
	return side1 + side2;
}