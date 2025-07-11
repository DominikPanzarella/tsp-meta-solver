#include "repository/configuration2/config/lkh3generalsetting.h"

// ascentCandidates
std::optional<int> LKH3GeneralSetting::getAscentCandidates() const { return ascentCandidates; }
void LKH3GeneralSetting::setAscentCandidates(int val) { ascentCandidates = val; }

// backboneTrials
std::optional<int> LKH3GeneralSetting::getBackboneTrials() const { return backboneTrials; }
void LKH3GeneralSetting::setBackboneTrials(int val) { backboneTrials = val; }

// backtracking
std::optional<bool> LKH3GeneralSetting::getBacktracking() const { return backtracking; }
void LKH3GeneralSetting::setBacktracking(bool val) { backtracking = val; }

// candidateFiles
const std::vector<std::string>& LKH3GeneralSetting::getCandidateFiles() const { return candidateFiles; }
void LKH3GeneralSetting::addCandidateFile(const std::string& file) { candidateFiles.push_back(file); }

// bwtsp
std::optional<std::tuple<int,int,std::optional<int>>> LKH3GeneralSetting::getBWTSP() const { return bwtsp; }
void LKH3GeneralSetting::setBWTSP(const std::tuple<int,int,std::optional<int>>& val) { bwtsp = val; }

// candidateSetType
std::optional<std::string> LKH3GeneralSetting::getCandidateSetType() const { return candidateSetType; }
void LKH3GeneralSetting::setCandidateSetType(const std::string& val) { candidateSetType = val; }

// excess
std::optional<int> LKH3GeneralSetting::getExcess() const { return excess; }
void LKH3GeneralSetting::setExcess(int val) { excess = val; }

// extraCandidates
std::optional<int> LKH3GeneralSetting::getExtraCandidates() const { return extraCandidates; }
void LKH3GeneralSetting::setExtraCandidates(int val) { extraCandidates = val; }

// extraCandidateSetType
std::optional<std::string> LKH3GeneralSetting::getExtraCandidateSetType() const { return extraCandidateSetType; }
void LKH3GeneralSetting::setExtraCandidateSetType(const std::string& val) { extraCandidateSetType = val; }

// gain23
std::optional<bool> LKH3GeneralSetting::getGain23() const { return gain23; }
void LKH3GeneralSetting::setGain23(bool val) { gain23 = val; }

// gainCriterion
std::optional<bool> LKH3GeneralSetting::getGainCriterion() const { return gainCriterion; }
void LKH3GeneralSetting::setGainCriterion(bool val) { gainCriterion = val; }

// subgradient
std::optional<bool> LKH3GeneralSetting::getSubgradient() const { return subgradient; }
void LKH3GeneralSetting::setSubgradient(bool val) { subgradient = val; }

// initialPeriod
std::optional<int> LKH3GeneralSetting::getInitialPeriod() const { return initialPeriod; }
void LKH3GeneralSetting::setInitialPeriod(int val) { initialPeriod = val; }

// initialStepSize
std::optional<int> LKH3GeneralSetting::getInitialStepSize() const { return initialStepSize; }
void LKH3GeneralSetting::setInitialStepSize(int val) { initialStepSize = val; }

// initialTourAlgorithm
std::optional<std::string> LKH3GeneralSetting::getInitialTourAlgorithm() const { return initialTourAlgorithm; }
void LKH3GeneralSetting::setInitialTourAlgorithm(const std::string& val) { initialTourAlgorithm = val; }

// initialTourFraction
std::optional<double> LKH3GeneralSetting::getInitialTourFraction() const { return initialTourFraction; }
void LKH3GeneralSetting::setInitialTourFraction(double val) { initialTourFraction = val; }

// kicks
std::optional<int> LKH3GeneralSetting::getKicks() const { return kicks; }
void LKH3GeneralSetting::setKicks(int val) { kicks = val; }

// kickType
std::optional<int> LKH3GeneralSetting::getKickType() const { return kickType; }
void LKH3GeneralSetting::setKickType(int val) { kickType = val; }

// makespan
std::optional<bool> LKH3GeneralSetting::getMakespan() const { return makespan; }
void LKH3GeneralSetting::setMakespan(bool val) { makespan = val; }

// maxBreadth
std::optional<int> LKH3GeneralSetting::getMaxBreadth() const { return maxBreadth; }
void LKH3GeneralSetting::setMaxBreadth(int val) { maxBreadth = val; }

// maxCandidates
std::optional<int> LKH3GeneralSetting::getMaxCandidates() const { return maxCandidates; }
void LKH3GeneralSetting::setMaxCandidates(int val) { maxCandidates = val; }

// maxSwaps
std::optional<int> LKH3GeneralSetting::getMaxSwaps() const { return maxSwaps; }
void LKH3GeneralSetting::setMaxSwaps(int val) { maxSwaps = val; }

// maxTrials
std::optional<int> LKH3GeneralSetting::getMaxTrials() const { return maxTrials; }
void LKH3GeneralSetting::setMaxTrials(int val) { maxTrials = val; }

// moveType
std::optional<int> LKH3GeneralSetting::getMoveType() const { return moveType; }
void LKH3GeneralSetting::setMoveType(int val) { moveType = val; }

// nonSequentialMoveType
std::optional<int> LKH3GeneralSetting::getNonSequentialMoveType() const { return nonSequentialMoveType; }
void LKH3GeneralSetting::setNonSequentialMoveType(int val) { nonSequentialMoveType = val; }

