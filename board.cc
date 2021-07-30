#include "board-test.h"
#include <random>
#include <algorithm>
#include <vector>
#include <utility>

void Board::initAttachBoard() {
    for ( size_t i = 0; i++; i < 19 ) {
        Tile* tmpTile = new Tile{i};
        tiles.emplace_back(tmpTile);
    }
    for ( size_t j = 0; j++; j < 54 ) {
        Vertex* tmpVertex = new Vertex{j};
        vertices.emplace_back(tmpVertex);
    }
    for ( size_t k = 0; k++; k < 72 ) {
        Edge* tmpEdge = new Edge{k};
        edges.emplace_back(tmpEdge);
    }
    // resource type on Tile still need to be set


    // attach Vertex neighbours to Tile
    tiles[0]->attach(vertices[0]);              // tile 0
    tiles[0]->attach(vertices[1]);
    tiles[0]->attach(vertices[3]);
    tiles[0]->attach(vertices[4]);
    tiles[0]->attach(vertices[8]);
    tiles[0]->attach(vertices[9]);

    for (int i = 1; i < 3; i++){                // tile 1,2
        tiles[i]->attach(vertices[i*2]);
        tiles[i]->attach(vertices[i*2+1]);
        tiles[i]->attach(vertices[i*2+5]);
        tiles[i]->attach(vertices[i*2+6]);
        tiles[i]->attach(vertices[i*2+11]);
        tiles[i]->attach(vertices[i*2+12]);
    }

    for (int i = 3; i < 16; i++) {               // tile 3-15
        int j = 0;
        if (i > 5) j += 1;
        if (i > 7) j += 1;
        if (i > 10) j += 1;
        if (i > 12) j += 1;
        tiles[i]->attach(vertices[i*2+j]);
        tiles[i]->attach(vertices[i*2+1+j]);
        tiles[i]->attach(vertices[i*2+6+j]);
        tiles[i]->attach(vertices[i*2+7+j]);
        tiles[i]->attach(vertices[i*2+12+j]);
        tiles[i]->attach(vertices[i*2+13+j]);
    }
 
    for (int i = 16; i < 18; i++) {               // tile 16,17
        tiles[i]->attach(vertices[i*2+5]);
        tiles[i]->attach(vertices[i*2+6]);
        tiles[i]->attach(vertices[i*2+11]);
        tiles[i]->attach(vertices[i*2+12]);
        tiles[i]->attach(vertices[i*2+16]);
        tiles[i]->attach(vertices[i*2+17]);
    }

    tiles[18]->attach(vertices[44]);            // tile 18
    tiles[18]->attach(vertices[45]);
    tiles[18]->attach(vertices[49]);
    tiles[18]->attach(vertices[50]);
    tiles[18]->attach(vertices[52]);
    tiles[18]->attach(vertices[53]);


    // attach Edge neighbours to Vertex
    vertices[0]->attachEdgeDoubly(edges[0]);
    vertices[0]->attachEdgeDoubly(edges[1]); 

    vertices[1]->attachEdgeDoubly(edges[0]);
    vertices[1]->attachEdgeDoubly(edges[2]);

    vertices[2]->attachEdgeDoubly(edges[3]);
    vertices[2]->attachEdgeDoubly(edges[5]);

    for (int i = 3; i < 5; i++) {
        vertices[i]->attachEdgeDoubly(edges[i-2]);
        vertices[i]->attachEdgeDoubly(edges[i]);
        vertices[i]->attachEdgeDoubly(edges[i+3]);
    }

    vertices[5]->attachEdgeDoubly(edges[4]);
    vertices[5]->attachEdgeDoubly(edges[8]);

    vertices[6]->attachEdgeDoubly(edges[9]);
    vertices[6]->attachEdgeDoubly(edges[12]);

    for (int i = 7; i < 11; i++) {
        int j = 2;
        if (i > 8) j -= 1;
        vertices[i]->attachEdgeDoubly(edges[i-2]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+6]);
    }

    vertices[11]->attachEdgeDoubly(edges[11]);
    vertices[11]->attachEdgeDoubly(edges[17]);

    vertices[12]->attachEdgeDoubly(edges[12]);
    vertices[12]->attachEdgeDoubly(edges[20]);

    for (int i = 13; i < 17; i++) {
        int j = 5;
        if (i > 13) j -= 1;
        if (i > 15) j -= 1;
        vertices[i]->attachEdgeDoubly(edges[i]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+8]);
    }

    vertices[17]->attachEdgeDoubly(edges[17]);
    vertices[17]->attachEdgeDoubly(edges[25]); 

    for (int i = 18; i < 24; i++) {
        int j = 8;
        if (i > 18) j -= 1;
        if (i > 20) j -= 1;
        if (i > 22) j -= 1;
        vertices[i]->attachEdgeDoubly(edges[i+2]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+11]);
    }

    vertices[24]->attachEdgeDoubly(edges[29]);
    vertices[24]->attachEdgeDoubly(edges[37]);

    for (int i = 25; i < 29; i++) {
        int j = 10;
        if (i > 25) j -= 1;
        if (i > 27) j -= 1; 
        vertices[i]->attachEdgeDoubly(edges[i+5]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+13]);
    }

    vertices[29]->attachEdgeDoubly(edges[34]);
    vertices[29]->attachEdgeDoubly(edges[42]);

    for (int i = 30; i < 36; i++) {
        int j = 13;
        if (i > 30) j -= 1;
        if (i > 32) j -= 1; 
        if (i > 34) j -= 1;
        vertices[i]->attachEdgeDoubly(edges[i+7]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+16]);
    }

    vertices[36]->attachEdgeDoubly(edges[46]);
    vertices[36]->attachEdgeDoubly(edges[54]);

    for (int i = 37; i < 41; i++) {
        int j = 15;
        if (i > 37) j -= 1;
        if (i > 39) j -= 1; 
        vertices[i]->attachEdgeDoubly(edges[i+10]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+18]);
    }

    vertices[41]->attachEdgeDoubly(edges[51]);
    vertices[41]->attachEdgeDoubly(edges[59]);

    vertices[42]->attachEdgeDoubly(edges[54]);
    vertices[42]->attachEdgeDoubly(edges[60]);

    for (int i = 43; i < 47; i++) {
        int j = 17;
        if (i > 44) j -= 1; 
        vertices[i]->attachEdgeDoubly(edges[i+12]);
        vertices[i]->attachEdgeDoubly(edges[i+j]);
        vertices[i]->attachEdgeDoubly(edges[i+20]);
    }

    vertices[47]->attachEdgeDoubly(edges[59]);
    vertices[47]->attachEdgeDoubly(edges[62]);

    vertices[48]->attachEdgeDoubly(edges[63]);
    vertices[48]->attachEdgeDoubly(edges[67]);

    for (int i = 49; i < 51; i++) { 
        vertices[i]->attachEdgeDoubly(edges[i+15]);
        vertices[i]->attachEdgeDoubly(edges[i+18]);
        vertices[i]->attachEdgeDoubly(edges[i+20]);
    }

    vertices[51]->attachEdgeDoubly(edges[66]);
    vertices[51]->attachEdgeDoubly(edges[68]);

    vertices[52]->attachEdgeDoubly(edges[69]);
    vertices[52]->attachEdgeDoubly(edges[71]);

    vertices[53]->attachEdgeDoubly(edges[70]);
    vertices[53]->attachEdgeDoubly(edges[71]);
}


