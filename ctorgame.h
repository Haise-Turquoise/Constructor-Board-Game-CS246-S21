#ifndef _CTORGAME_H_
#define _CTORGAME_H_
#include <string>
#include <vector>
#include <iostream>

class Board;

class CtorGame {
    std::string file = "layout.txt";
    int seed = -1;
    bool load = false;
    bool boardGiven = false;
    bool randBoard = false;
    bool customized = false;
    bool haveGeese = true;
    bool suggestion = false;

    public:
    CtorGame(std::string file = "", int seed = -1, bool load = 0, bool boardGiven = 0, bool randBoard = 0);
    void setFile(std::string file);
    void setSeed(int seed);
    void setLoad(bool load);
    void setBoard(bool boardGiven);
    void setRandBoard(bool randBoard);
    void setCustomized(bool customized);
    
    
    int setUp(Board & board, const std::vector<std::string> &fourPlayers); // return -1 when get EOF
    void endGame(Board & board, std::string fileName = "backup.sv");
    bool play();
    
    // for debug
    void info();
};
 

#endif
