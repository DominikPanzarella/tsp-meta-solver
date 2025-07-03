#include <gtest/gtest.h>
#include "service/algorithm/lkh3solver.h"
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

class LKH3ParamTest : public ::testing::TestWithParam<std::string> {
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

    static const std::unordered_map<std::string, int>& getOptima(){
        static std::unordered_map<std::string, int> optima = LKH3Solver::loadOptima("resources/tsp_optima.csv");
        return optima;
    }
};

TEST_P(LKH3ParamTest, LKH3FastSolveSymmetric) {
    std::string path = GetParam();
    auto problem = loadProblem(path);
    ASSERT_NE(problem, nullptr) << "Problem loading failed for file: " << path;

    std::string name = problem->getName();
    std::string tspFile = "resources/" + name + ".tsp";
    std::string solFile = "tmp_lkh3/solution_" + name + ".txt";
    std::string paramFile = "tmp_lkh3/params_" + name + ".par";

    LKH3Config config;
    config.PROBLEM_FILE = tspFile;
    config.OUTPUT_TOUR_FILE = solFile;
    config.OPTIMUM = std::nullopt;  // carica se disponibile
    config.MAX_TRIALS = 500;        // molto basso per velocità
    config.RUNS = 1;                // poche esecuzioni
    config.SEED = 42;
    config.TRACE_LEVEL = 0;
    config.MAX_CANDIDATES = 5;
    config.MOVE_TYPE = 2;           // 2-opt più veloce, meno potente
    config.BACKTRACKING = false;    // disabilitato
    config.SUBGRADIENT = false;     // disabilitato
    config.RESTRICTED_SEARCH = true; // abilitato per velocità

    const auto& optima = getOptima();
    auto it = optima.find(name);
    if(it != optima.end())
        config.OPTIMUM = it->second;

    LKH3Solver lkh3(LKH3_PATH, config);
    auto solution = lkh3.execute(problem);
    auto tspSolution = std::dynamic_pointer_cast<TspSolution>(solution);
    ASSERT_NE(tspSolution, nullptr);

    auto tspPath = tspSolution->getPath();
    ASSERT_NE(tspPath, nullptr);

    const auto& tour = tspPath->nodes();
    double cost = tspPath->getCost();

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
                         LKH3ParamTest,
                         ::testing::ValuesIn(collectTspInstances("resources")));