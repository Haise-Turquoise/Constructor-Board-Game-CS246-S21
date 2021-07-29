#include "board-test.h"

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

    // start attach, take Tile 16 and Tile 14 for example:
    // Tile neighbours attach to Tile
    tiles[14]->attach(vertices[32]);
    tiles[14]->attach(vertices[33]);
    tiles[14]->attach(vertices[38]);
    tiles[14]->attach(vertices[39]);
    tiles[14]->attach(vertices[44]);
    tiles[14]->attach(vertices[45]);

    tiles[16]->attach(vertices[37]);
    tiles[16]->attach(vertices[38]);
    tiles[16]->attach(vertices[43]);
    tiles[16]->attach(vertices[44]);
    tiles[16]->attach(vertices[48]);
    tiles[16]->attach(vertices[49]);

    // Vertex neighbours attach to Vertex
    vertices[32]->attachEdge(edges[39]);
    vertices[32]->attachEdge(edges[44]);
    vertices[32]->attachEdge(edges[48]);

    vertices[38]->attachEdge(edges[48]);
    vertices[38]->attachEdge(edges[52]);
    vertices[38]->attachEdge(edges[56]);

    vertices[48]->attachEdge(edges[63]);
    vertices[48]->attachEdge(edges[67]);
    
    vertices[38]->attachVertex(vertices[32]);
    vertices[38]->attachVertex(vertices[37]);
    vertices[38]->attachVertex(vertices[44]);

    vertices[48]->attachVertex(vertices[43]);
    vertices[48]->attachVertex(vertices[49]);


    // attach edge to the neighbour edges
    edges[56]->attachEdge(edges[48]);
    edges[56]->attachEdge(edges[52]);
    edges[56]->attachEdge(edges[61]);
    edges[56]->attachEdge(edges[64]);

    edges[63]->attachEdge(edges[55]);
    edges[63]->attachEdge(edges[60]);
    edges[63]->attachEdge(edges[67]);

    edges[56]->attachVertex(vertices[38]);
    edges[56]->attachVertex(vertices[44]);

    edges[63]->attachVertex(vertices[43]);
    edges[63]->attachVertex(vertices[48]);
    
}