#include <gtest/gtest.h>

#include "controller/tspcontroller.h"
#include "utils/testutils.cpp"


#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

class TspControllerTest : public ::testing::TestWithParam<std::shared_ptr<IAlgorithm>>  {
protected:
    static std::vector<std::string> paths;
    static std::shared_ptr<TspController> tspController;
    static std::shared_ptr<IExecutor> executor;
    static std::vector<std::shared_ptr<IProblem>> problems;

    static void SetUpTestSuite() {
        const std::string resourcesPath = "resources";
        paths = collectTspInstances(resourcesPath);
        executor = createSingleQueueExecutor();
        tspController = TspController::getInstance();

        for(const auto& path : paths){
            auto problem = tspController->read(path);
            ASSERT_NE(problem, nullptr) << "Failed to read: " << path;
            problems.push_back(problem);
        }
    }

    static void TearDownTestSuite() {
        tspController.reset();
        executor.reset();
    }

    void removeFileIfExists(const std::string& filename){
        if(fs::exists(filename))        fs::remove(filename);
    }


};

std::vector<std::string> TspControllerTest::paths;
std::shared_ptr<TspController> TspControllerTest::tspController;
std::shared_ptr<IExecutor> TspControllerTest::executor;
std::vector<std::shared_ptr<IProblem>> TspControllerTest::problems;

TEST_P(TspControllerTest, ReadAllTspInstances) {

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

    bool success = tspController->write("", "csv", collector);
    EXPECT_TRUE(success);
}

INSTANTIATE_TEST_SUITE_P(
    AlgorithmsTest,
    TspControllerTest,
    ::testing::ValuesIn(
        algoToTest()
    ),
    [](const ::testing::TestParamInfo<std::shared_ptr<IAlgorithm>>& info) {
        return info.param->name();
    }
);

