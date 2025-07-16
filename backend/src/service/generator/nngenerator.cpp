#include "service/generator/nngenerator.h"
#include <limits>
#include <unordered_set>
#include <iostream>

const std::shared_ptr<NNGenerator> &NNGenerator::getInstance()
{
    static std::shared_ptr<NNGenerator> mySelf(new NNGenerator());
    return mySelf;
}

NNGenerator::SubgraphInfo NNGenerator::buildFi(int i, std::vector<std::vector<int>> &adjMatrix, int &nextNode) const
{
    const int INF = std::numeric_limits<int>::max();

    int eps = 1;
    int cost1 = 1000;                  
    int cost2 = 1000 - eps;   
    int cost3 = 1000 + eps;                 

    if (i == 1)
    {
        int a = nextNode++; // A -_> left
        int b = nextNode++; // B --> middle
        int c = nextNode++; // C --> right

        for (auto &row : adjMatrix)
            row.resize(nextNode, INF);
        adjMatrix.resize(nextNode, std::vector<int>(nextNode, INF));

        adjMatrix[a][b] = cost1;
        adjMatrix[b][a] = cost1;
    
        adjMatrix[b][c] = cost1;
        adjMatrix[c][b] = cost1;

        adjMatrix[a][c] = cost2;
        adjMatrix[c][a] = cost2;


        return {a, b, c};
    }

    SubgraphInfo left = buildFi(i - 1, adjMatrix, nextNode);

    int d = nextNode++; 

    SubgraphInfo right = buildFi(i - 1, adjMatrix, nextNode);

    int oldSize = adjMatrix.size();
    int newSize = nextNode;

    if (newSize > oldSize)
    {
        for (auto &row : adjMatrix)
            row.resize(newSize, INF);
        adjMatrix.resize(newSize, std::vector<int>(newSize, INF));
    }

    int li = getLi(i-1);

    // Arco left.right ↔ d
    adjMatrix[d][left.right] = cost3;
    adjMatrix[left.right][d] = cost3;

    // Arco right.start ↔ d
    adjMatrix[d][right.start] = cost3;
    adjMatrix[right.start][d] = cost3;

    // Arco right.middle ↔ d
    adjMatrix[d][right.middle] = li;
    adjMatrix[right.middle][d] = li;

    // Arco left.middle ↔ right.start
    adjMatrix[left.middle][right.start] = li;
    adjMatrix[right.start][left.middle] = li;

    return {left.start, d, right.right};
}

std::vector<std::vector<int>> NNGenerator::generate(int n, const std::shared_ptr<IShortestPath> &shortestPathSolver) const
{
    const int INF = std::numeric_limits<int>::max();
    std::vector<std::vector<int>> adjMatrix;
    int nextNode = 0;

    int eps = 1;
    int cost1 = 1000;    

    SubgraphInfo info = buildFi(n, adjMatrix, nextNode);

    // Arco middle ↔ start con peso li(n - 1)
    if (n > 1)
    {
        int li_minus1 = getLi(n-1) - 1;
        
        adjMatrix[info.start][info.middle] = li_minus1;
        adjMatrix[info.middle][info.start] = li_minus1;
        adjMatrix[info.start][info.right] = cost1;
        adjMatrix[info.right][info.start] = cost1;

        std::vector<std::vector<int>> distances = shortestPathSolver->shortestPath(adjMatrix);

        for (int i = 0; i < adjMatrix.size(); ++i)
        {
            for (int j = 0; j < adjMatrix.size(); ++j)
            {
                if (adjMatrix[i][j] == INF)
                {
                    adjMatrix[i][j] = distances[i][j];
                }
            }
        }
    }

    // Set diagonale a 0
    for (int i = 0; i < adjMatrix.size(); ++i)
        adjMatrix[i][i] = 0;

    return adjMatrix;
}
