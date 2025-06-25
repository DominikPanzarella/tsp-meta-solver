#include <gtest/gtest.h>

#include "repository/reader/tspreader.h"
#include "repository/reader/euc2dreader.h"
#include "repository/problem/tspproblem.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

TEST(Euc2DReaderTest, ReadA280) {
    const std::string& path = "resources/a280.tsp"; // o altro percorso che usi
    std::ifstream f(path);
    std::cout << "Opening file: " << std::filesystem::absolute(path) << " | Is open: " << f.is_open() << std::endl;
    
    ASSERT_TRUE(std::filesystem::exists(path)) << "File a280.tsp non trovato";

    Euc2DReader reader;
    reader.read(path);

    auto problem = reader.getProblem();  // getter aggiunto sotto

    ASSERT_NE(problem, nullptr);
    EXPECT_EQ(problem->getName(), "a280");
    EXPECT_EQ(problem->getDimension(), 280);
    EXPECT_EQ(problem->getEdgeWeightType(), EdgeWeightType::EUC_2D);
    EXPECT_TRUE(problem->getGraph().isSymmetric());
    EXPECT_TRUE(problem->getGraph().isComplete());
}
