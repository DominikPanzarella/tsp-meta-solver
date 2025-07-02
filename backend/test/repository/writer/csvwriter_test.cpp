#include <gtest/gtest.h>
#include "utils/testutils.h"
#include <filesystem>
#include <fstream>

#include "service/algorithm/nearestneighbour.h"
#include "service/algorithm/nearestinsertion.h"
#include "service/algorithm/farthestinsertion.h"
#include "repository/problem/iproblem.h"
#include "repository/reader/tspreader.h"
#include "repository/reader/euc2dreader.h"
#include "repository/reader/attreader.h"
#include "repository/reader/ceil2dreader.h"
#include "repository/reader/georeader.h"
#include "repository/reader/matrixreader.h"
#include "service/algorithm/solutioncollector.h"
#include "service/executor/singlequeueexecutor.h"
#include "repository/writer/csvwriter.h"

namespace fs = std::filesystem;

class CsvWriterTest : public ::testing::Test {
protected:
    std::shared_ptr<IProblem> loadProblem(const std::string& path) {
        auto euc2DReader = std::make_shared<Euc2DReader>();
        auto ceil2dReader = std::make_shared<Ceil2dReader>();
        auto matrixReader = std::make_shared<MatrixReader>();
        auto geoReader = std::make_shared<GeoReader>();
        auto attReader = std::make_shared<AttReader>();

        euc2DReader->set_successor(ceil2dReader);
        ceil2dReader->set_successor(matrixReader);
        matrixReader->set_successor(geoReader);
        geoReader->set_successor(attReader);

        return euc2DReader->read(path);
    }

    std::vector<std::shared_ptr<IAlgorithm>> getAlgorithms() {
        return {
            std::make_shared<NearestNeighbour>()
        };
    }

    void removeFileIfExists(const std::string& filename) {
        if (fs::exists(filename)) fs::remove(filename);
    }
};

TEST_F(CsvWriterTest, RunAllAlgorithmsOnAllInstancesAndWriteCsv) {
    const std::string resourcesPath = "resources";
    auto instances = collectTspInstances(resourcesPath);
    
    SingleQueueExecutor executor;
    CsvWriter writer;


    auto algorithms = getAlgorithms();

    // 1) Per ogni istanza e per ogni algoritmo: eseguo separatamente e raccolgo
    for (const auto& filepath : instances) {
        auto problem = loadProblem(filepath);
        ASSERT_NE(problem, nullptr) << "Failed to load problem: " << filepath;

        for (const auto& algo : algorithms) {
            executor.add(algo, problem);
        }
    }

    executor.run();

    // 2) Rimuovo eventuali file CSV preesistenti
    for (const auto& algo : algorithms) {
        std::string fn = "results_" + algo->name() + ".csv";
        removeFileIfExists(fn);
    }

    const auto& collector = executor.getSolutionCollector();
    const auto& solutionsByAlgo = collector->getSolutions();

    for(const auto& [algoName, solutions] : solutionsByAlgo) {
        for(const auto& solution : solutions){
            ASSERT_NE(solution, nullptr) << "Solution is nullptr for algo: " << algoName;
            ASSERT_NE(solution->getProblem(), nullptr) << "Problem is nullptr for algo: " << algoName;
            std::cout << algoName << " -- " << solution->getProblem()->getName() << std::endl;
        }
    }


    ASSERT_GT(solutionsByAlgo.size(),0);

    bool success = writer.write("", "csv",collector);

    EXPECT_TRUE(success);

}
