#include "Game.h"
#include "Deck.h"
#include "Round.h"
#include "Human.h"
#include "Computer.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

//default constructor
Game::Game()
{
	humanScore = 0;
	compScore = 0;
	roundNum = 0;
}

//parameterized constructor
Game::Game(int p, int c, int r)
{
	humanScore = p;
	compScore = c;
	roundNum = r;
}

/* *********************************************************************
Function Name: loadSave
Purpose: Load a previous save by a text file
Parameters:
			none
Return Value: none
Algorithm:
			1)Gets the name of the text file from the user
			2)Takes in all the information from the text file
			3)Creates a new round with the given information
			4)Starts playing from the new round
Assistance Received: none
********************************************************************* */
void Game::loadSave()
{
	string fileName;
	cout << "Enter name of save file: ";
	cin >> fileName;
	ifstream readFile(fileName);
	if (readFile.is_open())
	{
		string line;
		int position = 0;

		//Round number
		getline(readFile, line);
		position = line.find(":");
		string round = line.substr(position + 2);
		roundNum = stoi(round);
		//Computer
		getline(readFile, line);
		getline(readFile, line);
		//cpuScore
		getline(readFile, line);
		position = line.find(":");
		string cpuScore = line.substr(position + 2);
		compScore = stoi(cpuScore);
		//cpuHand
		getline(readFile, line);
		position = line.find(":");
		string cpuHand = line.substr(position + 2);
		vector<Tile> cpuHandNums;
		bool nullMarker = false;
		getNumbers(cpuHandNums, cpuHand, nullMarker);
		//cpuTrain
		getline(readFile, line);
		position = line.find(":");
		string cpuTrain = line.substr(position + 2);
		vector<Tile> cpuTrainNums;
		bool cpuMarker = false;
		getNumbers(cpuTrainNums, cpuTrain, cpuMarker);

		//checks if the computer train ends with an orphan double
		bool cpuOrphan = false;
		if (cpuTrainNums.size() > 0)
		{
			if (cpuTrainNums.front().getSide1() == cpuTrainNums.front().getSide2())
			{
				cpuOrphan = true;
			}
		}

		//Human
		getline(readFile, line);
		if (line.size() == 0)
		{
			getline(readFile, line);
		}
		
		//humScore
		getline(readFile, line);
		position = line.find(":");
		string humScore = line.substr(position + 2);
		humanScore = stoi(humScore);
		//humHand
		getline(readFile, line);
		position = line.find(":");
		string humHand = line.substr(position + 2);
		vector<Tile> humHandNums;
		getNumbers(humHandNums, humHand, nullMarker);
		//humTrain
		getline(readFile, line);
		position = line.find(":");
		string humTrain = line.substr(position + 2);
		vector<Tile> humTrainNums;
		bool humMarker = false;
		getNumbers(humTrainNums, humTrain, humMarker);

		//Checks if the human trains with an orphan double
		bool humOrphan = false;
		if (humTrainNums.size() > 0)
		{
			if (humTrainNums.back().getSide1() == humTrainNums.back().getSide2())
			{
				humOrphan = true;
			}
		}

		getline(readFile, line);
		//Mexican Train
		getline(readFile, line);
		position = line.find(":");
		string mexTrain;
		vector<Tile> mexTrainNums;
		if (position != line.size() - 1)
		{
			mexTrain = line.substr(position + 2);
			getNumbers(mexTrainNums, mexTrain, nullMarker);
		}
		else
		{
			mexTrain = "";
		}

		//Checks if the mexican train ends with an orphan double
		bool mexOrphan = false;
		if (mexTrainNums.size() > 0)
		{
			if (mexTrainNums.back().getSide1() == mexTrainNums.back().getSide2())
			{
				mexOrphan = true;
			}
		}

		getline(readFile, line);
		//Boneyard
		getline(readFile, line);
		position = line.find(":");
		string boneyard = line.substr(position + 2);
		vector<Tile> boneyardNums;
		getNumbers(boneyardNums, boneyard, nullMarker);

		getline(readFile, line);
		//NextPlayer
		getline(readFile, line);
		position = line.find(":");
		string nextPlayer = line.substr(position + 2);

		//Gets whose turn it is next
		bool humanTurn;
		if (nextPlayer == "Human")
		{
			humanTurn = true;
		}
		else
		{
			humanTurn = false;
		}
		//Creats the new round with all the infromation
		Round r(roundNum, compScore, cpuHandNums, cpuTrainNums, cpuMarker, humanScore, humHandNums, humTrainNums, humMarker, mexTrainNums, boneyardNums, humanTurn, cpuOrphan, humOrphan, mexOrphan);
		playRound(r);
	}
	else
	{
		cout << "error: file can not be found";
		exit(0);
	}
}

