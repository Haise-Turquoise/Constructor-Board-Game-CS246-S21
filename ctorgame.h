#ifndef _CTORGAME_H_
#define _CTORGAME_H_
#include <string>
#include <vector>
#include <iostream>

class Board;

class CtorGame {
    std::string file;
    int seed;
    bool load;
    bool boardGiven;
    bool randBoard;

    public:
    CtorGame(std::string file = "", int seed = -1, bool load = 0, bool boardGiven = 0, bool randBoard = 0);
    void setFile(std::string file);
    void setSeed(int seed);
    void setLoad(bool load);
    void setBoard(bool boardGiven);
    void setRandBoard(bool randBoard);
    
    
    int setUp(Board & board, const std::vector<std::string> &fourPlayers); // return -1 when get EOF
    void endGame(Board & board, std::string fileName = "backup.sv");
    bool play();
    
    // for debug
    void info();
};
 

#endif
