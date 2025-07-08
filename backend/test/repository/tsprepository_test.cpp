#include <gtest/gtest.h>

#include "repository/tsprepository.h"
#include "utils/testutils.cpp"


#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

class TspRepositoryTest : public ::testing::TestWithParam<std::shared_ptr<IAlgorithm>>  {
protected:
    static std::vector<std::string> paths;
    static std::unique_ptr<TspRepository> tspRepository;
    static std::shared_ptr<IExecutor> executor;
    static std::vector<std::shared_ptr<IProblem>> problems;

    static void SetUpTestSuite() {
        const std::string resourcesPath = "resources";
        paths = collectTspInstances(resourcesPath);
        executor = createSingleQueueExecutor();
        tspRepository = std::make_unique<TspRepository>();

        for(const auto& path : paths){
            auto problem = tspRepository->read(path);
            ASSERT_NE(problem, nullptr) << "Failed to read: " << path;
            problems.push_back(problem);
        }
    }

    static void TearDownTestSuite() {
        tspRepository.reset();
        executor.reset();
    }

    void removeFileIfExists(const std::string& filename){
        if(fs::exists(filename))        fs::remove(filename);
    }


};

std::vector<std::string> TspRepositoryTest::paths;
std::unique_ptr<TspRepository> TspRepositoryTest::tspRepository;
std::shared_ptr<IExecutor> TspRepositoryTest::executor;
std::vector<std::shared_ptr<IProblem>> TspRepositoryTest::problems;

TEST_P(TspRepositoryTest, ReadAllTspInstances) {

    const auto& algorithm = GetParam();
    ASSERT_NE(algorithm, nullptr);

    for (const auto& problem : problems) {
        executor->add(algorithm, problem);
    }

    executor->run();

    std::string filename = "results_" + algorithm->name() + ".csv";
    removeFileIfExists(filename);

    const auto& collector = executor->getSolutionCollector();
    const auto& solutionsByAlgo = collector->getSolutions();
    ASSERT_NE(collector, nullptr) << "SolutionCollector is null";

    for (const auto& solution : solutionsByAlgo.at(algorithm->name())) {
        ASSERT_NE(solution, nullptr);
        ASSERT_NE(solution->getProblem(), nullptr);
    }

    bool success = tspRepository->write("results", "csv", collector);
    EXPECT_TRUE(success);
}

INSTANTIATE_TEST_SUITE_P(
    AlgorithmsTest,
    TspRepositoryTest,
    ::testing::ValuesIn(
        algoToTest()
    ),
    [](const ::testing::TestParamInfo<std::shared_ptr<IAlgorithm>>& info) {
        return info.param->name();
    }
);

