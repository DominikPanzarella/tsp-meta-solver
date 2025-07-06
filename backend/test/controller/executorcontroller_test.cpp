#include <gtest/gtest.h>

#include "controller/executorcontroller.h"
#include "controller/tspcontroller.h"
#include "utils/testutils.cpp"


#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

class ExecutorControllerTest : public ::testing::TestWithParam<std::shared_ptr<IAlgorithm>>  {
protected:
    static std::vector<std::string> paths;
    static std::shared_ptr<ExecutorController> executorController;
    static std::shared_ptr<TspController> tspController;
    static std::vector<std::shared_ptr<IProblem>> problems;

    static void SetUpTestSuite() {
        const std::string resourcesPath = "resources";
        paths = collectTspInstances(resourcesPath);
        tspController = TspController::getInstance();
        executorController = ExecutorController::getInstance();

        for(const auto& path : paths){
            auto problem = tspController->read(path);
            ASSERT_NE(problem, nullptr) << "Failed to read: " << path;
            problems.push_back(problem);
        }
    }

    static void TearDownTestSuite() {
        tspController.reset();
        executorController.reset();
    }

    void removeFileIfExists(const std::string& filename){
        if(fs::exists(filename))        fs::remove(filename);
    }


};

std::vector<std::string> ExecutorControllerTest::paths;
std::shared_ptr<TspController> ExecutorControllerTest::tspController;
std::shared_ptr<ExecutorController> ExecutorControllerTest::executorController;
std::vector<std::shared_ptr<IProblem>> ExecutorControllerTest::problems;

TEST_P(ExecutorControllerTest, ReadAllTspInstances) {

    const auto& algorithm = GetParam();
    ASSERT_NE(algorithm, nullptr);

    for (const auto& problem : problems) {
        executorController->add(algorithm, problem);
    }

    executorController->run();

    std::string filename = "results_" + algorithm->name() + ".csv";
    removeFileIfExists(filename);

    const auto& collector = executorController->getSolutionCollector();
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
    ExecutorControllerTest,
    ::testing::ValuesIn(
        algoToTest()
    ),
    [](const ::testing::TestParamInfo<std::shared_ptr<IAlgorithm>>& info) {
        return info.param->name();
    }
);

