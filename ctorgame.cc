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
            if (cin.eof())  return -1;
            cerr << ">  Invalid command." << endl;
            cin.clear();
            cin.ignore();
        }       
    }
    return pos;
}
// helper when ask user to input a string command, return "eof" when EOF
string askForCommand() {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd = "eof";
    while (true) {
        try { 
            cin >> cmd;  break;
        }  
        catch (ios::failure &) {
            if (cin.eof())  return "eof"; 
        }       
    }
    return cmd;
}
// End game and save all status in file backup.sv if fileName not provided
void CtorGame::endGame(Board & board, string fileName){ 
    string out = board.saveGame(); 
    ofstream fileOut{fileName}; 
    fileOut << out << endl; 
    cout << ">  Saved in "<< fileName << " !" << endl;
}

// set up the game: each builder chooce two location to build basement
int CtorGame::setUp(Board & board, const vector<string> &fourPlayers) {
    vector<int> sequence = {0,1,2,3,3,2,1,0};
    for (int i = 0; i < 8; i++) {
        cout << ">  Builder " << fourPlayers[sequence[i]] << ", where do you want to build a basement?" << endl;
        bool built = false;
        while (!built) { 
            int pos = askForInteger(53);
            if ( pos == -1 ) { endGame(board); return -1;}      // eof 
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
    vector<string> fourPlayers = {"Blue", "Red", "Orange", "Yellow"};
    if (!load) {                                            // each builder chooce two location to build basement
        cout << ">  Seting up game..." << endl;
        if (setUp(board, fourPlayers) == -1) return 0;      // eof
        board.printBoard();
    }

    cout << ">  Start!" << endl;
    vector<bool> fairOrLoad = {0,0,0,0};
    while (true) {
        int curTurn = board.getCurTurn();
        cout << ">  Builder " << fourPlayers[curTurn] << "'s turn." << endl;
        string cmd;  
        // roll dice 
        bool rolled = false;    
        int dice = 0;
        while (true) {
            if (rolled) break;
            cmd = askForCommand();
            if (cmd == "eof") {endGame(board); return 0;}

            if (cmd == "roll") {
                if (!fairOrLoad[curTurn]) {         // load dice
                    cout << ">  Input a dice value between 2 to 12 (inclusive):"<< endl;
                    dice = askForInteger(12,2);
                    if (dice == -1) { endGame(board); return 0;}
                    board.rollDice(dice);
                } else {                            // fair dice
                    dice = board.rollDice();
                }
                rolled = true; 
            } else if (cmd == "fair") {             // set current player's dice to be fair 
                fairOrLoad[curTurn] = true;
                board.setDice(true);
                cout<< ">  Player " << fourPlayers[curTurn] << " uses fair dice now" << endl;
            } else if (cmd == "load") {             // set current player's dice to be load
                fairOrLoad[curTurn] = false;
                board.setDice(false);
                cout<< ">  Player " << fourPlayers[curTurn] << " uses loaded dice now" << endl;
            } else {
                cerr << ">  Please first roll the Dice. Remember to enter 'fair' or 'load' when needed" << endl;
            } 
        }
        cout << ">  You have rolled: " << dice << endl; 
        if (dice != 7) {                            // obtaining resources
            board.gainResources(dice);
        } else {                                    // move geese
            cout<<">  Dice is 7. Geese attack!"<<endl;
            board.loseHalf();
            cout << ">  Choose where to place the Geese" << endl;
            while (true) {
                int pos = askForInteger(18);        
                if (pos == -1) { endGame(board); return 0;}
                if (pos == board.getGeese()) {
                    cout << ">  Geese should be moved to the tile not previously on." << endl;
                } else {
                    int eofVal = board.moveGeese(pos);
                    if (eofVal == -1) { endGame(board); return 0;}
                    break;
                }
            } 
        }

        board.printUsingChoice();

        // during the turn 
        while (true) {
            cmd = askForCommand();
            if (cmd == "eof") {endGame(board); return 0;}

            if (cmd == "help") {
                cout << ">  Valid commands:" << endl;
                cout << ">    board" << endl << ">    status" << endl << ">    residences" << endl;
                cout << ">    build-road <edge#>    e.g. build-road 7"<< endl;
                cout << ">    build-res <housing#>    e.g. build-res 25" << endl;
                cout << ">    improve <housing#>    e.g. improve 25"<< endl;
                cout << ">    trade <colour> <give> <take>    Note: making sure the first letter is capitalized: trade Orange Brick HEAT" << endl;
                cout << ">    next" << endl << ">    save <file>    e.g. save backup.sv" << endl << ">    help" << endl;
            } 
            else if (cmd == "board") { 
                board.printBoard();
            } 
            else if (cmd == "status") { 
                board.printAllPlayerStatus();
            } 
            else if (cmd == "residences") { 
                board.printCurPlayerRes();
            } 
            else if (cmd == "build-road") {
                int pos = askForInteger(71);
                if (pos == -1) {endGame(board); return 0;}
                board.buildRoad(pos);
                cout<<">  Player built road "<< pos <<endl;
            } 
            else if (cmd == "build-res") {
                int pos = askForInteger(53);
                if (pos == -1) {endGame(board); return 0;}
                board.buildRes(pos);
                cout << ">  Player built residence "<< pos <<endl;
            } 
            else if (cmd == "improve") {
                int pos = askForInteger(53);
                if (pos == -1) {endGame(board); return 0;}
                board.improveRes(pos);
                cout << ">  Player upgraded residence "<< pos <<endl;
            } 
            else if (cmd == "trade") { 
                string colour = askForCommand();
                string give = askForCommand();
                string take = askForCommand();
                if ((colour == "eof") || (give == "eof") || (take == "eof")) {
                    endGame(board); return 0;
                }
                int pos = board.trade(colour,give,take);
                if (pos == -1) {endGame(board); return 0;}
            } 
            else if (cmd == "next") {
                break;
            } 
            else if (cmd == "save") {
                string fileName = askForCommand();
                if (fileName == "eof") {endGame(board); return 0;} 
                endGame(board,fileName); 
                return 0;
            } 
            else {
                cerr << ">  Error: " << cmd << ": command not found! ";
                cerr << ">  Using command 'help' to check all commands." << endl;
            } 

            bool won = board.checkWon();
            if (won) {
                cout << ">  Builder " << fourPlayers[board.getCurTurn()] << " won the game!" << endl;
                cout << ">  Would you like to play again? (yes/no)" << endl;
                string yesOrNo = askForCommand();
                if (yesOrNo == "yes") return 1;
                if (yesOrNo == "eof") {endGame(board); return 0;} 
                if (yesOrNo == "no") return 0;
            }
        } 
        board.endCurTurn();
    }
    return 0;
}
