#pragma once

#include "repository/configuration2/config/igeneralsetting.h"
#include <optional>
#include <string>
#include <vector>
#include <tuple>

class LKH3GeneralSetting : public IGeneralSetting {
public:
    LKH3GeneralSetting() = default;

    // Getter & Setter
    std::optional<int> getAscentCandidates() const;
    void setAscentCandidates(int val);

    std::optional<int> getBackboneTrials() const;
    void setBackboneTrials(int val);

    std::optional<bool> getBacktracking() const;
    void setBacktracking(bool val);

    const std::vector<std::string>& getCandidateFiles() const;
    void addCandidateFile(const std::string& file);

    std::optional<std::tuple<int,int,std::optional<int>>> getBWTSP() const;
    void setBWTSP(const std::tuple<int,int,std::optional<int>>& val);

    std::optional<std::string> getCandidateSetType() const;
    void setCandidateSetType(const std::string& val);

    std::optional<int> getExcess() const;
    void setExcess(int val);

    std::optional<int> getExtraCandidates() const;
    void setExtraCandidates(int val);

    std::optional<std::string> getExtraCandidateSetType() const;
    void setExtraCandidateSetType(const std::string& val);

    std::optional<bool> getGain23() const;
    void setGain23(bool val);

    std::optional<bool> getGainCriterion() const;
    void setGainCriterion(bool val);

    std::optional<bool> getSubgradient() const;
    void setSubgradient(bool val);

    std::optional<int> getInitialPeriod() const;
    void setInitialPeriod(int val);

    std::optional<int> getInitialStepSize() const;
    void setInitialStepSize(int val);

    std::optional<std::string> getInitialTourAlgorithm() const;
    void setInitialTourAlgorithm(const std::string& val);


    std::optional<double> getInitialTourFraction() const;
    void setInitialTourFraction(double val);

    std::optional<int> getKicks() const;
    void setKicks(int val);

    std::optional<int> getKickType() const;
    void setKickType(int val);

    std::optional<bool> getMakespan() const;
    void setMakespan(bool val);

    std::optional<int> getMaxBreadth() const;
    void setMaxBreadth(int val);

    std::optional<int> getMaxCandidates() const;
    void setMaxCandidates(int val);

    std::optional<int> getMaxSwaps() const;
    void setMaxSwaps(int val);

    std::optional<int> getMaxTrials() const;
    void setMaxTrials(int val);

    std::optional<int> getMoveType() const;
    void setMoveType(int val);

    std::optional<int> getNonSequentialMoveType() const;
    void setNonSequentialMoveType(int val);

    std::optional<int> getPatchingA() const;
    void setPatchingA(int val);

    std::optional<int> getPatchingC() const;
    void setPatchingC(int val);

    std::optional<int> getSubsequentMoveType() const;
    void setSubsequentMoveType(int val);

    std::optional<bool> getSubsequentPatching() const;
    void setSubsequentPatching(bool val);

    std::optional<int> getOptimum() const;
    void setOptimum(int val);

    std::optional<bool> getStopAtOptimum() const;
    void setStopAtOptimum(bool val);

    std::optional<double> getTimeLimit() const;
    void setTimeLimit(double val);

    std::optional<int> getDepot() const;
    void setDepot(int val);

    std::optional<std::string> getComment() const;
    void setComment(const std::string& val);

    std::optional<int> getTraceLevel() const;
    void setTraceLevel(int val);

    std::optional<int> getPopulationSize() const;
    void setPopulationSize(int val);

    std::optional<int> getPrecision() const;
    void setPrecision(int val);

    std::optional<bool> getRestrictedSearch() const;
    void setRestrictedSearch(bool val);

    std::optional<int> getRuns() const;
    void setRuns(int val);

    std::optional<int> getSeed() const;
    void setSeed(int val);

    std::optional<int> getSalesmen() const;
    void setSalesmen(int val);

    std::optional<int> getScale() const;
    void setScale(int val);

    std::optional<std::string> getSintefSolutionFile() const;
    void setSintefSolutionFile(const std::string& val);

    std::optional<std::string> getPiFile() const;
    void setPiFile(const std::string& val);

    std::optional<int> getSubproblemSize() const;
    void setSubproblemSize(int val);

    std::optional<std::string> getSubproblemTourFile() const;
    void setSubproblemTourFile(const std::string& val);

    std::optional<int> getMTSPMinSize() const;
    void setMTSPMinSize(int val);

    std::optional<int> getMTSPMaxSize() const;
    void setMTSPMaxSize(int val);

    std::optional<std::string> getMTSPObjective() const;
    void setMTSPObjective(const std::string& val);

    std::optional<std::string> getMTSPSolutionFile() const;
    void setMTSPSolutionFile(const std::string& val);

    std::optional<int> getVehicles() const;
    void setVehicles(int val);

    std::optional<bool> getSpecial() const;
    void setSpecial(bool val);

private:
    std::optional<int> ascentCandidates;
    std::optional<int> backboneTrials;
    std::optional<bool> backtracking;
    std::vector<std::string> candidateFiles;
    std::optional<std::tuple<int,int,std::optional<int>>> bwtsp;
    std::optional<std::string> candidateSetType;
    std::optional<int> excess;
    std::optional<int> extraCandidates;
    std::optional<std::string> extraCandidateSetType;
    std::optional<bool> gain23;
    std::optional<bool> gainCriterion;
    std::optional<bool> subgradient;
    std::optional<int> initialPeriod;
    std::optional<int> initialStepSize;
    std::optional<std::string> initialTourAlgorithm;

    std::optional<double> initialTourFraction;


    std::optional<int> kicks;
    std::optional<int> kickType;
    std::optional<bool> makespan;
    std::optional<int> maxBreadth;
    std::optional<int> maxCandidates;
    std::optional<int> maxSwaps;
    std::optional<int> maxTrials;
    std::optional<int> moveType;
    std::optional<int> nonSequentialMoveType;
    std::optional<int> patchingA;
    std::optional<int> patchingC;
    std::optional<int> subsequentMoveType;
    std::optional<bool> subsequentPatching;

    std::optional<int> optimum;
    std::optional<bool> stopAtOptimum;
    std::optional<double> timeLimit;

    std::optional<int> depot;
    std::optional<std::string> comment;


    
    std::optional<int> traceLevel;
    std::optional<int> populationSize;
    std::optional<int> precision;
    std::optional<bool> restrictedSearch;
    std::optional<int> runs;
    std::optional<int> seed;
    std::optional<int> salesmen;
    std::optional<int> scale;
    std::optional<std::string> sintefSolutionFile;
    std::optional<std::string> piFile;
    std::optional<int> subproblemSize;

    std::optional<std::string> subproblemTourFile;
    std::optional<int> mtspMinSize;
    std::optional<int> mtspMaxSize;
    std::optional<std::string> mtspObjective;
    std::optional<std::string> mtspSolutionFile;
    std::optional<int> vehicles;
    std::optional<bool> special;
};
