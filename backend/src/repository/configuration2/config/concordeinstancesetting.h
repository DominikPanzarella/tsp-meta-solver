#pragma once

#include <string>
#include <optional>
#include "repository/configuration2/config/iinstancesetting.h"

class ConcordeInstanceSetting : public IInstanceSetting {
public:
    ConcordeInstanceSetting() =default;

    const std::string& getProblemFile() const;
    void setProblemFile(const std::string& path);

    const std::string& getOutputTourFile() const;
    void setOutputTourFile(const std::string& path);

    const std::optional<std::string>& getInitialTourFile() const;
    void setInitialTourFile(const std::optional<std::string>& file);

    const std::optional<std::string>& getRestartFile() const;
    void setRestartFile(const std::optional<std::string>& file);

    const std::optional<std::string>& getEdgegenFile() const;
    void setEdgegenFile(const std::optional<std::string>& file);

    const std::optional<std::string>& getInitialEdgeFile() const;
    void setInitialEdgeFile(const std::optional<std::string>& file);

    const std::optional<std::string>& getFullEdgeFile() const;
    void setFullEdgeFile(const std::optional<std::string>& file);

    const std::optional<std::string>& getExtraCutFile() const;
    void setExtraCutFile(const std::optional<std::string>& file);

    const std::optional<std::string>& getCutpoolFile() const;
    void setCutpoolFile(const std::optional<std::string>& file);

    const std::optional<std::string>& getProblemName() const;
    void setProblemName(const std::optional<std::string>& name);

private:

    std::string problem_file;
    std::string output_file;
    std::optional<std::string> initial_tour_file;
    std::optional<std::string> restart_file;
    std::optional<std::string> edgegen_file;
    std::optional<std::string> initial_edge_file;
    std::optional<std::string> full_edge_file;
    std::optional<std::string> extra_cut_file;
    std::optional<std::string> cutpool_file;
    std::optional<std::string> problem_name;
};
