#include <gtest/gtest.h>
#include "repository/reader/matrixreader.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace fs = std::filesystem;

// ✅ Controlla se è un'istanza EXPLICIT
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


// ✅ Recupera i path validi
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

// ✅ Lista statica per evitare doppio parsing
static std::vector<std::string> matrix_paths = getMatrixPaths();

// ✅ Classe di test parametrico
class MatrixParamTest : public ::testing::TestWithParam<std::string> {};
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(MatrixParamTest);

// ✅ Test vero e proprio
TEST_P(MatrixParamTest, ReadMatrixInstance) {
    const std::string& path = GetParam();

    if (path == "__none__") {
        GTEST_SKIP() << "Test saltato: nessuna istanza matrix trovata.";
    }

    std::ifstream f(path);
    ASSERT_TRUE(f.is_open()) << "File non apribile: " << path;

    MatrixReader reader;
    auto p = reader.read(path);

    std::cout << "Dimension: " << p->getDimension() << std::endl;
    int size = p->getGraph().getMatrix().size();
    auto matrix = p->getGraph().getMatrix();
    std::cout << "Matrix rows:" <<  size << std::endl;

    bool flag = true;
    for(int i=0; i<size; i++){
        if(matrix[i].size() != size)    flag = false;
    }

    std::cout << "All rows have the same numbero of column: " <<  (flag?"True":"False") << std::endl;

    p->PrintMatrix();

    ASSERT_NE(p, nullptr) << "Problema non letto da: " << path;
    EXPECT_FALSE(p->getName().empty()) << "Nome non valido";
    EXPECT_FALSE(p->getType().empty()) << "Tipo non valido";
    //EXPECT_FALSE(p->getComment().empty()) << "Commento non valido";
    EXPECT_GT(p->getDimension(), 0) << "Dimensione nulla: " << path;
    EXPECT_EQ(p->getEdgeWeightType(), EdgeWeightType::EXPLICIT);
    EXPECT_TRUE(p->getGraph().isSymmetric()) << "Matrice non simmetrica: " << path;
    EXPECT_TRUE(p->getGraph().isComplete()) << "Matrice non completa: " << path;
}

// Istanziazione dei test
INSTANTIATE_TEST_SUITE_P(MatrixInstances,
                         MatrixParamTest,
                         ::testing::ValuesIn(matrix_paths),
                         [](const testing::TestParamInfo<std::string>& info) {
                             return fs::path(info.param).stem().string(); // e.g. gr96
                         });
