#include "concordesolver.h"
#include "service/algorithm/path.h"
#include "service/algorithm/tspsolution.h"

#include "repository/configuration2/config/concordeinstancesetting.h"
#include "repository/configuration2/config/concordegeneralsetting.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

ConcordeSolver::ConcordeSolver(const std::string& concordePath, const std::string& resourcesPath ,std::shared_ptr<IGeneralSetting> concordeSetting)
    : m_concordePath(std::filesystem::absolute(concordePath)),
      m_resourcesPath(resourcesPath),
      m_config(std::move(concordeSetting)),
      m_workingDir(std::filesystem::absolute("tmp_concorde"))
{
    if(std::filesystem::exists(m_workingDir))
        std::filesystem::remove_all(m_workingDir);
    std::filesystem::create_directories(m_workingDir);
}

std::string ConcordeSolver::name() const {
    return "Concorde";
}

std::shared_ptr<ISolution> ConcordeSolver::execute(std::shared_ptr<IProblem> problem,std::shared_ptr<IInstanceSetting> instanceSettings) {
    std::string name = problem->getName();
    std::string tspFile = m_resourcesPath + "/" + problem->getName() + ".tsp";

    std::shared_ptr<ConcordeInstanceSetting> setting = std::dynamic_pointer_cast<ConcordeInstanceSetting>(instanceSettings);

    if (!setting)
        throw std::runtime_error("Wrong Instance Settings given as parameter");


    setting->setProblemFile(name + ".tsp");
    setting->setOutputTourFile(name + ".sol");

    if (!runConcorde(tspFile, problem->getName(), instanceSettings)) {
        throw std::runtime_error("Concorde execution failed");
    }

    return readSolution(problem);
}

