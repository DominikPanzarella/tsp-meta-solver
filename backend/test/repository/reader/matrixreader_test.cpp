#include <gtest/gtest.h>
#include "repository/reader/matrixreader.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace fs = std::filesystem;

bool isMatrixInstance(const fs::path& path) {
    std::ifstream file(path);
    std::string line;
    bool isExplicit = false;
    bool hasFormat = false;

    while (std::getline(file, line)) {
        if (line.find("EDGE_WEIGHT_TYPE") != std::string::npos &&
            line.find("EXPLICIT") != std::string::npos) {
            isExplicit = true;
        }
        if (line.find("EDGE_WEIGHT_FORMAT") != std::string::npos) {
            hasFormat = true;
        }
    }

    return isExplicit && hasFormat;
}

std::vector<std::string> getMatrixPaths() {
    std::vector<std::string> paths;
    const std::string resource_dir = "resources";

    if (!fs::exists(resource_dir)) {
        std::cerr << "Directory 'resources/' non trovata\n";
        return {"__none__"};  // fallback
    }

    for (const auto& entry : fs::directory_iterator(resource_dir)) {
        if (entry.path().extension() == ".tsp" && isMatrixInstance(entry.path())) {
            paths.push_back(entry.path().string());
        }
    }

    if (paths.empty()) {
        std::cerr << "⚠️ Nessuna istanza EXPLICIT trovata in /resources\n";
        return {"__none__"};
    }

    std::cout << "✓ Trovate " << paths.size() << " istanze EXPLICIT.\n";
    return paths;
}

static std::vector<std::string> matrix_paths = getMatrixPaths();

class MatrixParamTest : public ::testing::TestWithParam<std::string> {
protected:
    std::shared_ptr<IProblem> problem;
    std::string path;

    void SetUp() override {
        path = GetParam();

        if (path == "__none__") {
            GTEST_SKIP() << "Test saltato: nessuna istanza matrix trovata.";
        }

        MatrixReader reader;
        problem = reader.read(path);
        ASSERT_NE(problem, nullptr) << "Problema non letto da: " << path;
    }
};

GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(MatrixParamTest);

TEST_P(MatrixParamTest, ReadMatrixInstance) {
    std::cout << "✓ Path: " << path << "\n";
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

    EXPECT_FALSE(problem->getName().empty()) << "Nome non valido";
    EXPECT_FALSE(problem->getType().empty()) << "Tipo non valido";
    EXPECT_GT(problem->getDimension(), 0) << "Dimensione nulla: " << path;
    EXPECT_EQ(problem->getEdgeWeightType(), EdgeWeightType::EXPLICIT);
    EXPECT_TRUE(problem->getGraph().isSymmetric()) << "Matrice non simmetrica: " << path;
    EXPECT_TRUE(problem->getGraph().isComplete()) << "Matrice non completa: " << path;
}

TEST_P(MatrixParamTest, MatrixIsValidAdjacency) {
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

INSTANTIATE_TEST_SUITE_P(MatrixInstances,
                         MatrixParamTest,
                         ::testing::ValuesIn(matrix_paths),
                         [](const testing::TestParamInfo<std::string>& info) {
                             return fs::path(info.param).stem().string(); // es: gr96
                         });
