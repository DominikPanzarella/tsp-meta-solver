#include "repository/configuration2/configprovider.h"
#include "repository/parser/jsonparser.h"
#include "repository/configuration2/config/nearestinsertioninstancesetting.h"
#include "repository/configuration2/config/farthestinsertioninstancesetting.h"
#include "repository/configuration2/config/nearestneighbourinstancesetting.h"
#include "repository/configuration2/config/concordeinstancesetting.h"
#include "repository/configuration2/config/lkh3instancesetting.h"
#include "repository/configuration2/compute/computestartingnode.h"

#include <cstdlib>      // for random generator


const std::shared_ptr<ConfigProvider>& ConfigProvider::getInstance() {
    static std::shared_ptr<ConfigProvider> mySelf(new ConfigProvider());
    return mySelf;
}

ConfigProvider::ConfigProvider() : m_cs{std::make_unique<ComputeStartingNode>() } {
    
}

JSON ConfigProvider::read(const std::string& file_path) {
    JsonParser parser;

    m_json = parser.read(file_path);

    return m_json;
}

void ConfigProvider::configure(std::vector<std::shared_ptr<IProblem>> problems) {

    configureNI(problems);

    configureNN(problems);

    configureFI(problems);

    configureCC(problems);
    
    configureLKH3(problems);

    std::vector<std::string> algorithms = getEnabledAlgorithms();
    
    for(const auto& algo : algorithms){
        const std::string& algoName = algo;
        for(const auto& problem : problems){
            const std::string& name = problem->getName();
            if (algoName == "NearestInsertion") {
                if (!m_ni->hasInstance(name)) {
                    m_ni->addInstance(name, std::make_shared<NearestInsertionInstanceSetting>());
                }
            } else if (algoName == "NearestNeighbour") {
                if (!m_nn->hasInstance(name)) {
                    //TODO: starting node can be selected randomly
                    m_nn->addInstance(name, std::make_shared<NearestNeighbourInstanceSetting>());      
                }
            } else if (algoName == "FarthestInsertion") {
                if (!m_fi->hasInstance(name)) {
                    m_fi->addInstance(name, std::make_shared<FarthestInsertionInstanceSetting>());
                }
            } else if (algoName == "Concorde") {
                if (!m_cc->hasInstance(name)) {
                    m_cc->addInstance(name, std::make_shared<ConcordeInstanceSetting>());
                }
            } else if (algoName == "LKH3") {
                if (!m_lkh3->hasInstance(name)) {
                    m_lkh3->addInstance(name, std::make_shared<LKH3InstanceSetting>());
                }
            }
        }
    }

}

std::vector<std::string> ConfigProvider::getEnabledAlgorithms() {
    std::vector<std::string> enabledAlgos;

    if (m_json.contains("Execution")) {
        const auto& execution = m_json["Execution"];
        const auto& eee = (*execution)["EnabledAlgorithms"];
        enabledAlgos = eee->getArrayOfStrings();
    }

    return enabledAlgos;
}

// ###################################################
// # NEAREST INSERTION                               #
// ###################################################

std::shared_ptr<NearestInsertionGeneralSetting> ConfigProvider::getNearestInsertionSettings() {
    return m_ni;
}

void ConfigProvider::configureNI(std::vector<std::shared_ptr<IProblem>> problems){
    std::shared_ptr<NearestInsertionGeneralSetting> config = std::make_shared<NearestInsertionGeneralSetting>();

    auto niNode = m_json["NearestInsertion"];

    // NO GENERAL SETTINGS

    if(niNode->contains("GeneralSettings")){
        auto generalSetting = (*niNode)["GeneralSettings"];

        if(generalSetting->contains("HardInstances")){
            auto hardInstances = (*generalSetting)["HardInstances"];

            int nodes = 4;
            if(hardInstances->contains("Nodes")){
                nodes = (*hardInstances)["Nodes"]->get<int>();
            }

            config->setHardInstancesNumberOfNodes(nodes);
        }

    }

    // SINGLE INSTANCE SETTINGS

    /*
    if(niNode->contains("InstancesSettings")){
        auto instanceNode = (*niNode)["InstancesSettings"];

        for(const auto& instanceName : instanceNode->keys()){
            auto instanceJson = (*instanceNode)[instanceName];

        
            int m_startingNode = 0;

            if(instanceJson->contains("StartingNode")){
                m_startingNode = (*instanceJson)["StartingNode"]->get<int>();
            }

            auto instanceSetting = std::make_shared<NearestInsertionInstanceSetting>(m_startingNode);

            config->addInstance(instanceName, instanceSetting);
        }
    }
    */

    //starting node is chosen by picking the shortes edge
    for(const auto& problem : problems) {
        std::vector<std::pair<int,int>> shortestEdges = m_cs->computeShortestEdges(problem);
        //now random pikcing


        int randomEdge = rand() % shortestEdges.size();
        std::pair<int,int> shortestEdge = shortestEdges.at(randomEdge);

        //pick random node to start

        int randomNode = rand() % 2;
        int startingNode = (randomNode==0) ? shortestEdge.first : shortestEdge.second;

        auto instanceSetting = std::make_shared<NearestInsertionInstanceSetting>(startingNode);

        config->addInstance(problem->getName(), instanceSetting);

    }

    m_ni = std::move(config);
}


