#include <gtest/gtest.h>

#include "controller/tspcontroller.h"
#include "utils/testutils.cpp"
#include "service/generator/shortestPath/floydwarshall.h"
#include "service/generator/nigenerator.h"
#include "controller/constructioncontroller.h"
#include "service/algorithm/nearestinsertion.h"
#include "repository/configuration2/config/iinstancesetting.h"
#include "repository/configuration2/config/nearestinsertioninstancesetting.h"
#include "service/algorithm/isolution.h"
#include <filesystem>
#include <memory>

// === Test ===

TEST(GenerateInstance, GenerateMatrixWith8Nodes) {
    std::shared_ptr<ConstructionController> controller = ConstructionController::getInstance();

    std::shared_ptr<NIGenerator> generator = NIGenerator::getInstance();
    std::shared_ptr<IShortestPath> solver = FloydWarshall::getInstance();
    ASSERT_NE(solver, nullptr) << "FloydWarshall::getInstance() returned nullptr";
    int n = 15;

    auto matrix = generator->generate(n, solver);

    // stampa la matrice
    std::cout << "Generated adjacency matrix (" << n << "x" << n << "):\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val == std::numeric_limits<int>::max())
                std::cout << "INF ";
            else
                std::cout << val << " ";
        }
        std::cout << "\n";
    }

    // Puoi anche aggiungere asserzioni se vuoi:
    EXPECT_EQ(matrix.size(), n);
    for (int i = 0; i < n; ++i) {
        EXPECT_EQ(matrix[i].size(), n);
        EXPECT_EQ(matrix[i][i], 0); // diagonale a zero
    }

    controller->construct("resources", "ni15.tsp",matrix);

    //now test ni

    std::shared_ptr<TspController> tspController = TspController::getInstance();

    std::shared_ptr<IProblem> problem = tspController->read("resources/ni15.tsp");

    ASSERT_NE(problem, nullptr) << "Error reading ni15.tsp";


    std::shared_ptr<IInstanceSetting> setting = std::make_shared<NearestInsertionInstanceSetting>(0);

    NearestInsertion algo;

    std::shared_ptr<ISolution> solution = algo.execute(problem, setting);

    ASSERT_NE(solution, nullptr) << "Error n solutoon";

    const std::shared_ptr<IPath>& path = solution->getPath();

    const std::vector<int>& nodes = path->nodes();

    std::cout << "****** SOLUTION ******" << std::endl;
    for(int i=0; i<nodes.size(); i++)
        std::cout << nodes[i] << " ";

    std::cout << std::endl;
    
    std::cout << "****** TOTAL COST ******" << std::endl;
    std::cout << solution->getCost() << std::endl;


}