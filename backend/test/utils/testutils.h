#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>

inline std::vector<std::string> collectTspInstances(const std::string& dir) {
    std::vector<std::string> paths;
    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.path().extension() == ".tsp") {
            paths.push_back(entry.path().string());
        }
    }
    std::sort(paths.begin(), paths.end());
    return paths;
}
