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

double ConcordeSolver::parseUpperBoundFromLog(const std::string& logFile){
    std::ifstream in(logFile);
    if (!in) return 1e200; // impossibile leggere -> upperbound invalido

    std::string line;
    double lastUpperBound = 1e200;

    while (std::getline(in, line)) {
        // TOUR FOUND - upperbound is 239301.00
        auto pos1 = line.find("TOUR FOUND - upperbound is");
        if (pos1 != std::string::npos) {
            std::stringstream ss(line.substr(pos1));
            std::string dummy;
            double val;
            // salta parole fino a "is" e leggi il double
            while (ss >> dummy) {
                if (dummy == "is" && (ss >> val)) {
                    lastUpperBound = val;
                    break;
                }
            }
        }

        // Optimal Solution: 6528.00
        auto pos2 = line.find("Optimal Solution:");
        if (pos2 != std::string::npos) {
            std::stringstream ss(line.substr(pos2));
            std::string dummy;
            double val;
            ss >> dummy >> dummy >> val; // legge "Optimal Solution: val"
            lastUpperBound = val;
        }

        if (line.find("Final lower bound") != std::string::npos && line.find("upper bound") != std::string::npos) {
            size_t pos = line.find("upper bound");
            std::string substr = line.substr(pos);
            std::stringstream ss(substr);
            std::string word;
            double val = 1e200;
            // trova la prima double dopo "upper bound"
            while (ss >> word) {
                try {
                    val = std::stod(word);
                    lastUpperBound = val;
                    break;
                } catch (...) {
                    // continua a leggere fino a trovare un double
                }
            }
        }
    }

    return lastUpperBound;
}

std::shared_ptr<ISolution> ConcordeSolver::execute(std::shared_ptr<IProblem> problem, std::shared_ptr<IInstanceSetting> instanceSettings) {
    std::string name = problem->getName();
    std::string tspFile = m_resourcesPath + "/" + name + ".tsp";

    std::shared_ptr<ConcordeInstanceSetting> setting = std::dynamic_pointer_cast<ConcordeInstanceSetting>(instanceSettings);
    if (!setting)
        throw std::runtime_error("Wrong Instance Settings given as parameter");

    setting->setProblemFile(name + ".tsp");
    setting->setOutputTourFile(name + ".sol");

    try {
        runConcorde(tspFile, name, instanceSettings);
    }
    catch (...) {
        std::cerr << "[Concorde] Execution failed for " << name << ", trying to recover partial solution..." << std::endl;

        std::string logFile = m_workingDir + "/" + name + ".log";
        double partialUpperBound = parseUpperBoundFromLog(logFile);
        std::vector<int> empty;
        auto path = std::make_shared<Path>(empty, partialUpperBound);
        auto solution = std::make_shared<TspSolution>(path, problem);
        return solution;
    }

    // Se runConcorde è andato a buon fine, prova a leggere la soluzione
    try {
        return readSolution(problem);
    }
    catch (const std::exception& e) {
        std::cerr << "[Concorde] Could not read solution file after successful run: " << e.what() << std::endl;

        std::string logFile = m_workingDir + "/" + name + ".log";
        double partialUpperBound = parseUpperBoundFromLog(logFile);
        std::vector<int> empty;

        auto path = std::make_shared<Path>(empty, partialUpperBound);
        auto solution = std::make_shared<TspSolution>(path, problem);
        return solution;
    }
}

bool ConcordeSolver::runConcorde(const std::string& tspFile, const std::string& problemName, std::shared_ptr<IInstanceSetting> instanceSettings) {
    // Copia file .tsp nella working directory
    std::string tspDest = m_workingDir + "/" + problemName + ".tsp";
    std::filesystem::copy_file(tspFile, tspDest, std::filesystem::copy_options::overwrite_existing);

    if (!std::filesystem::exists(tspDest))
        throw std::runtime_error("File TSP non copiato: " + tspDest);

    std::ifstream test(tspDest);
    if (!test || test.peek() == std::ifstream::traits_type::eof())
        throw std::runtime_error("File TSP vuoto: " + tspDest);

    // Cambio directory temporaneo
    auto oldCwd = std::filesystem::current_path();
    std::filesystem::current_path(m_workingDir);

    std::shared_ptr<ConcordeGeneralSetting> setting = std::dynamic_pointer_cast<ConcordeGeneralSetting>(m_config);
    std::shared_ptr<ConcordeInstanceSetting> settingInstance = std::dynamic_pointer_cast<ConcordeInstanceSetting>(instanceSettings);

    if (!setting || !settingInstance)
        throw std::runtime_error("Concorde execution failed: invalid settings");

    std::stringstream cmd;
    cmd << "\"" << m_concordePath << "\"";

    // Output tour file (obbligatorio)
    cmd << " -o \"" << settingInstance->getOutputTourFile() << "\"";

    // ========== PARAMETRI INSTANCE ==========
    auto addOptStr = [&](const std::optional<std::string>& opt, const std::string& flag) {
        if (opt) cmd << " " << flag << " \"" << *opt << "\"";
    };

    addOptStr(settingInstance->getInitialTourFile(), "-t");
    addOptStr(settingInstance->getRestartFile(), "-R");
    addOptStr(settingInstance->getEdgegenFile(), "-D");
    addOptStr(settingInstance->getInitialEdgeFile(), "-e");
    addOptStr(settingInstance->getFullEdgeFile(), "-E");
    addOptStr(settingInstance->getExtraCutFile(), "-F");
    addOptStr(settingInstance->getCutpoolFile(), "-P");

    if (settingInstance->getProblemName())
        cmd << " -n \"" << *settingInstance->getProblemName() << "\"";

    // ========== PARAMETRI GLOBALI ==========
    auto addOptInt = [&](const std::optional<int>& opt, const std::string& flag) {
        if (opt) cmd << " " << flag << " " << *opt;
    };
    auto addOptBool = [&](const std::optional<bool>& opt, const std::string& flag, bool negated = false) {
        if (opt && (*opt != negated)) cmd << " " << flag;
    };

    addOptBool(setting->getBranching(), "-b", true); // disabilita branching se false
    addOptBool(setting->getDFSBranching(), "-d");
    addOptBool(setting->getBossMode(), "-h");
    addOptStr(setting->getGruntHost(), "-g");

    addOptInt(setting->getMaxChunkSize(), "-C");
    addOptInt(setting->getBranchAttempts(), "-J");

    addOptBool(setting->getSkipCutsAtRoot(), "-q");
    addOptBool(setting->getNoBranchOnSubtour(), "-U");
    addOptBool(setting->getOnlyBlossomPolyhedron(), "-i");
    addOptBool(setting->getOnlySubtourPolyhedron(), "-I");
    addOptBool(setting->getMultiPassCuts(), "-m");

    addOptInt(setting->getSeed(), "-s");
    addOptInt(setting->getRandomGridSize(), "-r");
    addOptBool(setting->getVerbose(), "-v");
    addOptBool(setting->getFastCutsOnly(), "-V");

    addOptInt(setting->getWriteMinReducedCostArcs(), "-z");
    addOptInt(setting->getDistanceNorm(), "-N");
    addOptBool(setting->getDeleteTempFiles(), "-x");
    addOptBool(setting->getSaveTourAsEdgeFile(), "-f");

    // File TSP finale
    cmd << " \"" << settingInstance->getProblemFile() << "\"";
    cmd << " > \"" << problemName << ".log\" 2>&1"; // log stdout/stderr


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

