#include "Human.h"
#include <iostream>
#include "Player.h"
#include "Tile.h"
#include <vector>

using namespace std;

//default constructor
Human::Human()
{


}

/* *********************************************************************
Function Name: drawToHand
Purpose: Add the tile passed through the parameter into the human players hand
Parameters:
			drawTile. The tile that will be added to the humans hand
Return Value: none
Algorithm:
			1)Adds the tile to the back of the humans hand
Assistance Received: none
********************************************************************* */
void Human::drawToHand(Tile drawTile)
{
	humanHand.push_back(drawTile);
}

/* *********************************************************************
Function Name: getHandSize
Purpose: gets the size of the players hand to know if their hand is empty
Parameters:
			none
Return Value: int, size of the human players hand
Algorithm:
			1)returns the size of the human players hand
Assistance Received: none
********************************************************************* */
int Human::getHandSize()
{
	return humanHand.size();
}

/* *********************************************************************
Function Name: getTile
Purpose: Gets the tile from a certain spot in the human hand
Parameters:
			iter, an int that is the number tile in human hand you want
Return Value: Tile, the tile that is in the human hand at spot iter
Algorithm:
			1)returns the tile at iter
Assistance Received: none
********************************************************************* */
Tile Human::getTile(int iter)
{
	return humanHand.at(iter);
}

/* *********************************************************************
Function Name: removeTile
Purpose: Removes a certain tile from the human's hand
Parameters:
			iter, an int that is the number tile in human hand you want
Return Value: none
Algorithm:
			1)Removes the tile at iter
Assistance Received: none
********************************************************************* */
void Human::removeTile(int iter)
{
	humanHand.erase(humanHand.begin() + iter);
}

