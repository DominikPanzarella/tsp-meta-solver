#include <gtest/gtest.h>
#include "utils/testutils.h"
#include <filesystem>
#include <fstream>

#include "service/algorithm/nearestneighbour.h"
#include "service/algorithm/nearestinsertion.h"
#include "service/algorithm/farthestinsertion.h"
#include "service/algorithm/lkh3solver.h"
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

class CsvWriterAlgoTest : public ::testing::TestWithParam<std::shared_ptr<IAlgorithm>> {
    protected:
        static std::vector<std::shared_ptr<IProblem>> problems;
    
        static void SetUpTestSuite() {
            const std::string resourcesPath = "resources";
            auto paths = collectTspInstances(resourcesPath);
    
            auto euc2DReader = std::make_shared<Euc2DReader>();
            auto ceil2dReader = std::make_shared<Ceil2dReader>();
            auto matrixReader = std::make_shared<MatrixReader>();
            auto geoReader = std::make_shared<GeoReader>();
            auto attReader = std::make_shared<AttReader>();
    
            euc2DReader->set_successor(ceil2dReader);
            ceil2dReader->set_successor(matrixReader);
            matrixReader->set_successor(geoReader);
            geoReader->set_successor(attReader);
    
            for (const auto& path : paths) {
                auto problem = euc2DReader->read(path);
                ASSERT_NE(problem, nullptr) << "Failed to read: " << path;
                problems.push_back(problem);
            }
        }
    
        static void TearDownTestSuite() {
            problems.clear();  // cleanup
        }
    
        void removeFileIfExists(const std::string& filename) {
            if (fs::exists(filename)) fs::remove(filename);
        }
    };
    
    // Inizializzazione del campo statico
    std::vector<std::shared_ptr<IProblem>> CsvWriterAlgoTest::problems;
    
    TEST_P(CsvWriterAlgoTest, RunAlgorithmOnLoadedInstancesAndWriteCsv) {
        auto algorithm = GetParam();
        ASSERT_NE(algorithm, nullptr);
    
        SingleQueueExecutor executor;
        CsvWriter writer;
    
        for (const auto& problem : problems) {
            executor.add(algorithm, problem);
        }
    
        executor.run();
    
        std::string filename = "results_" + algorithm->name() + ".csv";
        removeFileIfExists(filename);
    
        const auto& collector = executor.getSolutionCollector();
        const auto& solutionsByAlgo = collector->getSolutions();
    
        //ASSERT_TRUE(solutionsByAlgo.contains(algorithm->name()));
    
        for (const auto& solution : solutionsByAlgo.at(algorithm->name())) {
            ASSERT_NE(solution, nullptr);
            ASSERT_NE(solution->getProblem(), nullptr);
        }
    
        bool success = writer.write("", "csv", collector);
        EXPECT_TRUE(success);
    }

    INSTANTIATE_TEST_SUITE_P(
        AlgorithmTests,
        CsvWriterAlgoTest,
        ::testing::Values(
            std::make_shared<NearestNeighbour>(),
            std::make_shared<NearestInsertion>(),
            std::make_shared<FarthestInsertion>(),
            std::make_shared<LKH3Solver>()
        ),
        [](const ::testing::TestParamInfo<std::shared_ptr<IAlgorithm>>& info) {
            return info.param->name();
        }
    );
    
