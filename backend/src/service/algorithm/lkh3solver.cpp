#include "lkh3solver.h"
#include "service/algorithm/path.h"
#include "service/algorithm/tspsolution.h"

#include "repository/configuration2/config/lkh3instancesetting.h"


#include <filesystem>

#include <cstdlib>


LKH3Solver::LKH3Solver(const std::string& lkhPath,  const std::string& resourcesPath, std::shared_ptr<LKH3GeneralSetting> lkh3Setting) 
: m_lkhPath(std::filesystem::absolute(lkhPath)), m_workingDir(std::filesystem::absolute("tmp_lkh3")), m_config{lkh3Setting}, m_resourcesPath(resourcesPath)
{
    if(std::filesystem::exists(m_workingDir))
        std::filesystem::remove_all(m_workingDir);
    std::filesystem::create_directories(m_workingDir);
}

std::string LKH3Solver::name() const {
    return "LKH3";
}
std::string LKH3Solver::writeParamFile(const std::string& paramFile, std::shared_ptr<IInstanceSetting> instanceSettings) {
    std::ofstream out(paramFile);
    if (!out.is_open()) {
        throw std::runtime_error("Unable to open parameter file: " + paramFile);
    }

    std::shared_ptr<LKH3InstanceSetting> settingInstance = std::dynamic_pointer_cast<LKH3InstanceSetting>(instanceSettings);
    std::shared_ptr<LKH3GeneralSetting> settingGeneral = std::dynamic_pointer_cast<LKH3GeneralSetting>(m_config);

    if (!settingGeneral || !settingInstance)
        throw std::runtime_error("LKH3 settings are invalid or not properly casted");

    if (!settingInstance->getProblemFile() || settingInstance->getProblemFile()->empty())
        throw std::invalid_argument("PROBLEM_FILE cannot be empty");
    if (!settingInstance->getOutputTourFile() || settingInstance->getOutputTourFile()->empty())
        throw std::invalid_argument("OUTPUT_TOUR_FILE cannot be empty");

    // Macros to simplify code
    #define WRITE_OPT(opt, key) if (opt) out << key << " = " << *opt << "\n"
    #define WRITE_OPT_BOOL(opt, key) if (opt) out << key << " = " << (*opt ? "YES" : "NO") << "\n"

    // Instance-specific settings
    out << "PROBLEM_FILE = " << *settingInstance->getProblemFile() << "\n";
    out << "OUTPUT_TOUR_FILE = " << *settingInstance->getOutputTourFile() << "\n";
    WRITE_OPT(settingInstance->getInitialTourFile(), "INITIAL_TOUR_FILE");
    WRITE_OPT(settingInstance->getInputTourFile(), "INPUT_TOUR_FILE");
    WRITE_OPT(settingInstance->getMergeTourFile(), "MERGE_TOUR_FILE");
    WRITE_OPT(settingInstance->getTourFile(), "TOUR_FILE");

    // General settings
    WRITE_OPT(settingGeneral->getAscentCandidates(), "ASCENT_CANDIDATES");
    WRITE_OPT(settingGeneral->getBackboneTrials(), "BACKBONE_TRIALS");
    WRITE_OPT_BOOL(settingGeneral->getBacktracking(), "BACKTRACKING");

    for (const auto& f : settingGeneral->getCandidateFiles())
        out << "CANDIDATE_FILE = " << f << "\n";

    if (auto bwtsp = settingGeneral->getBWTSP()) {
        const auto& [B, Q, optR] = *bwtsp;
        out << "BWTSP = " << B << " " << Q;
        if (optR) out << " " << *optR;
        out << "\n";
    }

    WRITE_OPT(settingGeneral->getCandidateSetType(), "CANDIDATE_SET_TYPE");
    WRITE_OPT(settingGeneral->getExcess(), "EXCESS");
    WRITE_OPT(settingGeneral->getExtraCandidates(), "EXTRA_CANDIDATES");
    WRITE_OPT(settingGeneral->getExtraCandidateSetType(), "EXTRA_CANDIDATE_SET_TYPE");

    WRITE_OPT_BOOL(settingGeneral->getGain23(), "GAIN23");
    WRITE_OPT_BOOL(settingGeneral->getGainCriterion(), "GAIN_CRITERION");
    WRITE_OPT_BOOL(settingGeneral->getSubgradient(), "SUBGRADIENT");

    WRITE_OPT(settingGeneral->getInitialPeriod(), "INITIAL_PERIOD");
    WRITE_OPT(settingGeneral->getInitialStepSize(), "INITIAL_STEP_SIZE");
    WRITE_OPT(settingGeneral->getInitialTourAlgorithm(), "INITIAL_TOUR_ALGORITHM");
    WRITE_OPT(settingGeneral->getInitialTourFraction(), "INITIAL_TOUR_FRACTION");

    WRITE_OPT(settingGeneral->getKicks(), "KICKS");
    WRITE_OPT(settingGeneral->getKickType(), "KICK_TYPE");
    WRITE_OPT_BOOL(settingGeneral->getMakespan(), "MAKESPAN");
    WRITE_OPT(settingGeneral->getMaxBreadth(), "MAX_BREADTH");
    WRITE_OPT(settingGeneral->getMaxCandidates(), "MAX_CANDIDATES");
    WRITE_OPT(settingGeneral->getMaxSwaps(), "MAX_SWAPS");
    WRITE_OPT(settingGeneral->getMaxTrials(), "MAX_TRIALS");
    WRITE_OPT(settingGeneral->getMoveType(), "MOVE_TYPE");
    WRITE_OPT(settingGeneral->getNonSequentialMoveType(), "NONSEQUENTIAL_MOVE_TYPE");
    WRITE_OPT(settingGeneral->getPatchingA(), "PATCHING_A");
    WRITE_OPT(settingGeneral->getPatchingC(), "PATCHING_C");
    WRITE_OPT(settingGeneral->getSubsequentMoveType(), "SUBSEQUENT_MOVE_TYPE");
    WRITE_OPT_BOOL(settingGeneral->getSubsequentPatching(), "SUBSEQUENT_PATCHING");

    WRITE_OPT(settingGeneral->getOptimum(), "OPTIMUM");
    WRITE_OPT_BOOL(settingGeneral->getStopAtOptimum(), "STOP_AT_OPTIMUM");
    WRITE_OPT(settingGeneral->getTimeLimit(), "TIME_LIMIT");

    WRITE_OPT(settingGeneral->getDepot(), "DEPOT");
    WRITE_OPT(settingGeneral->getComment(), "COMMENT");

    WRITE_OPT(settingGeneral->getTraceLevel(), "TRACE_LEVEL");
    WRITE_OPT(settingGeneral->getPopulationSize(), "POPULATION_SIZE");
    WRITE_OPT(settingGeneral->getPrecision(), "PRECISION");
    WRITE_OPT_BOOL(settingGeneral->getRestrictedSearch(), "RESTRICTED_SEARCH");
    WRITE_OPT(settingGeneral->getRuns(), "RUNS");
    WRITE_OPT(settingGeneral->getSeed(), "SEED");
    WRITE_OPT(settingGeneral->getSalesmen(), "SALESMEN");
    WRITE_OPT(settingGeneral->getScale(), "SCALE");
    WRITE_OPT(settingGeneral->getSintefSolutionFile(), "SINTEF_SOLUTION_FILE");
    WRITE_OPT(settingGeneral->getPiFile(), "PI_FILE");

    WRITE_OPT(settingGeneral->getSubproblemSize(), "SUBPROBLEM_SIZE");
    WRITE_OPT(settingGeneral->getSubproblemTourFile(), "SUBPROBLEM_TOUR_FILE");

    WRITE_OPT(settingGeneral->getMTSPMinSize(), "MTSP_MIN_SIZE");
    WRITE_OPT(settingGeneral->getMTSPMaxSize(), "MTSP_MAX_SIZE");
    WRITE_OPT(settingGeneral->getMTSPObjective(), "MTSP_OBJECTIVE");
    WRITE_OPT(settingGeneral->getMTSPSolutionFile(), "MTSP_SOLUTION_FILE");
    WRITE_OPT(settingGeneral->getVehicles(), "VEHICLES");

    if (settingGeneral->getSpecial().value_or(false))
        out << "SPECIAL\n";

    #undef WRITE_OPT
    #undef WRITE_OPT_BOOL

    out.close();
    return paramFile;
}


