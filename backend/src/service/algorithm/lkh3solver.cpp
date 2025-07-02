#include "lkh3solver.h"
#include "service/algorithm/path.h"
#include "service/algorithm/tspsolution.h"

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <filesystem>

LKH3Solver::LKH3Solver(const std::string& lkhPath) 
: m_lkhPath(std::filesystem::absolute(lkhPath)), m_workingDir("tmp_lkh3")
{
    std::filesystem::create_directory(m_workingDir);
}

std::string LKH3Solver::name() const {
    return "LKH3";
}

std::string LKH3Solver::writeParamFile(const std::string& tspFile, const std::string& solFile, const std::string& paramFile){
    std::ofstream out(paramFile);
    out << "PROBLEM_FILE = " << tspFile << std::endl;
    out << "OUTPUT_TOUR_FILE = " << solFile << std::endl;
    out.close();
    return paramFile;
}

bool LKH3Solver::runLKH(const std::string& paramFile){
    std::stringstream cmd;
    cmd << "\"" << m_lkhPath << "\" \"" << paramFile << "\"";
    int ret = std::system(cmd.str().c_str());
    return ret == 0;
}


std::shared_ptr<ISolution> LKH3Solver::readSolution(const std::string& solFile, std::shared_ptr<IProblem> problem) {
    std::ifstream in(solFile);

    if (!in.is_open()) {
        throw std::runtime_error("Impossibile aprire il file soluzione di LKH3: " + solFile);
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line == "TOUR_SECTION") break;
    }

    if (in.eof()) {
        throw std::runtime_error("TOUR_SECTION non trovata nel file soluzione di LKH3");
    }

    std::vector<int> tour;
    int node;
    while (in >> node) {
        if (node == -1) break;
        tour.push_back(node - 1); // LKH3 è 1-based
    }

    if (!tour.empty() && tour.front() != tour.back()) {
        tour.push_back(tour.front());
    }

    // Calcolo del costo totale del tour
    double totalCost = 0.0;
    for (size_t i = 1; i < tour.size(); ++i) {
        totalCost += problem->getCost(tour[i - 1], tour[i]);
    }

    auto path = std::make_shared<Path>(tour, totalCost);
    auto solution = std::make_shared<TspSolution>(path, problem);
    return solution;
}


std::shared_ptr<ISolution> LKH3Solver::execute(std::shared_ptr<IProblem> problem) {
    //per il momento hardcodiamo il percorso del problema
    std::string tspFile = "resources/" + problem->getName() + ".tsp";
    std::string solFile = m_workingDir + "/solution_"+problem->getName()+".txt";
    std::string paramFile = m_workingDir + "/params_"+problem->getName()+".par";

    writeParamFile(tspFile, solFile, paramFile);


    if (!runLKH(paramFile)) {
        throw std::runtime_error("LKH3 execution failed");
    }

    return readSolution(solFile, problem);
}