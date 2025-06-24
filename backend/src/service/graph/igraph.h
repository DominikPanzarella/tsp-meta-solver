#pragma once
#include <vector>

class IGraph {
public:
    virtual ~IGraph() = default;

    virtual void init(int n_nodes) = 0;

    virtual void setEdge(int i, int j, int weight) = 0;

    virtual int getEdge(int i, int j) const = 0;

    virtual int size() const = 0;

    virtual bool isSymmetric() const = 0;

    virtual bool isComplete() const = 0;

    virtual const std::vector<std::vector<int>>& getMatrix() const = 0;
    
};
