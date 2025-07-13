#include "nearestinsertion.h"
#include "service/algorithm/ipath.h"
#include "service/algorithm/path.h"
#include "service/algorithm/tspsolution.h"
#include "repository/configuration2/config/nearestinsertioninstancesetting.h"
#include <chrono>
#include <unordered_set>
#include <limits>
#include <vector>
#include <memory>

std::string NearestInsertion::name() const {
    return "NearestInsertion";
}

std::shared_ptr<ISolution> NearestInsertion::execute(std::shared_ptr<IProblem> problem, std::shared_ptr<IInstanceSetting> instanceSettings){
    const auto& dist = problem->getGraph().getMatrix();
    int n = problem->getDimension();
    if (n == 0) return nullptr;

    std::vector<int> tour;
    std::unordered_set<int> notInTour;
    std::vector<bool> inTour(n, false);

    std::shared_ptr<NearestInsertionInstanceSetting> setting = std::dynamic_pointer_cast<NearestInsertionInstanceSetting>(instanceSettings);

    if(setting == nullptr)      throw std::runtime_error("Wrong Instance Settings given as parameter [NI]");

    int startingNode = setting->getStartingNode();

    if (startingNode < 0 || startingNode >= n)      throw std::runtime_error("Starting node is out of bounds");

    tour.push_back(startingNode);

    inTour[startingNode] = true;

    for (int i = 0; i < n; ++i) {
        if (i != startingNode) {
            notInTour.insert(i);
        }
    }

    // Insert nearest node from startingNode
    int nearest = -1;
    double minDist = std::numeric_limits<double>::infinity();
    for (int j : notInTour) {
        if (dist[startingNode][j] < minDist) {
            minDist = dist[startingNode][j];
            nearest = j;
        }
    }

    tour.push_back(nearest);
    inTour[nearest] = true;
    notInTour.erase(nearest);

    while (!notInTour.empty()) {
        int bestCandidate = -1;
        double bestMinDist = std::numeric_limits<double>::infinity(); // note: smallest distance!

        for (int v : notInTour) {
            double minDistToTour = std::numeric_limits<double>::infinity();
            for (int u : tour) {
                if (dist[u][v] < minDistToTour) {
                    minDistToTour = dist[u][v];
                }
            }

            // In NearestInsertion pick the node with smallest minDistToTour
            if (minDistToTour < bestMinDist) {
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

    std::shared_ptr<IPath> path = std::make_shared<Path>(tour, totalCost);
    auto solution = std::make_shared<TspSolution>(path, problem);

    return solution;
}