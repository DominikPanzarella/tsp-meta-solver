#include <gtest/gtest.h>
#include "repository/reader/georeader.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

// Controlla se il file ha EDGE_WEIGHT_TYPE : GEO
bool isGeoInstance(const fs::path& path) {
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("EDGE_WEIGHT_TYPE") != std::string::npos &&
            line.find("GEO") != std::string::npos)
            return true;
    }
    return false;
}


// Fixture per test parametrico
class GeoParamTest : public ::testing::TestWithParam<std::string> {
protected:
    std::shared_ptr<IProblem> problem;
    std::string path;

    void SetUp() override{
        path = GetParam();

        if (path == "__none__") {
            GTEST_SKIP() << "Test saltato: nessuna istanza matrix trovata.";
        }

        GeoReader reader;
        problem = reader.read(path);
        ASSERT_NE(problem, nullptr) << "Problema non letto da: " << path;
    }
};

GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(GeoParamTest);

// Test vero e proprio
TEST_P(GeoParamTest, ReadGeoInstance) {
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
    EXPECT_EQ(problem->getEdgeWeightType(), EdgeWeightType::GEO);
    EXPECT_EQ(problem->getDisplayDataType(), DisplayDataType::COORD_DISPLAY);
    EXPECT_TRUE(problem->getGraph().isSymmetric()) << "Matrice non simmetrica: " << path;
    EXPECT_TRUE(problem->getGraph().isComplete()) << "Matrice non completa: " << path;
}

TEST_P(GeoParamTest, MatrixIsValidAdjacency) {
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


// Recupera tutti i path GEO
std::vector<std::string> getGeoPaths() {
    std::vector<std::string> paths;
    const std::string resource_dir = "resources";

    if (!fs::exists(resource_dir)) {
        std::cerr << "Directory 'resources/' non trovata\n";
        return {"__none__"};  // fallback
    }

    for (const auto& entry : fs::directory_iterator(resource_dir)) {
        if (entry.path().extension() == ".tsp" && isGeoInstance(entry.path())) {
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

// Istanzia il test per ogni file GEO
INSTANTIATE_TEST_SUITE_P(GeoInstances,
                         GeoParamTest,
                         ::testing::ValuesIn(getGeoPaths()),
                         [](const testing::TestParamInfo<std::string>& info) {
                             fs::path p = info.param;
                             return p.stem().string(); // e.g. "gr96"
                         });
