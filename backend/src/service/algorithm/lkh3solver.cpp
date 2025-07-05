#include "lkh3solver.h"
#include "service/algorithm/path.h"
#include "service/algorithm/tspsolution.h"

#include <filesystem>

#include <cstdlib>


LKH3Solver::LKH3Solver(const std::string& lkhPath,LKH3Config config) 
: m_lkhPath(std::filesystem::absolute(lkhPath)), m_workingDir("tmp_lkh3"), m_config{config}
{
    std::filesystem::create_directory(m_workingDir);
}

std::string LKH3Solver::name() const {
    return "LKH3";
}

std::string LKH3Solver::writeParamFile(const std::string& paramFile) {
    std::ofstream out(paramFile);

    // Controlli obbligatori
    if (m_config.PROBLEM_FILE.empty())
        throw std::invalid_argument("PROBLEM_FILE cannot be empty");
    if (m_config.OUTPUT_TOUR_FILE.empty())
        throw std::invalid_argument("OUTPUT_TOUR_FILE cannot be empty");

    out << "PROBLEM_FILE = " << m_config.PROBLEM_FILE << "\n";
    out << "OUTPUT_TOUR_FILE = " << m_config.OUTPUT_TOUR_FILE << "\n";

    // Candidate edges & sets
    if (m_config.ASCENT_CANDIDATES) out << "ASCENT_CANDIDATES = " << *m_config.ASCENT_CANDIDATES << "\n";
    if (m_config.BACKBONE_TRIALS) out << "BACKBONE_TRIALS = " << *m_config.BACKBONE_TRIALS << "\n";
    if (m_config.BACKTRACKING) out << "BACKTRACKING = " << (*m_config.BACKTRACKING ? "YES" : "NO") << "\n";

    for (const auto& f : m_config.CANDIDATE_FILE)
        out << "CANDIDATE_FILE = " << f << "\n";

    if (m_config.BWTSP) {
        int B = std::get<0>(*m_config.BWTSP);
        int Q = std::get<1>(*m_config.BWTSP);
        if (std::get<2>(*m_config.BWTSP))
            out << "BWTSP = " << B << " " << Q << " " << *std::get<2>(*m_config.BWTSP) << "\n";
        else
            out << "BWTSP = " << B << " " << Q << "\n";
    }

    if (m_config.CANDIDATE_SET_TYPE) out << "CANDIDATE_SET_TYPE = " << *m_config.CANDIDATE_SET_TYPE << "\n";
    if (m_config.EXCESS) out << "EXCESS = " << *m_config.EXCESS << "\n";
    if (m_config.EXTRA_CANDIDATES) out << "EXTRA_CANDIDATES = " << *m_config.EXTRA_CANDIDATES << "\n";
    if (m_config.EXTRA_CANDIDATE_SET_TYPE) out << "EXTRA_CANDIDATE_SET_TYPE = " << *m_config.EXTRA_CANDIDATE_SET_TYPE << "\n";

    // Gain / heuristics
    if (m_config.GAIN23) out << "GAIN23 = " << (*m_config.GAIN23 ? "YES" : "NO") << "\n";
    if (m_config.GAIN_CRITERION) out << "GAIN_CRITERION = " << (*m_config.GAIN_CRITERION ? "YES" : "NO") << "\n";
    if (m_config.SUBGRADIENT) out << "SUBGRADIENT = " << (*m_config.SUBGRADIENT ? "YES" : "NO") << "\n";

    // Initial tour and ascent
    if (m_config.INITIAL_PERIOD) out << "INITIAL_PERIOD = " << *m_config.INITIAL_PERIOD << "\n";
    if (m_config.INITIAL_STEP_SIZE) out << "INITIAL_STEP_SIZE = " << *m_config.INITIAL_STEP_SIZE << "\n";
    if (m_config.INITIAL_TOUR_ALGORITHM) out << "INITIAL_TOUR_ALGORITHM = " << *m_config.INITIAL_TOUR_ALGORITHM << "\n";
    if (m_config.INITIAL_TOUR_FILE) out << "INITIAL_TOUR_FILE = " << *m_config.INITIAL_TOUR_FILE << "\n";
    if (m_config.INITIAL_TOUR_FRACTION) out << "INITIAL_TOUR_FRACTION = " << *m_config.INITIAL_TOUR_FRACTION << "\n";

    // Tours controlling search
    if (m_config.INPUT_TOUR_FILE) out << "INPUT_TOUR_FILE = " << *m_config.INPUT_TOUR_FILE << "\n";
    if (m_config.MERGE_TOUR_FILE) out << "MERGE_TOUR_FILE = " << *m_config.MERGE_TOUR_FILE << "\n";

    // Kicks and moves
    if (m_config.KICKS) out << "KICKS = " << *m_config.KICKS << "\n";
    if (m_config.KICK_TYPE) out << "KICK_TYPE = " << *m_config.KICK_TYPE << "\n";
    if (m_config.MAKESPAN) out << "MAKESPAN = " << (*m_config.MAKESPAN ? "YES" : "NO") << "\n";
    if (m_config.MAX_BREADTH) out << "MAX_BREADTH = " << *m_config.MAX_BREADTH << "\n";
    if (m_config.MAX_CANDIDATES) out << "MAX_CANDIDATES = " << *m_config.MAX_CANDIDATES << "\n";
    if (m_config.MAX_SWAPS) out << "MAX_SWAPS = " << *m_config.MAX_SWAPS << "\n";
    if (m_config.MAX_TRIALS) out << "MAX_TRIALS = " << *m_config.MAX_TRIALS << "\n";
    if (m_config.MOVE_TYPE) out << "MOVE_TYPE = " << *m_config.MOVE_TYPE << "\n";
    if (m_config.NONSEQUENTIAL_MOVE_TYPE) out << "NONSEQUENTIAL_MOVE_TYPE = " << *m_config.NONSEQUENTIAL_MOVE_TYPE << "\n";
    if (m_config.PATCHING_A) out << "PATCHING_A = " << *m_config.PATCHING_A << "\n";
    if (m_config.PATCHING_C) out << "PATCHING_C = " << *m_config.PATCHING_C << "\n";
    if (m_config.SUBSEQUENT_MOVE_TYPE) out << "SUBSEQUENT_MOVE_TYPE = " << *m_config.SUBSEQUENT_MOVE_TYPE << "\n";
    if (m_config.SUBSEQUENT_PATCHING) out << "SUBSEQUENT_PATCHING = " << (*m_config.SUBSEQUENT_PATCHING ? "YES" : "NO") << "\n";

    // Optimization / stopping
    if (m_config.OPTIMUM) out << "OPTIMUM = " << *m_config.OPTIMUM << "\n";
    if (m_config.STOP_AT_OPTIMUM) out << "STOP_AT_OPTIMUM = " << (*m_config.STOP_AT_OPTIMUM ? "YES" : "NO") << "\n";
    if (m_config.TIME_LIMIT) out << "TIME_LIMIT = " << *m_config.TIME_LIMIT << "\n";

    // Problem characteristics
    if (m_config.DEPOT) out << "DEPOT = " << *m_config.DEPOT << "\n";
    if (m_config.COMMENT) out << "COMMENT " << *m_config.COMMENT << "\n";

    // Output
    if (m_config.TOUR_FILE) out << "TOUR_FILE = " << *m_config.TOUR_FILE << "\n";
    if (m_config.TRACE_LEVEL) out << "TRACE_LEVEL = " << *m_config.TRACE_LEVEL << "\n";

    // Misc
    if (m_config.POPULATION_SIZE) out << "POPULATION_SIZE = " << *m_config.POPULATION_SIZE << "\n";
    if (m_config.PRECISION) out << "PRECISION = " << *m_config.PRECISION << "\n";
    if (m_config.RESTRICTED_SEARCH) out << "RESTRICTED_SEARCH = " << (*m_config.RESTRICTED_SEARCH ? "YES" : "NO") << "\n";
    if (m_config.RUNS) out << "RUNS = " << *m_config.RUNS << "\n";
    if (m_config.SEED) out << "SEED = " << *m_config.SEED << "\n";
    if (m_config.SALESMEN) out << "SALESMEN = " << *m_config.SALESMEN << "\n";
    if (m_config.SCALE) out << "SCALE = " << *m_config.SCALE << "\n";
    if (m_config.SINTEF_SOLUTION_FILE) out << "SINTEF_SOLUTION_FILE = " << *m_config.SINTEF_SOLUTION_FILE << "\n";
    if (m_config.PI_FILE) out << "PI_FILE = " << *m_config.PI_FILE << "\n";

    // Subproblem
    if (m_config.SUBPROBLEM_SIZE) out << "SUBPROBLEM_SIZE = " << *m_config.SUBPROBLEM_SIZE << "\n";
    if (m_config.SUBPROBLEM_TOUR_FILE) out << "SUBPROBLEM_TOUR_FILE = " << *m_config.SUBPROBLEM_TOUR_FILE << "\n";

    // MTSP / VRP
    if (m_config.MTSP_MIN_SIZE) out << "MTSP_MIN_SIZE = " << *m_config.MTSP_MIN_SIZE << "\n";
    if (m_config.MTSP_MAX_SIZE) out << "MTSP_MAX_SIZE = " << *m_config.MTSP_MAX_SIZE << "\n";
    if (m_config.MTSP_OBJECTIVE) out << "MTSP_OBJECTIVE = " << *m_config.MTSP_OBJECTIVE << "\n";
    if (m_config.MTSP_SOLUTION_FILE) out << "MTSP_SOLUTION_FILE = " << *m_config.MTSP_SOLUTION_FILE << "\n";
    if (m_config.VEHICLES) out << "VEHICLES = " << *m_config.VEHICLES << "\n";

    // Flag special (optional)
    if (m_config.SPECIAL) out << "SPECIAL = " << (*m_config.SPECIAL ? "YES" : "NO") << "\n";

    out.close();
    return paramFile;
}


