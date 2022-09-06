#include "Game.h"
#include "Deck.h"
#include "Round.h"
#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;

//default constructor
Round::Round()
{
	isHumanTurn = true;
	roundNum = 1;
	isMexicanTrainStarted = false;
	isHumanTrainMarked = false;
	isComputerTrainMarked = false;
	isHumanEligible = false;
	isComputerEligible = false;
	isHumanOrphan = false;
	isComputerOrphan = false;
	isMexicanOrphan = false;
	doublePlayed = false;
	needDraw = false;
	boneyard.createDeck();
	boneyard.shuffle();
	tilesPlaced = 0;
	winner = 0;
}

//parameterized constructor
Round::Round(int round)
{
	isHumanTurn = true;
	roundNum = round;
	isMexicanTrainStarted = false;
	isHumanTrainMarked = false;
	isComputerTrainMarked = false;
	isHumanEligible = false;
	isComputerEligible = false;
	isHumanOrphan = false;
	isComputerOrphan = false;
	isMexicanOrphan = false;
	doublePlayed = false;
	needDraw = false;
	boneyard.createDeck();
	boneyard.shuffle();
	tilesPlaced = 0;
	winner = 0;
}

//parameterized constructor for loading game
Round::Round(int round, int cpuScore, vector<Tile> cpuHand, vector<Tile> cpuTrain, bool cpuMarker, int humScore, vector<Tile> humHand, vector<Tile> humTrain, bool humMarker, 
					vector<Tile> mexTrain, vector<Tile> deck, bool humanTurn, bool cpuOrphan, bool humOrphan, bool mexOrphan)
{
	roundNum = round;
	compScore = cpuScore;
	for (int i = 0; i < cpuHand.size(); i++)
	{
		computerPlayer.drawToHand(cpuHand.at(i));
	}
	for (int i = cpuTrain.size() - 1; i >= 0; i--)
	{
		computerTrain.push_back(cpuTrain.at(i));
	}
	isComputerTrainMarked = cpuMarker;

	humanScore = humScore;
	for (int i = 0; i < humHand.size(); i++)
	{
		humanPlayer.drawToHand(humHand.at(i));
	}
	humanTrain = humTrain;
	isHumanTrainMarked = humMarker;
	if (mexTrain.size() > 0)
	{
		isMexicanTrainStarted = true;
		mexicanTrain.push_back(humanTrain.at(0));
		for (int i = 0; i < mexTrain.size(); i++)
		{
			mexicanTrain.push_back(mexTrain.at(i));
		}
	}
	else
	{
		isMexicanTrainStarted = false;
		mexicanTrain.push_back(humanTrain.at(0));
	}
	for (int i = 0; i < deck.size(); i++)
	{
		boneyard.addToDeck(deck.at(i));
	}
	isHumanTurn = humanTurn;
	isHumanEligible = false;
	isComputerEligible = false;
	isHumanOrphan = humOrphan;
	isComputerOrphan = cpuOrphan;
	isMexicanOrphan = mexOrphan;
	doublePlayed = false;
	needDraw = false;
	tilesPlaced = 0;
	winner = 0;
}

/* *********************************************************************
Function Name: setIsHumanTurn
Purpose: Allows the game class to set whose turn it is when making the round object
Parameters:
			bool HumanTurn. Holds true if its the players turn and false if it's the 
			computers turn.
Return Value: none
Algorithm:
			1)Sets the parameter value to the value held in round
Assistance Received: none
********************************************************************* */
void Round::setIsHumanTurn(bool HumanTurn)
{
	isHumanTurn = HumanTurn;
}

/* *********************************************************************
Function Name: coinflip
Purpose: Flips a coin to see who goes first if the scores are tied at the
			beginning of a new round
Parameters:
			none
Return Value: none
Algorithm:
			1)Takes in the users choice of 1 for heads or 2 for tails
			2)Creates a random number either 1 or 2
			3)If the player calls it right they go first otherwise the computer does
Assistance Received: none
********************************************************************* */
void Round::coinFlip()
{
	cout << "Flipping a coin to see who goes first!" << endl;
	//holds the players choice of 1 for heads and 2 for tails
	int coinChoice = 0;
	while (coinChoice != 1 && coinChoice != 2)
	{
		cout << "Choose 1 for heads or 2 for tails" << endl;
		cin >> coinChoice;
	}
	srand(time(NULL));
	//Holds the value of the random number generated for the coin flip
	int flipResult;
	
	//Creates a random number either 1 for heads or 2 for tails
	flipResult = rand() % 2 + 1;
	
	//Compares the players coinflip choice and the number randomly generated
	//If equal player starts, if not equal computer starts
	if (flipResult == coinChoice)
	{
		isHumanTurn = true;
		if (flipResult == 1)
		{
			cout << "It was heads, you go first!" << endl << endl << endl;
		}
		else
		{
			cout << "It was tails, you go first!" << endl << endl << endl;
		}
	}
	else
	{
		isHumanTurn = false;
		if (flipResult == 1)
		{
			cout << "It was heads, the computer goes first" << endl << endl << endl;
		}
		else
		{
			cout << "It was tails, the computer goes first" << endl << endl << endl;
		}
	}
}

