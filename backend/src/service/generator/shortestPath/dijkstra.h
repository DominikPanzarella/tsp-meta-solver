#pragma once

#include "service/generator/shortestPath/ishortestpath.h"

class Dijkstra : public IShortestPath{
public:
    // Returns shortest distances from src to all other vertices
    virtual std::vector<std::pair<int,int>> shortestPath(std::shared_ptr<IProblem> problem, int src) const override;
};