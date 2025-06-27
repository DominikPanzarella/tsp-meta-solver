#include <gtest/gtest.h>

#include "repository/tsprepository.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace fs = std::filesystem;

std::vector<std::string> getCorTestInstancePaths() {
    return {
        "resources/dsj1000.tsp",        //Ceil2D
        "resources/a280.tsp",           //Euc2D
        "resources/brazil58.tsp",       //Matrix
        "resources/gr96.tsp",           //Geo
        "resources/att48.tsp"
    };
}

class TspRepoParamTest : public ::testing::TestWithParam<std::string>{
protected:
    std::shared_ptr<IProblem> problem;
    std::string path;    

    void SetUp() override {
        path = GetParam();

        TspRepository tspRepository;

        // Setup chain of responsibility

        problem = tspRepository.read(path);
    }

};

TEST_P(TspRepoParamTest, ReadInstances) {
    ASSERT_NE(problem, nullptr) << "Impossibile leggere l'istanza: " << path;
    EXPECT_GT(problem->getDimension(), 0) << "Istanza vuota: " << path;
}


// Instanzia il test con 5 istanze di tipo diverso
INSTANTIATE_TEST_SUITE_P(ReaderChainTests,
    TspRepoParamTest,
    ::testing::ValuesIn(getCorTestInstancePaths()),
    [](const testing::TestParamInfo<std::string>& info) {
        return fs::path(info.param).stem().string(); // Nome test leggibile
    });