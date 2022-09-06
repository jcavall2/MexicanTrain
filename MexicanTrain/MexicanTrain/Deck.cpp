#include "Deck.h"
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

//default constructor
Deck::Deck()
{


}

/* *********************************************************************
Function Name: createDeck
Purpose: Creates the 55 tiles that are used per round
Parameters:
			none
Return Value: none
Algorithm:
			1)Creates all different tiles from 0-0 to 9-9
Assistance Received: none
********************************************************************* */
void Deck::createDeck()
{
	//declares maxPips at 9 for how many pips can go on one side of the tile
	int maxPips = 9;
	for (int i = 0; i <= maxPips; i++)
	{
		for (int j = i; j <= maxPips; j++)
		{
			boneyard.push_back(Tile(i, j));
		}
	}
		
}

/* *********************************************************************
Function Name: shuffle
Purpose: randomly shuffles the tiles in the boneyard
Parameters:
			none
Return Value: none
Algorithm:
			1)Creates a temporary vector and sets it equal to the boneyard
			2)Clears the boneyard vector
			3)Randomly assigns the tiles from temp into boneyard
Assistance Received: none
********************************************************************* */
void Deck::shuffle()
{
	srand(time(NULL));
	vector<Tile> temp;
	temp = boneyard;
	boneyard.clear();

	int maxTiles = 55;

	int randNum;
	while (boneyard.size() < maxTiles)
	{
		randNum = rand() % temp.size();
		boneyard.push_back(temp.at(randNum));
		temp.erase(temp.begin() + randNum);
	}
}

/* *********************************************************************
Function Name: draw
Purpose: Gets the top tile from the boneyard then removes it
Parameters:
			none
Return Value: A tile object, The top most tile from the boneyard
Algorithm:
			1)Creates a copy of the top tile from the boneyard
			2)Deletes the orignal tile from the boneyard
			3)Returns that copy
Assistance Received: none
********************************************************************* */
Tile Deck::draw()
{
	Tile drawTile;

	drawTile = boneyard.at(0);

	boneyard.erase(boneyard.begin());

	return drawTile;
}

/* *********************************************************************
Function Name: removeEngine
Purpose: Finds the engine tile in the boneyard and then removes it
Parameters:
			engine, a tile object that is the engine for the current round
Return Value: none
Algorithm:
			1)Searches through the boneyard for an exact copy of the engine
Assistance Received: none
********************************************************************* */
void Deck::removeEngine(Tile engine)
{
	for (int i = 0; i < boneyard.size(); i++)
	{
		if (engine.getSide1() == boneyard.at(i).getSide1() && engine.getSide2() == boneyard.at(i).getSide2())
		{
			boneyard.erase(boneyard.begin() + i);
		}
	}
}

/* *********************************************************************
Function Name: getNextTile()
Purpose: Returns the top tile of the boneyard but does not remove it like draw
Parameters:
			none
Return Value: Tile, the top most tile from the boneyard
Algorithm:
			1)Checks if the boneyard is empty and returns the tile (-1)-(-2) if it is
			2)Otherwise returns the top tile
Assistance Received: none
********************************************************************* */
Tile Deck::getNextTile()
{
	if (isBoneyardEmpty())
	{
		return Tile(-1, -2);
	}
	return boneyard.at(0);
}

/* *********************************************************************
Function Name: isBoneyardEmpty
Purpose: Checks if the boneyard is empty
Parameters:
			none
Return Value: True if the boneyard is empty, false otherwise
Algorithm:
			1)Checks if the boneyard is empty
Assistance Received: none
********************************************************************* */
bool Deck::isBoneyardEmpty()
{
	if (boneyard.empty())
	{
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: getBoneyardSize
Purpose: Get the size of the boneyard
Parameters:
			none
Return Value: int, the current size of the boneyard
Algorithm:
			1)Returns the size of the boneyard
Assistance Received: none
********************************************************************* */
int Deck::getBoneyardSize()
{
	return boneyard.size();
}

/* *********************************************************************
Function Name: getTileAt
Purpose: To get the tiles sequentially from the boneyard for the save file
Parameters:
			iter, an int, an iterator for where in the boneyard we are looking
Return Value: Tile, the tile at that specific part of the boneyard
Algorithm:
			1)return boneyard at the iterators location
Assistance Received: none
********************************************************************* */
Tile Deck::getTileAt(int iter)
{
	return boneyard.at(iter);
}

/* *********************************************************************
Function Name: addToDeck
Purpose: To add a tile to the back of the boneyard for loading a save file
Parameters:
			newTile, a tile that is to be added to the back of the boneyard
Return Value: none
Algorithm:
			1)Adds the tile to the back of the boneyard vector
Assistance Received: none
********************************************************************* */
void Deck::addToDeck(Tile newTile)
{
	boneyard.push_back(newTile);
}