bool LKH3Solver::runLKH(const std::string& paramFile){
    std::stringstream cmd;
    cmd << "\"" << m_lkhPath << "\" \"" << paramFile << "\"";
    int ret = std::system(cmd.str().c_str());
    return ret == 0;
}


std::shared_ptr<ISolution> LKH3Solver::readSolution( std::shared_ptr<IProblem> problem) {
    std::ifstream in(m_config.OUTPUT_TOUR_FILE);

    if (!in.is_open()) {
        throw std::runtime_error("Cannot open solution file (LKH3): " + m_config.OUTPUT_TOUR_FILE);
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line == "TOUR_SECTION") break;
    }

    if (in.eof()) {
        throw std::runtime_error("TOUR_SECTION was not found in LKH3");
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
    prepareForProblem(problem, tspFile, solFile);

    
    std::string paramFile = m_workingDir + "/params_"+problem->getName()+".par";

    writeParamFile(paramFile);


    if (!runLKH(paramFile)) {
        throw std::runtime_error("LKH3 execution failed");
    }

    return readSolution(problem);
}

void LKH3Solver::setConfig(LKH3Config config) {
    m_config = config;
}

void LKH3Solver::resetConfig(){
    m_config = LKH3Config{};
}


void LKH3Solver::prepareForProblem(const std::shared_ptr<IProblem>& problem, std::string tspFile, std::string solFile) {
    m_config.PROBLEM_FILE = tspFile;
    m_config.OUTPUT_TOUR_FILE = solFile;
}