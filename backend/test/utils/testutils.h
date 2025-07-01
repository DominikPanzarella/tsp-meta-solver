#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>
#include <unordered_set>


inline std::vector<std::string> collectTspInstances(const std::string& dir) {
    std::vector<std::string> paths;
    static const std::unordered_set<std::string> exclude = {
        "brd14051.tsp",
        "d15112.tsp",
        "d18512.tsp",
        "pla33810.tsp",
        "pla85900.tsp",
        "rl11849.tsp",
        "usa13509.tsp"
    };
    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.path().extension() == ".tsp") {
            const std::string filename = entry.path().filename().string();
            if(exclude.find(filename) == exclude.end())
                paths.push_back(entry.path().string());
        }
    }
    std::sort(paths.begin(), paths.end());
    return paths;
}

/*

Da escludere:
 - brd14051.tsp
 - d15112.tsp
 - d18512.tsp
 - pla33810.tsp
 - pla85900.tsp
 - rl11849.tsp
 - usa13509.tsp

*/