// ###################################################
// # NEAREST NEIGHBOUR                               #
// ###################################################

std::shared_ptr<NearestNeighbourGeneralSetting> ConfigProvider::getNearestNeighbourSettings(){
    return m_nn;
}

void ConfigProvider::configureNN(std::vector<std::shared_ptr<IProblem>> problems){
    std::shared_ptr<NearestNeighbourGeneralSetting> config = std::make_shared<NearestNeighbourGeneralSetting>();

    auto niNode = m_json["NearesetNeighbour"];

    // NO GENERAL SETTINGS

    if(niNode->contains("GeneralSettings")){
        auto generalSetting = (*niNode)["GeneralSettings"];

        if(generalSetting->contains("HardInstances")){
            auto hardInstances = (*generalSetting)["HardInstances"];

            int nodes = 4;
            if(hardInstances->contains("Nodes")){
                nodes = (*hardInstances)["Nodes"]->get<int>();
            }

            config->setHardInstancesNumberOfNodes(nodes);

            
        }

    }

    // SINGLE INSTANCE SETTINGS

    if(niNode->contains("InstancesSettings")){
        auto instanceNode = (*niNode)["InstancesSettings"];

        for(const auto& instanceName : instanceNode->keys()){
            auto instanceJson = (*instanceNode)[instanceName];

        
            int m_startingNode = 0;

            if(instanceJson->contains("StartingNode")){
                m_startingNode = (*instanceJson)["StartingNode"]->get<int>();
            }

            auto instanceSetting = std::make_shared<NearestNeighbourInstanceSetting>(m_startingNode);

            config->addInstance(instanceName, instanceSetting);
        }
    }

    m_nn = std::move(config);
}

// ###################################################
// # FARTHEST INSERTION                              #
// ###################################################

std::shared_ptr<FarthestInsertionGeneralSetting> ConfigProvider::getFarthestInsertionSettings(){
    return m_fi;
}

void ConfigProvider::configureFI(std::vector<std::shared_ptr<IProblem>> problems){
    std::shared_ptr<FarthestInsertionGeneralSetting> config = std::make_shared<FarthestInsertionGeneralSetting>();

    auto niNode = m_json["FarthestInsertion"];

    // NO GENERAL SETTINGS

    if(niNode->contains("GeneralSettings")){
        auto generalSetting = (*niNode)["GeneralSettings"];

        if(generalSetting->contains("HardInstances")){
            auto hardInstances = (*generalSetting)["HardInstances"];

            int nodes = 4;
            if(hardInstances->contains("Nodes")){
                nodes = (*hardInstances)["Nodes"]->get<int>();
            }

            config->setHardInstancesNumberOfNodes(nodes);
        }

    }

    // SINGLE INSTANCE SETTINGS

    /*if(niNode->contains("InstancesSettings")){
        auto instanceNode = (*niNode)["InstancesSettings"];

        for(const auto& instanceName : instanceNode->keys()){
            auto instanceJson = (*instanceNode)[instanceName];

        
            int m_startingNode = 0;

            if(instanceJson->contains("StartingNode")){
                m_startingNode = (*instanceJson)["StartingNode"]->get<int>();
            }

            auto instanceSetting = std::make_shared<FarthestInsertionInstanceSetting>(m_startingNode);

            config->addInstance(instanceName, instanceSetting);
        }
    }*/

        //starting node is chosen by picking the shortes edge
        for(const auto& problem : problems) {
            std::vector<std::pair<int,int>> shortestEdges = m_cs->computeShortestEdges(problem);
            //now random pikcing
    
    
            int randomEdge = rand() % shortestEdges.size();
            std::pair<int,int> shortestEdge = shortestEdges.at(randomEdge);
    
            //pick random node to start
    
            int randomNode = rand() % 2;
            int startingNode = (randomNode==0) ? shortestEdge.first : shortestEdge.second;
    
            auto instanceSetting = std::make_shared<FarthestInsertionInstanceSetting>(startingNode);
    
            config->addInstance(problem->getName(), instanceSetting);
    
        }

    m_fi = std::move(config);

}

