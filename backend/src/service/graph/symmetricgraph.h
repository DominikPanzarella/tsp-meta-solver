#pragma once

//////////////
// #INCLUDE //
//////////////
#include "igraph.h"

#include <vector>

class SymmetricGraph : public IGraph{
public:

    /** Graph management **/

    //Default construcotr
    SymmetricGraph() = default;

    //Destructor
    ~SymmetricGraph() = default;

    //Copy Constructor
    SymmetricGraph(const SymmetricGraph& other) = default;

    // Copy Assignment Operator
    SymmetricGraph& operator=(const SymmetricGraph& other) = delete;

    // Move Constructor
    SymmetricGraph(SymmetricGraph&& other) = delete;

    void init(int n_nodes) override;

    void setEdge(int x, int y, int weight) override;

    int getEdge(int x, int y) const override;

    int size() const override;

    bool isSymmetric() const override;

    bool isComplete() const override;

    const std::vector<std::vector<int>>& getMatrix() const override;


private:
    std::vector<std::vector<int>> adjacencyMatrix;

    int n_nodes;
};