#include <gtest/gtest.h>

#include "controller/tspcontroller.h"
#include "utils/testutils.cpp"
#include "service/generator/shortestPath/floydwarshall.h"
#include "service/generator/nngenerator.h"

#include <filesystem>
#include <memory>

// === Test ===

TEST(NNGeneratorTest, GenerateMatrixWith8Nodes) {
    std::shared_ptr<NNGenerator> generator = NNGenerator::getInstance();
    std::shared_ptr<IShortestPath> solver = FloydWarshall::getInstance();
    ASSERT_NE(solver, nullptr) << "FloydWarshall::getInstance() returned nullptr";
    int n = 1;

    auto matrix = generator->generate(n, solver);

    // stampa la matrice
    std::cout << "Generated adjacency matrix (" << matrix.size() << "x" << matrix.size() << "):\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val == std::numeric_limits<int>::max())
                std::cout << "INF ";
            else
                std::cout << val << " ";
        }
        std::cout << "\n";
    }

    n = 2;

    matrix = generator->generate(n, solver);

    // stampa la matrice
    std::cout << "Generated adjacency matrix (" << matrix.size() << "x" << matrix.size() << "):\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val == std::numeric_limits<int>::max())
                std::cout << "INF ";
            else
                std::cout << val << " ";
        }
        std::cout << "\n";
    }

    n = 3;

    matrix = generator->generate(n, solver);

    // stampa la matrice
    std::cout << "Generated adjacency matrix (" << matrix.size() << "x" << matrix.size() << "):\n";
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
}