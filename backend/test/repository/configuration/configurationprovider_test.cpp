#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "repository/configuration/configurationprovider.h"

namespace fs = std::filesystem;

// Funzione helper per stampare optional<int>
void printOptional(const std::string& name, const std::optional<int>& val) {
    if (val.has_value())
        std::cout << name << ": " << val.value() << std::endl;
    else
        std::cout << name << ": <none>" << std::endl;
}

// Funzione helper per stampare optional<double>
void printOptional(const std::string& name, const std::optional<double>& val) {
    if (val.has_value())
        std::cout << name << ": " << val.value() << std::endl;
    else
        std::cout << name << ": <none>" << std::endl;
}

// Funzione helper per stampare optional<bool>
void printOptional(const std::string& name, const std::optional<bool>& val) {
    if (val.has_value())
        std::cout << name << ": " << (val.value() ? "true" : "false") << std::endl;
    else
        std::cout << name << ": <none>" << std::endl;
}

// Funzione helper per stampare optional<string>
void printOptional(const std::string& name, const std::optional<std::string>& val) {
    if (val.has_value())
        std::cout << name << ": " << val.value() << std::endl;
    else
        std::cout << name << ": <none>" << std::endl;
}

TEST(ConfigurationReaderSimpleTest, PrintConfigValues) {
    std::string configPath = "../tspmetasolver.set";  // cambia path se necessario

    ConfigurationProvider provider;

    ASSERT_NO_THROW(provider.readConfiguration(configPath));

    const auto& lkh3 = provider.getLKH3Config();
    const auto& conc = provider.getConcordeConfig();

    std::cout << "###### LKH3 CONFIGURATION ######" << std::endl;

    std::cout << "PROBLEM_FILE: " << lkh3.PROBLEM_FILE << std::endl;
    std::cout << "OUTPUT_TOUR_FILE: " << lkh3.OUTPUT_TOUR_FILE << std::endl;

    printOptional("ASCENT_CANDIDATES", lkh3.ASCENT_CANDIDATES);
    printOptional("BACKBONE_TRIALS", lkh3.BACKBONE_TRIALS);
    printOptional("BACKTRACKING", lkh3.BACKTRACKING);
    printOptional("CANDIDATE_SET_TYPE", lkh3.CANDIDATE_SET_TYPE);
    printOptional("EXCESS", lkh3.EXCESS);
    printOptional("EXTRA_CANDIDATES", lkh3.EXTRA_CANDIDATES);
    printOptional("EXTRA_CANDIDATE_SET_TYPE", lkh3.EXTRA_CANDIDATE_SET_TYPE);

    printOptional("GAIN23", lkh3.GAIN23);
    printOptional("GAIN_CRITERION", lkh3.GAIN_CRITERION);
    printOptional("SUBGRADIENT", lkh3.SUBGRADIENT);

    printOptional("INITIAL_PERIOD", lkh3.INITIAL_PERIOD);
    printOptional("INITIAL_STEP_SIZE", lkh3.INITIAL_STEP_SIZE);
    printOptional("INITIAL_TOUR_ALGORITHM", lkh3.INITIAL_TOUR_ALGORITHM);
    printOptional("INITIAL_TOUR_FILE", lkh3.INITIAL_TOUR_FILE);
    printOptional("INITIAL_TOUR_FRACTION", lkh3.INITIAL_TOUR_FRACTION);

    printOptional("INPUT_TOUR_FILE", lkh3.INPUT_TOUR_FILE);
    printOptional("MERGE_TOUR_FILE", lkh3.MERGE_TOUR_FILE);

    printOptional("KICKS", lkh3.KICKS);
    printOptional("KICK_TYPE", lkh3.KICK_TYPE);
    printOptional("MAKESPAN", lkh3.MAKESPAN);
    printOptional("MAX_BREADTH", lkh3.MAX_BREADTH);
    printOptional("MAX_CANDIDATES", lkh3.MAX_CANDIDATES);
    printOptional("MAX_SWAPS", lkh3.MAX_SWAPS);
    printOptional("MAX_TRIALS", lkh3.MAX_TRIALS);
    printOptional("MOVE_TYPE", lkh3.MOVE_TYPE);
    printOptional("NONSEQUENTIAL_MOVE_TYPE", lkh3.NONSEQUENTIAL_MOVE_TYPE);
    printOptional("PATCHING_A", lkh3.PATCHING_A);
    printOptional("PATCHING_C", lkh3.PATCHING_C);
    printOptional("SUBSEQUENT_MOVE_TYPE", lkh3.SUBSEQUENT_MOVE_TYPE);
    printOptional("SUBSEQUENT_PATCHING", lkh3.SUBSEQUENT_PATCHING);

    printOptional("OPTIMUM", lkh3.OPTIMUM);
    printOptional("STOP_AT_OPTIMUM", lkh3.STOP_AT_OPTIMUM);
    printOptional("TIME_LIMIT", lkh3.TIME_LIMIT);

    printOptional("DEPOT", lkh3.DEPOT);
    printOptional("COMMENT", lkh3.COMMENT);

    printOptional("TOUR_FILE", lkh3.TOUR_FILE);
    printOptional("TRACE_LEVEL", lkh3.TRACE_LEVEL);

    printOptional("POPULATION_SIZE", lkh3.POPULATION_SIZE);
    printOptional("PRECISION", lkh3.PRECISION);
    printOptional("RESTRICTED_SEARCH", lkh3.RESTRICTED_SEARCH);
    printOptional("RUNS", lkh3.RUNS);
    printOptional("SEED", lkh3.SEED);
    printOptional("SALESMEN", lkh3.SALESMEN);
    printOptional("SCALE", lkh3.SCALE);
    printOptional("SINTEF_SOLUTION_FILE", lkh3.SINTEF_SOLUTION_FILE);
    printOptional("PI_FILE", lkh3.PI_FILE);

    printOptional("SUBPROBLEM_SIZE", lkh3.SUBPROBLEM_SIZE);
    printOptional("SUBPROBLEM_TOUR_FILE", lkh3.SUBPROBLEM_TOUR_FILE);

    printOptional("MTSP_MIN_SIZE", lkh3.MTSP_MIN_SIZE);
    printOptional("MTSP_MAX_SIZE", lkh3.MTSP_MAX_SIZE);
    printOptional("MTSP_OBJECTIVE", lkh3.MTSP_OBJECTIVE);
    printOptional("MTSP_SOLUTION_FILE", lkh3.MTSP_SOLUTION_FILE);
    printOptional("VEHICLES", lkh3.VEHICLES);

    printOptional("SPECIAL", lkh3.SPECIAL);

    // BWTSP tuple stamp
    if (lkh3.BWTSP.has_value()) {
        auto& [b, q, l] = lkh3.BWTSP.value();
        std::cout << "BWTSP: " << b << " " << q << " ";
        if (l.has_value())
            std::cout << l.value();
        else
            std::cout << "<none>";
        std::cout << std::endl;
    } else {
        std::cout << "BWTSP: <none>" << std::endl;
    }

    std::cout << "\n###### CONCORDE CONFIGURATION ######" << std::endl;

    std::cout << "PROBLEM_FILE: " << conc.PROBLEM_FILE << std::endl;
    std::cout << "OUTPUT_TOUR_FILE: " << conc.OUTPUT_TOUR_FILE << std::endl;

    printOptional("INITIAL_TOUR_FILE", conc.INITIAL_TOUR_FILE);
    printOptional("RESTART_FILE", conc.RESTART_FILE);

    printOptional("BRANCHING", conc.BRANCHING);
    printOptional("DFS_BRANCHING", conc.DFS_BRANCHING);
    printOptional("BOSS_MODE", conc.BOSS_MODE);
    printOptional("GRUNT_HOST", conc.GRUNT_HOST);

    printOptional("EDGEGEN_FILE", conc.EDGEGEN_FILE);
    printOptional("INITIAL_EDGE_FILE", conc.INITIAL_EDGE_FILE);
    printOptional("FULL_EDGE_FILE", conc.FULL_EDGE_FILE);

    printOptional("EXTRA_CUT_FILE", conc.EXTRA_CUT_FILE);
    printOptional("CUTPOOL_FILE", conc.CUTPOOL_FILE);

    printOptional("MAX_CHUNK_SIZE", conc.MAX_CHUNK_SIZE);
    printOptional("BRANCH_ATTEMPTS", conc.BRANCH_ATTEMPTS);
    printOptional("SKIP_CUTS_AT_ROOT", conc.SKIP_CUTS_AT_ROOT);
    printOptional("NO_BRANCH_ON_SUBTOUR", conc.NO_BRANCH_ON_SUBTOUR);
    printOptional("ONLY_BLOSSOM_POLYHEDRON", conc.ONLY_BLOSSOM_POLYHEDRON);
    printOptional("ONLY_SUBTOUR_POLYHEDRON", conc.ONLY_SUBTOUR_POLYHEDRON);
    printOptional("MULTI_PASS_CUTS", conc.MULTI_PASS_CUTS);

    printOptional("SEED", conc.SEED);
    printOptional("RANDOM_GRID_SIZE", conc.RANDOM_GRID_SIZE);

    printOptional("VERBOSE", conc.VERBOSE);
    printOptional("FAST_CUTS_ONLY", conc.FAST_CUTS_ONLY);
    printOptional("WRITE_MIN_REDUCED_COST_ARCS", conc.WRITE_MIN_REDUCED_COST_ARCS);

    printOptional("DISTANCE_NORM", conc.DISTANCE_NORM);

    printOptional("DELETE_TEMP_FILES", conc.DELETE_TEMP_FILES);

    printOptional("PROBLEM_NAME", conc.PROBLEM_NAME);
    printOptional("SAVE_TOUR_AS_EDGE_FILE", conc.SAVE_TOUR_AS_EDGE_FILE);
}
