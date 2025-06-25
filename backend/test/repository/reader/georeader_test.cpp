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
};

// Test vero e proprio
TEST_P(GeoParamTest, ReadGeoInstance) {
    const std::string& path = GetParam();

    std::ifstream f(path);
    ASSERT_TRUE(f.is_open()) << "File non apribile: " << path;

    GeoReader reader;
    reader.read(path);
    auto p = reader.getProblem();

    ASSERT_NE(p, nullptr) << "Problema non letto da: " << path;
    ASSERT_NE(p->getName(), "") << "Nome non valido";
    ASSERT_NE(p->getType(), "") << "Nome non valido";
    ASSERT_NE(p->getComment(), "") << "Commento non valido";
    ASSERT_GT(p->getDimension(), 0) << "Dimensione nulla: " << path;
    EXPECT_EQ(p->getEdgeWeightType(), EdgeWeightType::GEO);
    EXPECT_EQ(p->getDisplayDataType(), DisplayDataType::COORD_DISPLAY);
    EXPECT_TRUE(p->getGraph().isSymmetric()) << "Matrice non simmetrica: " << path;
    EXPECT_TRUE(p->getGraph().isComplete()) << "Matrice non completa: " << path;
}

// Recupera tutti i path GEO
std::vector<std::string> getGeoPaths() {
    std::vector<std::string> paths;
    const std::string resource_dir = "resources";
    for (const auto& entry : fs::directory_iterator(resource_dir)) {
        if (entry.path().extension() == ".tsp" && isGeoInstance(entry.path())) {
            paths.push_back(entry.path().string());
        }
    }
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