/* *********************************************************************
Function Name: engine
Purpose: Gets the engine tile depending on which round it currently is
Parameters:
			none
Return Value: The engine tile that will be used for that round, a tile object
Algorithm:
			1)Uses a switch statement which uses the round number mod 10
			2)Round 1 engine pip is 9, 2 is 8...10 is 0 then 11 is back to 9
Assistance Received: none
********************************************************************* */
Tile Round::engine()
{
	//Declares enginePips which is the number of pips the engine tile will have
	int enginePips = 0;

	//Switch statement that takes the round number and mod 10's it to know how many pips the engine tile should have
	switch (roundNum % 10)
	{
	case 1:
		enginePips = 9;
		break;
	case 2:
		enginePips = 8;
		break;
	case 3:
		enginePips = 7;
		break;
	case 4:
		enginePips = 6;
		break;
	case 5:
		enginePips = 5;
		break;
	case 6:
		enginePips = 4;
		break;
	case 7:
		enginePips = 3;
		break;
	case 8:
		enginePips = 2;
		break;
	case 9:
		enginePips = 1;
		break;
	case 0:
		enginePips = 0;
		break;
	}
	return Tile(enginePips, enginePips);
}

/* *********************************************************************
Function Name: addEngine
Purpose: Adds the engine to each of the trains so they know what tiles are playable on them
			Removes the engine tile from the boneyard since it is already being used
Parameters:
			Tile engine. The tile that is used for the engine for that round.
Return Value: none
Algorithm:
			1)Adds the engine tile to the back of each of the trains
			2)Removes the engine tile from the boneyard
Assistance Received: none
********************************************************************* */
void Round::addEngine(Tile engine)
{
	humanTrain.push_back(engine);
	computerTrain.push_back(engine);
	mexicanTrain.push_back(engine);
	boneyard.removeEngine(engine);
}

/* *********************************************************************
Function Name: humanDeal
Purpose: Deals the human player a full hand of 16 tiles
Parameters:
			none
Return Value: none
Algorithm:
			1)Creates an int of size 16 which is the amount of tiles in the opening hand
			2)Stores the address of humanPlayer to a pointer to the player class
			3)Puts the top 16 tiles from the boneyard into the human players hand
Assistance Received: none
********************************************************************* */
void Round::humanDeal()
{
	//Assigns the human hand size to 16 which is a full hand at the beginning of a game
	int fullHand = 16;
	//Stores address of humanPlayer to player
	player = &humanPlayer;

	for (int i = 0; i < fullHand; i++)
	{
		player->drawToHand(boneyard.draw());
	}
}

/* *********************************************************************
Function Name: computerDeal
Purpose: Deals the computer player a full hand of 16 tiles
Parameters:
			none
Return Value: none
Algorithm:
			1)Creates an int of size 16 which is the amount of tiles in the opening hand
			2)Stores the address of computerPlayer to a pointer to the player class
			3)Puts the top 16 tiles from the boneyard into the computer players hand
Assistance Received: none
********************************************************************* */
void Round::computerDeal()
{
	//Assigns the computer hand size to 16 which is a full hand at the beginning of a game
	int fullHand = 16;
	//Stores address of computerPlayer to player
	player = &computerPlayer;

	for (int i = 0; i < fullHand; i++)
	{
		player->drawToHand(boneyard.draw());
	}
}


