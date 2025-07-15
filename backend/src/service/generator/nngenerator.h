#pragma once

#include "service/generator/igenerator.h"

class NNGenerator : public IGenerator{

public:
    ~NNGenerator() =default;

    static const std::shared_ptr<NNGenerator>& getInstance();

    virtual std::vector<std::vector<int>> generate(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const override;

protected:
    NNGenerator() =default;

    struct SubgraphInfo {
        int start, middle, right;
    };

    int getLi(int i) const {
        int pow2i = 1 << i; // 2^i
        int sign = (i % 2 == 0) ? 1 : -1; // (-1)^i
    
        double val = (4.0 * pow2i - sign + 3.0) / 6.0;
        return static_cast<int>( 1000 * (val + 0.5));  // arrotondamento
    }
    

    SubgraphInfo buildFi(int i, std::vector<std::vector<int>>& adjMatrix, int& nextNode) const;


};