/* *********************************************************************
Function Name: getNumbers
Purpose: Get just the numbers from the lines for the trains, hands, and boneyard
Parameters:
			Tiles. A vector that is passed by reference. The vector that will have the tiles be placed into
			input. The input string that the numbers are being extracted from
			marker. A bool passed by reference that tells if the train is marked or not
Return Value: none
Algorithm:
			1)Creates all different tiles from 0-0 to 9-9
Assistance Received: none
********************************************************************* */
void Game::getNumbers(vector<Tile> &tiles, string input, bool& marker)
{
	//So the string can find where the dash's are
	const char dash = '-';
	//So the string can replace all dash's with spaces
	const char space = ' ';

	//Replaces all the dashes with spaces
	replace(input.begin(), input.end(), dash, space);

	stringstream line;
	
	line << input;

	//temp is the individual spaced out numbers or letters are given to
	string temp;
	//The number that is found in line
	int num;
	//The vector that the numbers found in placed into
	vector<int> numbers;
	//while not at the end of line
	while (!line.eof())
	{
		//puts the single number or letter into temp
		line >> temp;

		//If the character found in temp is a number put that number into the numbers vector
		if (stringstream(temp) >> num)
		{
			numbers.push_back(num);
		}
		//If the character found is an M then marker is true
		if (temp == "M")
		{
			marker = true;
		}
		temp = "";
	}
	//Turns every two ints in numbers vector into a tile then puts the tile into the tiles vector
	for (int i = 0; i < numbers.size(); i = i + 2)
	{
		Tile newTile(numbers.at(i), numbers.at(i + 1));
		tiles.push_back(newTile);
	}
}

/* *********************************************************************
Function Name: startRound
Purpose: Create a new round
Parameters:
			none
Return Value: none
Algorithm:
			1)Increments round then creates new round object with that round value
			2)Sets whose turn it is first by score or coinflip
			3)Sets the scores in the round object
			4)Gets the engine for the round and adds it to the trains
			5)Deals the hands to both players
			6)plays the round
Assistance Received: none
********************************************************************* */
void Game::startRound()
{
	roundNum++;
	Round r(roundNum);
	if (humanScore > compScore)
	{
		r.setIsHumanTurn(false);
	}
	else if (humanScore < compScore)
	{
		r.setIsHumanTurn(true);
	}
	else
	{
		r.coinFlip();
	}
	r.setHumanScore(humanScore);
	r.setCompScore(compScore);
	r.addEngine(r.engine());

	r.humanDeal();
	r.computerDeal();
	
	playRound(r);
}

/* *********************************************************************
Function Name: playRound
Purpose: keeps the round going until a winner is returned
Parameters:
			none
Return Value: none
Algorithm:
			1)Keeps calling play in round until a winner has been returned
			2)Asks if the user wants to keep playing
Assistance Received: none
********************************************************************* */
void Game::playRound(Round r)
{
	for ( ; ; )
	{
		if (r.getWinner() == 1)
		{
			cout << "You Won!" << endl;
			break;
		}
		else if (r.getWinner() == 2)
		{
			cout << "The Computer Won!" << endl;
			break;
		}
		else if (r.getWinner() == 3)
		{
			cout << "It's a stalemate, boneyard is empty and neither player can play" << endl;
			break;
		}
		else
		{
			r.play();
		}
	}
	//adds up the computers and humans scores
	compScore += r.getComputerPips();
	humanScore += r.getHumanPips();

	continuePlay();
}

/* *********************************************************************
Function Name: continuePlay
Purpose: Asks the user if they would like to keep playing or stop
Parameters:
			none
Return Value: none
Algorithm:
			1)Outputs both players scores
			2)Asks the user if they would want to play another round
			3)Starts a new round if they want to
			4)Tells who the winner is if they want to stop playing
Assistance Received: none
********************************************************************* */
void Game::continuePlay()
{
	string answer = " ";
	cout << endl;
	cout << "Your score is: " << humanScore << endl;
	cout << "The computer score is: " << compScore << endl;
	for( ; ; )
	{
		cout << "Would you like to play another round? Reply \"yes\" or \"no\"" << endl;
		cin >> answer;
		if (answer == "yes")
		{
			startRound();
			break;
		}
		else if (answer == "no")
		{
			if (humanScore > compScore)
			{
				cout << "The computer wins with " << compScore << " points!" << endl;
			}
			else if (humanScore < compScore)
			{
				cout << "You win with " << humanScore << " points!" << endl;
			}
			else
			{
				cout << "It's a tie at " << humanScore << " points!" << endl;
			}
			break;
		}
			
		else
		{
			continue;
		}
	}
}