/* *********************************************************************
Function Name: play
Purpose: Handles the actual gameplay such as asking for help and playing tiles
Parameters:
			none
Return Value: none
Algorithm:
			1)Stores the address of whoevers turn it is into the player pointer
			2)Displays the table which is the trains, hands, and boneyard
			3)Shows the eligibility of each of the trains
			4)Has the player select what they want to do
			5)Will either save the game, play a tile, ask for help, or quit the game
			6)Checks if the player has any playable tiles
			7)Makes them draw if not
			8)Has the human select which tile to play
			9)Has the human select which train to play on
			10)If a double is placed the turn doesn't swap so another tile can be played
			11)Calls the computers tile selecting algorithm for the computers turn or if human asks for it
			12)Checks if either player is out of tiles in hand to end the game
			13)Checks if the boneyard is empty and neither player can play
Assistance Received: none
********************************************************************* */
void Round::play()
{
	//If statement for whose turn it is
	if (isHumanTurn)
	{
		//Assigns address of humanPlayer to player
		player = &humanPlayer;
	}
	else
	{
		//Assigns address of computerPlayer to player
		player = &computerPlayer;
	}
	//Displays all table information
	displayTable();
	//Checks if the human player played a double, if not changes train eligibility and updates the pips at the end of the trains
	if (!doublePlayed)
	{
		setEligibility();
		updateConnectingPips();
	}
	//Outputs whose turn it is
	if (isHumanTurn)
	{
		cout << "\t\tYour Turn" << endl;
	}
	else
	{
		cout << "\t\tComputer's Turn" << endl;
	}
	//Outputs which trains are eligible to be played on
	showEligibility();
	//Declares selectedTile which is the tile the human player is trying to play
	Tile selectedTile;
	//Declares option which is what the human player wants to do at the beginning of their turn
	int option = 2;
	//Only displays the options if the human player has not already played a double
	if (tilesPlaced < 1)
	{
		cout << "Select an option: " << endl;
		cout << "\t 1. Save the Game" << endl;
		cout << "\t 2. Make a Move" << endl;
		cout << "\t 3. Ask for help(human player only)" << endl;
		cout << "\t 4. Quit the game" << endl;
		cin >> option;
	}
	if (option == 1)
	{
		saveGame();
	}
	else if (option == 2)
	{
		if (isHumanTurn)
		{
			for ( ; ; )
			{
				//Checks if the player has any playable tiles
				if (!hasPlayableTile())
				{
					//Checks if the boneyard is empty 
					if (!boneyard.isBoneyardEmpty())
					{
						cout << "No playable Tile, drawing from the boneyard" << endl;
						//draws from the boneyard to the human players hand
						player->drawToHand(boneyard.draw());
						displayTable();
						//checks if the player still has no playable tiles even after drawing
						if (!hasPlayableTile())
						{
							cout << "Placing marker and passing turn" << endl;
							//Marks the human train
							isHumanTrainMarked = true;
							//Changes the turn
							isHumanTurn = false;
							//Resets tilesPlaced to 0 
							tilesPlaced = 0;
							break;
						} 
					}
					//If the boneyard is empty there's nothing for the player to do
					else
					{
						cout << "No playable tiles and boneyard is empty, passing turn and placing marker" << endl;
						//Marks the human train
						isHumanTrainMarked = true;
						break;
					}
				}
				//The int for which number tile the player is selecting
				int tileSelect;
				cout << "Select which tile you would like you place: ";
				cin >> tileSelect;
				//Checks if the number the user put in is not valid
				if (tileSelect < 1 || tileSelect > player->getHandSize())
				{
					cout << "invalid tile selection" << endl;
					continue;
				}
				cout << "Select which eligible train you would like to play on:" << endl;
				//Checks if the human train is eligible and if it is lets the player know that
				if (isHumanEligible)
				{
					cout << "Press 1 for human train" << endl;
				}
				//Checks if the computer train is eligible and if it is lets the player know that
				if (isComputerEligible)
				{
					cout << "Press 2 for computer train" << endl;
				}
				//Checks if the mexican train is started
				if (isMexicanTrainStarted)
				{
					//Checks if the mexican train is eligible and if it is lets the player know that
					if (isMexicanEligible)
					{
						cout << "Press 3 for Mexican train" << endl;
					}
				}
				//Let's the player start the mexican train if it's not started yet
				else
				{
					cout << "Press 3 to Start Mexican Train" << endl;
				}
				//Declares trainSelect which is an int for which train the player wants to play on
				int trainSelect;
				cin >> trainSelect;
				//The player selects the human train
				if (trainSelect == 1)
				{
					//Checks if the human train is not eligible
					if (!isHumanEligible)
					{
						cout << "Not an eligible Train" << endl;
						continue;
					}
					else
					{
						//checks if the player plays a double
						if (humanConnectingPip == player->getTile(tileSelect - 1).getSide1() && humanConnectingPip == player->getTile(tileSelect - 1).getSide2())
						{
							//checks if its the first tile they'd played that turn
							if (tilesPlaced == 0)
							{
								humanTrain.push_back(player->getTile(tileSelect - 1));
								player->removeTile(tileSelect - 1);
								isHumanTrainMarked = false;
								tilesPlaced++;
								doublePlayed = true;
								isHumanOrphan = true;
								break;
							}
							//checks if its the second tile they'd played that turn
							else if (tilesPlaced == 1)
							{
								Tile temp = player->getTile(tileSelect - 1);
								player->removeTile(tileSelect - 1);
								if (hasPlayableTile())
								{
									humanTrain.push_back(temp);
									isHumanTrainMarked = false;
									tilesPlaced++;
									doublePlayed = true;
									isHumanOrphan = true;
									break;
								}
								//Can't play two doubles if you don't have an immediate followup nondouble
								else
								{
									cout << "Don't have anything to play after the second double tile" << endl;
									player->drawToHand(temp);
									continue;
								}
							}
							else
							{
								cout << "Can't play three doubles in one turn" << endl;
								continue;
							}
						}
						//Checks if side1 connects to the end of the human train
						else if (humanConnectingPip == player->getTile(tileSelect - 1).getSide1())
						{
							humanTrain.push_back(player->getTile(tileSelect - 1));
							player->removeTile(tileSelect - 1);
							isHumanTrainMarked = false;
							isHumanOrphan = false;
							doublePlayed = false;
							break;
						}
						//Checks if side2 connects to the end of the human train meaning the sides must be swapped 
						else if (humanConnectingPip == player->getTile(tileSelect - 1).getSide2())
						{
							Tile selectedTile = player->getTile(tileSelect - 1);
							selectedTile.swapSides();
							humanTrain.push_back(selectedTile);
							player->removeTile(tileSelect - 1);
							isHumanTrainMarked = false;
							isHumanOrphan = false;
							doublePlayed = false;
							break;
						}
						//If the tile does not connect to the end of the human train
						else
						{
							cout << "That tile does not match the pips of the human train" << endl;
							continue;
						}
					}
				
				}
				//The player selects the computer train
				else if (trainSelect == 2)
				{
					//Checks if the computer train is not eligible
					if (!isComputerEligible)
					{
						cout << "Not an eligible Train" << endl;
						continue;
					}
					else
					{
						//checks if the player plays a double
						if (computerConnectingPip == player->getTile(tileSelect - 1).getSide1() && computerConnectingPip == player->getTile(tileSelect - 1).getSide2())
						{
							//checks if its the first tile they'd played that turn
							if (tilesPlaced == 0)
							{
								computerTrain.push_back(player->getTile(tileSelect - 1));
								player->removeTile(tileSelect - 1);
								tilesPlaced++;
								doublePlayed = true;
								if (hasPlayableTile())
								{
									isComputerOrphan = true;
								}
								break;
							}
							//checks if its the second tile they'd played that turn
							else if (tilesPlaced == 1)
							{
								Tile temp = player->getTile(tileSelect - 1);
								player->removeTile(tileSelect - 1);
								if (hasPlayableTile())
								{
									computerTrain.push_back(temp);
									tilesPlaced++;
									doublePlayed = true;
									isComputerOrphan = true;
									break;
								}
								//Can't play two doubles if you don't have an immediate followup nondouble
								else
								{
									cout << "Don't have anything to play after the second double tile" << endl;
									player->drawToHand(temp);
									continue;
								}
							}
						}
						//Checks if side1 connects to the end of the computer train meaning the sides must be swapped 
						else if (computerConnectingPip == player->getTile(tileSelect - 1).getSide1())
						{
							Tile selectedTile = player->getTile(tileSelect - 1);
							selectedTile.swapSides();
							computerTrain.push_back(selectedTile);
							player->removeTile(tileSelect - 1);
							isComputerOrphan = false;
							doublePlayed = false;
							break;
						}
						//Checks if side2 connects to the end of the computer train
						else if (computerConnectingPip == player->getTile(tileSelect - 1).getSide2())
						{
							computerTrain.push_back(player->getTile(tileSelect - 1));
							player->removeTile(tileSelect - 1);
							isComputerOrphan = false;
							doublePlayed = false;
							break;
						}
						//If the tile does not connect to the end of the computer train
						else
						{
							cout << "That tile does not match the pips of the computer train" << endl;
							continue;
						}
					} 
				}
				//The player selects the mexican train
				else if (trainSelect == 3)
				{
				//checks if the player plays a double
					if (mexicanConnectingPip == player->getTile(tileSelect - 1).getSide1() && mexicanConnectingPip == player->getTile(tileSelect - 1).getSide2())
					{
						{
							//checks if its the first tile they'd played that turn
							if (tilesPlaced == 0)
							{
								mexicanTrain.push_back(player->getTile(tileSelect - 1));
								player->removeTile(tileSelect - 1);
								tilesPlaced++;
								doublePlayed = true;
								if (hasPlayableTile())
								{
									isMexicanOrphan = true;
								}
								break;
							}
							//checks if its the second tile they'd played that turn
							else if (tilesPlaced == 1)
							{
								Tile temp = player->getTile(tileSelect - 1);
								player->removeTile(tileSelect - 1);
								if (hasPlayableTile())
								{
									mexicanTrain.push_back(temp);
									tilesPlaced++;
									doublePlayed = true;
									isMexicanOrphan = true;
									break;
								}
								//Can't play two doubles if you don't have an immediate followup nondouble
								else
								{
									cout << "Don't have anything to play after the second double tile" << endl;
									player->drawToHand(temp);
									continue;
								}
							}
						}
					}
					//Checks if side1 connects to the end of the mexican train
					else if (mexicanConnectingPip == player->getTile(tileSelect - 1).getSide1())
					{
						isMexicanTrainStarted = true;
						mexicanTrain.push_back(player->getTile(tileSelect - 1));
						player->removeTile(tileSelect - 1);
						isMexicanOrphan = false;
						doublePlayed = false;
						break;
					}
					//Checks if side2 connects to the end of the mexican train meaning the sides must be swapped 
					else if (mexicanConnectingPip == player->getTile(tileSelect - 1).getSide2())
					{
						isMexicanTrainStarted = true;
						Tile selectedTile = player->getTile(tileSelect - 1);
						selectedTile.swapSides();
						mexicanTrain.push_back(selectedTile);
						player->removeTile(tileSelect - 1);
						isMexicanOrphan = false;
						doublePlayed = false;
						break;
					}
					else
					{
						cout << "That tile does not match the engine tile" << endl;
						continue;
					}
				}
				//If the tile does not connect to the end of the mexican train
				else
				{
					cout << "Not a Train Selected" << endl;
					continue;
				}
			}
			//Swaps the turn and resets tilesPlaced if a double was not played
			if (!doublePlayed)
			{
				tilesPlaced = 0;
				isHumanTurn = false;
			}
		}
		//if its the computers turn
		else
		{
		//checks if the computer has a tile to play
			if (!hasPlayableTile())
			{
				//checks if the boneyard is empty
				if (!boneyard.isBoneyardEmpty())
				{
					cout << "Computer has no playable tile must draw from the boneyard" << endl;
					player->drawToHand(boneyard.draw());
					displayTable();
					//checks if still no playable tile
					if (!hasPlayableTile())
					{
						cout << "Placing marker and passing turn" << endl;
						isComputerTrainMarked = true;
					}
					else
					{
						needDraw = false;
						player->makeDecision(humanTrain, isHumanEligible, computerTrain, isComputerEligible, mexicanTrain, isMexicanEligible, isHumanTrainMarked, isComputerTrainMarked, isHumanOrphan, isComputerOrphan, isMexicanOrphan, needDraw, boneyard.getNextTile());
						cout << endl << endl;
					}
				}
				else
				{
					cout << "Computer has no playable tiles and boneyard is empty, passing turn and placing marker" << endl;
					isComputerTrainMarked = true;
				}
			}
			//if has a playable tile runs the computers tile selecting algorithm
			else
			{
				needDraw = false;
				player->makeDecision(humanTrain, isHumanEligible, computerTrain, isComputerEligible, mexicanTrain, isMexicanEligible, isHumanTrainMarked, isComputerTrainMarked, isHumanOrphan, isComputerOrphan, isMexicanOrphan, needDraw, boneyard.getNextTile());
				cout << endl << endl;
				if (needDraw)
				{
						boneyard.draw();
				}
			}
			needDraw = false;
			isHumanTurn = true;
			if (mexicanTrain.size() > 1)
			{
				isMexicanTrainStarted = true;
			}
		}
		//checks if the humans hand is empty
		if (humanPlayer.getHandSize() == 0)
		{
			winner = 1;
			player = &computerPlayer;
			for (int i = 0; i < player->getHandSize(); i++)
			{
				totalComputerPips += player->getTile(i).getSide1();
				totalComputerPips += player->getTile(i).getSide2();
			}
		}
		//checks if the computers hand is empty
		else if (computerPlayer.getHandSize() == 0)
		{
			winner = 2;
			player = &humanPlayer;
			for (int i = 0; i < player->getHandSize(); i++)
			{
				totalHumanPips += player->getTile(i).getSide1();
				totalHumanPips += player->getTile(i).getSide2();
			}
		}
		//checks if neither player can play and the boneyard is empty
		else if (isComputerTrainMarked && isHumanTrainMarked && boneyard.isBoneyardEmpty())
		{
			winner = 3;
			player = &humanPlayer;
			for (int i = 0; i < player->getHandSize(); i++)
			{
				totalHumanPips += player->getTile(i).getSide1();
				totalHumanPips += player->getTile(i).getSide2();
			}
			player = &computerPlayer;
				for (int i = 0; i < player->getHandSize(); i++)
				{
					totalComputerPips += player->getTile(i).getSide1();
					totalComputerPips += player->getTile(i).getSide2();
				}
		}
		//if the game is not over re-call play
		else
		{
			play();
		}
	}
	//If the user selects help from the computer
	else if (option == 3)
	{
		//if its the humans turn
		if (isHumanTurn)
		{
			//If there's a playable tile in hand runs the computers algorithm to find the best move
			if (hasPlayableTile())
			{
				player->makeDecision(humanTrain, isHumanEligible, computerTrain, isComputerEligible, mexicanTrain, isMexicanEligible, isHumanTrainMarked, isComputerTrainMarked, isHumanOrphan, isComputerOrphan, isMexicanOrphan, needDraw, boneyard.getNextTile());
				cout << endl << endl;
			}
			//lets the player know there are no playable tiles
			else
			{
				cout << "No playable tiles" << endl;
			}
		}
		//if the user tries to make the computer ask for help
		else
		{
			cout << "This is only usable by the human player" << endl;
		}
	}
	//Exits the game
	else if (option == 4)
	{
		exit(0);
	}
}

