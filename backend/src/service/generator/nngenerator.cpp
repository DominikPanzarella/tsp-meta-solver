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

    if (i == 1)
    {
        int a = nextNode++; // A: start
        int b = nextNode++; // B: middle
        int c = nextNode++; // C: right

        for (auto &row : adjMatrix)
            row.resize(nextNode, INF);
        adjMatrix.resize(nextNode, std::vector<int>(nextNode, INF));

        adjMatrix[a][b] = adjMatrix[b][a] = 1000;
        adjMatrix[b][c] = adjMatrix[c][b] = 1000;
        adjMatrix[a][c] = adjMatrix[c][a] = 999;

        return {a, b, c};
    }

    SubgraphInfo left = buildFi(i - 1, adjMatrix, nextNode);
    int d = nextNode++; // new middle
    SubgraphInfo right = buildFi(i - 1, adjMatrix, nextNode);

    int oldSize = adjMatrix.size();
    int newSize = nextNode; // dopo aver incrementato nextNode

    if (newSize > oldSize)
    {
        for (auto &row : adjMatrix)
            row.resize(newSize, INF);
        adjMatrix.resize(newSize, std::vector<int>(newSize, INF));
    }

    int li = getLi(i);

    // Arco left.right ↔ d
    adjMatrix[d][left.right] = 1001;
    adjMatrix[left.right][d] = 1001;

    // Arco right.start ↔ d
    adjMatrix[d][right.start] = 1001;
    adjMatrix[right.start][d] = 1001;

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

    SubgraphInfo info = buildFi(n, adjMatrix, nextNode);

    // Arco middle ↔ start con peso li(n - 1)
    if (n > 1)
    {
        int li_minus1 = getLi(n) - 1;
        // adjMatrix[info.middle][info.start] = adjMatrix[info.start][info.middle] = li_minus1;
        adjMatrix[info.start][info.middle] = li_minus1;
        adjMatrix[info.middle][info.start] = li_minus1;
        adjMatrix[info.start][info.right] = 1000;
        adjMatrix[info.right][info.start] = 1000;

        // Set diagonale a 0
        for (int i = 0; i < adjMatrix.size(); ++i)
            adjMatrix[i][i] = 0;

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

    return adjMatrix;
}
