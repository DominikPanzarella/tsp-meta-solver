#include "service/generator/nigenerator.h"
#include <limits>
#include <unordered_set>
#include <iostream>

const std::shared_ptr<NIGenerator>& NIGenerator::getInstance(){
    static std::shared_ptr<NIGenerator> mySelf(new NIGenerator());
    return mySelf;
}

std::vector<std::vector<int>> NIGenerator::generate(int a, int b, int c,const std::shared_ptr<IShortestPath> &shortestPathSolver) const{
    throw std::logic_error("NIGenerator doesn't require parameters a, b, c.");
}

std::vector<std::vector<int>> NIGenerator::generate(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const {

    int INF = std::numeric_limits<int>::max();
    std::vector<std::vector<int>> adjMatrix(n, std::vector<int>(n, INF));

    int eps = 1;
    int cost1 = 1000;                  // costo per archi (i, i+1)
    int cost2 = 2000 - eps;            // costo per archi (i, i+2)


    //Step 1
    for (int i = 0; i < n; ++i) {
        int j = (i + 1 ) % n;
        adjMatrix[i][j] = cost1;
        adjMatrix[j][i] = cost1;
    }

    //Step 2
    for(int i=0; i<n; ++i){
        int j = (i + 2 ) % n;
        adjMatrix[i][j] = cost2;
        adjMatrix[j][i] = cost2;
    }

    for (int i = 0; i < n; ++i) {
        adjMatrix[i][i] = 0;
    }

    std::vector<std::vector<int>> distances = shortestPathSolver->shortestPath(adjMatrix);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] == INF) {
                adjMatrix[i][j] = distances[i][j];
            }
        }
    }

    return adjMatrix;

}