// patchingA
std::optional<int> LKH3GeneralSetting::getPatchingA() const { return patchingA; }
void LKH3GeneralSetting::setPatchingA(int val) { patchingA = val; }

// patchingC
std::optional<int> LKH3GeneralSetting::getPatchingC() const { return patchingC; }
void LKH3GeneralSetting::setPatchingC(int val) { patchingC = val; }

// subsequentMoveType
std::optional<int> LKH3GeneralSetting::getSubsequentMoveType() const { return subsequentMoveType; }
void LKH3GeneralSetting::setSubsequentMoveType(int val) { subsequentMoveType = val; }

// subsequentPatching
std::optional<bool> LKH3GeneralSetting::getSubsequentPatching() const { return subsequentPatching; }
void LKH3GeneralSetting::setSubsequentPatching(bool val) { subsequentPatching = val; }

// optimum
std::optional<int> LKH3GeneralSetting::getOptimum() const { return optimum; }
void LKH3GeneralSetting::setOptimum(int val) { optimum = val; }

// stopAtOptimum
std::optional<bool> LKH3GeneralSetting::getStopAtOptimum() const { return stopAtOptimum; }
void LKH3GeneralSetting::setStopAtOptimum(bool val) { stopAtOptimum = val; }

// timeLimit
std::optional<double> LKH3GeneralSetting::getTimeLimit() const { return timeLimit; }
void LKH3GeneralSetting::setTimeLimit(double val) { timeLimit = val; }

// depot
std::optional<int> LKH3GeneralSetting::getDepot() const { return depot; }
void LKH3GeneralSetting::setDepot(int val) { depot = val; }

// comment
std::optional<std::string> LKH3GeneralSetting::getComment() const { return comment; }
void LKH3GeneralSetting::setComment(const std::string& val) { comment = val; }

// traceLevel
std::optional<int> LKH3GeneralSetting::getTraceLevel() const { return traceLevel; }
void LKH3GeneralSetting::setTraceLevel(int val) { traceLevel = val; }

// populationSize
std::optional<int> LKH3GeneralSetting::getPopulationSize() const { return populationSize; }
void LKH3GeneralSetting::setPopulationSize(int val) { populationSize = val; }

// precision
std::optional<int> LKH3GeneralSetting::getPrecision() const { return precision; }
void LKH3GeneralSetting::setPrecision(int val) { precision = val; }

// restrictedSearch
std::optional<bool> LKH3GeneralSetting::getRestrictedSearch() const { return restrictedSearch; }
void LKH3GeneralSetting::setRestrictedSearch(bool val) { restrictedSearch = val; }

// runs
std::optional<int> LKH3GeneralSetting::getRuns() const { return runs; }
void LKH3GeneralSetting::setRuns(int val) { runs = val; }

// seed
std::optional<int> LKH3GeneralSetting::getSeed() const { return seed; }
void LKH3GeneralSetting::setSeed(int val) { seed = val; }

// salesmen
std::optional<int> LKH3GeneralSetting::getSalesmen() const { return salesmen; }
void LKH3GeneralSetting::setSalesmen(int val) { salesmen = val; }

// scale
std::optional<int> LKH3GeneralSetting::getScale() const { return scale; }
void LKH3GeneralSetting::setScale(int val) { scale = val; }

// sintefSolutionFile
std::optional<std::string> LKH3GeneralSetting::getSintefSolutionFile() const { return sintefSolutionFile; }
void LKH3GeneralSetting::setSintefSolutionFile(const std::string& val) { sintefSolutionFile = val; }

// piFile
std::optional<std::string> LKH3GeneralSetting::getPiFile() const { return piFile; }
void LKH3GeneralSetting::setPiFile(const std::string& val) { piFile = val; }

// subproblemSize
std::optional<int> LKH3GeneralSetting::getSubproblemSize() const { return subproblemSize; }
void LKH3GeneralSetting::setSubproblemSize(int val) { subproblemSize = val; }

// subproblemTourFile
std::optional<std::string> LKH3GeneralSetting::getSubproblemTourFile() const { return subproblemTourFile; }
void LKH3GeneralSetting::setSubproblemTourFile(const std::string& val) { subproblemTourFile = val; }

// mtspMinSize
std::optional<int> LKH3GeneralSetting::getMTSPMinSize() const { return mtspMinSize; }
void LKH3GeneralSetting::setMTSPMinSize(int val) { mtspMinSize = val; }

// mtspMaxSize
std::optional<int> LKH3GeneralSetting::getMTSPMaxSize() const { return mtspMaxSize; }
void LKH3GeneralSetting::setMTSPMaxSize(int val) { mtspMaxSize = val; }

// mtspObjective
std::optional<std::string> LKH3GeneralSetting::getMTSPObjective() const { return mtspObjective; }
void LKH3GeneralSetting::setMTSPObjective(const std::string& val) { mtspObjective = val; }

// mtspSolutionFile
std::optional<std::string> LKH3GeneralSetting::getMTSPSolutionFile() const { return mtspSolutionFile; }
void LKH3GeneralSetting::setMTSPSolutionFile(const std::string& val) { mtspSolutionFile = val; }

// vehicles
std::optional<int> LKH3GeneralSetting::getVehicles() const { return vehicles; }
void LKH3GeneralSetting::setVehicles(int val) { vehicles = val; }

// special
std::optional<bool> LKH3GeneralSetting::getSpecial() const { return special; }
void LKH3GeneralSetting::setSpecial(bool val) { special = val; }
