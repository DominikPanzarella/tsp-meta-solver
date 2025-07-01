#include "nearestneighbour.h"
#include "service/algorithm/ipath.h"
#include "service/algorithm/path.h"
#include "service/algorithm/tspsolution.h"
#include <chrono>

std::string NearestNeighbour::name() const {
    return "NearestNeighbour";
}

std::shared_ptr<ISolution> NearestNeighbour::execute(std::shared_ptr<IProblem> problem) {
    auto start = std::chrono::high_resolution_clock::now(); //start misuring time
    const auto& dist = problem->getGraph().getMatrix();
    int n = problem->getDimension();

    std::vector<bool> visited(n, false);
    std::vector<int> tour;

    int current = 0; // nodo iniziale
    visited[current] = true;
    tour.push_back(current);

    double totalCost = 0.0;

    for (int step = 1; step < n; ++step) {
        double minDist = std::numeric_limits<double>::infinity();
        int next = -1;

        for (int i = 0; i < n; ++i) {
            if (!visited[i] && dist[current][i] < minDist) {
                minDist = dist[current][i];
                next = i;
            }
        }

        if (next == -1) break;

        visited[next] = true;
        tour.push_back(next);
        totalCost += dist[current][next];
        current = next;
    }

    // Chiusura tour
    totalCost += dist[current][tour[0]];
    tour.push_back(tour[0]);


    auto end = std::chrono::high_resolution_clock::now();       // End misuring time
    int duration_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::shared_ptr<IPath> path = std::make_shared<Path>(tour, totalCost);
    auto solution = std::make_shared<TspSolution>(path);
    solution->setExecutionTime(duration_us);

    return solution;
}
