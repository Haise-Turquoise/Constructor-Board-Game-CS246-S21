#include "subject.h"
#include "observer.h"
#include "tile.h"
#include "vertex.h"
#include "edge.h"
#include <vector>

class Board {
    std::vector<Tile*> tiles;
    std::vector<Vertex*> vertices;
    std::vector<Edge*> edges;

    public:
    void initAttachBoard();
    void printBoard();

};