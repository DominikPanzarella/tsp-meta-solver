#include "concordesolver.h"
#include "service/algorithm/path.h"
#include "service/algorithm/tspsolution.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>

ConcordeSolver::ConcordeSolver(const std::string& concordePath)
    : m_concordePath{std::filesystem::absolute(concordePath)},
      m_workingDir("tmp_concorde") {

    // Crea la directory se non esiste
    std::filesystem::create_directories(m_workingDir);
}

std::string ConcordeSolver::name() const {
    return "Concorde";
}

std::shared_ptr<ISolution> ConcordeSolver::execute(std::shared_ptr<IProblem> problem) {
    std::string tspFile = "resources/" + problem->getName() + ".tsp";

    if (!runConcorde(tspFile, problem->getName())) {
        throw std::runtime_error("Concorde execution failed");
    }

    return readSolution(problem);
}

bool ConcordeSolver::runConcorde(const std::string& tspFile, const std::string& problemName) {
    std::string outputFile = m_workingDir + "/" + problemName + ".sol";
    std::string tspDest = m_workingDir + "/" + problemName + ".tsp";

    // Copia il file TSP nella working dir
    std::filesystem::copy_file(tspFile, tspDest, std::filesystem::copy_options::overwrite_existing);

    // Salva e cambia la working dir
    auto oldCwd = std::filesystem::current_path();
    std::filesystem::current_path(m_workingDir);

    // Costruisci comando usando solo il nome locale
    std::stringstream cmd;
    cmd << "\"" << m_concordePath << "\""
        << " -o \"" << problemName << ".sol\""
        << " \"" << problemName << ".tsp\"";

    std::cout << "[Concorde] Executing: " << cmd.str() << std::endl;

    int ret = std::system(cmd.str().c_str());

    // Ripristina la working dir
    std::filesystem::current_path(oldCwd);

    return ret == 0;
}


std::shared_ptr<ISolution> ConcordeSolver::readSolution(std::shared_ptr<IProblem> problem) {
    // TODO: parsing di tmp_concorde/<problemName>.sol
    std::string solFile = m_workingDir + "/" + problem->getName() + ".sol";

    if (!std::filesystem::exists(solFile))      throw std::runtime_error("Solution file not found: " + solFile);

    std::ifstream in(solFile);
    if(!in)                                     throw std::runtime_error("Unable to open solution file: " + solFile);

    int n;

    in >> n;        //number of nodes
    if(n <=0)                                   throw std::runtime_error("Invalid number of nodes in solution file");

    std::vector<int> tour;
    tour.reserve(n);

    int node;
    while(in >> node)
        tour.push_back(node);

    if ((int)tour.size() != n) {
        throw std::runtime_error("Mismatch between declared node count and tour length");
    }

    if (!tour.empty() && tour.front() != tour.back()) {
        tour.push_back(tour.front());
    }

    double totalCost = 0.0;
    for(size_t i=1; i<tour.size(); ++i)
        totalCost += problem->getCost(tour[i-1], tour[i]);

    
    auto path = std::make_shared<Path>(tour, totalCost);
    auto solution = std::make_shared<TspSolution>(path, problem);
    return solution;
}
