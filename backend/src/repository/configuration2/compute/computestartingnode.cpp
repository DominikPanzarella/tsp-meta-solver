#include "repository/configuration2/compute/computestartingnode.h"

#include <limits>
#include <iostream>

std::pair<int, int> ComputeStartingNode::computeShortestEdge(std::shared_ptr<IProblem> problem) const
{
    const std::vector<std::vector<int>> &adjMatrix = problem->getGraph().getMatrix();

    int i = -1; // row tracking := first node
    int j = -1; // col tracking := second node

    // We need to brutally check all aviables edges
    int dimension = problem->getDimension();
    int minCost = std::numeric_limits<int>::max();

    for (int row = 0; row < dimension; row++)
    {
        for (int col = 0; col < dimension; col++)
        {
            if (row == col)
                continue;

            int edgeCost = adjMatrix[row][col];

            if (edgeCost < minCost)
            {
                i = row;
                j = col;
                minCost = edgeCost;
            }
        }
    }

    return std::make_pair(i, j);
}

std::vector<std::pair<int, int>> ComputeStartingNode::computeShortestEdges(std::shared_ptr<IProblem> problem) const
{
    const auto &adjMatrix = problem->getGraph().getMatrix();
    int dimension = problem->getDimension();
    int minCost = std::numeric_limits<int>::max();

    std::vector<std::pair<int, int>> results;

    for (int row = 0; row < dimension; ++row)
    {
        for (int col = 0; col < dimension; ++col)
        {
            if (row == col)
                continue;

            int edgeCost = adjMatrix[row][col];

            if (edgeCost > 0)
            {
                if (edgeCost < minCost)
                {
                    minCost = edgeCost;
                    results.clear();
                    results.emplace_back(row, col);
                }
                else if (edgeCost == minCost)
                {
                    results.emplace_back(row, col);
                }
            }
        }
    }

    return results;
}

std::pair<int, int> ComputeStartingNode::computeLongestEdge(std::shared_ptr<IProblem> problem) const
{
    const std::vector<std::vector<int>> &adjMatrix = problem->getGraph().getMatrix();

    int i = -1; // row tracking := first node
    int j = -1; // col tracking := second node

    // We need to brutally check all aviables edges
    int dimension = problem->getDimension();
    int maxCost = std::numeric_limits<int>::min();

    for (int row = 0; row < dimension; row++)
    {
        for (int col = 0; col < dimension; col++)
        {

            if (row == col)
                continue;

            int edgeCost = adjMatrix[row][col];

            if (edgeCost > maxCost)
            {
                i = row;
                j = col;
                maxCost = edgeCost;
            }
        }
    }

    return std::make_pair(i, j);
}

std::vector<std::pair<int, int>> ComputeStartingNode::computeLongestEdges(std::shared_ptr<IProblem> problem) const
{
    const auto &adjMatrix = problem->getGraph().getMatrix();
    int dimension = problem->getDimension();
    int maxCost = std::numeric_limits<int>::min();

    std::vector<std::pair<int, int>> results;

    for (int row = 0; row < dimension; ++row)
    {
        for (int col = 0; col < dimension; ++col)
        {
            if (row == col)
                continue;

            int edgeCost = adjMatrix[row][col];

            if (edgeCost > 0)
            {
                if (edgeCost > maxCost)
                {
                    maxCost = edgeCost;
                    results.clear();
                    results.emplace_back(row, col);
                }
                else if (edgeCost == maxCost)
                {
                    results.emplace_back(row, col);
                }
            }
        }
    }

    return results;
}