/* *********************************************************************
Function Name: displayTable
Purpose: Outputs the trains, hands, round number, whose turn, and top boneyard tile
Parameters:
			none
Return Value: none
Algorithm:
			1)Formats and outputs all the information
Assistance Received: none
********************************************************************* */
void Round::displayTable()
{
	//Declares humanHandSize and give it the value of the current size of the human hand
	int humanHandSize = humanPlayer.getHandSize();
	//Declares computerHandSize and give it the value of the current size of the computer hand
	int computerHandSize = computerPlayer.getHandSize();
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t round: " << roundNum << endl;
	cout << "\t\t\t\t\t\t\t\t\t your score: " << humanScore << endl << endl;

	//outputs the numbering for each tile in the human players hand
	for (int i = 0; i < humanHandSize; i++)
	{
		if (i < 9)
		{
			cout <<" " << i+1 << "   ";
		}
		else
		{
			cout << " " << i + 1 << "  ";
		}
	}
	cout << endl;

	//outputs the human players hand
	for (int i = 0; i < humanHandSize; i++)
	{
		humanPlayer.getTile(i).Display();
		cout << "  ";
	}
	cout << endl << endl << endl << endl;

	//Output doubles vertically
	int numOfCompDoubles = 0;
	if (isComputerTrainMarked)
	{
		cout << "  ";
	}
	for (int i = computerTrain.size() - 1; i >= 0; i--)
	{
		if (computerTrain.at(i).getSide1() == computerTrain.at(i).getSide2())
		{
			cout << computerTrain.at(i).getSide1() << " ";
		}
		else
		{
			cout << "    ";
		}
	}
	if (humanTrain.size() > 1)
	{
		for (int i = 1; i < humanTrain.size(); i++)
		{
			if (humanTrain.at(i).getSide1() == humanTrain.at(i).getSide2())
			{
				cout << humanTrain.at(i).getSide1() << " ";
			}
			else
			{
				cout << "    ";
			}
		}
	}
	
	cout << endl;
	//Outputs the M if the computer train is marked
	if (isComputerTrainMarked)
	{
		cout << "M ";
	}
	//Outputs the computers train
	for (int i = computerTrain.size() - 1; i >= 0; i--)
	{
		if (computerTrain.at(i).getSide1() == computerTrain.at(i).getSide2())
		{
			cout << "| ";
			numOfCompDoubles++;
		}
		else
		{
			computerTrain.at(i).Display();
			cout << " ";
		}
		
	}
	//outputs the humans train skipping the first tile because it's the engine
	if (humanTrain.size() > 1)
	{
		for (int i = 1; i < humanTrain.size(); i++)
		{
			if (humanTrain.at(i).getSide1() == humanTrain.at(i).getSide2())
			{
				cout << "| ";
			}
			else
			{
				humanTrain.at(i).Display();
				cout << " ";
			}
		}
		//Outputs the M if the human train is marked
		if (isHumanTrainMarked)
		{
			cout << "M";
		}
	}
	cout << endl;

	if (isComputerTrainMarked)
	{
		cout << "  ";
	}
	for (int i = computerTrain.size() - 1; i >= 0; i--)
	{
		if (computerTrain.at(i).getSide1() == computerTrain.at(i).getSide2())
		{
			cout << computerTrain.at(i).getSide1() << " ";
		}
		else
		{
			cout << "    ";
		}
	}
	if (humanTrain.size() > 1)
	{
		for (int i = 1; i < humanTrain.size(); i++)
		{
			if (humanTrain.at(i).getSide1() == humanTrain.at(i).getSide2())
			{
				cout << humanTrain.at(i).getSide2() << " ";
			}
			else
			{
				cout << "    ";
			}
		}
	}
	cout << endl;


	//Checks if the mexican train is started
	if (isMexicanTrainStarted)
	{
		cout << "  ";
		//Needs an extra space if the computer train is marked
		if (isComputerTrainMarked)
		{
			cout << "  ";
		}
		//Slides it over for how long the computer train is
		for (int i = (4 + numOfCompDoubles); i < (computerTrain.size()) * 4; i++)
		{
			cout << " ";
		}
		//Outputs the mexican train
		for (int i = 1; i < mexicanTrain.size(); i++)
		{
			mexicanTrain.at(i).Display();
			cout << " ";
		}
	}
	cout << endl;

	cout << "\t\t\t\t\t\t\t\t\tBoneyard next Tile: "; 
	//Prints out none if the boneyard is empty
	if (boneyard.isBoneyardEmpty())
	{
		cout << "none";
	}
	//Prints out the top tile in the boneyard
	else
	{
		boneyard.getNextTile().Display();
	}
	cout << endl << endl << endl;

	//Prints out the computer players hand
	for (int i = 0; i < computerHandSize; i++)
	{
		computerPlayer.getTile(i).Display();
		cout << "  ";
	}
	cout << endl;

	cout << "\t\t\t\t\t\t\t\t\t computer score: " << compScore << endl;

	cout << endl << endl;
}

