#include "repository/configuration2/config/concordeinstancesetting.h"


// Getters e setters

const std::string& ConcordeInstanceSetting::getProblemFile() const {
    return problem_file;
}
void ConcordeInstanceSetting::setProblemFile(const std::string& path) {
    problem_file = path;
}

const std::string& ConcordeInstanceSetting::getOutputTourFile() const {
    return output_file;
}
void ConcordeInstanceSetting::setOutputTourFile(const std::string& path) {
    output_file = path;
}

const std::optional<std::string>& ConcordeInstanceSetting::getInitialTourFile() const {
    return initial_tour_file;
}
void ConcordeInstanceSetting::setInitialTourFile(const std::optional<std::string>& file) {
    initial_tour_file = file;
}

const std::optional<std::string>& ConcordeInstanceSetting::getRestartFile() const {
    return restart_file;
}
void ConcordeInstanceSetting::setRestartFile(const std::optional<std::string>& file) {
    restart_file = file;
}

const std::optional<std::string>& ConcordeInstanceSetting::getEdgegenFile() const {
    return edgegen_file;
}
void ConcordeInstanceSetting::setEdgegenFile(const std::optional<std::string>& file) {
    edgegen_file = file;
}

const std::optional<std::string>& ConcordeInstanceSetting::getInitialEdgeFile() const {
    return initial_edge_file;
}
void ConcordeInstanceSetting::setInitialEdgeFile(const std::optional<std::string>& file) {
    initial_edge_file = file;
}

const std::optional<std::string>& ConcordeInstanceSetting::getFullEdgeFile() const {
    return full_edge_file;
}
void ConcordeInstanceSetting::setFullEdgeFile(const std::optional<std::string>& file) {
    full_edge_file = file;
}

const std::optional<std::string>& ConcordeInstanceSetting::getExtraCutFile() const {
    return extra_cut_file;
}
void ConcordeInstanceSetting::setExtraCutFile(const std::optional<std::string>& file) {
    extra_cut_file = file;
}

const std::optional<std::string>& ConcordeInstanceSetting::getCutpoolFile() const {
    return cutpool_file;
}
void ConcordeInstanceSetting::setCutpoolFile(const std::optional<std::string>& file) {
    cutpool_file = file;
}

const std::optional<std::string>& ConcordeInstanceSetting::getProblemName() const {
    return problem_name;
}
void ConcordeInstanceSetting::setProblemName(const std::optional<std::string>& name) {
    problem_name = name;
}
