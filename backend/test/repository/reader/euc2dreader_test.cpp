#include <gtest/gtest.h>

#include "repository/reader/tspreader.h"
#include "repository/reader/euc2dreader.h"
#include "repository/problem/tspproblem.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace fs = std::filesystem;

bool isEuc2DInstance(const fs::path& path){
    std::ifstream file(path);
    std::string line;

    while(std::getline(file, line)){
        if (line.find("EDGE_WEIGHT_TYPE") != std::string::npos &&
            line.find("EUC_2D") != std::string::npos) {
            return true;
        }
    }
    return false;
}

// Test fixture
class Euc2DParamTest : public ::testing::TestWithParam<std::string> {
};

// Actual test
TEST_P(Euc2DParamTest, ReadInstance){
    const std::string& path = GetParam();
    std::ifstream f(path);

    ASSERT_TRUE(f.is_open());

    Euc2DReader reader;
    auto p = reader.read(path);

    ASSERT_NE(p, nullptr) << "Problema non caricato per: " << path;
    ASSERT_NE(p->getName(), "") << "Nome non valido";
    ASSERT_NE(p->getComment(), "") << "Commento non valido";
    ASSERT_NE(p->getType(), "") << "Nome non valido";
    ASSERT_GT(p->getDimension(), 0) << "Dimensione nulla: " << path;
    EXPECT_EQ(p->getEdgeWeightType(), EdgeWeightType::EUC_2D);
    EXPECT_TRUE(p->getGraph().isSymmetric()) << "Non simmetrico: " << path;
    EXPECT_TRUE(p->getGraph().isComplete()) << "Non completo: " << path;


}

// Generate the list of EUC_2D files
std::vector<std::string> getEuc2DPaths() {
    std::vector<std::string> paths;
    const std::string resource_dir = "resources";
    for (const auto& entry : fs::directory_iterator(resource_dir)) {
        if (entry.path().extension() == ".tsp" && isEuc2DInstance(entry.path()))
            paths.push_back(entry.path().string());
    }
    return paths;
}

// Instantiate test case
INSTANTIATE_TEST_SUITE_P(Euc2DInstances,
                         Euc2DParamTest,
                         ::testing::ValuesIn(getEuc2DPaths()),
                         [](const testing::TestParamInfo<std::string>& info) {
                             fs::path p = info.param;
                             return p.stem().string(); // e.g. "a280"
                         });