/* *********************************************************************
Function Name: getHumanPips
Purpose: Gets the total Human pips to add to the human's score
Parameters:
			none
Return Value: totalHumanPips, an int
Algorithm:
			1)Returns the totalHumanPips
Assistance Received: none
********************************************************************* */
int Round::getHumanPips()
{
	return totalHumanPips;
}

/* *********************************************************************
Function Name: getComputerPips
Purpose: Gets the total computer pips to add to the computer's score
Parameters:
			none
Return Value: totalComputerPips, an int
Algorithm:
			1)Returns the totalComputerPips
Assistance Received: none
********************************************************************* */
int Round::getComputerPips()
{
	return totalComputerPips;
}

/* *********************************************************************
Function Name: setHumanScore
Purpose: Sets the players score for when starting a new round
Parameters:
			hScore. An int that is the players total score
Return Value: none
Algorithm:
			1)Sets the humans score
Assistance Received: none
********************************************************************* */
void Round::setHumanScore(int hScore)
{
	humanScore = hScore;
}

/* *********************************************************************
Function Name: setCompScore
Purpose: Sets the computers score for when starting a new round
Parameters:
			cScore. An int that is the computers total score
Return Value: none
Algorithm:
			1)Sets the computers score
Assistance Received: none
********************************************************************* */
void Round::setCompScore(int cScore)
{
	compScore = cScore;
}

