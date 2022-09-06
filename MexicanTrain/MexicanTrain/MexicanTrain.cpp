/************************************************************
* Name:  Joseph Cavallo                                     *
* Project: 1, Mexican Train C++                             *
* Class: CMP 366 Organization of Programming Languages      *
* Date : 9/28/21                                            *
************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <stdlib.h>

#include "Tile.h"
#include "Deck.h"
#include "Game.h"
#include "Round.h"

using namespace std;

int main()
{
    Game g;
    int answer = 0;
    cout << "Would you like to: " << endl;
    cout << "1. Load a previous save" << endl;
    cout << "2. Start a new game" << endl;
    while (answer != 1 && answer != 2)
    {
        cin >> answer;
        if (answer == 1)
        {
            g.loadSave();
        }
        else if (answer == 2)
        {
            g.startRound();
        }
    }
}