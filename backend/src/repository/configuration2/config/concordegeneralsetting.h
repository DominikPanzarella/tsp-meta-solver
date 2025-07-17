#pragma once

#include <optional>
#include <vector>
#include "repository/configuration2/config/igeneralsetting.h"

class ConcordeGeneralSetting : public IGeneralSetting {
public:
    ConcordeGeneralSetting() = default;

    std::optional<bool> getBranching() const;
    void setBranching(std::optional<bool> value);

    std::optional<bool> getDFSBranching() const;
    void setDFSBranching(std::optional<bool> value);

    std::optional<bool> getBossMode() const;
    void setBossMode(std::optional<bool> value);

    std::optional<std::string> getGruntHost() const;
    void setGruntHost(std::optional<std::string> host);

    std::optional<int> getMaxChunkSize() const;
    void setMaxChunkSize(std::optional<int> value);

    std::optional<int> getBranchAttempts() const;
    void setBranchAttempts(std::optional<int> value);

    std::optional<bool> getSkipCutsAtRoot() const;
    void setSkipCutsAtRoot(std::optional<bool> value);

    std::optional<bool> getNoBranchOnSubtour() const;
    void setNoBranchOnSubtour(std::optional<bool> value);

    std::optional<bool> getOnlyBlossomPolyhedron() const;
    void setOnlyBlossomPolyhedron(std::optional<bool> value);

    std::optional<bool> getOnlySubtourPolyhedron() const;
    void setOnlySubtourPolyhedron(std::optional<bool> value);

    std::optional<bool> getMultiPassCuts() const;
    void setMultiPassCuts(std::optional<bool> value);

    std::optional<int> getSeed() const;
    void setSeed(std::optional<int> value);

    std::optional<int> getRandomGridSize() const;
    void setRandomGridSize(std::optional<int> value);

    std::optional<bool> getVerbose() const;
    void setVerbose(std::optional<bool> value);

    std::optional<bool> getFastCutsOnly() const;
    void setFastCutsOnly(std::optional<bool> value);

    std::optional<int> getWriteMinReducedCostArcs() const;
    void setWriteMinReducedCostArcs(std::optional<int> value);

    std::optional<int> getDistanceNorm() const;
    void setDistanceNorm(std::optional<int> value);

    std::optional<bool> getDeleteTempFiles() const;
    void setDeleteTempFiles(std::optional<bool> value);

    std::optional<bool> getSaveTourAsEdgeFile() const;
    void setSaveTourAsEdgeFile(std::optional<bool> value);

    std::vector<std::vector<int>> getIntegralityGap() const;
    void setIntegralityGap(std::vector<std::vector<int>> iG);

private:
    std::optional<bool> branching;
    std::optional<bool> dfs_branching;
    std::optional<bool> boss_mode;
    std::optional<std::string> grunt_host;

    std::optional<int> max_chunk_size;
    std::optional<int> branch_attempts;
    std::optional<bool> skip_cuts_at_root;
    std::optional<bool> no_branch_on_subtour;
    std::optional<bool> only_blossom_polyhedron;
    std::optional<bool> only_subtour_polyhedron;
    std::optional<bool> multi_pass_cuts;

    std::optional<int> seed;
    std::optional<int> random_grid_size;

    std::optional<bool> verbose;
    std::optional<bool> fast_cuts_only;
    std::optional<int> write_min_reduced_cost_arcs;

    std::optional<int> distance_norm;
    std::optional<bool> delete_temp_files;
    std::optional<bool> save_tour_as_edge_file;

    std::vector<std::vector<int>> integralityGaps;
};