/* *********************************************************************
Function Name: setEligibility
Purpose: Checks which trains are eligible to be played on
Parameters:
			none
Return Value: none
Algorithm:
			1)Sets all eligibility to false
			2)Checks if there are any trains with an orphan double
			3)Checks which trains are playable on for the human or computer
Assistance Received: none
********************************************************************* */
void Round::setEligibility()
{
	isHumanEligible = false;
	isComputerEligible = false;
	isMexicanEligible = false;
	if (isHumanOrphan || isComputerOrphan || isMexicanOrphan)
	{
		if (isHumanOrphan)
		{
			isHumanEligible = true;
		}
		if (isComputerOrphan)
		{
			isComputerEligible = true;
		}
		if (isMexicanOrphan)
		{
			isMexicanEligible = true;
		}
	}
	else
	{
		if (isHumanTurn)
		{
			isHumanEligible = true;
			if (isComputerTrainMarked)
			{
				isComputerEligible = true;
			}
			isMexicanEligible = true;
		}
		else
		{
			if (isHumanTrainMarked)
			{
				isHumanEligible = true;
			}
			isComputerEligible = true;
			isMexicanEligible = true;
		}
	}
	cout << endl;
}

/* *********************************************************************
Function Name: showEligibility
Purpose: Let the player know which trains are eligible to be played on
Parameters:
			none
Return Value: none
Algorithm:
			1)Checks if the train is eligible then outputs the train if it is
Assistance Received: none
********************************************************************* */
void Round::showEligibility()
{
	cout << "Eligible trains: " << endl;
	if (isHumanEligible)
	{
		cout << "Human Train" << endl;
	}
	if (isComputerEligible)
	{
		cout << "Computer Train" << endl;
	}
	if (isMexicanEligible)
	{
		cout << "Mexican Train" << endl;
	}
	cout << endl;
}
/* *********************************************************************
Function Name: updateConnectingPips
Purpose: updates the amount of pips at the end of each train to know what can connect to it
Parameters:
			none
Return Value: none
Algorithm:
			1)Sets the trains connecting pip to the side at the end of each train
Assistance Received: none
********************************************************************* */

