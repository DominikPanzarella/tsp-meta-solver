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
};

// Test vero e proprio
TEST_P(Ceil2dParamTest, ReadCeil2dInstance) {
    const std::string& path = GetParam();

    std::ifstream f(path);
    ASSERT_TRUE(f.is_open()) << "File non apribile: " << path;

    Ceil2dReader reader;
    auto p = reader.read(path);

    ASSERT_NE(p, nullptr) << "Problema non letto da: " << path;
    ASSERT_NE(p->getName(), "") << "Nome non valido";
    ASSERT_NE(p->getType(), "") << "Nome non valido";
    ASSERT_NE(p->getComment(), "") << "Commento non valido";
    ASSERT_GT(p->getDimension(), 0) << "Dimensione nulla: " << path;
    EXPECT_EQ(p->getEdgeWeightType(), EdgeWeightType::CEIL_2D);
    EXPECT_EQ(p->getDisplayDataType(), DisplayDataType::UNKNOWN);
    EXPECT_TRUE(p->getGraph().isSymmetric()) << "Matrice non simmetrica: " << path;
    EXPECT_TRUE(p->getGraph().isComplete()) << "Matrice non completa: " << path;
}

// Recupera tutti i path Att
std::vector<std::string> getCeil2dPaths() {
    std::vector<std::string> paths;
    const std::string resource_dir = "resources";
    for (const auto& entry : fs::directory_iterator(resource_dir)) {
        if (entry.path().extension() == ".tsp" && isCeil2dInstance(entry.path())) {
            paths.push_back(entry.path().string());
        }
    }
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
