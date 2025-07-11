#include "nearestneighbour.h"
#include "service/algorithm/ipath.h"
#include "service/algorithm/path.h"
#include "service/algorithm/tspsolution.h"
#include "repository/configuration2/config/nearestneighbourinstancesetting.h"
#include <chrono>

std::string NearestNeighbour::name() const {
    return "NearestNeighbour";
}

std::shared_ptr<ISolution> NearestNeighbour::execute(std::shared_ptr<IProblem> problem,std::shared_ptr<IInstanceSetting> instanceSettings) {
   
    const auto& dist = problem->getGraph().getMatrix();
    int n = problem->getDimension();

    std::vector<bool> visited(n, false);
    std::vector<int> tour;


    std::shared_ptr<NearestNeighbourInstanceSetting> setting = std::dynamic_pointer_cast<NearestNeighbourInstanceSetting>(instanceSettings);

    if(setting == nullptr)      throw std::runtime_error("Wrong Instance Settings given as parameter");

    int current = setting->getStartingNode();

    if (current < 0 || current >= n)      throw std::runtime_error("Starting node is out of bounds");

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


    std::shared_ptr<IPath> path = std::make_shared<Path>(tour, totalCost);
    auto solution = std::make_shared<TspSolution>(path, problem);


    return solution;
}
