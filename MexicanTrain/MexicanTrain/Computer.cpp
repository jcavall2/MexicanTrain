#include "Computer.h"
#include "Player.h"

using namespace std;

//default constructor
Computer::Computer()
{


}

/* *********************************************************************
Function Name: drawToHand
Purpose: Add the tile passed through the parameter into the computer players hand
Parameters:
			drawTile. The tile that will be added to the computers hand
Return Value: none
Algorithm:
			1)Adds the tile to the back of the computers hand
Assistance Received: none
********************************************************************* */
void Computer::drawToHand(Tile drawTile)
{
	computerHand.push_back(drawTile);
}

/* *********************************************************************
Function Name: getHandSize
Purpose: gets the size of the players hand to know if their hand is empty
Parameters:
			none
Return Value: int, size of the computer players hand
Algorithm:
			1)returns the size of the human computers hand
Assistance Received: none
********************************************************************* */
int Computer::getHandSize()
{
	return computerHand.size();
}

/* *********************************************************************
Function Name: getTile
Purpose: Gets the tile from a certain spot in the computer hand
Parameters:
			iter, an int that is the number tile in computer hand you want
Return Value: Tile, the tile that is in the computer hand at spot iter
Algorithm:
			1)returns the tile at iter
Assistance Received: none
********************************************************************* */
Tile Computer::getTile(int iter)
{
	return computerHand.at(iter);
}

/* *********************************************************************
Function Name: removeTile
Purpose: Removes a certain tile from the computer's hand
Parameters:
			iter, an int that is the number tile in computer hand you want
Return Value: none
Algorithm:
			1)Removes the tile at iter
Assistance Received: none
********************************************************************* */
void Computer::removeTile(int iter)
{
	computerHand.erase(computerHand.begin() + iter);
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
			6)Tries to play one non-double on the human train
			7)Tries to play largest non-double tile
			8)Tries to play a double without followup
