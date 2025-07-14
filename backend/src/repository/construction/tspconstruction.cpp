#include "repository/construction/tspconstruction.h"

#include <fstream>
#include <filesystem>

const std::shared_ptr<TspConstruction>& TspConstruction::getInstance(){
    static std::shared_ptr<TspConstruction> mySelf(new TspConstruction());
    return mySelf;
}


void TspConstruction::construct(std::string path, const std::string& filename, const std::vector<std::vector<int>>& adjMatrix) const {
    namespace fs = std::filesystem;

    if (!fs::exists(path)) {
        fs::create_directories(path);
    }

    std::string fullPath = path + "/" + filename + ".tsp";
    std::ofstream file(fullPath);


    if (!file.is_open()) {
        throw std::runtime_error("Impossibile aprire il file: " + fullPath);
    }

    int n = adjMatrix.size();

    file << "NAME: " << filename << "\n";
    file << "TYPE: TSP\n";
    file << "COMMENT: Generated instance\n";
    file << "DIMENSION: " << n << "\n";
    file << "EDGE_WEIGHT_TYPE: EXPLICIT\n";
    file << "EDGE_WEIGHT_FORMAT: FULL_MATRIX\n";
    file << "EDGE_WEIGHT_SECTION\n";

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file << adjMatrix[i][j] << " ";
        }
        file << "\n";
    }

    file << "EOF\n";
    file.close();
    
}