/* *********************************************************************
Function Name: makeDecision
Purpose: The algorithm for deciding what best tile(s) to play is
Parameters:
			humanTrain, A vector passed by reference of the human train
			humanEligible, a bool telling whether or not the human train is eligible to be played on
			computerTrain, A vector passed by reference of the computer train
			computerEligible, a bool telling whether or not the computer train is eligible to be played on
			mexicanTrain, A vector passed by referece of the mexican train
			mexicanEligible, a bool telling whether or not the mexican train is eligible to be played on
			humanMarked, a bool passed by reference telling whether or not the human train is marked
			computerMarked, a bool passed by reference telling whether or not the computer train is marked
			humanOrphan, a bool passed by reference telling whether or not there is an orphan double on the human train
			computerOrphan, a bool passed by reference telling whether or not there is an orphan double on the computer train
			mexicanOrphan, a bool passed by reference telling whether or not there is an orphan double on the mexican train
			needDraw, a bool passed by reference telling whether or the player would need to draw
			drawTile, a Tile that is the tile that the player would be drawing if they need to draw
Return Value: none
Algorithm:
			1)Checks if the mexican train is started yet, if not says to play a tile there if possible
			2)Gets the double tile and best nondouble tile playable on each train if there is any
			3)Clears the double tile on one of the trains if its the same for two trains
			4)Tries to play two double tiles and one non-double
			5)Tries to play one double tile and one non-double
			6)Tries to play one non-double on the computer train
			7)Tries to play largest non-double tile
			8)Tries to play a double without followup
Assistance Received: none
********************************************************************* */
void Human::makeDecision(vector<Tile> &humanTrain, bool humanEligible, vector<Tile>& computerTrain, bool compEligible, vector<Tile>& mexicanTrain, bool mexicanEligible,
									bool& humanMarked, bool& computerMarked, bool& humanOrphan, bool& computerOrphan, bool& mexicanOrphan, bool& needDraw, Tile drawTile)
{
	//Tries playing on mexican train if not started yet
	if (mexicanTrain.size() == 1)
	{
		//Looks for largest tile to start mexican train
		Tile bestTile(-1, -1);
		for (int i = 0; i < humanHand.size(); i++)
		{
			if (humanHand.at(i).getSide1() == mexicanTrain.front().getSide1() || humanHand.at(i).getSide2() == mexicanTrain.front().getSide1())
			{
				if (bestTile.getTotalPips() < humanHand.at(i).getTotalPips())
				{
					bestTile = humanHand.at(i);
				}
			}
		}
		//If a tile is found that can be used to start mexican train
		if (bestTile.getTotalPips() > -1)
		{
			cout << "The computer suggests to start the mexican train with the tile ";
			bestTile.Display();
			cout << " because it's best to start the mexican train as early as possible and it's the largest tile to use." << endl;
			return;
		}
	}
	//The best possible non-double tile and any possible double found for each train
	Tile bestHumanTile(-1, -2);
	Tile humanDoubleTile(-1, -2);
	Tile bestComputerTile(-1, -2);
	Tile computerDoubleTile(-1, -2);
	Tile bestMexicanTile(-1, -2);
	Tile mexicanDoubleTile(-1, -2);
	Tile nullTile(-1, -2);

	for (int i = 0; i < humanHand.size(); i++)
	{
		//Getting the best possible non-double tile and double tile for the human train
		if (humanEligible)
		{
			if (humanHand.at(i).getSide1() == humanTrain.back().getSide2() && humanHand.at(i).getSide2() == humanTrain.back().getSide2())
			{
				humanDoubleTile = humanHand.at(i);
			}
			else if (humanHand.at(i).getSide1() == humanTrain.back().getSide2())
			{
				if (bestHumanTile.getTotalPips() < humanHand.at(i).getTotalPips())
				{
					bestHumanTile = humanHand.at(i);
				}
			}
			else if (humanHand.at(i).getSide2() == humanTrain.back().getSide2())
			{
				if (bestHumanTile.getTotalPips() < humanHand.at(i).getTotalPips())
				{
					bestHumanTile = humanHand.at(i);
					bestHumanTile.swapSides();
				}
			}
		}
		//Getting the best possible non-double tile and double tile for the computer train
		if (compEligible)
		{
			if (humanHand.at(i).getSide1() == computerTrain.back().getSide1() && humanHand.at(i).getSide2() == computerTrain.back().getSide1())
			{
				computerDoubleTile = humanHand.at(i);
			}
			else if (humanHand.at(i).getSide1() == computerTrain.back().getSide1())
			{
				if (bestComputerTile.getTotalPips() < humanHand.at(i).getTotalPips())
				{
					bestComputerTile = humanHand.at(i);
					bestComputerTile.swapSides();
				}
			}
			else if (humanHand.at(i).getSide2() == computerTrain.back().getSide1())
			{
				if (bestComputerTile.getTotalPips() < humanHand.at(i).getTotalPips())
				{
					bestComputerTile = humanHand.at(i);
				}
			}
		}
		//Getting the best possible non-double tile and double tile for the mexican train
		if (mexicanEligible)
		{
			if (humanHand.at(i).getSide1() == mexicanTrain.back().getSide2() && humanHand.at(i).getSide2() == mexicanTrain.back().getSide2())
			{
				mexicanDoubleTile = humanHand.at(i);
			}
			else if (humanHand.at(i).getSide1() == mexicanTrain.back().getSide2())
			{
				if (bestMexicanTile.getTotalPips() < humanHand.at(i).getTotalPips())
				{
					bestMexicanTile = humanHand.at(i);
				}
			}
			else if (humanHand.at(i).getSide2() == mexicanTrain.back().getSide2())
			{
				if (bestMexicanTile.getTotalPips() < humanHand.at(i).getTotalPips())
				{
					bestMexicanTile = humanHand.at(i);
					bestMexicanTile.swapSides();
				}
			}
		}
	}
	//Same double tile means the trains end in the same number can't have both
	if (humanDoubleTile.getSide1() == computerDoubleTile.getSide1())
	{
		computerDoubleTile = nullTile;
	}
	//Same double tile means the trains end in the same number can't have both
	if (humanDoubleTile.getSide1() == mexicanDoubleTile.getSide1() || computerDoubleTile.getSide1() == mexicanDoubleTile.getSide1())
	{
		mexicanDoubleTile = nullTile;
	}
	//Trying to play two doubles one non double starting with the first double on the human train
	if (humanDoubleTile.getSide1() > -1)
	{
		//Trying to play the second double on the computer train
		if (computerDoubleTile.getSide1() > -1)
		{
			//Trying to play the non double on the mexican train
			if (bestMexicanTile.getSide1() > -1)
			{
				cout << "The computer suggests playing ";
				humanDoubleTile.Display();
				cout << " on the human train, ";
				computerDoubleTile.Display();
				cout << " on the computer train, and ";
				bestMexicanTile.Display();
				cout << " on the mexican train so you can play three tiles in one turn and make two orphan doubles for the computer to have to play on.";
				return;
			}
			//Trying to play the non double on the human train
			else if (bestHumanTile.getSide1() > -1)
			{
				cout << "The computer suggests playing ";
				humanDoubleTile.Display();
				cout << " on the human train, ";
				computerDoubleTile.Display();
				cout << " on the computer train, and ";
				bestHumanTile.Display();
				cout << " on the human train so you can play three tiles in one turn and make an orphan double for the computer to have to play on.";
				return;
			}
			//Trying to play the non double on the computer train
			else if (bestComputerTile.getSide1() > -1)
			{
				cout << "The computer suggests playing ";
				humanDoubleTile.Display();
				cout << " on the human train, ";
				computerDoubleTile.Display();
				cout << " on the computer train, and ";
				bestComputerTile.Display();
				cout << " on the computer train so you can play three tiles in one turn and make an orphan double for the computer to have to play on.";
				return;
			}
			//If the first two doubles empty the hand
			else if (humanHand.size() == 2)
			{
				cout << "The computer suggests playing ";
				humanDoubleTile.Display();
				cout << " on the human train and ";
				computerDoubleTile.Display();
				cout << " on the computer train which empties your hand making you the winner.";
				return;
			}
		}
		//Trying to play the second double on the mexican train
		else if (mexicanDoubleTile.getSide1() > -1)
		{
			//Trying to play the non double on the computer train
			if (bestComputerTile.getSide1() > -1)
			{
				cout << "The computer suggests playing ";
				humanDoubleTile.Display();
				cout << " on the human train, ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train, and ";
				bestComputerTile.Display();
				cout << " on the computer train so you can play three tiles in one turn and make two orphan doubles for the computer to have to play on.";
				return;
			}
			//Trying to play the non double on the Human train
			else if (bestHumanTile.getSide1() > -1)
			{
				cout << "The computer suggests playing ";
				humanDoubleTile.Display();
				cout << " on the human train, ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train, and ";
				bestHumanTile.Display();
				cout << " on the human train so you can play three tiles in one turn and make an orphan double for the computer to have to play on.";
				return;
			}
			//Trying to play the non double on the mexican train
			else if (bestMexicanTile.getSide1() > -1)
			{
				cout << "The computer suggests playing ";
				humanDoubleTile.Display();
				cout << " on the human train, ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train, and ";
				bestMexicanTile.Display();
				cout << " on the mexican train so you can play three tiles in one turn and make an orphan double for the computer to have to play on.";
				return;
			}
			//If the first two doubles empty the hand
			else if (humanHand.size() == 2)
			{
				cout << "The computer suggests playing ";
				humanDoubleTile.Display();
				cout << " on the human train and ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train which empties your hand making you the winner.";
				return;
			}
		}
	}
	//Trying to play two doubles one non double starting with the first double on the computer train
	else if (computerDoubleTile.getSide1() > -1)
	{
	//Trying to play the second double on the mexican train
		if (mexicanDoubleTile.getSide1() > -1)
		{
			//Trying to play the non double on the human train
			if (bestHumanTile.getSide1() > -1)
			{
				cout << "The computer suggests playing ";
				computerDoubleTile.Display();
				cout << " on the computer train, ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train, and ";
				bestHumanTile.Display();
				cout << " on the human train so you can play three tiles in one turn and make two orphan doubles for the computer to have to play on.";
				return;
			}
			//Trying to play the non double on the computer train
			else if (bestComputerTile.getSide1() > -1)
			{
				cout << "The computer suggests playing ";
				computerDoubleTile.Display();
				cout << " on the computer train, ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train, and ";
				bestComputerTile.Display();
				cout << " on the computer train so you can play three tiles in one turn and make an orphan double for the computer to have to play on.";
				return;
			}
			//Trying to play the non double on the mexican train
			else if (bestMexicanTile.getSide1() > -1)
			{
				cout << "The computer suggests playing ";
				computerDoubleTile.Display();
				cout << " on the computer train, ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train, and ";
				bestMexicanTile.Display();
				cout << " on the Mexican train so you can play three tiles in one turn and make an orphan double for the computer to have to play on.";
				return;
			}
			//If the first two doubles empty the hand
			else if (humanHand.size() == 2)
			{
				cout << "The computer suggests playing ";
				computerDoubleTile.Display();
				cout << " on the computer train and ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train which empties your hand making you the winner.";
				return;
			}
		}
	}
	//Trying to play a double and a non double in one turn with the double being on the human train
	if (humanDoubleTile.getSide1() > -1)
	{
		//Trying to play the non double on the computer train
		if (bestComputerTile.getSide1() > -1)
		{
			cout << "The computer suggests playing ";
			humanDoubleTile.Display();
			cout << " on the human train and ";
			bestComputerTile.Display();
			cout << " on the computer train so you can play two tiles in one turn and make an orphan double the computer must play on.";
			return;
		}
		//Trying to play the non double on the mexican train
		else if (bestMexicanTile.getSide1() > -1)
		{
			cout << "The computer suggests playing ";
			humanDoubleTile.Display();
			cout << " on the human train and ";
			bestMexicanTile.Display();
			cout << " on the mexican train so you can play two tiles in one turn and make an orphan double the computer must play on.";
			return;
		}
		//Trying to play the non double on the human train
		else if (bestHumanTile.getSide1() > -1)
		{
			cout << "The computer suggests playing ";
			humanDoubleTile.Display();
			cout << " on the human train and ";
			bestHumanTile.Display();
			cout << " on the human train so you can play two tiles in one turn.";
			return;
		}

		//If the double tile empties the hand
		else if (humanHand.size() == 1)
		{
			cout << "The computer suggests playing ";
			humanDoubleTile.Display();
			cout << " on the human train which empties your hand making you the winner.";
			return;
		}
	}
	//Trying to play a double and a non double in one turn with the double being on the computer train
	else if (computerDoubleTile.getSide1() > -1)
	{
		//Trying to play the non double on the human train
		if (bestHumanTile.getSide1() > -1)
		{
			cout << "The computer suggests playing ";
			computerDoubleTile.Display();
			cout << " on the computer train and ";
			bestHumanTile.Display();
			cout << " on the human train so you can play two tiles in one turn and make an orphan double the computer must play on.";
			return;
		}
		//Trying to play the non double on the mexican train
		else if (bestMexicanTile.getSide1() > 1)
		{
			cout << "The computer suggests playing ";
			computerDoubleTile.Display();
			cout << " on the computer train and ";
			bestMexicanTile.Display();
			cout << " on the mexican train so you can play two tiles in one turn and make an orphan double the computer must play on.";
			return;
		}
		//Trying to play the non double on the computer train
		else if (bestComputerTile.getSide1() > 1)
		{
			cout << "The computer suggests playing ";
			computerDoubleTile.Display();
			cout << " on the computer train and ";
			bestComputerTile.Display();
			cout << " on the computer train so you can play two tiles in one turn.";
			return;
		}

		//If the double tile empties the hand
		else if (humanHand.size() == 1)
		{
			cout << "The computer suggests playing ";
			computerDoubleTile.Display();
			cout << " on the computer train which empties your hand making you the winner.";
			return;
		}
	}
	//Trying to play a double and a non double in one turn with the double being on the mexican train
	else if (mexicanDoubleTile.getSide1() > -1)
	{
		//Trying to play the non double on the human train
		if (bestHumanTile.getSide1() > -1)
		{
			cout << "The computer suggets playing ";
			mexicanDoubleTile.Display();
			cout << " on the mexican train and ";
			bestHumanTile.Display();
			cout << " on the human train so you can play two tiles in one turn and make an orphan double the computer must play on.";
			return;
		}
		//Trying to play the non double on the computer train
		else if (bestComputerTile.getSide1() > -1)
		{
			cout << "The computer suggests playing ";
			mexicanDoubleTile.Display();
			cout << " on the mexican train and ";
			bestComputerTile.Display();
			cout << " on the computer train so you can play two tiles in one turn and make an orphan double the computer must play on.";
			return;
		}
		//Trying to play the non double on the mexican train
		else if (bestMexicanTile.getSide1() > -1)
		{
			cout << "The computer suggests playing ";
			mexicanDoubleTile.Display();
			cout << " on the mexican train and ";
			bestMexicanTile.Display();
			cout << " on the mexican train so you can play two tiles in one turn.";
			return;
		}
		//If the double tile empties the hand
		else if (humanHand.size() == 1)
		{
			cout << "The computer suggests playing ";
			mexicanDoubleTile.Display();
			cout << " on the mexican train which empties your hand making you the winner.";
			return;
		}
	}
	//Trying to play the largest non-double tile on the computer train
	if (bestComputerTile.getSide1() > -1)
	{
		cout << " The computer suggests playing ";
		bestComputerTile.Display();
		if (computerMarked)
		{
			cout << " on the computer train because the computer train has a marker and it's the larget in hand tile that could be played on that train.";
		}
		else
		{
			cout << " on the computer train because the computer train has an orphan double and it's the largest in hand tile that could be played on that train.";
		}
		return;
	}
	//Trying to play the largest non-double tile on the human train
	else if (bestHumanTile.getSide1() > -1)
	{
		//If the human train has a larger total pips then play on human train otherwise play on mexican train since they have the same priority
		if (bestHumanTile.getTotalPips() > bestMexicanTile.getTotalPips())
		{
			cout << "The computer suggests playing ";
			bestHumanTile.Display();
			cout << " on the human train because it is the largest playable tile in hand.";
			return;
		}
		else
		{
			cout << "The computer suggests playing ";
			bestMexicanTile.Display();
			cout << " on the mexican train because it is the largest playable tile in hand.";
			return;
		}
	}
	//Trying to play the largest non-double tile on the mexican train
	else if (bestMexicanTile.getSide1() > -1)
	{
		cout << "The computer suggests playing ";
		bestMexicanTile.Display();
		cout << " on the mexican train because it is the largest playable tile in hand.";
		return;
	}
	//Trying to play a double tile on the human train and having to draw and being able to play that drawn tile
	if (humanDoubleTile.getSide1() > -1)
	{
		if (compEligible)
		{
			//Trying to play that drawn tile on the computer train
			if (drawTile.getSide1() == computerTrain.back().getSide1() || drawTile.getSide2() == computerTrain.back().getSide1())
			{
				cout << "The computer suggests playing ";
				humanDoubleTile.Display();
				cout << " on the human train which means you will have to draw ";
				drawTile.Display();
				cout << " from the boneyard and it is playable on the computer train.";
				return;
			}
		}
		if (mexicanEligible)
		{
			//Trying to play that drawn tile on the mexican train
			if (drawTile.getSide1() == mexicanTrain.back().getSide2() || drawTile.getSide2() == mexicanTrain.back().getSide2())
			{
				cout << "The computer suggests playing ";
				humanDoubleTile.Display();
				cout << " on the human train which means you will have to draw ";
				drawTile.Display();
				cout << " from the boneyard and it is playable on the mexican train.";
				return;
			}
		}
		if (humanEligible)
		{
			//Trying to play that drawn tile on the human train
			if (drawTile.getSide1() == humanTrain.back().getSide2() || drawTile.getSide2() == humanTrain.back().getSide2())
			{
				cout << "The computer suggests playing ";
				humanDoubleTile.Display();
				cout << " on the human train which means you will have to draw ";
				drawTile.Display();
				cout << " from the boneyard and it is playable on the human train.";
				return;
			}
		}
	}
	//Trying to play a double tile on the computer train and having to draw and being able to play that drawn tile
	else if (computerDoubleTile.getSide1() > -1)
	{
		if (compEligible)
		{
			//Trying to play that drawn tile on the computer train
			if (drawTile.getSide1() == computerTrain.back().getSide1() || drawTile.getSide2() == computerTrain.back().getSide1())
			{
				cout << "The computer suggests playing ";
				computerDoubleTile.Display();
				cout << " on the computer train which means you will have to draw ";
				drawTile.Display();
				cout << " from the boneyard and it is playable on the computer train.";
				return;
			}
		}
		if (mexicanEligible)
		{
			//Trying to play that drawn tile on the mexican train
			if (drawTile.getSide1() == mexicanTrain.back().getSide2() || drawTile.getSide2() == mexicanTrain.back().getSide1())
			{
				cout << "The computer suggests playing ";
				computerDoubleTile.Display();
				cout << " on the computer train which means you will have to draw ";
				drawTile.Display();
				cout << " from the boneyard and it is playable on the mexican train.";
				return;
			}
		}
		if (humanEligible)
		{
			//Trying to play that drawn tile on the human train
			if (drawTile.getSide1() == humanTrain.back().getSide2() || drawTile.getSide2() == humanTrain.back().getSide2())
			{
				cout << "The computer suggests playing ";
				computerDoubleTile.Display();
				cout << " on the computer train which means you will have to draw ";
				drawTile.Display();
				cout << " from the boneyard and it is playable on the human train.";
				return;
			}
		}
	}
	//Trying to play a double tile on the mexican train and having to draw and being able to play that drawn tile
	else if (mexicanDoubleTile.getSide1() > -1)
	{
		if (compEligible)
		{
			//Trying to play that drawn tile on the computer train
			if (drawTile.getSide1() == computerTrain.back().getSide1() || drawTile.getSide2() == computerTrain.back().getSide1())
			{
				cout << "The computer suggests playing ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train which means you will have to draw ";
				drawTile.Display();
				cout << " from the boneyard and it is playable on the computer train.";
				return;
			}
		}
		if (mexicanEligible)
		{
			//Trying to play that drawn tile on the mexican train
			if (drawTile.getSide1() == mexicanTrain.back().getSide2() || drawTile.getSide2() == mexicanTrain.back().getSide2())
			{
				cout << "The computer suggests playing ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train which means you will have to draw ";
				drawTile.Display();
				cout << " from the boneyard and it is playable on the mexican train.";
				return;
			}
		}
		if (humanEligible)
		{
			//Trying to play that drawn tile on the human train
			if (drawTile.getSide1() == humanTrain.back().getSide2() || drawTile.getSide2() == humanTrain.back().getSide2())
			{
				cout << "The computer suggests playing ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train which means you will have to draw ";
				drawTile.Display();
				cout << " from the boneyard and it is playable on the human train.";
				return;
			}
		}
	}
	//The boneyard is not empty but the drawn tile will not be playable
	if (drawTile.getSide1() > -1)
	{
		//Trying to play a double on the human train
		if (humanDoubleTile.getSide1() > -1)
		{
			cout << "The computer suggests playing ";
			humanDoubleTile.Display();
			cout << " on the human train but will have to draw and can't play the drawn tile.";
			return;
		}
		//Trying to play a double on the computer train
		if (computerDoubleTile.getSide1() > -1)
		{
			cout << "The computer suggests playing ";
			computerDoubleTile.Display();
			cout << " on the computer train but will have to draw and can't play the drawn tile.";
			return;
		}
		//Trying to play a double on the mexican train
		if (mexicanDoubleTile.getSide1() > -1)
		{
			cout << "The computer suggests playing ";
			mexicanDoubleTile.Display();
			cout << " on the mexican train but will have to draw and can't play the drawn tile.";
			return;
		}
	}
	//The boneyard is empty so no tile can be drawn after playing a double
	else
	{
		//Trying to play a double on the human train
		if (humanDoubleTile.getSide1() > -1)
		{
			cout << "The computer suggests playing ";
			humanDoubleTile.Display();
			cout << " on the human train and can not draw because the boneyard is empty.";
			return;
		}
		//Trying to play a double on the computer train
		if (computerDoubleTile.getSide1() > -1)
		{
			cout << "The computer suggests playing ";
			computerDoubleTile.Display();
			cout << " on the computer train and can not draw because the boneyard is empty.";
			return;
		}
		//Trying to play a double on the mexican train
		if (mexicanDoubleTile.getSide1() > -1)
		{
			cout << "The computer suggests playing ";
			mexicanDoubleTile.Display();
			cout << " on the mexican train and can not draw because the boneyard is empty.";
			return;
		}
	}
}