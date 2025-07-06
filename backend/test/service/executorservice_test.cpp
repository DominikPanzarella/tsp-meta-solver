#include <gtest/gtest.h>

#include "service/executorservice.h"
#include "service/tspservice.h"
#include "utils/testutils.cpp"


#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

class ExecutorServiceTest : public ::testing::TestWithParam<std::shared_ptr<IAlgorithm>>  {
protected:
    static std::vector<std::string> paths;
    static std::shared_ptr<ExecutorService> executorService;
    static std::shared_ptr<TspService> tspService;
    static std::vector<std::shared_ptr<IProblem>> problems;

    static void SetUpTestSuite() {
        const std::string resourcesPath = "resources";
        paths = collectTspInstances(resourcesPath);

        tspService = TspService::getInstance();
        executorService = ExecutorService::getInstance();

        ASSERT_NE(tspService, nullptr) << "tspService is null";
        ASSERT_NE(executorService, nullptr) << "executorService is null";

        for(const auto& path : paths){
            auto problem = tspService->read(path);
            ASSERT_NE(problem, nullptr) << "Failed to read: " << path;
            problems.push_back(problem);
        }
    }

    static void TearDownTestSuite() {
        tspService.reset();
        executorService.reset();
    }

    void removeFileIfExists(const std::string& filename){
        if(fs::exists(filename))        fs::remove(filename);
    }


};

std::vector<std::string> ExecutorServiceTest::paths;
std::shared_ptr<TspService> ExecutorServiceTest::tspService;
std::shared_ptr<ExecutorService> ExecutorServiceTest::executorService;
std::vector<std::shared_ptr<IProblem>> ExecutorServiceTest::problems;

TEST_P(ExecutorServiceTest, ReadAllTspInstances) {

    const auto& algorithm = GetParam();
    ASSERT_NE(algorithm, nullptr);

    for (const auto& problem : problems) {
        executorService->add(algorithm, problem);
    }

    executorService->run();

    std::string filename = "results_" + algorithm->name() + ".csv";
    removeFileIfExists(filename);

    const auto& collector = executorService->getSolutionCollector();
    const auto& solutionsByAlgo = collector->getSolutions();
    ASSERT_NE(collector, nullptr) << "SolutionCollector is null";

    for (const auto& solution : solutionsByAlgo.at(algorithm->name())) {
        ASSERT_NE(solution, nullptr);
        ASSERT_NE(solution->getProblem(), nullptr);
    }

    bool success = tspService->write("", "csv", collector);
    EXPECT_TRUE(success);
}

INSTANTIATE_TEST_SUITE_P(
    AlgorithmsTest,
    ExecutorServiceTest,
    ::testing::ValuesIn(
        algoToTest()
    ),
    [](const ::testing::TestParamInfo<std::shared_ptr<IAlgorithm>>& info) {
        return info.param->name();
    }
);