bool LKH3Solver::runLKH(const std::string& paramFile){
    std::stringstream cmd;
    cmd << "\"" << m_lkhPath << "\" \"" << paramFile << "\"";
    int ret = std::system(cmd.str().c_str());
    return ret == 0;
}


std::shared_ptr<ISolution> LKH3Solver::readSolution( std::shared_ptr<IProblem> problem, std::shared_ptr<IInstanceSetting> instanceSettings) {
    std::shared_ptr<LKH3InstanceSetting> setting = std::dynamic_pointer_cast<LKH3InstanceSetting>(instanceSettings);

    std::ifstream in(*setting->getOutputTourFile());

    if (!in.is_open()) {
        throw std::runtime_error("Cannot open solution file (LKH3): " + *setting->getOutputTourFile());
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


std::shared_ptr<ISolution> LKH3Solver::execute(std::shared_ptr<IProblem> problem, std::shared_ptr<IInstanceSetting> instanceSettings) {
    //per il momento hardcodiamo il percorso del problema
    std::string tspFile = m_resourcesPath + "/" + problem->getName() + ".tsp";
    std::string solFile = m_workingDir + "/solution_"+problem->getName()+".txt";
    
    std::shared_ptr<LKH3InstanceSetting> setting = std::dynamic_pointer_cast<LKH3InstanceSetting>(instanceSettings);

    if (!setting)
        throw std::runtime_error("Wrong Instance Settings given as parameter");


    setting->setProblemFile(tspFile);
    setting->setOutputTourFile(solFile);

    
    std::string paramFile = m_workingDir + "/params_"+problem->getName()+".par";

    writeParamFile(paramFile, instanceSettings);


    if (!runLKH(paramFile)) {
        throw std::runtime_error("LKH3 execution failed");
    }

    return readSolution(problem, instanceSettings);
}
