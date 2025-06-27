#include <gtest/gtest.h>
#include "repository/reader/ceil2dreader.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

// Controlla se il file ha EDGE_WEIGHT_TYPE : ATT
bool isCeil2dInstance(const fs::path& path) {
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("EDGE_WEIGHT_TYPE") != std::string::npos &&
            line.find("CEIL_2D") != std::string::npos)
            return true;
    }
    return false;
}

// Fixture per test parametrico
class Ceil2dParamTest : public ::testing::TestWithParam<std::string> {
    protected:
        std::shared_ptr<IProblem> problem;
        std::string path;

        void SetUp(){
            path = GetParam();

            if (path == "__none__") {
                GTEST_SKIP() << "Test saltato: nessuna istanza matrix trovata.";
            }
    
            Ceil2dReader reader;
            problem = reader.read(path);
            ASSERT_NE(problem, nullptr) << "Problema non letto da: " << path;
        }
};

// Test vero e proprio
TEST_P(Ceil2dParamTest, ReadCeil2dInstance) {
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

    ASSERT_NE(problem, nullptr) << "Problema non letto da: " << path;
    ASSERT_NE(problem->getName(), "") << "Nome non valido";
    ASSERT_NE(problem->getType(), "") << "Nome non valido";
    ASSERT_NE(problem->getComment(), "") << "Commento non valido";
    ASSERT_GT(problem->getDimension(), 0) << "Dimensione nulla: " << path;
    EXPECT_EQ(problem->getEdgeWeightType(), EdgeWeightType::CEIL_2D);
    EXPECT_EQ(problem->getDisplayDataType(), DisplayDataType::UNKNOWN);
    EXPECT_TRUE(problem->getGraph().isSymmetric()) << "Matrice non simmetrica: " << path;
    EXPECT_TRUE(problem->getGraph().isComplete()) << "Matrice non completa: " << path;
}

TEST_P(Ceil2dParamTest, MatrixIsValidAdjacency) {
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

// Recupera tutti i path Att
std::vector<std::string> getCeil2dPaths() {
    std::vector<std::string> paths;
    const std::string resource_dir = "resources";

    if (!fs::exists(resource_dir)) {
        std::cerr << "Directory 'resources/' non trovata\n";
        return {"__none__"};  // fallback
    }

    for (const auto& entry : fs::directory_iterator(resource_dir)) {
        if (entry.path().extension() == ".tsp" && isCeil2dInstance(entry.path())) {
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

// Istanzia il test per ogni file ATT
INSTANTIATE_TEST_SUITE_P(Ceil2dInstances,
                         Ceil2dParamTest,
                         ::testing::ValuesIn(getCeil2dPaths()),
                         [](const testing::TestParamInfo<std::string>& info) {
                             fs::path p = info.param;
                             return p.stem().string(); // e.g. "att48.tsp"
                         });