// ###################################################
// # CONCORDE                                        #
// ###################################################


std::shared_ptr<ConcordeGeneralSetting> ConfigProvider::getConcordeSettings(){
    return m_cc;
}

void ConfigProvider::configureCC(std::vector<std::shared_ptr<IProblem>> problems) {
    std::shared_ptr<ConcordeGeneralSetting> config = std::make_shared<ConcordeGeneralSetting>();

    auto ccNode = m_json["Concorde"];

    // GENERAL SETTINGS
    if (ccNode->contains("GeneralSettings")) {
        auto generalSetting = (*ccNode)["GeneralSettings"];

        // Per ogni parametro opzionale di ConcordeGeneralSetting prova a leggerlo
        if (generalSetting->contains("Branching")) {
            config->setBranching((*generalSetting)["Branching"]->get<bool>());
        }
        if (generalSetting->contains("DFSBranching")) {
            config->setDFSBranching((*generalSetting)["DFSBranching"]->get<bool>());
        }
        if (generalSetting->contains("BossMode")) {
            config->setBossMode((*generalSetting)["BossMode"]->get<bool>());
        }
        if (generalSetting->contains("GruntHost")) {
            config->setGruntHost((*generalSetting)["GruntHost"]->get<std::string>());
        }
        if (generalSetting->contains("MaxChunkSize")) {
            config->setMaxChunkSize((*generalSetting)["MaxChunkSize"]->get<int>());
        }
        if (generalSetting->contains("BranchAttempts")) {
            config->setBranchAttempts((*generalSetting)["BranchAttempts"]->get<int>());
        }
        if (generalSetting->contains("SkipCutsAtRoot")) {
            config->setSkipCutsAtRoot((*generalSetting)["SkipCutsAtRoot"]->get<bool>());
        }
        if (generalSetting->contains("NoBranchOnSubtour")) {
            config->setNoBranchOnSubtour((*generalSetting)["NoBranchOnSubtour"]->get<bool>());
        }
        if (generalSetting->contains("OnlyBlossomPolyhedron")) {
            config->setOnlyBlossomPolyhedron((*generalSetting)["OnlyBlossomPolyhedron"]->get<bool>());
        }
        if (generalSetting->contains("OnlySubtourPolyhedron")) {
            config->setOnlySubtourPolyhedron((*generalSetting)["OnlySubtourPolyhedron"]->get<bool>());
        }
        if (generalSetting->contains("MultiPassCuts")) {
            config->setMultiPassCuts((*generalSetting)["MultiPassCuts"]->get<bool>());
        }
        if (generalSetting->contains("Seed")) {
            config->setSeed((*generalSetting)["Seed"]->get<int>());
        }
        if (generalSetting->contains("RandomGridSize")) {
            config->setRandomGridSize((*generalSetting)["RandomGridSize"]->get<int>());
        }
        if (generalSetting->contains("Verbose")) {
            config->setVerbose((*generalSetting)["Verbose"]->get<bool>());
        }
        if (generalSetting->contains("FastCutsOnly")) {
            config->setFastCutsOnly((*generalSetting)["FastCutsOnly"]->get<bool>());
        }
        if (generalSetting->contains("WriteMinReducedCostArcs")) {
            config->setWriteMinReducedCostArcs((*generalSetting)["WriteMinReducedCostArcs"]->get<int>());
        }
        if (generalSetting->contains("DistanceNorm")) {
            config->setDistanceNorm((*generalSetting)["DistanceNorm"]->get<int>());
        }
        if (generalSetting->contains("DeleteTempFiles")) {
            config->setDeleteTempFiles((*generalSetting)["DeleteTempFiles"]->get<bool>());
        }
        if (generalSetting->contains("SaveTourAsEdgeFile")) {
            config->setSaveTourAsEdgeFile((*generalSetting)["SaveTourAsEdgeFile"]->get<bool>());
        }
    }

    // INSTANCES SETTINGS
    if (ccNode->contains("InstancesSettings")) {
        auto instancesNode = (*ccNode)["InstancesSettings"];

        for (const auto& instanceName : instancesNode->keys()) {
            auto instanceJson = (*instancesNode)[instanceName];

            auto instanceSetting = std::make_shared<ConcordeInstanceSetting>();

            if (instanceJson->contains("PROBLEM_FILE")) {
                instanceSetting->setProblemFile((*instanceJson)["PROBLEM_FILE"]->get<std::string>());
            }
            if (instanceJson->contains("OUTPUT_TOUR_FILE")) {
                instanceSetting->setOutputTourFile((*instanceJson)["OUTPUT_TOUR_FILE"]->get<std::string>());
            }
            if (instanceJson->contains("INITIAL_TOUR_FILE")) {
                instanceSetting->setInitialTourFile((*instanceJson)["INITIAL_TOUR_FILE"]->get<std::string>());
            }
            if (instanceJson->contains("RESTART_FILE")) {
                instanceSetting->setRestartFile((*instanceJson)["RESTART_FILE"]->get<std::string>());
            }
            if (instanceJson->contains("EDGEGEN_FILE")) {
                instanceSetting->setEdgegenFile((*instanceJson)["EDGEGEN_FILE"]->get<std::string>());
            }
            if (instanceJson->contains("INITIAL_EDGE_FILE")) {
                instanceSetting->setInitialEdgeFile((*instanceJson)["INITIAL_EDGE_FILE"]->get<std::string>());
            }
            if (instanceJson->contains("FULL_EDGE_FILE")) {
                instanceSetting->setFullEdgeFile((*instanceJson)["FULL_EDGE_FILE"]->get<std::string>());
            }
            if (instanceJson->contains("EXTRA_CUT_FILE")) {
                instanceSetting->setExtraCutFile((*instanceJson)["EXTRA_CUT_FILE"]->get<std::string>());
            }
            if (instanceJson->contains("CUTPOOL_FILE")) {
                instanceSetting->setCutpoolFile((*instanceJson)["CUTPOOL_FILE"]->get<std::string>());
            }
            if (instanceJson->contains("PROBLEM_NAME")) {
                instanceSetting->setProblemName((*instanceJson)["PROBLEM_NAME"]->get<std::string>());
            }

            config->addInstance(instanceName, instanceSetting);
        }
    }

    m_cc = std::move(config);
}