void Round::updateConnectingPips()
{
	humanConnectingPip = humanTrain.back().getSide2();
	computerConnectingPip = computerTrain.back().getSide1();
	mexicanConnectingPip = mexicanTrain.back().getSide2();
}

/* *********************************************************************
Function Name: hasPlayableTile
Purpose: Checks if the human or computer player has any tiles that are playable
Parameters:
			none
Return Value: True or false whether or not the human or computer has a tile they can play or if they need to draw
Algorithm:
			1)Checks the eligible trains and the tiles in hand for whether or not they can be played
Assistance Received: none
********************************************************************* */
bool Round::hasPlayableTile()
{
	for(int i = 0; i < player->getHandSize(); i++)
	{
		if (isHumanEligible)
		{
			if (humanConnectingPip == player->getTile(i).getSide1() || humanConnectingPip == player->getTile(i).getSide2())
			{
				return true;
			}
		}
		if (isComputerEligible)
		{
			if (computerConnectingPip == player->getTile(i).getSide1() || computerConnectingPip == player->getTile(i).getSide2())
			{
				return true;
			}
		}
		if (isMexicanEligible)
		{
			if (mexicanConnectingPip == player->getTile(i).getSide1() || mexicanConnectingPip == player->getTile(i).getSide2())
			{
				return true;
			}
		}
		if (!isMexicanTrainStarted)
		{
			if (mexicanConnectingPip == player->getTile(i).getSide1() || mexicanConnectingPip == player->getTile(i).getSide2())
			{
				return true;
			}
		}
	}
	return false;
}

