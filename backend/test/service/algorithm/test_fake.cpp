#include <gtest/gtest.h>
#include "service/algorithm/nearestneighbour.h"
#include "service/algorithm/farthestinsertion.h"
#include "service/algorithm/nearestinsertion.h"
#include "repository/problem/iproblem.h"
#include "repository/reader/tspreader.h"
#include "repository/reader/euc2dreader.h"
#include "repository/reader/attreader.h"
#include "repository/reader/ceil2dreader.h"
#include "repository/reader/georeader.h"
#include "repository/reader/matrixreader.h"
#include "service/algorithm/tspsolution.h"
#include "service/algorithm/path.h"
#include "service/executor/singlequeueexecutor.h"
#include "service/algorithm/solutioncollector.h"
#include "utils/testutils.h"
#include <filesystem>
#include <fstream>
#include <sstream>


namespace fs = std::filesystem;

class SingleQueueFakeParamTest : public ::testing::TestWithParam<std::string> {
    protected:
        static std::ofstream result_file;

        static void SetUpTestSuite() {
            bool file_exist = fs::exists("single_queue_fake_instance_solution_report.csv");
            result_file.open("single_queue_fake_instance_solution_report.csv", std::ios::app);
            if(!file_exist)
                result_file << "File,N_TOUR,Cost,Time(us),Path\n";
        }
        
        static void TearDownTestSuite() {
            result_file.close();
        }

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

std::ofstream SingleQueueFakeParamTest::result_file;

TEST_P(SingleQueueFakeParamTest, ExecutorRunsAndProducesValidTour){
    std::string path = GetParam();
    auto problem = loadProblem(path);
    ASSERT_NE(problem, nullptr) << "Problem loading failed: " << path;

    auto algo = std::make_shared<NearestNeighbour>();
    auto algo2 = std::make_shared<NearestInsertion>();
    auto algo3 = std::make_shared<FarthestInsertion>();

    SingleQueueExecutor executor;
    executor.add(algo, problem);
    executor.add(algo2, problem);
    executor.add(algo3, problem);

    executor.run();

    auto collector = executor.getSolutionCollector();
    ASSERT_NE(collector, nullptr);
    ASSERT_EQ(collector->size(), 3);

    const std::vector<std::shared_ptr<ISolution>>& solutions = collector->getSolutions();
    ASSERT_FALSE(solutions.empty());

    for(auto solution : solutions){
        auto tspSolution = std::dynamic_pointer_cast<TspSolution>(solution);
        ASSERT_NE(tspSolution, nullptr);
    
        auto pathObj = tspSolution->getPath();
        ASSERT_NE(pathObj, nullptr);
    
        const auto& tour = pathObj->nodes();
        double cost = pathObj->getCost();
        int n = problem->getDimension();
    
        ASSERT_EQ(tour.size(), n + 1);
        std::vector<bool> visited(n, false);
        for (size_t i = 0; i < tour.size() - 1; ++i) {
            ASSERT_GE(tour[i], 0);
            ASSERT_LT(tour[i], n);
            ASSERT_FALSE(visited[tour[i]]) << "Nodo ripetuto!";
            visited[tour[i]] = true;
        }
        ASSERT_EQ(tour.front(), tour.back()) << "Tour non chiuso!";
        ASSERT_GT(cost, 0.0);
    
        result_file << path << ","
                << solution->getDimension() << ","
                << solution->getCost() << ","
                << solution->getExecutionTime() << "us,";
        for(auto node : pathObj->nodes())
            result_file << node << " ";
        result_file << std::endl;
    
                 // Output a schermo
        std::cout << "✓ " << fs::path(path).filename()
        << " | Nodes: " << n
        << " | Cost: " << cost
        << " | Time: " << solution->getExecutionTime() << "ms"
        << std::endl;
    }


}

    
INSTANTIATE_TEST_SUITE_P(SingleInstanceTest,
    SingleQueueFakeParamTest,
    ::testing::Values("resources/test4.tsp"));
