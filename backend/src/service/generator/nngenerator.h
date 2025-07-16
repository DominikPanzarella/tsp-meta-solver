#pragma once

#include "service/generator/igenerator.h"
#include <math.h>       /* pow */

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
        int pow2i = pow(2,i);
        int sign = pow(-1,i);
    
        int val = ( (4 * pow2i) - sign + 3) / 6;
        return 1000 * val;
    }
    

    SubgraphInfo buildFi(int i, std::vector<std::vector<int>>& adjMatrix, int& nextNode) const;


};