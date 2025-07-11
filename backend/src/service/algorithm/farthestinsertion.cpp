#include "farthestinsertion.h"
#include "service/algorithm/ipath.h"
#include "service/algorithm/path.h"
#include "service/algorithm/tspsolution.h"
#include "repository/configuration2/config/farthestinsertioninstancesetting.h"
#include <chrono>
#include <unordered_set>
#include <limits>
#include <vector>
#include <memory>

std::string FarthestInsertion::name() const {
    return "FarthestInsertion";
}

std::shared_ptr<ISolution> FarthestInsertion::execute(std::shared_ptr<IProblem> problem, std::shared_ptr<IInstanceSetting> instanceSettings) {
    const auto& dist = problem->getGraph().getMatrix();
    int n = problem->getDimension();
    if (n == 0) return nullptr;

    std::vector<int> tour;
    std::unordered_set<int> notInTour;
    std::vector<bool> inTour(n, false);

    auto setting = std::dynamic_pointer_cast<FarthestInsertionInstanceSetting>(instanceSettings);
    if (!setting)
        throw std::runtime_error("Wrong Instance Settings given as parameter");

    int startingNode = setting->getStartingNode();
    if (startingNode < 0 || startingNode >= n)
        throw std::runtime_error("Starting node is out of bounds");

    // Step 1: Start with startingNode
    tour.push_back(startingNode);
    inTour[startingNode] = true;

    for (int i = 0; i < n; ++i) {
        if (i != startingNode) {
            notInTour.insert(i);
        }
    }

    // Step 2: Insert the farthest node from startingNode
    int farthest = -1;
    double maxDist = -1.0;
    for (int j : notInTour) {
        if (dist[startingNode][j] > maxDist) {
            maxDist = dist[startingNode][j];
            farthest = j;
        }
    }

    tour.push_back(farthest);
    inTour[farthest] = true;
    notInTour.erase(farthest);

    while (!notInTour.empty()) {
        int bestCandidate = -1;
        double bestMinDist = -1.0;

        for (int v : notInTour) {
            double minDistToTour = std::numeric_limits<double>::infinity();
            for (int u : tour) {
                if (dist[u][v] < minDistToTour) {
                    minDistToTour = dist[u][v];
                }
            }

            if (minDistToTour > bestMinDist) {
                bestMinDist = minDistToTour;
                bestCandidate = v;
            }
        }

        double bestInsertionCost = std::numeric_limits<double>::infinity();
        auto insertPos = tour.end();

        for (auto it = tour.begin(); it != tour.end(); ++it) {
            auto nextIt = std::next(it);
            if (nextIt == tour.end()) nextIt = tour.begin();  // close the tour

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

    // Close the tour
    tour.push_back(tour[0]);

    // Calculate total cost
    double totalCost = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        totalCost += dist[tour[i]][tour[i + 1]];
    }

    auto path = std::make_shared<Path>(tour, totalCost);
    return std::make_shared<TspSolution>(path, problem);
}