Assistance Received: none
********************************************************************* */
void Computer::makeDecision(vector<Tile>& humanTrain, bool humanEligible, vector<Tile>& computerTrain, bool compEligible, vector<Tile>& mexicanTrain, bool mexicanEligible,
	bool& humanMarked, bool& computerMarked, bool& humanOrphan, bool& computerOrphan, bool& mexicanOrphan, bool& needDraw, Tile drawTile)
{
	//Tries playing on mexican train if not started yet
	if (mexicanTrain.size() == 1)
	{
		//Looks for largest tile to start mexican train
		Tile bestTile(-1, -1);
		for (int i = 0; i < computerHand.size(); i++)
		{
			if (computerHand.at(i).getSide1() == mexicanTrain.front().getSide1() || computerHand.at(i).getSide2() == mexicanTrain.front().getSide1())
			{
				if (bestTile.getTotalPips() < computerHand.at(i).getTotalPips())
				{
					bestTile = computerHand.at(i);
				}
			}
		}
		//If a tile is found that can be used to start mexican train
		if (bestTile.getTotalPips() > -1)
		{
			for (int i = 0; i < computerHand.size(); i++)
			{
				if (bestTile.getSide1() == computerHand.at(i).getSide1() && bestTile.getSide2() == computerHand.at(i).getSide2())
				{
					if (mexicanTrain.front().getSide2() == bestTile.getSide2())
					{
						bestTile.swapSides();
					}
					mexicanTrain.push_back(bestTile);
					removeTile(i);
					cout << "The computer started the mexican train with the tile ";
					bestTile.Display();
					cout << " because it's best to start the mexican train as early as possible and it's the largest tile they could have used." << endl;
					return;
				}
			}
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
	for (int i = 0; i < computerHand.size(); i++)
	{
		//Getting the best possible non-double tile and double tile for the human train
		if (humanEligible)
		{
			if (computerHand.at(i).getSide1() == humanTrain.back().getSide2() && computerHand.at(i).getSide2() == humanTrain.back().getSide2())
			{
				humanDoubleTile = computerHand.at(i);
			}
			else if (computerHand.at(i).getSide1() == humanTrain.back().getSide2())
			{
				if (bestHumanTile.getTotalPips() < computerHand.at(i).getTotalPips())
				{
					bestHumanTile = computerHand.at(i);
				}
			}
			else if (computerHand.at(i).getSide2() == humanTrain.back().getSide2())
			{
				if (bestHumanTile.getTotalPips() < computerHand.at(i).getTotalPips())
				{
					bestHumanTile = computerHand.at(i);
					bestHumanTile.swapSides();
				}
			}
		}
		//Getting the best possible non-double tile and double tile for the computer train
		if (compEligible)
		{
			if (computerHand.at(i).getSide1() == computerTrain.back().getSide1() && computerHand.at(i).getSide2() == computerTrain.back().getSide1())
			{
				computerDoubleTile = computerHand.at(i);
			}
			else if (computerHand.at(i).getSide1() == computerTrain.back().getSide1())
			{
				if (bestComputerTile.getTotalPips() < computerHand.at(i).getTotalPips())
				{
					bestComputerTile = computerHand.at(i);
					bestComputerTile.swapSides();
				}
			}
			else if (computerHand.at(i).getSide2() == computerTrain.back().getSide1())
			{
				if (bestComputerTile.getTotalPips() < computerHand.at(i).getTotalPips())
				{
					bestComputerTile = computerHand.at(i);
				}
			}
		}
		//Getting the best possible non-double tile and double tile for the mexican train
		if (mexicanEligible)
		{
			if (computerHand.at(i).getSide1() == mexicanTrain.back().getSide2() && computerHand.at(i).getSide2() == mexicanTrain.back().getSide2())
			{
				mexicanDoubleTile = computerHand.at(i);
			}
			else if (computerHand.at(i).getSide1() == mexicanTrain.back().getSide2())
			{
				if (bestMexicanTile.getTotalPips() < computerHand.at(i).getTotalPips())
				{
					bestMexicanTile = computerHand.at(i);
				}
			}
			else if (computerHand.at(i).getSide2() == mexicanTrain.back().getSide2())
			{
				if (bestMexicanTile.getTotalPips() < computerHand.at(i).getTotalPips())
				{
					bestMexicanTile = computerHand.at(i);
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
				humanTrain.push_back(humanDoubleTile);
				humanOrphan = true;
				computerTrain.push_back(computerDoubleTile);
				computerOrphan = true;
				mexicanTrain.push_back(bestMexicanTile);
				for (int i = 0; i < computerHand.size();)
				{
					if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((bestMexicanTile.getSide1() == computerHand.at(i).getSide1() && bestMexicanTile.getSide2() == computerHand.at(i).getSide2()) || (bestMexicanTile.getSide1() == computerHand.at(i).getSide2() && bestMexicanTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					i++;
				}
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train, ";
				computerDoubleTile.Display();
				cout << " on the computer train, and ";
				bestMexicanTile.Display();
				cout << " on the mexican train so it could play three tiles in one turn and make two orphan doubles for the player to have to play on.";
				return;
			}
			//Trying to play the non double on the human train
			else if (bestHumanTile.getSide1() > -1)
			{
				humanTrain.push_back(humanDoubleTile);
				computerTrain.push_back(computerDoubleTile);
				computerMarked = false;
				computerOrphan = true;
				humanTrain.push_back(bestHumanTile);
				for (int i = 0; i < computerHand.size();)
				{
					if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((bestHumanTile.getSide1() == computerHand.at(i).getSide1() && bestHumanTile.getSide2() == computerHand.at(i).getSide2()) || (bestHumanTile.getSide1() == computerHand.at(i).getSide2() && bestHumanTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					i++;
				}
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train, ";
				computerDoubleTile.Display();
				cout << " on the computer train, and ";
				bestHumanTile.Display();
				cout << " on the human train so it could play three tiles in one turn and make an orphan double for the player to have to play on.";
				return;
			}
			//Trying to play the non double on the computer train
			else if (bestComputerTile.getSide1() > -1)
			{
				humanTrain.push_back(humanDoubleTile);
				humanOrphan = true;
				computerTrain.push_back(computerDoubleTile);
				computerTrain.push_back(bestComputerTile);
				computerMarked = false;
				for (int i = 0; i < computerHand.size();)
				{
					if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((bestComputerTile.getSide1() == computerHand.at(i).getSide1() && bestComputerTile.getSide2() == computerHand.at(i).getSide2()) || (bestComputerTile.getSide1() == computerHand.at(i).getSide2() && bestComputerTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					i++;
				}
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train, ";
				computerDoubleTile.Display();
				cout << " on the computer train, and ";
				bestComputerTile.Display();
				cout << " on the computer train so it could play three tiles in one turn and make an orphan double for the player to have to play on.";
				return;
			}
			//If the first two doubles empty the hand
			else if (computerHand.size() == 2)
			{
				humanTrain.push_back(humanDoubleTile);
				computerTrain.push_back(computerDoubleTile);
				computerMarked = false;
				computerHand.erase(computerHand.begin());
				computerHand.erase(computerHand.begin());
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train and ";
				computerDoubleTile.Display();
				cout << " on the computer train which empties it's hand making it the winner.";
				return;
			}
		}
		//Trying to play the second double on the mexican train
		else if (mexicanDoubleTile.getSide1() > -1)
		{
			//Trying to play the non double on the computer train
			if (bestComputerTile.getSide1() > -1)
			{
				humanTrain.push_back(humanDoubleTile);
				humanOrphan = true;
				mexicanTrain.push_back(mexicanDoubleTile);
				mexicanOrphan = true;
				computerTrain.push_back(bestComputerTile);
				computerMarked = false;
				for (int i = 0; i < computerHand.size();)
				{
					if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((bestComputerTile.getSide1() == computerHand.at(i).getSide1() && bestComputerTile.getSide2() == computerHand.at(i).getSide2()) || (bestComputerTile.getSide1() == computerHand.at(i).getSide2() && bestComputerTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					i++;
				}
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train, ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train, and ";
				bestComputerTile.Display();
				cout << " on the computer train so it could play three tiles in one turn and make two orphan doubles for the player to have to play on.";
				return;
			}
			//Trying to play the non double on the Human train
			else if (bestHumanTile.getSide1() > -1)
			{
				humanTrain.push_back(humanDoubleTile);
				mexicanTrain.push_back(mexicanDoubleTile);
				mexicanOrphan = true;
				humanTrain.push_back(bestHumanTile);
				for (int i = 0; i < computerHand.size();)
				{
					if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((bestHumanTile.getSide1() == computerHand.at(i).getSide1() && bestHumanTile.getSide2() == computerHand.at(i).getSide2()) || (bestHumanTile.getSide1() == computerHand.at(i).getSide2() && bestHumanTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					i++;
				}
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train, ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train, and ";
				bestHumanTile.Display();
				cout << " on the human train so it could play three tiles in one turn and make an orphan double for the player to have to play on.";
				return;
			}
			//Trying to play the non double on the mexican train
			else if (bestMexicanTile.getSide1() > -1)
			{
				humanTrain.push_back(humanDoubleTile);
				humanOrphan = true;
				mexicanTrain.push_back(mexicanDoubleTile);
				mexicanTrain.push_back(bestMexicanTile);
				for (int i = 0; i < computerHand.size();)
				{
					if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((bestMexicanTile.getSide1() == computerHand.at(i).getSide1() && bestMexicanTile.getSide2() == computerHand.at(i).getSide2()) || (bestMexicanTile.getSide1() == computerHand.at(i).getSide2() && bestMexicanTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					i++;
				}
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train, ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train, and ";
				bestMexicanTile.Display();
				cout << " on the mexican train so it could play three tiles in one turn and make an orphan double for the player to have to play on.";
				return;
			}
			//If the first two doubles empty the hand
			else if (computerHand.size() == 2)
			{
				humanTrain.push_back(humanDoubleTile);
				mexicanTrain.push_back(mexicanDoubleTile);
				computerHand.erase(computerHand.begin());
				computerHand.erase(computerHand.begin());
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train and ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train which empties it's hand making it the winner.";
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
				computerTrain.push_back(computerDoubleTile);
				computerMarked = false;
				computerOrphan = true;
				mexicanTrain.push_back(mexicanDoubleTile);
				mexicanOrphan = true;
				humanTrain.push_back(bestHumanTile);
				for (int i = 0; i < computerHand.size();)
				{
					if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((bestHumanTile.getSide1() == computerHand.at(i).getSide1() && bestHumanTile.getSide2() == computerHand.at(i).getSide2()) || (bestHumanTile.getSide1() == computerHand.at(i).getSide2() && bestHumanTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					i++;
				}
				cout << "The computer played ";
				computerDoubleTile.Display();
				cout << " on the computer train, ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train, and ";
				bestHumanTile.Display();
				cout << " on the human train so it could play three tiles in one turn and make two orphan doubles for the player to have to play on.";
				return;
			}
			//Trying to play the non double on the computer train
			else if (bestComputerTile.getSide1() > -1)
			{
				computerTrain.push_back(computerDoubleTile);
				mexicanTrain.push_back(mexicanDoubleTile);
				mexicanOrphan = true;
				computerTrain.push_back(bestComputerTile);
				computerMarked = false;
				for (int i = 0; i < computerHand.size();)
				{
					if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((bestComputerTile.getSide1() == computerHand.at(i).getSide1() && bestComputerTile.getSide2() == computerHand.at(i).getSide2()) || (bestComputerTile.getSide1() == computerHand.at(i).getSide2() && bestComputerTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					i++;
				}
				cout << "The computer played ";
				computerDoubleTile.Display();
				cout << " on the computer train, ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train, and ";
				bestComputerTile.Display();
				cout << " on the computer train so it could play three tiles in one turn and make an orphan double for the player to have to play on.";
				return;
			}
			//Trying to play the non double on the mexican train
			else if (bestMexicanTile.getSide1() > -1)
			{
				computerTrain.push_back(computerDoubleTile);
				computerMarked = false;
				computerOrphan = true;
				mexicanTrain.push_back(mexicanDoubleTile);
				mexicanTrain.push_back(bestMexicanTile);
				for (int i = 0; i < computerHand.size();)
				{
					if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					if ((bestMexicanTile.getSide1() == computerHand.at(i).getSide1() && bestMexicanTile.getSide2() == computerHand.at(i).getSide2()) || (bestMexicanTile.getSide1() == computerHand.at(i).getSide2() && bestMexicanTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						continue;
					}
					i++;
				}
				cout << "The computer played ";
				computerDoubleTile.Display();
				cout << " on the computer train, ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train, and ";
				bestMexicanTile.Display();
				cout << " on the Mexican train so it could play three tiles in one turn and make an orphan double for the player to have to play on.";
				return;
			}
			//If the first two doubles empty the hand
			else if (computerHand.size() == 2)
			{
				computerTrain.push_back(computerDoubleTile);
				computerMarked = false;
				mexicanTrain.push_back(mexicanDoubleTile);
				computerHand.erase(computerHand.begin());
				computerHand.erase(computerHand.begin());
				cout << "The computer played ";
				computerDoubleTile.Display();
				cout << " on the computer train and ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train which empties it's hand making it the winner.";
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
			humanTrain.push_back(humanDoubleTile);
			humanOrphan = true;
			computerTrain.push_back(bestComputerTile);
			computerMarked = false;
			for (int i = 0; i < computerHand.size();)
			{
				if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				if ((bestComputerTile.getSide1() == computerHand.at(i).getSide1() && bestComputerTile.getSide2() == computerHand.at(i).getSide2()) || (bestComputerTile.getSide1() == computerHand.at(i).getSide2() && bestComputerTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				i++;
			}
			cout << "The computer played ";
			humanDoubleTile.Display();
			cout << " on the human train and ";
			bestComputerTile.Display();
			cout << " on the computer train so it could play two tiles in one turn and make an orphan double the player must play on.";
			return;
		}
		//Trying to play the non double on the mexican train
		else if (bestMexicanTile.getSide1() > -1)
		{
			humanTrain.push_back(humanDoubleTile);
			humanOrphan = true;
			mexicanTrain.push_back(bestMexicanTile);
			for (int i = 0; i < computerHand.size();)
			{
				if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				if ((bestMexicanTile.getSide1() == computerHand.at(i).getSide1() && bestMexicanTile.getSide2() == computerHand.at(i).getSide2()) || (bestMexicanTile.getSide1() == computerHand.at(i).getSide2() && bestMexicanTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				i++;
			}
			cout << "The computer played ";
			humanDoubleTile.Display();
			cout << " on the human train and ";
			bestMexicanTile.Display();
			cout << " on the mexican train so it could play two tiles in one turn and make an orphan double the player must play on.";
			return;
		}
		//Trying to play the non double on the human train
		else if (bestHumanTile.getSide1() > -1)
		{
			humanTrain.push_back(humanDoubleTile);
			humanTrain.push_back(bestHumanTile);
			for (int i = 0; i < computerHand.size();)
			{
				if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				if ((bestHumanTile.getSide1() == computerHand.at(i).getSide1() && bestHumanTile.getSide2() == computerHand.at(i).getSide2()) || (bestHumanTile.getSide1() == computerHand.at(i).getSide2() && bestHumanTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				i++;
			}
			cout << "The computer played ";
			humanDoubleTile.Display();
			cout << " on the human train and ";
			bestHumanTile.Display();
			cout << " on the human train so it could play two tiles in one turn.";
			return;
		}
		//If the double tile empties the hand
		else if (computerHand.size() == 1)
		{
			humanTrain.push_back(humanDoubleTile);
			computerHand.erase(computerHand.begin());
			cout << "The computer played ";
			humanDoubleTile.Display();
			cout << " on the human train which empties it's hand making it the winner.";
			return;
		}
	}
	//Trying to play a double and a non double in one turn with the double being on the computer train
	else if (computerDoubleTile.getSide1() > -1)
	{
		//Trying to play the non double on the human train
		if (bestHumanTile.getSide1() > -1)
		{
			computerTrain.push_back(computerDoubleTile);
			computerMarked = false;
			computerOrphan = true;
			humanTrain.push_back(bestHumanTile);
			for (int i = 0; i < computerHand.size();)
			{
				if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				if ((bestHumanTile.getSide1() == computerHand.at(i).getSide1() && bestHumanTile.getSide2() == computerHand.at(i).getSide2()) || (bestHumanTile.getSide1() == computerHand.at(i).getSide2() && bestHumanTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				i++;
			}
			cout << "The computer played ";
			computerDoubleTile.Display();
			cout << " on the computer train and ";
			bestHumanTile.Display();
			cout << " on the human train so it could play two tiles in one turn and make an orphan double the player must play on.";
			return;
		}
		//Trying to play the non double on the mexican train
		else if (bestMexicanTile.getSide1() > 1)
		{
			computerTrain.push_back(computerDoubleTile);
			computerMarked = false;
			computerOrphan = true;
			mexicanTrain.push_back(bestMexicanTile);
			for (int i = 0; i < computerHand.size();)
			{
				if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				if ((bestMexicanTile.getSide1() == computerHand.at(i).getSide1() && bestMexicanTile.getSide2() == computerHand.at(i).getSide2()) || (bestMexicanTile.getSide1() == computerHand.at(i).getSide2() && bestMexicanTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				i++;
			}
			cout << "The computer played ";
			computerDoubleTile.Display();
			cout << " on the computer train and ";
			bestMexicanTile.Display();
			cout << " on the mexican train so it could play two tiles in one turn and make an orphan double the player must play on.";
			return;
		}
		//Trying to play the non double on the computer train
		else if (bestComputerTile.getSide1() > 1)
		{
			computerTrain.push_back(computerDoubleTile);
			computerTrain.push_back(bestComputerTile);
			computerMarked = false;
			for (int i = 0; i < computerHand.size();)
			{
				if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				if ((bestComputerTile.getSide1() == computerHand.at(i).getSide1() && bestComputerTile.getSide2() == computerHand.at(i).getSide2()) || (bestComputerTile.getSide1() == computerHand.at(i).getSide2() && bestComputerTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				i++;
			}
			cout << "The computer played ";
			computerDoubleTile.Display();
			cout << " on the computer train and ";
			bestComputerTile.Display();
			cout << " on the computer train so it could play two tiles in one turn.";
			return;
		}
		//If the double tile empties the hand
		else if (computerHand.size() == 1)
		{
			computerTrain.push_back(computerDoubleTile);
			computerMarked = false;
			computerHand.erase(computerHand.begin());
			cout << "The computer played ";
			computerDoubleTile.Display();
			cout << " on the computer train which empties it's hand making it the winner.";
			return;
		}
	}
	//Trying to play a double and a non double in one turn with the double being on the mexican train
	else if (mexicanDoubleTile.getSide1() > -1)
	{
		//Trying to play the non double on the human train
		if (bestHumanTile.getSide1() > -1)
		{
			mexicanTrain.push_back(mexicanDoubleTile);
			mexicanOrphan = true;
			humanTrain.push_back(bestHumanTile);
			for (int i = 0; i < computerHand.size();)
			{
				if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				if ((bestHumanTile.getSide1() == computerHand.at(i).getSide1() && bestHumanTile.getSide2() == computerHand.at(i).getSide2()) || (bestHumanTile.getSide1() == computerHand.at(i).getSide2() && bestHumanTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				i++;
			}
			cout << "The computer played ";
			mexicanDoubleTile.Display();
			cout << " on the mexican train and ";
			bestHumanTile.Display();
			cout << " on the human train so it could play two tiles in one turn and make an orphan double the player must play on.";
			return;
		}
		//Trying to play the non double on the computer train
		else if (bestComputerTile.getSide1() > -1)
		{
			mexicanTrain.push_back(mexicanDoubleTile);
			mexicanOrphan = true;
			computerTrain.push_back(bestComputerTile);
			computerMarked = false;
			for (int i = 0; i < computerHand.size();)
			{
				if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				if ((bestComputerTile.getSide1() == computerHand.at(i).getSide1() && bestComputerTile.getSide2() == computerHand.at(i).getSide2()) || (bestComputerTile.getSide1() == computerHand.at(i).getSide2() && bestComputerTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				i++;
			}
			cout << "The computer played ";
			mexicanDoubleTile.Display();
			cout << " on the mexican train and ";
			bestComputerTile.Display();
			cout << " on the computer train so it could play two tiles in one turn and make an orphan double the player must play on.";
			return;
		}
		//Trying to play the non double on the mexican train
		else if (bestMexicanTile.getSide1() > -1)
		{
			mexicanTrain.push_back(mexicanDoubleTile);
			mexicanTrain.push_back(bestMexicanTile);
			for (int i = 0; i < computerHand.size();)
			{
				if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				if ((bestMexicanTile.getSide1() == computerHand.at(i).getSide1() && bestMexicanTile.getSide2() == computerHand.at(i).getSide2()) || (bestMexicanTile.getSide1() == computerHand.at(i).getSide2() && bestMexicanTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					continue;
				}
				i++;
			}
			cout << "The computer played ";
			mexicanDoubleTile.Display();
			cout << " on the mexican train and ";
			bestMexicanTile.Display();
			cout << " on the mexican train so it could play two tiles in one turn.";
			return;
		}
		//If the double tile empties the hand
		else if (computerHand.size() == 1)
		{
			mexicanTrain.push_back(mexicanDoubleTile);
			computerHand.erase(computerHand.begin());
			cout << "The computer played ";
			mexicanDoubleTile.Display();
			cout << " on the mexican train which empties it's hand making it the winner.";
			return;
		}
	}
	//Trying to play the largest non-double tile on the human train
	if (bestHumanTile.getSide1() > -1)
	{
		humanTrain.push_back(bestHumanTile);
		humanOrphan = false;
		for (int i = 0; i < computerHand.size(); i++)
		{
			if ((bestHumanTile.getSide1() == computerHand.at(i).getSide1() && bestHumanTile.getSide2() == computerHand.at(i).getSide2()) || (bestHumanTile.getSide1() == computerHand.at(i).getSide2() && bestHumanTile.getSide2() == computerHand.at(i).getSide1()))
			{
				removeTile(i);
				break;
			}
		}
		cout << " The computer played ";
		bestHumanTile.Display();
		if (humanMarked)
		{
			cout << " on the human train because the human train has a marker and it's the larget in hand tile that could be played on that train.";
		}
		else
		{
			cout << " on the human train because it had an orphan double and it's the largest in hand tile that could be played on that train.";
		}
		
		return;
	}
	//Trying to play the largest non-double tile on the computer train
	else if (bestComputerTile.getSide1() > -1)
	{
		//If the computer train has a larger total pips then play on human train otherwise play on mexican train since they have the same priority
		if (bestComputerTile.getTotalPips() > bestMexicanTile.getTotalPips())
		{
			computerTrain.push_back(bestComputerTile);
			computerMarked = false;
			computerOrphan = false;
			for (int i = 0; i < computerHand.size(); i++)
			{
				if ((bestComputerTile.getSide1() == computerHand.at(i).getSide1() && bestComputerTile.getSide2() == computerHand.at(i).getSide2()) || (bestComputerTile.getSide1() == computerHand.at(i).getSide2() && bestComputerTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					break;
				}
			}
			cout << "The computer played ";
			bestComputerTile.Display();
			cout << " on the computer train because it is the largest playable tile in hand.";
			return;
		}
		else
		{
			mexicanTrain.push_back(bestMexicanTile);
			mexicanOrphan = false;
			for (int i = 0; i < computerHand.size(); i++)
			{
				if ((bestMexicanTile.getSide1() == computerHand.at(i).getSide1() && bestMexicanTile.getSide2() == computerHand.at(i).getSide2()) || (bestMexicanTile.getSide1() == computerHand.at(i).getSide2() && bestMexicanTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					break;
				}
			}
			cout << "The computer played ";
			bestMexicanTile.Display();
			cout << " on the mexican train because it is the largest playable tile in hand.";
			return;
		}
	}
	//Trying to play the largest non-double tile on the mexican train
	else if (bestMexicanTile.getSide1() > -1)
	{
		mexicanTrain.push_back(bestMexicanTile);
		mexicanOrphan = false;
		for (int i = 0; i < computerHand.size(); i++)
		{
			if ((bestMexicanTile.getSide1() == computerHand.at(i).getSide1() && bestMexicanTile.getSide2() == computerHand.at(i).getSide2()) || (bestMexicanTile.getSide1() == computerHand.at(i).getSide2() && bestMexicanTile.getSide2() == computerHand.at(i).getSide1()))
			{
				removeTile(i);
				break;
			}
		}
		cout << "The computer played ";
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
			if (drawTile.getSide1() == computerTrain.back().getSide1())
			{
				humanTrain.push_back(humanDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				humanOrphan = true;
				needDraw = true;
				drawTile.swapSides();
				computerTrain.push_back(drawTile);
				computerMarked = false;
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the computer train.";
				return;
			}
			else if (drawTile.getSide2() == computerTrain.back().getSide1())
			{
				humanTrain.push_back(humanDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				humanOrphan = true;
				needDraw = true;
				computerTrain.push_back(drawTile);
				computerMarked = false;
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the computer train.";
				return;
			}
		}
		if (mexicanEligible)
		{
			//Trying to play that drawn tile on the mexican train
			if (drawTile.getSide1() == mexicanTrain.back().getSide2())
			{
				humanTrain.push_back(humanDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				humanOrphan = true;
				needDraw = true;
				mexicanTrain.push_back(drawTile);
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the mexican train.";
				return;
			}
			else if (drawTile.getSide2() == mexicanTrain.back().getSide2())
			{
				humanTrain.push_back(humanDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				humanOrphan = true;
				needDraw = true;
				drawTile.swapSides();
				mexicanTrain.push_back(drawTile);
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the mexican train.";
				return;
			}
		}
		if (humanEligible)
		{
			//Trying to play that drawn tile on the human train
			if (drawTile.getSide1() == humanTrain.back().getSide2())
			{
				humanTrain.push_back(humanDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				needDraw = true;
				humanTrain.push_back(drawTile);
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the human train.";
				return;
			}
			else if (drawTile.getSide2() == humanTrain.back().getSide2())
			{
				humanTrain.push_back(humanDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				needDraw = true;
				drawTile.swapSides();
				humanTrain.push_back(drawTile);
				cout << "The computer played ";
				humanDoubleTile.Display();
				cout << " on the human train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the human train.";
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
			if (drawTile.getSide1() == computerTrain.back().getSide1())
			{
				computerTrain.push_back(computerDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				needDraw = true;
				drawTile.swapSides();
				computerTrain.push_back(drawTile);
				computerMarked = false;
				cout << "The computer played ";
				computerDoubleTile.Display();
				cout << " on the computer train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the computer train.";
				return;
			}
			else if (drawTile.getSide2() == computerTrain.back().getSide1())
			{
				computerTrain.push_back(computerDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				needDraw = true;
				computerTrain.push_back(drawTile);
				computerMarked = false;
				cout << "The computer played ";
				computerDoubleTile.Display();
				cout << " on the computer train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the computer train.";
				return;
			}
		}
		if (mexicanEligible)
		{
			//Trying to play that drawn tile on the mexican train
			if (drawTile.getSide1() == mexicanTrain.back().getSide2())
			{
				computerTrain.push_back(computerDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				computerOrphan = true;
				computerMarked = false;
				needDraw = true;
				mexicanTrain.push_back(drawTile);
				cout << "The computer played ";
				computerDoubleTile.Display();
				cout << " on the computer train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the mexican train.";
				return;
			}
			else if (drawTile.getSide2() == mexicanTrain.back().getSide2())
			{
				computerTrain.push_back(computerDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				computerOrphan = true;
				computerMarked = false;
				needDraw = true;
				drawTile.swapSides();
				mexicanTrain.push_back(drawTile);
				cout << "The computer played ";
				computerDoubleTile.Display();
				cout << " on the computer train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the mexican train.";
				return;
			}
		}
		if (humanEligible)
		{
			//Trying to play that drawn tile on the human train
			if (drawTile.getSide1() == humanTrain.back().getSide2())
			{
				computerTrain.push_back(computerDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				computerOrphan = true;
				computerMarked = false;
				needDraw = true;
				humanTrain.push_back(drawTile);
				cout << "The computer played ";
				computerDoubleTile.Display();
				cout << " on the computer train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the human train.";
				return;
			}
			else if (drawTile.getSide2() == humanTrain.back().getSide2())
			{
				computerTrain.push_back(computerDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				computerOrphan = true;
				computerMarked = false;
				needDraw = true;
				drawTile.swapSides();
				humanTrain.push_back(drawTile);
				cout << "The computer played ";
				computerDoubleTile.Display();
				cout << " on the computer train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the human train.";
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
			if (drawTile.getSide1() == computerTrain.back().getSide1())
			{
				mexicanTrain.push_back(mexicanDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				mexicanOrphan = true;
				needDraw = true;
				drawTile.swapSides();
				computerTrain.push_back(drawTile);
				computerMarked = false;
				cout << "The computer played ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the computer train.";
				return;
			}
			else if (drawTile.getSide2() == computerTrain.back().getSide1())
			{
				mexicanTrain.push_back(mexicanDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				mexicanOrphan = true;
				needDraw = true;
				computerTrain.push_back(drawTile);
				computerMarked = false;
				cout << "The computer played ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the computer train.";
				return;
			}
		}
		if (mexicanEligible)
		{
			//Trying to play that drawn tile on the mexican train
			if (drawTile.getSide1() == mexicanTrain.back().getSide2())
			{
				mexicanTrain.push_back(mexicanDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				needDraw = true;
				mexicanTrain.push_back(drawTile);
				cout << "The computer played ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the mexican train.";
				return;
			}
			else if (drawTile.getSide2() == mexicanTrain.back().getSide2())
			{
				mexicanTrain.push_back(mexicanDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				needDraw = true;
				drawTile.swapSides();
				mexicanTrain.push_back(drawTile);
				cout << "The computer played ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the mexican train.";
				return;
			}
		}
		if (humanEligible)
		{
			//Trying to play that drawn tile on the human train
			if (drawTile.getSide1() == humanTrain.back().getSide2())
			{
				mexicanTrain.push_back(mexicanDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				mexicanOrphan = true;
				needDraw = true;
				humanTrain.push_back(drawTile);
				cout << "The computer played ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the human train.";
				return;
			}
			else if (drawTile.getSide2() == humanTrain.back().getSide2())
			{
				mexicanTrain.push_back(mexicanDoubleTile);
				for (int i = 0; i < computerHand.size(); i++)
				{
					if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
					{
						removeTile(i);
						break;
					}
				}
				mexicanOrphan = true;
				needDraw = true;
				drawTile.swapSides();
				humanTrain.push_back(drawTile);
				cout << "The computer played ";
				mexicanDoubleTile.Display();
				cout << " on the mexican train and had to draw ";
				drawTile.Display();
				cout << " from the boneyard and was able to play it on the human train.";
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
			humanTrain.push_back(humanDoubleTile);
			for (int i = 0; i < computerHand.size(); i++)
			{
				if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					break;
				}
			}
			drawToHand(drawTile);
			needDraw = true;
			cout << "The computer played ";
			humanDoubleTile.Display();
			cout << " on the human train and had to draw but was unable to play the drawn tile.";
			computerMarked = true;
			return;
		}	
		//Trying to play a double on the computer train
		if (computerDoubleTile.getSide1() > -1)
		{
			computerTrain.push_back(computerDoubleTile);
			for (int i = 0; i < computerHand.size(); i++)
			{
				if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					break;
				}
			}
			computerOrphan = true;
			drawToHand(drawTile);
			needDraw = true;
			cout << "The computer played ";
			computerDoubleTile.Display();
			cout << " on the computer train and had to draw but was unable to play the drawn tile.";
			computerMarked = true;
			return;
		}
		//Trying to play a double on the mexican train
		if (mexicanDoubleTile.getSide1() > -1)
		{
			mexicanTrain.push_back(mexicanDoubleTile);
			for (int i = 0; i < computerHand.size(); i++)
			{
				if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					break;
				}
			}
			mexicanOrphan = true;
			drawToHand(drawTile);
			needDraw = true;
			cout << "The computer played ";
			mexicanDoubleTile.Display();
			cout << " on the mexican train and had to draw but was unable to play the drawn tile.";
			computerMarked = true;
			return;
		}
	}
	//The boneyard is empty so no tile can be drawn after playing a double
	else
	{
		//Trying to play a double on the human train
		if (humanDoubleTile.getSide1() > -1)
		{
			humanTrain.push_back(humanDoubleTile);
			for (int i = 0; i < computerHand.size(); i++)
			{
				if ((humanDoubleTile.getSide1() == computerHand.at(i).getSide1() && humanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (humanDoubleTile.getSide1() == computerHand.at(i).getSide2() && humanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					break;
				}
			}
			humanOrphan = true;
			cout << "The computer played ";
			humanDoubleTile.Display();
			cout << " on the human train and could not draw because the boneyard was empty.";
			return;
		}
		//Trying to play a double on the computer train
		if (computerDoubleTile.getSide1() > -1)
		{
			computerTrain.push_back(computerDoubleTile);
			for (int i = 0; i < computerHand.size(); i++)
			{
				if ((computerDoubleTile.getSide1() == computerHand.at(i).getSide1() && computerDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (computerDoubleTile.getSide1() == computerHand.at(i).getSide2() && computerDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					break;
				}
			}
			computerOrphan = true;
			cout << "The computer played ";
			computerDoubleTile.Display();
			cout << " on the computer train and could not draw because the boneyard was empty.";
			return;
		}
		//Trying to play a double on the mexican train
		if (mexicanDoubleTile.getSide1() > -1)
		{
			mexicanTrain.push_back(mexicanDoubleTile);
			for (int i = 0; i < computerHand.size(); i++)
			{
				if ((mexicanDoubleTile.getSide1() == computerHand.at(i).getSide1() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide2()) || (mexicanDoubleTile.getSide1() == computerHand.at(i).getSide2() && mexicanDoubleTile.getSide2() == computerHand.at(i).getSide1()))
				{
					removeTile(i);
					break;
				}
			}
			mexicanOrphan = true;
			cout << "The computer played ";
			mexicanDoubleTile.Display();
			cout << " on the mexican train and could not draw because the boneyard was empty.";
			return;
		}
	}
}