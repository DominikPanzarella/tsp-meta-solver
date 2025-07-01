#include "nearestinsertion.h"
#include "service/algorithm/ipath.h"
#include "service/algorithm/path.h"
#include "service/algorithm/tspsolution.h"
#include <omp.h>  // Include OpenMP
#include <chrono>
#include <unordered_set>

std::string NearestInsertion::name() const {
    return "FarthestInsertion";
}


std::shared_ptr<ISolution> NearestInsertion::execute(std::shared_ptr<IProblem> problem) {
    auto start = std::chrono::high_resolution_clock::now();

    const auto& dist = problem->getGraph().getMatrix();
    int n = problem->getDimension();
    if (n == 0) return nullptr;

    std::vector<int> tour;
    std::unordered_set<int> notInTour;
    std::vector<bool> inTour(n, false);

    // Step 1: Start with node 0
    tour.push_back(0);
    inTour[0] = true;
    for (int i = 1; i < n; ++i) {
        notInTour.insert(i);
    }

    // Step 2: Insert the node nearest to 0
    int nearest = -1;
    double minDist = std::numeric_limits<double>::infinity();
    for (int j : notInTour) {
        if (dist[0][j] < minDist) {
            minDist = dist[0][j];
            nearest = j;
        }
    }

    tour.push_back(nearest);
    inTour[nearest] = true;
    notInTour.erase(nearest);

    while (!notInTour.empty()) {
        int bestCandidate = -1;
        double bestDist = std::numeric_limits<double>::infinity();
        
        for (int v : notInTour) {
            for (int u : tour) {
                if (dist[u][v] < bestDist) {
                    bestDist = dist[u][v];
                    bestCandidate = v;
                }
            }
        }

        double bestInsertionCost = std::numeric_limits<double>::infinity();
        auto insertPos = tour.end();

        for (auto it = tour.begin(); it != tour.end(); ++it) {
            auto nextIt = std::next(it);
            if (nextIt == tour.end()) nextIt = tour.begin();  // chiusura tour

            int u = *it;
            int w = *nextIt;
            double insertionCost = dist[u][bestCandidate] + dist[bestCandidate][w] - dist[u][w];

            if (insertionCost < bestInsertionCost) {
                bestInsertionCost = insertionCost;
                insertPos = nextIt;
            }
        }

        tour.insert(insertPos, bestCandidate);
        inTour[bestCandidate] = true;
        notInTour.erase(bestCandidate);
    }

    // Chiusura tour
    tour.push_back(tour[0]);

    // Calcolo del costo totale
    double totalCost = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        totalCost += dist[tour[i]][tour[i + 1]];
    }

    auto end = std::chrono::high_resolution_clock::now();
    int execTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::shared_ptr<IPath> path = std::make_shared<Path>(tour, totalCost);
    auto solution = std::make_shared<TspSolution>(path);
    solution->setExecutionTime(execTimeUs);  // Richiede che TspSolution supporti setExecutionTime()

    return solution;
}