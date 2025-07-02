#include <gtest/gtest.h>
#include "service/algorithm/nearestneighbour.h"
#include "repository/problem/iproblem.h"
#include "repository/reader/tspreader.h"
#include "repository/reader/euc2dreader.h"
#include "repository/reader/attreader.h"
#include "repository/reader/ceil2dreader.h"
#include "repository/reader/georeader.h"
#include "repository/reader/matrixreader.h"
#include "service/algorithm/tspsolution.h"
#include "service/algorithm/path.h"
#include "service/executor/workstealingexecutor.h"
#include "service/algorithm/solutioncollector.h"
#include "utils/testutils.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <chrono>

namespace fs = std::filesystem;

class WorkStealingExecutorTest : public ::testing::TestWithParam<std::string> {
protected:
    std::shared_ptr<IProblem> loadProblem(const std::string& path) {
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

        return euc2DReader->read(path);
    }
};

TEST_P(WorkStealingExecutorTest, TasksAreDistributedAndExecutedWithStealing) {
    std::string path = GetParam();
    auto problem = loadProblem(path);
    ASSERT_NE(problem, nullptr) << "Problem loading failed: " << path;

    WorkStealingExecutor executor(11);
    auto algo = std::make_shared<NearestNeighbour>();

    // Inseriamo più task (per esempio 8, così che debbano distribuirsi)
    int nTasks = 8;
    for (int i = 0; i < nTasks; ++i) {
        executor.add(algo, problem);
    }

    // Controlliamo che i task siano distribuiti nelle code
    auto queueSizesBefore = executor.getQueueSizes();
    int totalTasksBefore = 0;
    for (auto s : queueSizesBefore) totalTasksBefore += s;
    EXPECT_EQ(totalTasksBefore, nTasks) << "Tutti i task devono essere messi nelle code";

    // Avviamo l'esecuzione
    executor.run();

    // Dopo esecuzione le code dovrebbero essere vuote o quasi vuote
    auto queueSizesAfter = executor.getQueueSizes();
    int totalTasksAfter = 0;
    for (auto s : queueSizesAfter) totalTasksAfter += s;

    EXPECT_LT(totalTasksAfter, totalTasksBefore) << "Alcuni task devono essere eseguiti e rimossi dalle code";

    // Il collector deve avere tutte le soluzioni
    auto collector = executor.getSolutionCollector();
    ASSERT_NE(collector, nullptr);
    EXPECT_GE(collector->size(), 1);
    EXPECT_LE(collector->size(), nTasks);

    // Verifichiamo che tutte le soluzioni siano valide
    const auto& solutionsMap = collector->getSolutions();
    ASSERT_FALSE(solutionsMap.empty()) << "La mappa delle soluzioni è vuota";

    // Itera su ogni algoritmo e sulle sue soluzioni
    for (const auto& [algoName, solutionsVec] : solutionsMap) {
        ASSERT_FALSE(solutionsVec.empty()) << "Nessuna soluzione per algoritmo " << algoName;
        for (const auto& sol : solutionsVec) {
            ASSERT_NE(sol, nullptr);
            auto tspSol = std::dynamic_pointer_cast<TspSolution>(sol);
            ASSERT_NE(tspSol, nullptr);
            auto pathObj = tspSol->getPath();
            ASSERT_NE(pathObj, nullptr);
            EXPECT_GT(pathObj->nodes().size(), 1);
        }
    }
}

INSTANTIATE_TEST_SUITE_P(AllTspInstances,
                         WorkStealingExecutorTest,
                         ::testing::ValuesIn(collectTspInstances("resources")));
