#include "repository/configuration2/config/lkh3instancesetting.h"

LKH3InstanceSetting::LKH3InstanceSetting()
    : m_startingNode(0) {}

std::optional<std::string> LKH3InstanceSetting::getProblemFile() const {
    return problemFile;
}

void LKH3InstanceSetting::setProblemFile(const std::string& val) {
    problemFile = val;
}

std::optional<std::string> LKH3InstanceSetting::getInitialTourFile() const {
    return initialTourFile;
}

void LKH3InstanceSetting::setInitialTourFile(const std::string& val) {
    initialTourFile = val;
}

std::optional<std::string> LKH3InstanceSetting::getInputTourFile() const {
    return inputTourFile;
}

void LKH3InstanceSetting::setInputTourFile(const std::string& val) {
    inputTourFile = val;
}

std::optional<std::string> LKH3InstanceSetting::getMergeTourFile() const {
    return mergeTourFile;
}

void LKH3InstanceSetting::setMergeTourFile(const std::string& val) {
    mergeTourFile = val;
}

std::optional<std::string> LKH3InstanceSetting::getOutputTourFile() const {
    return outputTourFile;
}

void LKH3InstanceSetting::setOutputTourFile(const std::string& val) {
    outputTourFile = val;
}

std::optional<std::string> LKH3InstanceSetting::getTourFile() const {
    return tourFile;
}

void LKH3InstanceSetting::setTourFile(const std::string& val) {
    tourFile = val;
}
