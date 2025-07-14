#pragma once

#include "service/generator/shortestPath/ishortestpath.h"

class FloydWarshall : public IShortestPath {
public:

    ~FloydWarshall() = default;

    static const std::shared_ptr<FloydWarshall>& getInstance();

    // Returns shortest distances from src to all other vertices
    virtual std::vector<std::vector<int>> shortestPath(std::vector<std::vector<int>> adj) const override;

private:

    FloydWarshall() = default;

};