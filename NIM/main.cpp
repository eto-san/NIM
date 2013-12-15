//
//  main.cpp
//  NIM
//
//  Created by EshaO on 11/28/13.
//  Copyright (c) 2013 EshaO. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;


// Random number generator for various program needs
int getRandNum ( int numHi, int numLo);

// Equation for computer pick on Smartmode
int compSmartMove ( int marbles, int max);

// To get pick from player
int humanMove (int half);

// Ask player if they want to continue playing or quit.
bool gameStatus ();



int main()
{
    int is_gameOn = 0;
    bool is_gameOver = false;
    int compScore = 0;
    int humScore = 0;
    
    cout << "\t\t\t\tThe Game of NIM\n";
    cout << "\t>>------------------------------------------<<\n";
    cout << "NIM is a mathematical strategy game where two players" << endl
        << "take turns removing marbles from a pile. On each turn," << endl
        << "players much remove at least one marble to , at most, " << endl
        << "half the marbles of the pile. You will be playing against" <<endl
        << "the computer.\n";
    
    //Ask the user if they want to play
    is_gameOver = gameStatus ();
    if (!is_gameOver) {cout << "Bye!"; return 0;}
    else {
        do{
            //Generating random number to determine if the computer will run
            //on smart mode or stupid mode.
            bool compSmartmode = false;
            if (getRandNum(2, 0)==1) { compSmartmode = true;}

            //Generating random number to determine who has first turn.
            bool compTurn = false;
            if ((getRandNum(2950, 281)%2)==1) compTurn = true;
            else
            {compTurn = false;}
    
            int pile = getRandNum ( 100, 10);
            cout <<">>------------------------------------------<<";
            cout <<"\nPile of " <<pile <<" marbles.\t";
    
            int pick = 0;
    
            while (pile !=1){
                cout << "Choose between 1 - " <<pile/2 <<endl;
                switch (compTurn)
                {
                    case true: if (!compSmartmode) {pick = getRandNum(pile/2, 1);
                        cout <<"Computer chose:\t" <<pick <<" marbles." <<endl;}
                        else { pick = compSmartMove(pile, pile/2);
                            cout <<"Computer chose:\t" << pick <<" marbles." <<endl;}
                        compTurn = false;
                        break;
                    case false: pick = humanMove(pile/2);
                        compTurn = true;
                        break;
                }
                
                pile = pile - pick;
                cout <<"\nPile = " <<pile <<"\t" ;
            }
    
            is_gameOn++;
        
            if (compTurn) {cout << "...and it's the computer's turn. You beat the computer!";
            humScore++;}
            else { cout << "..and it's your turn. Sorry you lose."; compScore++;}
    
            cout << "\n\n\t\t*******SCOREBOARD*******\n"
                <<"\nOut of " <<is_gameOn <<" game(s):"
                << " You: " <<humScore  <<"\t\t"
                << "Computer: " <<compScore
            << "\n\t\t************************" <<endl;
            
            is_gameOver = gameStatus();
            
        } while (is_gameOver);
    
    cout << "\nHope you had fun playing!" <<endl;
    return 0;
}

}

    

// ***************** FUNCTIONS **********************



/** Random number generator for various program needs
 i.e. pile = number of marbles in game pile
 firstTurn = which player gets to go first
 compMode= if computer plays smart or stupid */

int getRandNum ( int numHi, int numLo)
{
    if ( numHi == 1 && numLo == 1) return numHi;
    else {
        srand (time(NULL));
        return rand() % (numHi - numLo) + numLo;
    }

}


/** Calculates the amount of marbles for the computer to
pick so that the size of the pile a power of two minus 1 */

int compSmartMove ( int marbles, int half)
{
//    total marbles cannot != 3,7,15,31,63
    double test = log2(marbles+1);
    if (test == (int)test) return getRandNum(half,1);
    else {
        double exp = floor(log2(marbles));
        int result = (pow(2, exp))-1;
        return marbles - result;}
}


/** Queries the player for their choice. Validates player's
input to verify if it is a number, is positive, AND between 
1 and half of the current pile. */

int humanMove (int half)
{
    int choice = 0;
    string wrong_input;
    cout << "Your choice:\t";
    cin >> choice;
    while (!cin || choice > half || choice <= 0){
            cin.clear();
            getline (cin, wrong_input);
            cout << "*Error: Please enter a numerical value. (Range: 1 - " <<half <<")" <<endl;
            cout << "Your choice\t";
        cin >> choice;}
    return choice;
}

/** Determines if the program continues playing or
 if it stops and exits. */

bool gameStatus ()
{
    string choice = "Q";
    string wrong_input;
    cout << "Please enter 'P' to play or 'Q' to quit:\t";
    cin >> choice;
    while (!cin && !(choice == "P") && !(choice == "Q")){
        cin.clear();
        getline (cin, wrong_input);
        cout << "Error: Please enter 'P' to play or 'Q' to quit:" <<endl;
        cout << "Your choice\t";
        cin >> choice;}
    bool play = false;
    if ( choice == "P") return play = true;
    else ( choice == "Q");{ return play = false;}
}