//////////////
// #INCLUDE //
//////////////

#include "symmetricgraph.h"


void SymmetricGraph::init(int n_nodes) {
    this->n_nodes = n_nodes;
    //adjacencyMatrix = std::vector<std::vector<int>>(n_nodes, std::vector<int>(n_nodes, 0));
    adjacencyMatrix.resize(n_nodes, std::vector<int>(n_nodes, -1)); // -1 = no arco

}

void SymmetricGraph::setEdge(int x, int y, int weight) {
    if(x<0 || x>=n_nodes)   throw new std::invalid_argument("SymmetricGraph::setEdge() x parameter not valid");

    if(y<0 || y>=n_nodes)   throw new std::invalid_argument("SymmetricGraph::setEdge() y parameter not valid");

    adjacencyMatrix[x][y] = weight;
    adjacencyMatrix[y][x] = weight;
}

int SymmetricGraph::getEdge(int x, int y) const {
    if(x<0 || x>=n_nodes)   throw new std::invalid_argument("SymmetricGraph::getEdge() x parameter not valid");
    
    if(y<0 || y>=n_nodes)   throw new std::invalid_argument("SymmetricGraph::getEdge() y parameter not valid");

    return adjacencyMatrix[x][y];
}

int SymmetricGraph::size() const {
    return adjacencyMatrix.size();
}

bool SymmetricGraph::isSymmetric() const {
    return true;
}

bool SymmetricGraph::isComplete() const {
    for (int i = 0; i < n_nodes; ++i)
        for (int j = 0; j < n_nodes; ++j)
            if (i != j && adjacencyMatrix[i][j] == -1)
                return false;
    return true;
}

const std::vector<std::vector<int>>& SymmetricGraph::getMatrix() const {
    return adjacencyMatrix;
}