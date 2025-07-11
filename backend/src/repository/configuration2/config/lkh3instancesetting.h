#pragma once

#include "repository/configuration2/config/iinstancesetting.h"
#include <optional>
#include <string>

class LKH3InstanceSetting : public IInstanceSetting {
public:
    LKH3InstanceSetting();

    std::optional<std::string> getProblemFile() const;
    void setProblemFile(const std::string& val);

    std::optional<std::string> getInitialTourFile() const;
    void setInitialTourFile(const std::string& val);

    std::optional<std::string> getInputTourFile() const;
    void setInputTourFile(const std::string& val);

    std::optional<std::string> getMergeTourFile() const;
    void setMergeTourFile(const std::string& val);

    std::optional<std::string> getOutputTourFile() const;
    void setOutputTourFile(const std::string& val);

    std::optional<std::string> getTourFile() const;
    void setTourFile(const std::string& val);

private:
    int m_startingNode;

    std::optional<std::string> problemFile;
    std::optional<std::string> initialTourFile;
    std::optional<std::string> inputTourFile;
    std::optional<std::string> mergeTourFile;
    std::optional<std::string> outputTourFile;
    std::optional<std::string> tourFile;
};
