#include "concordesolver.h"
#include "service/algorithm/path.h"
#include "service/algorithm/tspsolution.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

ConcordeSolver::ConcordeSolver(const std::string& concordePath, ConcordeConfig config)
    : m_concordePath(std::filesystem::absolute(concordePath)),
      m_config(std::move(config)),
      m_workingDir("tmp_concorde")
      {

    std::filesystem::create_directories(m_workingDir);
}

std::string ConcordeSolver::name() const {
    return "Concorde";
}

std::shared_ptr<ISolution> ConcordeSolver::execute(std::shared_ptr<IProblem> problem) {
    std::string name = problem->getName();
    std::string tspFile = "resources/" + problem->getName() + ".tsp";

    m_config.PROBLEM_FILE = name + ".tsp";
    m_config.OUTPUT_TOUR_FILE = name + ".sol";

    if (!runConcorde(tspFile, problem->getName())) {
        throw std::runtime_error("Concorde execution failed");
    }

    return readSolution(problem);
}

bool ConcordeSolver::runConcorde(const std::string& tspFile, const std::string& problemName) {
    // Copia file .tsp nella working directory
    std::string tspDest = m_workingDir + "/" + problemName + ".tsp";

    std::filesystem::copy_file(tspFile, tspDest, std::filesystem::copy_options::overwrite_existing);

    auto oldCwd = std::filesystem::current_path();
    std::filesystem::current_path(m_workingDir);

    std::stringstream cmd;
    cmd << "\"" << m_concordePath << "\""
        << " -o \"" << m_config.OUTPUT_TOUR_FILE << "\""
       ;

    // Altri parametri (solo se settati)
    if (m_config.INITIAL_TOUR_FILE) {
        cmd << " -t \"" << *m_config.INITIAL_TOUR_FILE << "\"";
    }
    if (m_config.RESTART_FILE) {
        cmd << " -R \"" << *m_config.RESTART_FILE << "\"";
    }
    if (m_config.BRANCHING && !(*m_config.BRANCHING)) {
        cmd << " -b0"; // disabilita branching (esempio)
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

    cmd << " \"" << m_config.PROBLEM_FILE << "\"";

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


void ConcordeSolver::resetConfig(){
    m_config = ConcordeConfig{};
}

void ConcordeSolver::setConfig(const ConcordeConfig& config){
    m_config = config;  
}