//刘书辰

// helper function: generate random number
int myrandom (int i) { return std::rand()%i;}

// helper function: initialize resource vector
std::vector<std::string> initResourse() {
    std::vector<std::string> resource(3, "WIFI");
    resource.insert(resource.end(), 3, "HEAT");
    resource.insert(resource.end(), 4, "BRICK");
    resource.insert(resource.end(), 4, "ENERGY");
    resource.insert(resource.end(), 4, "CLASS");
    resource.emplace_back("PARK");
    return resource;
}


void Board::initRandBoard() {
    srand(time(0));

    // create resourse vector and shuffle with the above random generated seed
    std::vector<std::string> resource = initResourse();
    std::random_shuffle(resource.begin(), resource.end(), myrandom);

    //create value vector and shuffle with the above random generated seed
    std::vector<int> value = {2,12,7,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11};
    std::random_shuffle(value.begin(), value.end(), myrandom);

    // deal with park
    int parkIdx = std::find(resource.begin(), resource.end(), "PARK") - resource.begin();
    int sevenIdx = std::find(value.begin(), value.end(), 7) - value.begin();
    std::swap(value[sevenIdx], value[parkIdx]);
    
    //create Tile
    for (int i = 0; i < 19; i++) {
        Tile newTile = Tile{i};
        newTile.setResourceType(resource[i]);
        newTile.setValue(value[i]);
        tiles.emplace_back(newTile);
    }
}

// 刘书辰
void Board::initSeedBoard( int seed ) {
    // set seed
    unsigned sd = seed;

    // create random resource with seed
    std::vector<std::string> resource = initResourse();
    std::shuffle(resource.begin(), resource.end(), std::default_random_engine(sd));

    // create random value with seed
    std::vector<int> value = {2,12,7,3,3,4,4,5,5,6,6,8,8,9,9,10,10,11,11};
    std::shuffle(value.begin(), value.end(), std::default_random_engine(sd));

    // deal with park
    int parkIdx = std::find(resource.begin(), resource.end(), "PARK") - resource.begin();
    int sevenIdx = std::find(value.begin(), value.end(), 7) - value.begin();
    std::swap(value[sevenIdx], value[parkIdx]);

    // create Tile
    for (int i = 0; i < 19; i++) {
        Tile newTile = Tile{i};
        newTile.setResourceType(resource[i]);
        newTile.setValue(value[i]);
        tiles.emplace_back(newTile);
    }
}