bool ConcordeSolver::runConcorde(const std::string& tspFile, const std::string& problemName,std::shared_ptr<IInstanceSetting> instanceSettings) {
    // Copia file .tsp nella working directory
    std::string tspDest = m_workingDir + "/" + problemName + ".tsp";

    std::filesystem::copy_file(tspFile, tspDest, std::filesystem::copy_options::overwrite_existing);

    if (!std::filesystem::exists(tspDest)) {
        throw std::runtime_error("File TSP non copiato: " + tspDest);
    }
    
    std::ifstream test(tspDest);
    if (!test || test.peek() == std::ifstream::traits_type::eof()) {
        throw std::runtime_error("File TSP vuoto: " + tspDest);
    }

    auto oldCwd = std::filesystem::current_path();
    std::filesystem::current_path(m_workingDir);



    std::shared_ptr<ConcordeGeneralSetting> setting = std::dynamic_pointer_cast<ConcordeGeneralSetting>(m_config);
    std::shared_ptr<ConcordeInstanceSetting> settingInstance = std::dynamic_pointer_cast<ConcordeInstanceSetting>(instanceSettings);


    if(!setting)                    throw std::runtime_error("Concorde execution failed");
    if(!settingInstance)            throw std::runtime_error("Concorde execution failed");

    std::stringstream cmd;
    cmd << "\"" << m_concordePath << "\""
        << " -o \"" << settingInstance->getOutputTourFile() << "\"";

    // Altri parametri (solo se settati)
    /*
    if (!settingInstance->getInitialTourFile()->empty()) {
        cmd << " -t \"" << *settingInstance->getInitialTourFile() << "\"";
    }

    if (m_config.RESTART_FILE) {
        cmd << " -R \"" << *m_config.RESTART_FILE << "\"";
    }
    if (m_config.BRANCHING && !(*m_config.BRANCHING)) {
        cmd << " -b";
    }
    if (m_config.DFS_BRANCHING && *m_config.DFS_BRANCHING) {
        cmd << " -d";
    }
    if (m_config.BOSS_MODE && *m_config.BOSS_MODE) {
        cmd << " -h";
    }
    if (m_config.GRUNT_HOST) {
        cmd << " -g " << *m_config.GRUNT_HOST;
    }
    if (m_config.EDGEGEN_FILE) {
        cmd << " -D \"" << *m_config.EDGEGEN_FILE << "\"";
    }
    if (m_config.INITIAL_EDGE_FILE) {
        cmd << " -e \"" << *m_config.INITIAL_EDGE_FILE << "\"";
    }
    if (m_config.FULL_EDGE_FILE) {
        cmd << " -E \"" << *m_config.FULL_EDGE_FILE << "\"";
    }
    if (m_config.EXTRA_CUT_FILE) {
        cmd << " -F \"" << *m_config.EXTRA_CUT_FILE << "\"";
    }
    if (m_config.CUTPOOL_FILE) {
        cmd << " -P \"" << *m_config.CUTPOOL_FILE << "\"";
    }
    if (m_config.MAX_CHUNK_SIZE) {
        cmd << " -C " << *m_config.MAX_CHUNK_SIZE;
    }
    if (m_config.BRANCH_ATTEMPTS) {
        cmd << " -J " << *m_config.BRANCH_ATTEMPTS;
    }
    if (m_config.SKIP_CUTS_AT_ROOT && *m_config.SKIP_CUTS_AT_ROOT) {
        cmd << " -q";
    }
    if (m_config.NO_BRANCH_ON_SUBTOUR && *m_config.NO_BRANCH_ON_SUBTOUR) {
        cmd << " -U";
    }
    if (m_config.ONLY_BLOSSOM_POLYHEDRON && *m_config.ONLY_BLOSSOM_POLYHEDRON) {
        cmd << " -i";
    }
    if (m_config.ONLY_SUBTOUR_POLYHEDRON && *m_config.ONLY_SUBTOUR_POLYHEDRON) {
        cmd << " -I";
    }
    if (m_config.MULTI_PASS_CUTS && *m_config.MULTI_PASS_CUTS) {
        cmd << " -m";
    }
    if (m_config.SEED) {
        cmd << " -s " << *m_config.SEED;
    }
    if (m_config.RANDOM_GRID_SIZE) {
        cmd << " -r " << *m_config.RANDOM_GRID_SIZE;
    }
    if (m_config.VERBOSE && *m_config.VERBOSE) {
        cmd << " -v";
    }
    if (m_config.FAST_CUTS_ONLY && *m_config.FAST_CUTS_ONLY) {
        cmd << " -V";
    }
    if (m_config.WRITE_MIN_REDUCED_COST_ARCS) {
        cmd << " -z " << *m_config.WRITE_MIN_REDUCED_COST_ARCS;
    }
    if (m_config.DISTANCE_NORM) {
        cmd << " -N " << *m_config.DISTANCE_NORM;
    }
    if (m_config.DELETE_TEMP_FILES && *m_config.DELETE_TEMP_FILES) {
        cmd << " -x";
    }
    if (m_config.PROBLEM_NAME) {
        cmd << " -n " << *m_config.PROBLEM_NAME;
    }
    if (m_config.SAVE_TOUR_AS_EDGE_FILE && *m_config.SAVE_TOUR_AS_EDGE_FILE) {
        cmd << " -f";
    }
    */  
    cmd << " \"" << settingInstance->getProblemFile() << "\"";

    std::cout << "[Concorde] Executing: " << cmd.str() << std::endl;

    int ret = std::system(cmd.str().c_str());

    std::filesystem::current_path(oldCwd);

    return ret == 0;
}

std::shared_ptr<ISolution> ConcordeSolver::readSolution(std::shared_ptr<IProblem> problem) {
    std::string solFile = m_workingDir + "/" + problem->getName() + ".sol";

    if (!std::filesystem::exists(solFile)) {
        throw std::runtime_error("Solution file not found: " + solFile);
    }

    std::ifstream in(solFile);
    if(!in) {
        throw std::runtime_error("Unable to open solution file: " + solFile);
    }

    int n;
    in >> n;
    if (n <= 0) {
        throw std::runtime_error("Invalid number of nodes in solution file");
    }

    std::vector<int> tour;
    tour.reserve(n);

    int node;
    while(in >> node) {
        tour.push_back(node);
    }

    if ((int)tour.size() != n) {
        throw std::runtime_error("Mismatch between declared node count and tour length");
    }

    if (!tour.empty() && tour.front() != tour.back()) {
        tour.push_back(tour.front());
    }

    double totalCost = 0.0;
    for (size_t i = 1; i < tour.size(); ++i) {
        totalCost += problem->getCost(tour[i-1], tour[i]);
    }

    auto path = std::make_shared<Path>(tour, totalCost);
    auto solution = std::make_shared<TspSolution>(path, problem);
    return solution;
}

