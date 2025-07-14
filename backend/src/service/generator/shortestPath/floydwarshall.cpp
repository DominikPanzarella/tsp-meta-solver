#include "service/generator/shortestPath/floydwarshall.h"


const std::shared_ptr<FloydWarshall>& FloydWarshall::getInstance(){
    static std::shared_ptr<FloydWarshall> mySelf(new FloydWarshall());
    return mySelf;
}

std::vector<std::vector<int>> FloydWarshall::shortestPath(std::vector<std::vector<int>> adj) const {
    int n = adj.size();
    int INF = std::numeric_limits<int>::max();
    std::vector<std::vector<int>> dist = adj;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; ++j) {
                if (dist[k][j] == INF) continue;

                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
}