#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <unordered_set>

#include "service/executor/singlequeueexecutor.h"
#include "service/executor/iexecutor.h"
#include "service/algorithm/ialgorithm.h"
#include "service/algorithm/concordesolver.h"
#include "service/algorithm/nearestneighbour.h"
#include "service/algorithm/nearestinsertion.h"
#include "service/algorithm/farthestinsertion.h"
#include "service/algorithm/lkh3solver.h"


inline std::vector<std::string> collectTspInstances(const std::string& dir) {
    std::vector<std::string> paths;
    static const std::unordered_set<std::string> exclude = {
        "brd14051.tsp",
        "d15112.tsp",
        "d18512.tsp",
        "pla33810.tsp",
        "pla85900.tsp",
        "rl11849.tsp",
        "usa13509.tsp",
        "brd14051.tsp",
        "pla7397.tsp",
        "rl5934.tsp",
        "rl5915.tsp",
        "fnl4461.tsp",
        "fl3795.tsp",
        "pcb3038.tsp",
        "u2319.tsp",
        "u2152.tsp",
        "d2103.tsp",
        "rl1889.tsp",
        "u1817.tsp",
        "d1291.tsp",
        "fl1400.tsp",
        "fl1577.tsp",
        "vm1748.tsp",
        "rl1323.tsp",

    };
    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.path().extension() == ".tsp") {
            const std::string filename = entry.path().filename().string();
            if(exclude.find(filename) == exclude.end())
                paths.push_back(entry.path().string());
        }
    }
    std::sort(paths.begin(), paths.end());
    return paths;
}

inline std::shared_ptr<IExecutor> createSingleQueueExecutor(){
    return std::make_shared<SingleQueueExecutor>();
}

inline std::vector<std::shared_ptr<IAlgorithm>> algoToTest(){
    LKH3Config config;
    config.PROBLEM_FILE = "";  // placeholder, sarà sovrascritto da executor
    config.OUTPUT_TOUR_FILE = "tmp_lkh3/temp_solution.txt";
    config.MAX_TRIALS = 500;
    config.RUNS = 1;
    config.SEED = 42;
    config.TRACE_LEVEL = 0;
    config.MAX_CANDIDATES = 5;
    config.MOVE_TYPE = 2;
    config.BACKTRACKING = false;
    config.SUBGRADIENT = false;
    config.RESTRICTED_SEARCH = true;
    
    return {
        std::make_shared<NearestNeighbour>(),
        std::make_shared<NearestInsertion>(),
        std::make_shared<FarthestInsertion>(),
        std::make_shared<LKH3Solver>(LKH3_PATH, config),
        std::make_shared<ConcordeSolver>(CONCORDE_PATH)

    };
}
