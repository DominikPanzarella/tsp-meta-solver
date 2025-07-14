#include "service/generator/shortestPath/dijkstra.h"

#include <queue>
#include <functional>   // std::greater

std::vector<std::pair<int,int>> Dijkstra::shortestPath(std::shared_ptr<IProblem> problem, int src) const{
    const std::vector<std::vector<int>>& adj = problem->getGraph().getMatrix();
    int n = problem->getDimension();


    // Create a vector for distances and initialize all
    // distances as infinite
    std::vector<int> dist(n, INT_MAX);

    std::vector<int> prev(n, -1);       // predecessori

    using P = std::pair<int,int>;       // {distanza, nodo}

    // Create a priority queue to store vertices that
    // are being preprocessed.
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

    pq.emplace(0, src);
    dist[src] = 0;

    while (!pq.empty()){
        
        auto [d, u] = pq.top();
        pq.pop();

        for (int v = 0; v < adj[u].size(); ++v) {
            int weight = adj[u][v];
            if (weight <= 0 || u == v) continue;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.emplace(dist[v], v);
            }
        }
        
    }

    std::vector<std::pair<int,int>> result(n);
    for(int i=0; i<n; i++)
        result[i] = {dist[i], prev[i]};

    return result;
}
