#include <gtest/gtest.h>
#include "service/algorithm/nearestneighbour.h"
#include "repository/problem/iproblem.h"
#include "repository/reader/tspreader.h"
#include "repository/reader/euc2dreader.h"
#include "repository/reader/attreader.h"
#include "repository/reader/ceil2dreader.h"
#include "repository/reader/georeader.h"
#include "repository/reader/matrixreader.h"
#include "service/algorithm/tspsolution.h"
#include "service/algorithm/path.h"
#include "utils/testutils.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

class NNParamTest : public ::testing::TestWithParam<std::string> {
protected:
    std::shared_ptr<IProblem> loadProblem(const std::string& path) {

        auto euc2DReader = std::make_shared<Euc2DReader>();
        auto ceil2dReader = std::make_shared<Ceil2dReader>();
        auto matrixReader = std::make_shared<MatrixReader>();
        auto geoReader = std::make_shared<GeoReader>();
        auto attReader = std::make_shared<AttReader>();

        // Setup chain of responsibility
        euc2DReader->set_successor(ceil2dReader);
        ceil2dReader->set_successor(matrixReader);
        matrixReader->set_successor(geoReader);
        geoReader->set_successor(attReader);


        return euc2DReader->read(path);
    }
};

TEST_P(NNParamTest, NearestNeighbourGivesValidTour) {
    std::string path = GetParam();
    auto problem = loadProblem(path);
    ASSERT_NE(problem, nullptr) << "Problem loading failed for file: " << path;

    NearestNeighbour nn;
    auto solution = nn.execute(problem);
    auto tspSolution = std::dynamic_pointer_cast<TspSolution>(solution);
    ASSERT_NE(tspSolution, nullptr);

    auto tspPath = tspSolution->getPath();
    ASSERT_NE(tspPath, nullptr);

    const auto& tour = tspPath->nodes();
    double cost = tspPath->getCost();

    // Verifica: tour valido (tutti i nodi visitati una sola volta tranne il ritorno)
    int n = problem->getDimension();
    ASSERT_EQ(tour.size(), n + 1);
    std::vector<bool> visited(n, false);
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        ASSERT_GE(tour[i], 0);
        ASSERT_LT(tour[i], n);
        ASSERT_FALSE(visited[tour[i]]) << "Nodo ripetuto nel tour!";
        visited[tour[i]] = true;
    }

    ASSERT_EQ(tour.front(), tour.back()) << "Tour non chiuso correttamente!";
    ASSERT_GT(cost, 0.0);
}


INSTANTIATE_TEST_SUITE_P(AllTspInstances,
                         NNParamTest,
                         ::testing::ValuesIn(collectTspInstances("resources")));