// ###################################################
// # LKH3                                           #
// ###################################################

std::shared_ptr<LKH3GeneralSetting> ConfigProvider::getLKH3Settings(){
    return m_lkh3;
}

void ConfigProvider::configureLKH3(std::vector<std::shared_ptr<IProblem>> problems) {
    auto config = std::make_shared<LKH3GeneralSetting>();

    auto lkhNode = m_json["LKH3"];
    if (!lkhNode) {
        m_lkh3 = std::move(config);
        return;
    }

    // --- General Settings ---
    if (lkhNode->contains("GeneralSettings")) {
        auto generalSettings = (*lkhNode)["GeneralSettings"];

        if (generalSettings->contains("ASCENT_CANDIDATES"))
            config->setAscentCandidates((*generalSettings)["ASCENT_CANDIDATES"]->get<int>());

        if (generalSettings->contains("BACKBONE_TRIALS"))
            config->setBackboneTrials((*generalSettings)["BACKBONE_TRIALS"]->get<int>());

        if (generalSettings->contains("BACKTRACKING"))
            config->setBacktracking((*generalSettings)["BACKTRACKING"]->get<bool>());

        if (generalSettings->contains("CANDIDATE_FILE")) {
                auto candidateFiles = (*generalSettings)["CANDIDATE_FILE"];
            
            if (candidateFiles && candidateFiles->is_array()) {
                const auto& arr = candidateFiles->impl_->data;  // nlohmann::json array
            
                for (const auto& file : arr) {
                    config->addCandidateFile(file.get<std::string>());
             }
            }
        }
            

        if (generalSettings->contains("BWTSP")) {
            auto bwtspArr = (*generalSettings)["BWTSP"];
        
            if (bwtspArr && bwtspArr->is_array()) {
                int B = 0, Q = 0;
                std::optional<int> L = std::nullopt;
        
                auto b0 = (*bwtspArr)[0];
                auto b1 = (*bwtspArr)[1];
        
                if (b0) B = b0->get<int>();
                if (b1) Q = b1->get<int>();
        
                auto b2 = (*bwtspArr)[2];
                if (b2) L = b2->get<int>();
        
                config->setBWTSP(std::make_tuple(B, Q, L));
            }
        }
        

        if (generalSettings->contains("CANDIDATE_SET_TYPE"))
            config->setCandidateSetType((*generalSettings)["CANDIDATE_SET_TYPE"]->get<std::string>());

        if (generalSettings->contains("EXCESS"))
            config->setExcess((*generalSettings)["EXCESS"]->get<int>());

        if (generalSettings->contains("EXTRA_CANDIDATES"))
            config->setExtraCandidates((*generalSettings)["EXTRA_CANDIDATES"]->get<int>());

        if (generalSettings->contains("EXTRA_CANDIDATE_SET_TYPE"))
            config->setExtraCandidateSetType((*generalSettings)["EXTRA_CANDIDATE_SET_TYPE"]->get<std::string>());

        if (generalSettings->contains("GAIN23"))
            config->setGain23((*generalSettings)["GAIN23"]->get<bool>());

        if (generalSettings->contains("GAIN_CRITERION"))
            config->setGainCriterion((*generalSettings)["GAIN_CRITERION"]->get<bool>());

        if (generalSettings->contains("SUBGRADIENT"))
            config->setSubgradient((*generalSettings)["SUBGRADIENT"]->get<bool>());

        if (generalSettings->contains("INITIAL_PERIOD"))
            config->setInitialPeriod((*generalSettings)["INITIAL_PERIOD"]->get<int>());

        if (generalSettings->contains("INITIAL_STEP_SIZE"))
            config->setInitialStepSize((*generalSettings)["INITIAL_STEP_SIZE"]->get<int>());

        if (generalSettings->contains("INITIAL_TOUR_ALGORITHM"))
            config->setInitialTourAlgorithm((*generalSettings)["INITIAL_TOUR_ALGORITHM"]->get<std::string>());

        if (generalSettings->contains("INITIAL_TOUR_FRACTION"))
            config->setInitialTourFraction((*generalSettings)["INITIAL_TOUR_FRACTION"]->get<double>());

        if (generalSettings->contains("KICKS"))
            config->setKicks((*generalSettings)["KICKS"]->get<int>());

        if (generalSettings->contains("KICK_TYPE"))
            config->setKickType((*generalSettings)["KICK_TYPE"]->get<int>());

        if (generalSettings->contains("MAKESPAN"))
            config->setMakespan((*generalSettings)["MAKESPAN"]->get<bool>());

        if (generalSettings->contains("MAX_BREADTH"))
            config->setMaxBreadth((*generalSettings)["MAX_BREADTH"]->get<int>());

        if (generalSettings->contains("MAX_CANDIDATES"))
            config->setMaxCandidates((*generalSettings)["MAX_CANDIDATES"]->get<int>());

        if (generalSettings->contains("MAX_SWAPS"))
            config->setMaxSwaps((*generalSettings)["MAX_SWAPS"]->get<int>());

        if (generalSettings->contains("MAX_TRIALS"))
            config->setMaxTrials((*generalSettings)["MAX_TRIALS"]->get<int>());

        if (generalSettings->contains("MOVE_TYPE"))
            config->setMoveType((*generalSettings)["MOVE_TYPE"]->get<int>());

        if (generalSettings->contains("NONSEQUENTIAL_MOVE_TYPE"))
            config->setNonSequentialMoveType((*generalSettings)["NONSEQUENTIAL_MOVE_TYPE"]->get<int>());

        if (generalSettings->contains("PATCHING_A"))
            config->setPatchingA((*generalSettings)["PATCHING_A"]->get<int>());

        if (generalSettings->contains("PATCHING_C"))
            config->setPatchingC((*generalSettings)["PATCHING_C"]->get<int>());

        if (generalSettings->contains("SUBSEQUENT_MOVE_TYPE"))
            config->setSubsequentMoveType((*generalSettings)["SUBSEQUENT_MOVE_TYPE"]->get<int>());

        if (generalSettings->contains("SUBSEQUENT_PATCHING"))
            config->setSubsequentPatching((*generalSettings)["SUBSEQUENT_PATCHING"]->get<bool>());

        if (generalSettings->contains("OPTIMUM"))
            config->setOptimum((*generalSettings)["OPTIMUM"]->get<int>());

        if (generalSettings->contains("STOP_AT_OPTIMUM"))
            config->setStopAtOptimum((*generalSettings)["STOP_AT_OPTIMUM"]->get<bool>());

        if (generalSettings->contains("TIME_LIMIT"))
            config->setTimeLimit((*generalSettings)["TIME_LIMIT"]->get<double>());

        if (generalSettings->contains("DEPOT"))
            config->setDepot((*generalSettings)["DEPOT"]->get<int>());

        if (generalSettings->contains("COMMENT"))
            config->setComment((*generalSettings)["COMMENT"]->get<std::string>());

        if (generalSettings->contains("TRACE_LEVEL"))
            config->setTraceLevel((*generalSettings)["TRACE_LEVEL"]->get<int>());

        if (generalSettings->contains("POPULATION_SIZE"))
            config->setPopulationSize((*generalSettings)["POPULATION_SIZE"]->get<int>());

        if (generalSettings->contains("PRECISION"))
            config->setPrecision((*generalSettings)["PRECISION"]->get<int>());

        if (generalSettings->contains("RESTRICTED_SEARCH"))
            config->setRestrictedSearch((*generalSettings)["RESTRICTED_SEARCH"]->get<bool>());

        if (generalSettings->contains("RUNS"))
            config->setRuns((*generalSettings)["RUNS"]->get<int>());

        if (generalSettings->contains("SEED"))
            config->setSeed((*generalSettings)["SEED"]->get<int>());

        if (generalSettings->contains("SALESMEN"))
            config->setSalesmen((*generalSettings)["SALESMEN"]->get<int>());

        if (generalSettings->contains("SCALE"))
            config->setScale((*generalSettings)["SCALE"]->get<int>());

        if (generalSettings->contains("SINTEF_SOLUTION_FILE"))
            config->setSintefSolutionFile((*generalSettings)["SINTEF_SOLUTION_FILE"]->get<std::string>());

        if (generalSettings->contains("PI_FILE"))
            config->setPiFile((*generalSettings)["PI_FILE"]->get<std::string>());

        if (generalSettings->contains("SUBPROBLEM_SIZE"))
            config->setSubproblemSize((*generalSettings)["SUBPROBLEM_SIZE"]->get<int>());

        if (generalSettings->contains("SUBPROBLEM_TOUR_FILE"))
            config->setSubproblemTourFile((*generalSettings)["SUBPROBLEM_TOUR_FILE"]->get<std::string>());

        if (generalSettings->contains("MTSP_MIN_SIZE"))
            config->setMTSPMinSize((*generalSettings)["MTSP_MIN_SIZE"]->get<int>());

        if (generalSettings->contains("MTSP_MAX_SIZE"))
            config->setMTSPMaxSize((*generalSettings)["MTSP_MAX_SIZE"]->get<int>());

        if (generalSettings->contains("MTSP_OBJECTIVE"))
            config->setMTSPObjective((*generalSettings)["MTSP_OBJECTIVE"]->get<std::string>());

        if (generalSettings->contains("MTSP_SOLUTION_FILE"))
            config->setMTSPSolutionFile((*generalSettings)["MTSP_SOLUTION_FILE"]->get<std::string>());

        if (generalSettings->contains("VEHICLES"))
            config->setVehicles((*generalSettings)["VEHICLES"]->get<int>());

        if (generalSettings->contains("SPECIAL"))
            config->setSpecial((*generalSettings)["SPECIAL"]->get<bool>());
    }

    // --- Instance Settings ---
    if (lkhNode->contains("InstancesSettings")) {
        auto instancesSettings = (*lkhNode)["InstancesSettings"];

        for (const auto& instanceName : instancesSettings->keys()) {
            auto instanceJson = (*instancesSettings)[instanceName];

            auto instanceSetting = std::make_shared<LKH3InstanceSetting>();

            if (instanceJson->contains("ProblemFile"))
                instanceSetting->setProblemFile((*instanceJson)["ProblemFile"]->get<std::string>());

            if (instanceJson->contains("InitialTourFile"))
                instanceSetting->setInitialTourFile((*instanceJson)["InitialTourFile"]->get<std::string>());

            if (instanceJson->contains("InputTourFile"))
                instanceSetting->setInputTourFile((*instanceJson)["InputTourFile"]->get<std::string>());

            if (instanceJson->contains("MergeTourFile"))
                instanceSetting->setMergeTourFile((*instanceJson)["MergeTourFile"]->get<std::string>());
    
            if (instanceJson->contains("OutputTourFile"))
                instanceSetting->setOutputTourFile((*instanceJson)["OutputTourFile"]->get<std::string>());
    
            if (instanceJson->contains("TourFile"))
                instanceSetting->setOutputTourFile((*instanceJson)["TourFile"]->get<std::string>());
    

            config->addInstance(instanceName, instanceSetting);
        }
    }

    m_lkh3 = std::move(config);
}
