#pragma once

#include "service/generator/integratilitygapgenerator.h"
#include <limits>
#include <unordered_set>
#include <iostream>

const std::shared_ptr<IntegralityGapGenerator> &IntegralityGapGenerator::getInstance()
{
    static std::shared_ptr<IntegralityGapGenerator> mySelf(new IntegralityGapGenerator());
    return mySelf;
}

std::vector<std::vector<int>> IntegralityGapGenerator::generate(int n, const std::shared_ptr<IShortestPath> &shortestPathSolver) const
{
    throw std::logic_error("IntegralityGapGenerator requires parameters a, b, c.");
}

std::vector<std::vector<int>> IntegralityGapGenerator::generate(int a, int b, int c,const std::shared_ptr<IShortestPath> &shortestPathSolver) const{
    int INF = std::numeric_limits<int>::max();

    int nodes_a = a + 1;
    int nodes_b = b + 1;
    int nodes_c = c + 1;

    int n = nodes_a + nodes_b + nodes_c;

    std::vector<std::vector<int>> adj(n, std::vector<int>(n, INF));

    int weight_a = b * c;
    int weight_b = a * c;
    int weight_c = a * b;

    int i;
    // Catena A
    for (int i = 0; i < nodes_a - 1; ++i) {
        adj[i][i + 1] = weight_a;
        adj[i + 1][i] = weight_a;
    }

    // Catena B
    for (int i = nodes_a; i < nodes_a + nodes_b - 1; ++i) {
        adj[i][i + 1] = weight_b;
        adj[i + 1][i] = weight_b;
    }

    // Catena C
    for (int i = nodes_a + nodes_b; i < nodes_a + nodes_b + nodes_c - 1; ++i) {
        adj[i][i + 1] = weight_c;
        adj[i + 1][i] = weight_c;
    }


    
    adj[0][nodes_a] = weight_a + weight_b;
    adj[nodes_a][0] = weight_a + weight_b;

    adj[0][nodes_a + nodes_b] = weight_a + weight_c;
    adj[nodes_a + nodes_b][0] = weight_a + weight_c;

    adj[nodes_a][nodes_a + nodes_b] = weight_b + weight_c;
    adj[nodes_a + nodes_b][nodes_a] = weight_b + weight_c;

    
    adj[nodes_a - 1][nodes_a + nodes_b - 1] = weight_a + weight_b;
    adj[nodes_a + nodes_b- 1][nodes_a - 1] = weight_a + weight_b;

    adj[nodes_a - 1][nodes_a + nodes_b + nodes_c - 1] = weight_a + weight_c;
    adj[nodes_a + nodes_b + nodes_c - 1][nodes_a - 1] = weight_a + weight_c;

    adj[nodes_a + nodes_b -1][nodes_a + nodes_b + nodes_c - 1] = weight_b + weight_c;
    adj[nodes_a + nodes_b + nodes_c - 1][nodes_a + nodes_b -1] = weight_b + weight_c;



    std::vector<std::vector<int>> distances = shortestPathSolver->shortestPath(adj);
        
    for (int i = 0; i < adj.size(); ++i)
    {
        for (int j = 0; j < adj.size(); ++j)
        {
            if (adj[i][j] == INF)
            {
                adj[i][j] = distances[i][j];
            }
        }
    }

    // Set diagonale a 0
    for (int i = 0; i < n; ++i)
        adj[i][i] = 0;

    return adj;

}
