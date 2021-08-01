#include "ctorgame.h"
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

void CtorGame::info() { // for debug
    cout  << ">  file: " << file << endl;
    cout  << ">  seed: " << seed << endl;
    cout  << ">  load?: " << load << endl;
    cout  << ">  boardGiven?: " << boardGiven << endl;
    cout  << ">  randBoard?: " << randBoard << endl;
}

// helper when ask user to input a non-negative integer, return -1 when EOF
int askForInteger(int up = 100, int lb = 0) { // 
    cin.exceptions(ios::eofbit|ios::failbit);
    int pos = -1; 
    while (true) {
        try { 
            cin >> pos;
            if ((pos >= lb) && (pos <= up)) break;
            cerr << ">  Invalid value: index out of range!" << std::endl;
        }  
        catch (ios::failure &) {
            if (cin.eof())  break;
            cerr << ">  Invalid command." << endl;
            cin.clear();
            cin.ignore();
        }       
    }
    return pos;
}

void CtorGame::endGame(Board & board, string fileName){
    cout<< ">  End game and save all status in file backup.sv" << endl;
    string out = board.saveGame(); 
    ofstream fileOut{fileName}; 
    fileOut << out << endl;
    board.clearBoard();
    cout << ">  Saved in "<< fileName << " !" << endl;
}

int CtorGame::setUp(Board & board, const vector<string> fourPlayers) {
    vector<int> sequence = {0,1,2,3,3,2,1,0};
    // set up the game: each builder chooce two location to build basement
    for (int i = 0; i < 8; i++) {
        cout << ">  Builder " << fourPlayers[sequence[i]] << ", where do you want to build a basement?" << endl;
        bool built = false;
        while (!built) { 
            int pos = askForInteger(53);
            if ( pos == -1 ) { endGame(board); return -1;}      // eof
            //built = true; // for debug 
            built = board.buildResFree(sequence[i], pos);
        } 
    }
    
    return 0;
}

bool CtorGame::play() {
    Board board;
    if (load) {                             // given an exist game
        board.loadGame(file);
    } else if (boardGiven) {                // given board
        board.initLoadBoard(file);
    } else if (randBoard && (seed != -1)) { // given seed
        board.initSeedBoard(seed);
    } else if (randBoard) {                 // not given seed 
        board.initRandBoard();
    } else {
        board.initLoadBoard(file);          // using default file "layout.txt"
    }
    board.printBoard();
    cout << ">  Seting up game..." << endl;
    vector<string> fourPlayers = {"Blue", "Red", "Orange", "Yellow"};
    if (!load) { 
        if (setUp(board, fourPlayers) == -1) return 0;      // eof
    }
    board.printBoard();

    cout << ">  Play game" << endl;
    while (true) {
        cout << ">  Builder " << fourPlayers[board.getCurTurn()] << "'s turn." << endl;
        string cmd;  
        // roll dice 
        bool rolled = false;        
        bool fair = false;
        int dice = 0;
        while (true) {
            if (rolled) break;
            if (!(cin>>cmd)) { endGame(board); return 0; }
            if (cmd == "roll") {
                if (!fair) {                        // load dice
                    cout << ">  Input a dice value between 2 to 12 (inclusive):"<< endl;
                    dice = askForInteger(12,2);
                    if (dice == -1) { endGame(board); return 0;}
                    board.rollDice(dice);
                } else {
                    dice = board.rollDice();
                }
                rolled = true;
                cout<< ">  Finish rolling" << endl;
            } else if (cmd == "fair") {
                fair = true;
                board.setDice(fair);
                cout<< ">  Player " << fourPlayers[board.getCurTurn()] << " uses fair dice now" << endl;
            } else if (cmd == "load") {
                fair = false;
                board.setDice(fair);
                cout<< ">  Player " << fourPlayers[board.getCurTurn()] << " uses loaded dice now" << endl;
            } else {
                cerr << ">  Please first roll the Dice. Remember to enter 'fair' or 'load' when needed" << endl;
            } 
        }
        cout << "You have rolled: " << dice << endl;
        // obtaining resources or move geese
        if (dice != 7) {
            cout<<">  Dice not 7, builder gain resources"<< endl;
            board.gainResources(dice);
        } else {    // move geese
            cout<<" Dice is 7, lose half and move geese"<<endl;
            
            board.loseHalf();
            cout << ">  Choose where to place the Geese" << endl;
            while (true) {
                int pos = askForInteger(18);
                if (pos == -1) { endGame(board); return 0;}
                if (pos == board.getGeese()) {
                    cout << ">  Geese should be moved to the tile not previously on." << endl;
                } else {
                    board.moveGeese(pos);
                    break;
                }
            } 
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
                cout<<">  Print Board"<<endl;
                board.printBoard();
            } 
            else if (cmd == "status") {
                cout<<">  Print all status"<<endl;
                board.printAllPlayerStatus();
            } 
            else if (cmd == "residences") {
                cout<<">  Print cur status"<<endl;
                board.printCurPlayerRes();
            } 
            else if (cmd == "build-road") {
                int pos = askForInteger(71);
                if (pos == -1) {endGame(board); return 0;}
                cout<<">  Build road "<< pos <<endl;
                board.buildRoad(pos);
            } 
            else if (cmd == "build-res") {
                int pos = askForInteger(53);
                if (pos == -1) {endGame(board); return 0;}
                cout<<">  Build residence "<< pos <<endl;
                board.buildRes(pos);
            } 
            else if (cmd == "improve") {
                int pos = askForInteger(53);
                if (pos == -1) {endGame(board); return 0;}
                cout<<">  Improve res "<< pos <<endl;
                board.improveRes(pos);
            } 
            else if (cmd == "trade") {
                string colour, give, take;
                if (!(cin >> colour >> give >> take)) {     // read fail: eof
                    endGame(board); return 0;
                } 
                int pos = board.trade(colour,give,take);
                if (pos == -1) {endGame(board); return 0;}
            } 
            else if (cmd == "next") {
                break;
            } 
            else if (cmd == "save") {
                string fileName;
                cin >> fileName;    // should we check file name format?
                endGame(board,fileName);
                board.clearBoard();
                return 0;
            } 
            else {
                cerr << ">  Error: " << cmd << ": command not found! ";
                cerr << ">  Using command 'help' to check all commands." << endl;
            }
            bool won = board.checkWon();
            if (won) {
                cout << ">  Builder " << fourPlayers[board.getCurTurn()] << " won the game!" << endl;
                cout << ">  Would you like to play again?" << endl;
                
                if (!(cin >> cmd)) return 0;
                if (cmd == "yes") return 1;
            }
        } 
        board.endCurTurn();
    }
    return 0;
}
