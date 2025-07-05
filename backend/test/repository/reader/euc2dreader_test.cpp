#include <gtest/gtest.h>

#include "repository/reader/tspreader.h"
#include "repository/reader/euc2dreader.h"
#include "service/problem/tspproblem.h"
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
protected:
    std::shared_ptr<IProblem> problem;
    std::string path;

    void SetUp() override{
        path = GetParam();

        if (path == "__none__") {
            GTEST_SKIP() << "Test saltato: nessuna istanza matrix trovata.";
        }

        Euc2DReader reader;
        problem = reader.read(path);
        ASSERT_NE(problem, nullptr) << "Problema non letto da: " << path;
    }
};

GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(Euc2DParamTest);

// Actual test
TEST_P(Euc2DParamTest, ReadInstance){
    std::cout << "Path: " << path << "\n";
    std::cout << "Dimension: " << problem->getDimension() << std::endl;

    const auto& matrix = problem->getGraph().getMatrix();
    int size = matrix.size();

    std::cout << "Matrix rows: " << size << std::endl;

    bool flag = true;
    for (int i = 0; i < size; i++) {
        if (matrix[i].size() != size) flag = false;
    }

    std::cout << "All rows have the same number of columns: " << (flag ? "True" : "False") << std::endl;

    problem->PrintMatrix();
    
    ASSERT_NE(problem->getName(), "") << "Nome non valido";
    ASSERT_NE(problem->getComment(), "") << "Commento non valido";
    ASSERT_NE(problem->getType(), "") << "Nome non valido";
    ASSERT_GT(problem->getDimension(), 0) << "Dimensione nulla: " << path;
    EXPECT_EQ(problem->getEdgeWeightType(), EdgeWeightType::EUC_2D);
    EXPECT_TRUE(problem->getGraph().isSymmetric()) << "Non simmetrico: " << path;
    EXPECT_TRUE(problem->getGraph().isComplete()) << "Non completo: " << path;


}

TEST_P(Euc2DParamTest, MatrixIsValidAdjacency) {
    const auto& matrix = problem->getGraph().getMatrix();
    int n = matrix.size();

    ASSERT_EQ(n, problem->getDimension()) << "Dimensione della matrice non corrisponde.";

    for (int i = 0; i < n; ++i) {
        ASSERT_EQ(matrix[i].size(), n) << "Riga " << i << " ha dimensione diversa da " << n;

        for (int j = 0; j < n; ++j) {
            if (i == j) {
                EXPECT_EQ(matrix[i][j], 0) << "Elemento diagonale (" << i << "," << j << ") non è zero.";
            } else {
                EXPECT_EQ(matrix[i][j], matrix[j][i])
                    << "Matrice non simmetrica: matrix[" << i << "][" << j << "] != matrix[" << j << "][" << i << "]";
            }
        }
    }
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