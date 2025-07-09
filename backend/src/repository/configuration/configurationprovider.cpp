#include "repository/configuration/configurationprovider.h"

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>

const LKH3Config& ConfigurationProvider::getLKH3Config() const {
    return m_lkh3Config;
}

const ConcordeConfig& ConfigurationProvider::getConcordeConfig() const {
    return m_concordeConfig;
}

const GeneralConfig& ConfigurationProvider::getGeneralConfig() const {
    return m_generalConfig;
}

void ConfigurationProvider::readConfiguration(const std::string& path) {
    std::unordered_map<std::string, std::string> config;
    std::ifstream file(path);
    if(!file.is_open()){
        throw std::runtime_error("Cannot open config file: " + path);
    }
    std::string line;   
    while(std::getline(file, line)){
        // Trim line
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if(line.empty() || line[0] == '#')      continue;

        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;

        std::string key = line.substr(0, eq);
        std::string value = line.substr(eq + 1);

        // Trim key/value
        key.erase(0, key.find_first_not_of(" \t\r\n"));
        key.erase(key.find_last_not_of(" \t\r\n") + 1);
        value.erase(0, value.find_first_not_of(" \t\r\n"));
        value.erase(value.find_last_not_of(" \t\r\n") + 1);
        
        config[key] = value;

    }
    
    constructGeneralConfig(config);
    constructLKH3Config(config);
    constructConcordeConfig(config);
}

