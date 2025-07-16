#include "initializer.h"

// --- Including controller 
#include "controller/executorcontroller.h"
#include "controller/tspcontroller.h"
#include "controller/configcontroller.h"
#include "controller/constructioncontroller.h"

// --- Including algorithms 
#include "service/algorithm/concordesolver.h"
#include "service/algorithm/nearestneighbour.h"
#include "service/algorithm/nearestinsertion.h"
#include "service/algorithm/farthestinsertion.h"
#include "service/algorithm/lkh3solver.h"

#include "repository/configuration2/configprovider.h"
#include "repository/configuration2/config/nearestneighbourgeneralsetting.h"
#include "repository/configuration2/config/nearestinsertiongeneralsetting.h"
#include "repository/configuration2/config/concordegeneralsetting.h"
#include "repository/configuration2/config/lkh3generalsetting.h"
#include "repository/configuration2/config/farthestinsertiongeneralsetting.h"

#include "service/generator/shortestPath/floydwarshall.h"



#include <iostream>
#include <unordered_set>

std::string Initializer::m_resourcesPath = "";
std::string Initializer::m_resultsPath = "";
std::string Initializer::m_format = "";
std::vector<std::shared_ptr<IProblem>> Initializer::problems ={};

void Initializer::init(int argc, char *argv[]){

    // --- Controller setup ---
    std::cout << "Initialization ......" << std::endl;

    const std::shared_ptr<ConfigController>& provider = ConfigController::getInstance();
    provider->read("../tspmetasolver.json");

    const std::shared_ptr<ConstructionController> constructionController = ConstructionController::getInstance();


    // ########################################################
    // # Configure Algorithms                                #
    // ########################################################
    provider->configureAlgorithms();
    std::shared_ptr<NearestInsertionGeneralSetting> ni   = provider->getNearestInsertionSettings();
    std::shared_ptr<NearestNeighbourGeneralSetting> nn   = provider->getNearestNeighbourSettings();
    std::shared_ptr<FarthestInsertionGeneralSetting> fi  = provider->getFarthestInsertionSettings();
    std::shared_ptr<ConcordeGeneralSetting> cc           = provider->getConcordeSettings();
    std::shared_ptr<LKH3GeneralSetting> lkh3             = provider->getLKH3Settings();


    for(auto dim : ni->getHardInstancesNumberOfNodes()){
        std::vector<std::vector<int>> adj = constructionController->generateNI(dim, FloydWarshall::getInstance());
        std::string filename = "ni" + std::to_string(dim) + "_generated";
        constructionController->construct(argv[1], filename , adj);
    }

    for(auto dim : nn->getHardInstancesNumberOfNodes()){
        std::vector<std::vector<int>> adj = constructionController->generateNN(dim, FloydWarshall::getInstance());
        std::string filename = "nn" + std::to_string(dim) + "_generated";
        constructionController->construct(argv[1], filename , adj);
    }


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

    provider->configureProblems(problems);

    std::vector<std::shared_ptr<IAlgorithm>> algorithms;


    
    for(const std::string& algo : provider->getEnabledAlgorithms())
    {
        if (algo == "NearestInsertion") {
            algorithms.push_back(std::make_shared<NearestInsertion>());
        }
        else if (algo == "NearestNeighbour") {
            algorithms.push_back(std::make_shared<NearestNeighbour>());
        }
        else if (algo == "FarthestInsertion") {
            algorithms.push_back(std::make_shared<FarthestInsertion>());
        }
        else if (algo == "LKH3") {
            algorithms.push_back(std::make_shared<LKH3Solver>(LKH3_PATH, m_resourcesPath, lkh3));
        }
        else if (algo == "Concorde") {
            algorithms.push_back(std::make_shared<ConcordeSolver>(CONCORDE_PATH, m_resourcesPath, cc));
        }
    }


    std::cout << "Starting execution ......" << std::endl;

    for (const auto& algorithm : algorithms) {
        for (const auto& problem : problems) {
            std::string algoName = algorithm->name();
            std::string probName = problem->getName();
    
            std::shared_ptr<IInstanceSetting> setting;
    
            if (algoName == "NearestInsertion") {
                setting = provider->getNearestInsertionSettings()->getInstance(probName);
            } else if (algoName == "NearestNeighbour") {
                setting = provider->getNearestNeighbourSettings()->getInstance(probName);
            } else if (algoName == "FarthestInsertion") {
                setting = provider->getFarthestInsertionSettings()->getInstance(probName);
            } else if (algoName == "LKH3") {
                setting = provider->getLKH3Settings()->getInstance(probName);
            } else if (algoName == "Concorde") {
                setting = provider->getConcordeSettings()->getInstance(probName);
            }
    
            executorController->add(algorithm, problem, setting);
        }
    }

    
    executorController->run();


    std::cout << "Creating results files ......" << std::endl;

    const auto& collector = executorController->getSolutionCollector();
    bool success = tspController->write(m_resultsPath, m_format, collector);


    std::cout << "Execution done." << std::endl;

}

std::vector<std::string> Initializer::collectTspInstances(const std::string& dir) {
    std::vector<std::string> paths;
    static const std::unordered_set<std::string> exclude = {
        "brd14051.tsp", "d15112.tsp", "d18512.tsp", "pla33810.tsp", "pla85900.tsp",
        "rl11849.tsp", "usa13509.tsp", "brd14051.tsp", "pla7397.tsp", "rl5934.tsp",
        "rl5915.tsp", "fnl4461.tsp", "fl3795.tsp", "pcb3038.tsp", "u2319.tsp",
        "u2152.tsp", "d2103.tsp", "rl1889.tsp", "u1817.tsp", "d1291.tsp",
        "fl1400.tsp", "fl1577.tsp", "vm1748.tsp", "rl1323.tsp",
        "Tnm118.tsp", "Tnm121.tsp", "Tnm124.tsp", "Tnm127.tsp", "Tnm130.tsp",
        "Tnm133.tsp", "Tnm136.tsp", "Tnm139.tsp", "Tnm142.tsp", "Tnm145.tsp",
        "Tnm148.tsp", "Tnm151.tsp", "Tnm154.tsp", "Tnm157.tsp", "Tnm160.tsp",
        "Tnm163.tsp", "Tnm166.tsp", "Tnm169.tsp", "Tnm172.tsp", "Tnm175.tsp",
        "Tnm178.tsp", "Tnm181.tsp", "Tnm184.tsp", "Tnm187.tsp", "Tnm190.tsp",
        "Tnm193.tsp", "Tnm196.tsp", "Tnm199.tsp"
    };
    

    if (!std::filesystem::exists(dir)) {
        std::cerr << "Directory requested: " << std::filesystem::absolute(dir) << std::endl;
        throw std::runtime_error("Directory '" + dir + "' does not exist.");
    }

    std::cout << dir << std::endl;

    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.path().extension() == ".tsp") {
            const std::string filename = entry.path().filename().string();

            // Esclude file se sono nella lista exclude o contengono "_hard"
            if (exclude.find(filename) == exclude.end() && filename.find("_hard") == std::string::npos) {
                paths.push_back(entry.path().string());
            }
        }
    }

    std::sort(paths.begin(), paths.end());
    return paths;
}


Initializer::Initializer(const std::string resourcesPath, const std::string resultsPath, const std::string format)
{
    m_resourcesPath = resourcesPath;
    m_resultsPath = resultsPath;
    m_format = format;
}