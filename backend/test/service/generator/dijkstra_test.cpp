#include <gtest/gtest.h>

#include "controller/tspcontroller.h"
#include "utils/testutils.cpp"
#include "service/generator/shortestPath/dijkstra.h"

#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

class DijkstraTest : public ::testing::TestWithParam<std::shared_ptr<IAlgorithm>>  {
protected:
    static std::vector<std::string> paths;
    static std::shared_ptr<TspController> tspController;
    static std::vector<std::shared_ptr<IProblem>> problems;
    static std::shared_ptr<Dijkstra> m_dijkstra;

    static void SetUpTestSuite() {
        const std::string resourcesPath = "resources";
        paths = collectTspInstances(resourcesPath);
        tspController = TspController::getInstance();
        m_dijkstra  = std::make_shared<Dijkstra>();

        for(const auto& path : paths){
            auto problem = tspController->read(path);
            ASSERT_NE(problem, nullptr) << "Failed to read: " << path;
            problems.push_back(problem);
        }
    }

    static void TearDownTestSuite() {
        tspController.reset();
    }


};

std::vector<std::string> DijkstraTest::paths;
std::shared_ptr<TspController> DijkstraTest::tspController;
std::vector<std::shared_ptr<IProblem>> DijkstraTest::problems;
std::shared_ptr<Dijkstra> DijkstraTest:: m_dijkstra;

TEST_F(DijkstraTest, ReadAllTspInstances) {
    for(const auto& problem : problems){
        int n = problem->getDimension();
        ASSERT_GT(n, 0);

        // Esegui Dijkstra dal nodo 0
        auto result = m_dijkstra->shortestPath(problem, 0); // vector<pair<int, int>>
        ASSERT_EQ(result.size(), n);

        std::cout << "Source Node: " << "[" << 0 << "]" << std::endl;
        std::cout << "===== SHORTEST PATH =====" << std::endl;
        for(auto [dist, pred] : result){
            std::cout << "[" << pred << "] ----" << "(" << dist << ")" << std::endl;
        }

        for (int i = 0; i < n; ++i) {
            int dist = result[i].first;
            int pred = result[i].second;

            if (i == 0) {
                EXPECT_EQ(dist, 0);
                EXPECT_EQ(pred, -1);
            } else {
                if (dist < INT_MAX) {
                    EXPECT_GE(pred, 0);
                    EXPECT_LT(pred, n);

                    int weight = problem->getGraph().getEdge(pred, i);
                    EXPECT_EQ(dist, result[pred].first + weight);
                }
            }
        }

    }
   
}