void ConfigurationProvider::constructLKH3Config(std::unordered_map<std::string, std::string> map) {

    auto get_optional_int = [&](const std::string& key) -> std::optional<int> {
        if (!map.contains(key)) return std::nullopt;
        const std::string& val = map.at(key);
        if (val.empty()) return std::nullopt;
        try {
            size_t pos = 0;
            int res = std::stoi(val, &pos);
            if (pos != val.size()) return std::nullopt;
            return res;
        } catch (...) {
            return std::nullopt;
        }
    };
    
    auto get_optional_double = [&](const std::string& key) -> std::optional<double> {
        if (!map.contains(key)) return std::nullopt;
        const std::string& val = map.at(key);
        if (val.empty()) return std::nullopt;
        try {
            size_t pos = 0;
            double res = std::stod(val, &pos);
            if (pos != val.size()) return std::nullopt;
            return res;
        } catch (...) {
            return std::nullopt;
        }
    };
    
    auto get_optional_string = [&](const std::string& key) -> std::optional<std::string> {
        if (!map.contains(key)) return std::nullopt;
        const std::string& val = map.at(key);
        return val.empty() ? std::nullopt : std::optional<std::string>{val};
    };
    
    auto get_optional_bool = [&](const std::string& key) -> std::optional<bool> {
        if (!map.contains(key)) return std::nullopt;
        std::string val = map[key];
        std::transform(val.begin(), val.end(), val.begin(), ::tolower);
        if (val == "true" || val == "yes" || val == "1") return true;
        if (val == "false" || val == "no" || val == "0") return false;
        return std::nullopt;
    };
    

    m_lkh3Config.PROBLEM_FILE = map["LKH3/PROBLEM_FILE"];
    m_lkh3Config.OUTPUT_TOUR_FILE = map["LKH3/OUTPUT_TOUR_FILE"];

    m_lkh3Config.ASCENT_CANDIDATES = get_optional_int("LKH3/ASCENT_CANDIDATES");
    m_lkh3Config.BACKBONE_TRIALS = get_optional_int("LKH3/BACKBONE_TRIALS");
    m_lkh3Config.BACKTRACKING = get_optional_bool("LKH3/BACKTRACKING");
    m_lkh3Config.CANDIDATE_SET_TYPE = get_optional_string("LKH3/CANDIDATE_SET_TYPE");
    m_lkh3Config.EXCESS = get_optional_int("LKH3/EXCESS");
    m_lkh3Config.EXTRA_CANDIDATES = get_optional_int("LKH3/EXTRA_CANDIDATES");
    m_lkh3Config.EXTRA_CANDIDATE_SET_TYPE = get_optional_string("LKH3/EXTRA_CANDIDATE_SET_TYPE");

    m_lkh3Config.GAIN23 = get_optional_bool("LKH3/GAIN23");
    m_lkh3Config.GAIN_CRITERION = get_optional_bool("LKH3/GAIN_CRITERION");
    m_lkh3Config.SUBGRADIENT = get_optional_bool("LKH3/SUBGRADIENT");

    m_lkh3Config.INITIAL_PERIOD = get_optional_int("LKH3/INITIAL_PERIOD");
    m_lkh3Config.INITIAL_STEP_SIZE = get_optional_int("LKH3/INITIAL_STEP_SIZE");
    m_lkh3Config.INITIAL_TOUR_ALGORITHM = get_optional_string("LKH3/INITIAL_TOUR_ALGORITHM");
    m_lkh3Config.INITIAL_TOUR_FILE = get_optional_string("LKH3/INITIAL_TOUR_FILE");
    m_lkh3Config.INITIAL_TOUR_FRACTION = get_optional_double("LKH3/INITIAL_TOUR_FRACTION");

    m_lkh3Config.INPUT_TOUR_FILE = get_optional_string("LKH3/INPUT_TOUR_FILE");
    m_lkh3Config.MERGE_TOUR_FILE = get_optional_string("LKH3/MERGE_TOUR_FILE");

    m_lkh3Config.KICKS = get_optional_int("LKH3/KICKS");
    m_lkh3Config.KICK_TYPE = get_optional_int("LKH3/KICK_TYPE");
    m_lkh3Config.MAKESPAN = get_optional_bool("LKH3/MAKESPAN");
    m_lkh3Config.MAX_BREADTH = get_optional_int("LKH3/MAX_BREADTH");
    m_lkh3Config.MAX_CANDIDATES = get_optional_int("LKH3/MAX_CANDIDATES");
    m_lkh3Config.MAX_SWAPS = get_optional_int("LKH3/MAX_SWAPS");
    m_lkh3Config.MAX_TRIALS = get_optional_int("LKH3/MAX_TRIALS");
    m_lkh3Config.MOVE_TYPE = get_optional_int("LKH3/MOVE_TYPE");
    m_lkh3Config.NONSEQUENTIAL_MOVE_TYPE = get_optional_int("LKH3/NONSEQUENTIAL_MOVE_TYPE");
    m_lkh3Config.PATCHING_A = get_optional_int("LKH3/PATCHING_A");
    m_lkh3Config.PATCHING_C = get_optional_int("LKH3/PATCHING_C");
    m_lkh3Config.SUBSEQUENT_MOVE_TYPE = get_optional_int("LKH3/SUBSEQUENT_MOVE_TYPE");
    m_lkh3Config.SUBSEQUENT_PATCHING = get_optional_bool("LKH3/SUBSEQUENT_PATCHING");

    m_lkh3Config.OPTIMUM = get_optional_int("LKH3/OPTIMUM");
    m_lkh3Config.STOP_AT_OPTIMUM = get_optional_bool("LKH3/STOP_AT_OPTIMUM");
    m_lkh3Config.TIME_LIMIT = get_optional_double("LKH3/TIME_LIMIT");

    m_lkh3Config.DEPOT = get_optional_int("LKH3/DEPOT");
    m_lkh3Config.COMMENT = get_optional_string("LKH3/COMMENT");

    m_lkh3Config.TOUR_FILE = get_optional_string("LKH3/TOUR_FILE");
    m_lkh3Config.TRACE_LEVEL = get_optional_int("LKH3/TRACE_LEVEL");

    m_lkh3Config.POPULATION_SIZE = get_optional_int("LKH3/POPULATION_SIZE");
    m_lkh3Config.PRECISION = get_optional_int("LKH3/PRECISION");
    m_lkh3Config.RESTRICTED_SEARCH = get_optional_bool("LKH3/RESTRICTED_SEARCH");
    m_lkh3Config.RUNS = get_optional_int("LKH3/RUNS");
    m_lkh3Config.SEED = get_optional_int("LKH3/SEED");
    m_lkh3Config.SALESMEN = get_optional_int("LKH3/SALESMEN");
    m_lkh3Config.SCALE = get_optional_int("LKH3/SCALE");
    m_lkh3Config.SINTEF_SOLUTION_FILE = get_optional_string("LKH3/SINTEF_SOLUTION_FILE");
    m_lkh3Config.PI_FILE = get_optional_string("LKH3/PI_FILE");

    m_lkh3Config.SUBPROBLEM_SIZE = get_optional_int("LKH3/SUBPROBLEM_SIZE");
    m_lkh3Config.SUBPROBLEM_TOUR_FILE = get_optional_string("LKH3/SUBPROBLEM_TOUR_FILE");

    m_lkh3Config.MTSP_MIN_SIZE = get_optional_int("LKH3/MTSP_MIN_SIZE");
    m_lkh3Config.MTSP_MAX_SIZE = get_optional_int("LKH3/MTSP_MAX_SIZE");
    m_lkh3Config.MTSP_OBJECTIVE = get_optional_string("LKH3/MTSP_OBJECTIVE");
    m_lkh3Config.MTSP_SOLUTION_FILE = get_optional_string("LKH3/MTSP_SOLUTION_FILE");
    m_lkh3Config.VEHICLES = get_optional_int("LKH3/VEHICLES");

    m_lkh3Config.SPECIAL = get_optional_bool("LKH3/SPECIAL");

    // TODO: fixme
    // BWTSP
    /*if (map.contains("LKH3/BWTSP")) {
        std::istringstream iss(map["LKH3/BWTSP"]);
        int b = 0, q = 0;
        if (!(iss >> b >> q)) {
            throw std::runtime_error("Invalid BWTSP format: expected at least two integers");
        }
        std::optional<int> l = std::nullopt;
        int temp;
        if (iss >> temp) {
            l = temp;
        }
        m_lkh3Config.BWTSP = std::make_tuple(b, q, l);
    }*/
    
}