/* *********************************************************************
Function Name: getWinner
Purpose: Allows the game class to see if the game was won by anybody
Parameters:
			none
Return Value: winner, an int, 1 if the human won, 2 if the computer won, 3 if it was a tie, 0 if there is no winner yet
Algorithm:
			1)returns the winner variable
Assistance Received: none
********************************************************************* */
int Round::getWinner()
{
	return winner;
}
/* *********************************************************************
Function Name: saveGame
Purpose: Allows the game to be saved and continued later
Parameters:
			none
Return Value: no
Algorithm:
			1)creates a text file with all the neccesary information in it
Assistance Received: none
********************************************************************* */

void Round::saveGame()
{
	//True if what the user put in for a name is acceptable
	bool goodName = false;
	//The position of the period so if can find if .txt is in the name
	int periodPosition = 0;
	string fileName;
	while (!goodName)
	{
		cout << "Please write a name for the file(do not use spaces and add \".txt\" to the end): ";
		cin >> fileName;
 		cout << endl;
		periodPosition = fileName.find(".");
		if (periodPosition == -1)
		{
			cout << "Save name does not have .txt at the end" << endl;
		}
		else if (fileName.substr(periodPosition) != ".txt")
		{
			cout << "Save name does not have .txt at the end" << endl;
		}
		else
		{
			goodName = true;
		}
	}
	

	ofstream saveFile(fileName);

	saveFile << "Round: " << roundNum << endl << endl;
	saveFile << "Computer:" << endl;
	saveFile << "\tScore: " << compScore << endl;
	saveFile << "\tHand:";
	player = &computerPlayer;
	for (int i = 0; i < player->getHandSize(); i++)
	{
		saveFile << " " << player->getTile(i).getSide1() << "-" << player->getTile(i).getSide2();
	}
	saveFile << endl;
	saveFile << "\tTrain:";
	if (isComputerTrainMarked)
	{
		saveFile << " M";
	}
	for (int i = computerTrain.size() - 1; i >= 0; i--)
	{
		saveFile << " " << computerTrain.at(i).getSide1() << "-" << computerTrain.at(i).getSide2();
	}
	saveFile << endl << endl;

	player = &humanPlayer;
	saveFile << "Human:" << endl;
	saveFile << "\tScore: " << humanScore << endl;
	for (int i = 0; i < player->getHandSize(); i++)
	{
		saveFile << " " << player->getTile(i).getSide1() << "-" << player->getTile(i).getSide2();
	}
	saveFile << endl;
	saveFile << "\tTrain:";
	for (int i = 0; i < humanTrain.size(); i++)
	{
		saveFile << " " << humanTrain.at(i).getSide1() << "-" << humanTrain.at(i).getSide2();
	}
	if (isHumanTrainMarked)
	{
		saveFile << " M";
	}
	saveFile << endl << endl;
	
	saveFile << "Mexican Train:";
	for (int i = 1; i < mexicanTrain.size(); i++)
	{
		saveFile << " " << mexicanTrain.at(i).getSide1() << "-" << mexicanTrain.at(i).getSide2();
	}
	saveFile << endl << endl;

	saveFile << "Boneyard:";
	for (int i = 0; i < boneyard.getBoneyardSize(); i++)
	{
		saveFile << " " << boneyard.getTileAt(i).getSide1() << "-" << boneyard.getTileAt(i).getSide2();
	}
	saveFile << endl << endl;

	if (isHumanTurn)
	{
		saveFile << "Next Player: Human";
	}
	else
	{
		saveFile << "Next Player: Computer";
	}
	saveFile.close();
	exit(0);
}