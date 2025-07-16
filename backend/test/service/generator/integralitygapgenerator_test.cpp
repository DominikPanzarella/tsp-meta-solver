#include <gtest/gtest.h>

#include "controller/tspcontroller.h"
#include "utils/testutils.cpp"
#include "service/generator/shortestPath/floydwarshall.h"
#include "service/generator/integratilitygapgenerator.h"

#include <filesystem>
#include <memory>

// === Test ===

TEST(IGGeneratorTest, GenerateMatrixWith8Nodes) {
    std::shared_ptr<IntegralityGapGenerator> generator = IntegralityGapGenerator::getInstance();
    std::shared_ptr<IShortestPath> solver = FloydWarshall::getInstance();
    ASSERT_NE(solver, nullptr) << "FloydWarshall::getInstance() returned nullptr";
    int a = 3;
    int b = 2;
    int c = 3;

    auto matrix = generator->generate(a,b,c, solver);

    // stampa la matrice
    std::cout << "Generated adjacency matrix (a:"<<a<<",b:"<<b<<",c"<<c<<")"<<std::endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val == std::numeric_limits<int>::max())
                std::cout << "INF ";
            else
                std::cout << val << " ";
        }
        std::cout << "\n";
    }
}