void ConfigurationProvider::constructConcordeConfig(std::unordered_map<std::string, std::string> map){

    auto get_optional_int = [&](const std::string& key) -> std::optional<int> {
        if (!map.contains(key)) return std::nullopt;
        const std::string& val = map.at(key);
        if (val.empty()) return std::nullopt;
        try {
            size_t pos = 0;
            int res = std::stoi(val, &pos);
            if (pos != val.size()) return std::nullopt;
            return res;
        } catch (...) {
            return std::nullopt;
        }
    };
    
    auto get_optional_double = [&](const std::string& key) -> std::optional<double> {
        if (!map.contains(key)) return std::nullopt;
        const std::string& val = map.at(key);
        if (val.empty()) return std::nullopt;
        try {
            size_t pos = 0;
            double res = std::stod(val, &pos);
            if (pos != val.size()) return std::nullopt;
            return res;
        } catch (...) {
            return std::nullopt;
        }
    };
    
    auto get_optional_string = [&](const std::string& key) -> std::optional<std::string> {
        if (!map.contains(key)) return std::nullopt;
        const std::string& val = map.at(key);
        return val.empty() ? std::nullopt : std::optional<std::string>{val};
    };
    
    auto get_optional_bool = [&](const std::string& key) -> std::optional<bool> {
        if (!map.contains(key)) return std::nullopt;
        std::string val = map[key];
        std::transform(val.begin(), val.end(), val.begin(), ::tolower);
        if (val == "true" || val == "yes" || val == "1") return true;
        if (val == "false" || val == "no" || val == "0") return false;
        return std::nullopt;
    };
    

    m_concordeConfig.PROBLEM_FILE = map["Concorde/PROBLEM_FILE"];
    m_concordeConfig.OUTPUT_TOUR_FILE = map["Concorde/OUTPUT_TOUR_FILE"];

    m_concordeConfig.INITIAL_TOUR_FILE = get_optional_string("Concorde/INITIAL_TOUR_FILE");
    m_concordeConfig.RESTART_FILE = get_optional_string("Concorde/RESTART_FILE");

    m_concordeConfig.BRANCHING = get_optional_bool("Concorde/BRANCHING");
    m_concordeConfig.DFS_BRANCHING = get_optional_bool("Concorde/DFS_BRANCHING");
    m_concordeConfig.BOSS_MODE = get_optional_bool("Concorde/BOSS_MODE");
    m_concordeConfig.GRUNT_HOST = get_optional_string("Concorde/GRUNT_HOST");

    m_concordeConfig.EDGEGEN_FILE = get_optional_string("Concorde/EDGEGEN_FILE");
    m_concordeConfig.INITIAL_EDGE_FILE = get_optional_string("Concorde/INITIAL_EDGE_FILE");
    m_concordeConfig.FULL_EDGE_FILE = get_optional_string("Concorde/FULL_EDGE_FILE");

    m_concordeConfig.EXTRA_CUT_FILE = get_optional_string("Concorde/EXTRA_CUT_FILE");
    m_concordeConfig.CUTPOOL_FILE = get_optional_string("Concorde/CUTPOOL_FILE");

    m_concordeConfig.MAX_CHUNK_SIZE = get_optional_int("Concorde/MAX_CHUNK_SIZE");
    m_concordeConfig.BRANCH_ATTEMPTS = get_optional_int("Concorde/BRANCH_ATTEMPTS");
    m_concordeConfig.SKIP_CUTS_AT_ROOT = get_optional_bool("Concorde/SKIP_CUTS_AT_ROOT");
    m_concordeConfig.NO_BRANCH_ON_SUBTOUR = get_optional_bool("Concorde/NO_BRANCH_ON_SUBTOUR");
    m_concordeConfig.ONLY_BLOSSOM_POLYHEDRON = get_optional_bool("Concorde/ONLY_BLOSSOM_POLYHEDRON");
    m_concordeConfig.ONLY_SUBTOUR_POLYHEDRON = get_optional_bool("Concorde/ONLY_SUBTOUR_POLYHEDRON");
    m_concordeConfig.MULTI_PASS_CUTS = get_optional_bool("Concorde/MULTI_PASS_CUTS");

    m_concordeConfig.SEED = get_optional_int("Concorde/SEED");
    m_concordeConfig.RANDOM_GRID_SIZE = get_optional_int("Concorde/RANDOM_GRID_SIZE");

    m_concordeConfig.VERBOSE = get_optional_bool("Concorde/VERBOSE");
    m_concordeConfig.FAST_CUTS_ONLY = get_optional_bool("Concorde/FAST_CUTS_ONLY");
    m_concordeConfig.WRITE_MIN_REDUCED_COST_ARCS = get_optional_int("Concorde/WRITE_MIN_REDUCED_COST_ARCS");

    m_concordeConfig.DISTANCE_NORM = get_optional_int("Concorde/DISTANCE_NORM");

    m_concordeConfig.DELETE_TEMP_FILES = get_optional_bool("Concorde/DELETE_TEMP_FILES");

    m_concordeConfig.PROBLEM_NAME = get_optional_string("Concorde/PROBLEM_NAME");
    m_concordeConfig.SAVE_TOUR_AS_EDGE_FILE = get_optional_bool("Concorde/SAVE_TOUR_AS_EDGE_FILE");
}

void ConfigurationProvider::constructGeneralConfig(std::unordered_map<std::string, std::string> map){
    std::string enabled_algorithms = map["execution/enabled_algorithms"];

    std::stringstream ss(enabled_algorithms);
    std::string token;

    while(std::getline(ss, token, ',')){
        if(!token.empty())
        m_generalConfig.enabledAlgorithms.push_back(token);
    }

}