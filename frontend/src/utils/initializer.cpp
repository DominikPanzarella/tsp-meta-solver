#include "initializer.h"

// --- Including controller 
#include "controller/executorcontroller.h"
#include "controller/tspcontroller.h"

// --- Including algorithms 
#include "service/algorithm/concordesolver.h"
#include "service/algorithm/nearestneighbour.h"
#include "service/algorithm/nearestinsertion.h"
#include "service/algorithm/farthestinsertion.h"
#include "service/algorithm/lkh3solver.h"

#include <iostream>
#include <unordered_set>

std::string Initializer::m_resourcesPath = "";
std::string Initializer::m_resultsPath = "";
std::vector<std::shared_ptr<IProblem>> Initializer::problems ={};

void Initializer::init(int argc, char *argv[]){

    // --- Controller setup ---
    std::cout << "Initialization ......" << std::endl;

    const std::shared_ptr<ExecutorController>& executorController = ExecutorController::getInstance();

    const std::shared_ptr<TspController>& tspController = TspController::getInstance();

    std::vector<std::string> paths;
    paths = collectTspInstances(m_resourcesPath);


    if(paths.size() == 0)
    {
        throw std::runtime_error("No .tsp file found");
    }

    for(const auto& path : paths){
        auto problem = tspController->read(path);
        problems.push_back(problem);
    }

    std::vector<std::shared_ptr<IAlgorithm>> algorithms = algoToTest();

    std::cout << "Starting execution ......" << std::endl;

    for(const auto& algorithm : algorithms)
        for(const auto& problem : problems)
            executorController->add(algorithm, problem);


    executorController->run();


    std::cout << "Creating results files ......" << std::endl;

    const auto& collector = executorController->getSolutionCollector();
    bool success = tspController->write(m_resultsPath, "csv", collector);


    std::cout << "Execution done." << std::endl;

}

std::vector<std::string> Initializer::collectTspInstances(const std::string& dir) {
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

    if(!std::filesystem::exists(dir)){
        std::cerr << "Directory requested: " << std::filesystem::absolute(dir) << std::endl;
        throw std::runtime_error("Directory '" + dir + "' does not exist.");
    }

    std::cout << dir << std::endl;

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


//TODO: read from configiration files LKH3 and Concorde configurations + which algo to execute
std::vector<std::shared_ptr<IAlgorithm>> Initializer::algoToTest(){

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
        std::make_shared<LKH3Solver>(LKH3_PATH, m_resourcesPath, config),
        std::make_shared<ConcordeSolver>(CONCORDE_PATH, m_resourcesPath)
    };
}


Initializer::Initializer(const std::string resourcesPath, const std::string resultsPath)
{
    m_resourcesPath = resourcesPath;
    m_resultsPath = resultsPath;
}