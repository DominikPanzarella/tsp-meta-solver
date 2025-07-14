#include <gtest/gtest.h>

#include "controller/tspcontroller.h"
#include "utils/testutils.cpp"
#include "service/generator/shortestPath/floydwarshall.h"
#include "service/generator/nigenerator.h"

#include <filesystem>
#include <memory>

// === Test ===

TEST(NIGeneratorTest, GenerateMatrixWith8Nodes) {
    std::shared_ptr<NIGenerator> generator = NIGenerator::getInstance();
    std::shared_ptr<IShortestPath> solver = FloydWarshall::getInstance();
    ASSERT_NE(solver, nullptr) << "FloydWarshall::getInstance() returned nullptr";
    int n = 8;

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
}