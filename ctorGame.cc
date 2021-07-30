#include "ctorGame.h"
#include "board.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


CtorGame::CtorGame( string file, int seed, bool load, bool boardGiven, bool randBoard):
    file{file}, seed{seed}, load{load}, boardGiven{boardGiven}, randBoard{randBoard} {}

void CtorGame::setFile( string file){ this->file = file; }
void CtorGame::setSeed(int seed){ this->seed = seed; }
void CtorGame::setLoad(bool load){ this->load = load; }
void CtorGame::setBoard(bool boardGiven){ this->boardGiven = boardGiven; }
void CtorGame::setRandBoard(bool randBoard){ this->randBoard = randBoard; }

void CtorGame::info() {
    cout  << "file: " << file << endl;
    cout  << "seed: " << seed << endl;
    cout  << "load?: " << load << endl;
    cout  << "boardGiven?: " << boardGiven << endl;
    cout  << "randBoard?: " << randBoard << endl;
}

// helper when ask user to input a non-negative integer, return -1 when EOF
int askForInteger(int range = 100) { // 
    cin.exceptions(ios::eofbit|ios::failbit);
    int pos = -1; 
    while (true) {
        try { 
            cin >> pos;
            if ((pos >= 0) && (pos <= range)) break;
            cerr << "Invalid value: index out of range!" << std::endl;
        }  
        catch (ios::failure &) {
            if (cin.eof())  break;
            cerr << "Invalid command." << endl;
            cin.clear();
            cin.ignore();
        }       
    }
    return pos;
}

void CtorGame::endGame(Board & board, string fileName){
    /*
    cout<< "End game and save all status in file backup.sv" << endl;
    string out = board.saveGame(); 
    ofstream fileOut{fileName}; 
    fileOut << out << endl;
    */
   cout << "saving here" << endl;
}

int CtorGame::setUp(Board & board, const vector<string> fourPlayers) {
    // set up the game: each builder chooce two location to build basement
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 4; i++) {
            cout << "Builder " << fourPlayers[i] << ", where do you want to build a basement?" << endl;
            int pos = askForInteger(53);
            if (pos == -1) { endGame(board); return -1;}
            //board.buildRes(pos);
            //board.endCurTurn();
        }
    }
}

bool CtorGame::play() {
    Board board;
    /*if (load) {                             // given an exist game
        board.loadGame(file);
    } else if (boardGiven) {                // given board
        board.initLoadBoard(file);
    } else if (randBoard && (seed != -1)) { // given seed
        board.initSeedBoard(seed);
    } else if (randBoard) {                 // not given seed 
        board.initRandBoard();
    } else {
        board.initLoadBoard(file);          // using default file "layout.txt"
    }*/

    cout << "seting up game..." << endl;
    vector<string> fourPlayers = {"Blue", "Red", "Orange", "Yellow"};
    if (!load) {
        int val = setUp(board, fourPlayers);
        if (val == -1) return 0;
    }
    //board.printBoard();

    cout << "play game" << endl;
    while (true) {
        cout << "Builder " << fourPlayers[board.getCurTurn()] << "'s turn." << endl;
        string cmd;  
        
        // roll dice
        bool fairDice = false;
        bool rolled = false;
        int dice = 0;
        while (true) {
            if (rolled) break;
            if (!(cin>>cmd)) { endGame(board); return 0; }
            if (cmd == "roll") {
                //dice = board.rollDice(fairDice);
                rolled = true;
                cout << "finish rolling" << endl;
            } else if (cmd == "fair") {
                fairDice = true;
                cout<< "Player " << fourPlayers[board.getCurTurn()] << " uses fair dice now" << endl;
            } else if (cmd == "load") {
                fairDice = false;
                cout<< "Player " << fourPlayers[board.getCurTurn()] << " uses loaded dice now" << endl;
            } else {
                cerr << "Please first roll the Dice, remember to enter 'fair' if needed" << endl;
            } 
        }

        // obtaining resources or move geese
        if (dice != 7) {
            cout<<"dice not 7, builder gain resources"<< endl;
            //board.gainResources(dice);
        } else {    // move geese
            cout<<"dice is 7, lose half and move geese"<<endl;
            //int movePos = board.geeseRolled();
            //board.moveGeese(movePos);
        }


        // during the turn 
        while (true) {
            if (!(cin>>cmd)) { endGame(board); return 0; }

            if (cmd == "help") {
                cout << "Valid commands:" << endl;
                cout << "board" << endl << "status" << endl << "residences" << endl;
                cout << "build-road <edge#>" << endl << "build-res <housing#>" << endl;
                cout << "improve <housing#>" << endl << "trade <colour> <give> <take>" << endl;
                cout << "next" << endl << "save <file>" << endl << "help" << endl;
            } 
            else if (cmd == "board") {
                cout<<"print Board"<<endl;
                //board.printBoard();
            } 
            else if (cmd == "status") {
                cout<<"print all status"<<endl;
                //board.printAllPlayerStatus();
            } 
            else if (cmd == "residences") {
                cout<<"print cur status"<<endl;
                //board.printCurPlayerStatus();
            } 
            else if (cmd == "build-road") {
                int pos = askForInteger(71);
                if (pos == -1) {endGame(board); return 0;}
                cout<<"build road "<< pos <<endl;
                //board.buildRoad(pos);
            } 
            else if (cmd == "build-res") {
                int pos = askForInteger(53);
                if (pos == -1) {endGame(board); return 0;}
                cout<<"build residence "<< pos <<endl;
                //board.buildRes(pos);
            } 
            else if (cmd == "improve") {
                int pos = askForInteger(53);
                if (pos == -1) {endGame(board); return 0;}
                cout<<"improve res "<< pos <<endl;
                //board.improveRes(pos);
            } 
            else if (cmd == "trade") {
                string colour, give, take;
                if (!(cin >> colour >> give >> take)) {     // read fail: eof
                    endGame(board); return 0;
                }
                // following message should be placed in trade();
                cout << fourPlayers[board.getCurTurn()]<<" offers " << colour;
                cout << " one " << give << " for one " << take << "." << endl;

                //board.trade(colour,give,take);
            } 
            else if (cmd == "next") {
                break;
            } 
            else if (cmd == "save") {
                string fileName;
                cin >> fileName;    // should we check file name format?
                endGame(board,fileName);
                return 0;
            } 
            else {
                cerr << "Error: " << cmd << ": command not found! ";
                cerr << "Using command 'help' to check all commands." << endl;
            }
            bool won = board.checkWon();
            if (won) {
                cout << "you won" << endl;
                cout << "Would you like to play again?" << endl;
                
                if (!(cin >> cmd)) return 0;
                if (cmd == "yes") return 1;
            }
        }
        break;
        //board.endCurTurn();
    }
    return 0;
}