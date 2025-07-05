#include <gtest/gtest.h>

#include "repository/reader/tspreader.h"
#include "repository/reader/euc2dreader.h"
#include "repository/reader/attreader.h"
#include "repository/reader/ceil2dreader.h"
#include "repository/reader/georeader.h"
#include "repository/reader/matrixreader.h"
#include "service/problem/tspproblem.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace fs = std::filesystem;

std::vector<std::string> getTestInstancePaths() {
    return {
        "resources/dsj1000.tsp",        //Ceil2D
        "resources/a280.tsp",           //Euc2D
        "resources/brazil58.tsp",       //Matrix
        "resources/gr96.tsp",           //Geo
        "resources/att48.tsp"
    };
}

class CorParamTest : public ::testing::TestWithParam<std::string>{
protected:
    std::shared_ptr<IProblem> problem;
    std::string path;    

    void SetUp() override {
        path = GetParam();

        auto euc2DReader = std::make_shared<Euc2DReader>();
        auto ceil2dReader = std::make_shared<Ceil2dReader>();
        auto matrixReader = std::make_shared<MatrixReader>();
        auto geoReader = std::make_shared<GeoReader>();
        auto attReader = std::make_shared<AttReader>();

        // Setup chain of responsibility
        euc2DReader->set_successor(ceil2dReader);
        ceil2dReader->set_successor(matrixReader);
        matrixReader->set_successor(geoReader);
        geoReader->set_successor(attReader);

        problem = euc2DReader->read(path);
    }

};

TEST_P(CorParamTest, ReadInstances) {
    ASSERT_NE(problem, nullptr) << "Impossibile leggere l'istanza: " << path;
    EXPECT_GT(problem->getDimension(), 0) << "Istanza vuota: " << path;
}


// Instanzia il test con 5 istanze di tipo diverso
INSTANTIATE_TEST_SUITE_P(ReaderChainTests,
    CorParamTest,
    ::testing::ValuesIn(getTestInstancePaths()),
    [](const testing::TestParamInfo<std::string>& info) {
        return fs::path(info.param).stem().string(); // Nome test leggibile
    });