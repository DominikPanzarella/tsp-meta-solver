#include "repository/configuration2/config/concordegeneralsetting.h"

// Branching
std::optional<bool> ConcordeGeneralSetting::getBranching() const {
    return branching;
}
void ConcordeGeneralSetting::setBranching(std::optional<bool> value) {
    branching = value;
}

// DFS Branching
std::optional<bool> ConcordeGeneralSetting::getDFSBranching() const {
    return dfs_branching;
}
void ConcordeGeneralSetting::setDFSBranching(std::optional<bool> value) {
    dfs_branching = value;
}

// Boss Mode
std::optional<bool> ConcordeGeneralSetting::getBossMode() const {
    return boss_mode;
}
void ConcordeGeneralSetting::setBossMode(std::optional<bool> value) {
    boss_mode = value;
}

// Grunt Host
std::optional<std::string> ConcordeGeneralSetting::getGruntHost() const {
    return grunt_host;
}
void ConcordeGeneralSetting::setGruntHost(std::optional<std::string> host) {
    grunt_host = host;
}

// Max Chunk Size
std::optional<int> ConcordeGeneralSetting::getMaxChunkSize() const {
    return max_chunk_size;
}
void ConcordeGeneralSetting::setMaxChunkSize(std::optional<int> value) {
    max_chunk_size = value;
}

// Branch Attempts
std::optional<int> ConcordeGeneralSetting::getBranchAttempts() const {
    return branch_attempts;
}
void ConcordeGeneralSetting::setBranchAttempts(std::optional<int> value) {
    branch_attempts = value;
}

// Skip Cuts At Root
std::optional<bool> ConcordeGeneralSetting::getSkipCutsAtRoot() const {
    return skip_cuts_at_root;
}
void ConcordeGeneralSetting::setSkipCutsAtRoot(std::optional<bool> value) {
    skip_cuts_at_root = value;
}

// No Branch On Subtour
std::optional<bool> ConcordeGeneralSetting::getNoBranchOnSubtour() const {
    return no_branch_on_subtour;
}
void ConcordeGeneralSetting::setNoBranchOnSubtour(std::optional<bool> value) {
    no_branch_on_subtour = value;
}

// Only Blossom Polyhedron
std::optional<bool> ConcordeGeneralSetting::getOnlyBlossomPolyhedron() const {
    return only_blossom_polyhedron;
}
void ConcordeGeneralSetting::setOnlyBlossomPolyhedron(std::optional<bool> value) {
    only_blossom_polyhedron = value;
}

// Only Subtour Polyhedron
std::optional<bool> ConcordeGeneralSetting::getOnlySubtourPolyhedron() const {
    return only_subtour_polyhedron;
}
void ConcordeGeneralSetting::setOnlySubtourPolyhedron(std::optional<bool> value) {
    only_subtour_polyhedron = value;
}

// Multi Pass Cuts
std::optional<bool> ConcordeGeneralSetting::getMultiPassCuts() const {
    return multi_pass_cuts;
}
void ConcordeGeneralSetting::setMultiPassCuts(std::optional<bool> value) {
    multi_pass_cuts = value;
}

// Seed
std::optional<int> ConcordeGeneralSetting::getSeed() const {
    return seed;
}
void ConcordeGeneralSetting::setSeed(std::optional<int> value) {
    seed = value;
}

// Random Grid Size
std::optional<int> ConcordeGeneralSetting::getRandomGridSize() const {
    return random_grid_size;
}
void ConcordeGeneralSetting::setRandomGridSize(std::optional<int> value) {
    random_grid_size = value;
}

// Verbose
std::optional<bool> ConcordeGeneralSetting::getVerbose() const {
    return verbose;
}
void ConcordeGeneralSetting::setVerbose(std::optional<bool> value) {
    verbose = value;
}

// Fast Cuts Only
std::optional<bool> ConcordeGeneralSetting::getFastCutsOnly() const {
    return fast_cuts_only;
}
void ConcordeGeneralSetting::setFastCutsOnly(std::optional<bool> value) {
    fast_cuts_only = value;
}

// Write Min Reduced Cost Arcs
std::optional<int> ConcordeGeneralSetting::getWriteMinReducedCostArcs() const {
    return write_min_reduced_cost_arcs;
}
void ConcordeGeneralSetting::setWriteMinReducedCostArcs(std::optional<int> value) {
    write_min_reduced_cost_arcs = value;
}

// Distance Norm
std::optional<int> ConcordeGeneralSetting::getDistanceNorm() const {
    return distance_norm;
}
void ConcordeGeneralSetting::setDistanceNorm(std::optional<int> value) {
    distance_norm = value;
}

// Delete Temp Files
std::optional<bool> ConcordeGeneralSetting::getDeleteTempFiles() const {
    return delete_temp_files;
}
void ConcordeGeneralSetting::setDeleteTempFiles(std::optional<bool> value) {
    delete_temp_files = value;
}

// Save Tour As Edge File
std::optional<bool> ConcordeGeneralSetting::getSaveTourAsEdgeFile() const {
    return save_tour_as_edge_file;
}
void ConcordeGeneralSetting::setSaveTourAsEdgeFile(std::optional<bool> value) {
    save_tour_as_edge_file = value;
}
