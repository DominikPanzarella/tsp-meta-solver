#include "csvwriter.h"

#include <algorithm>
#include <cctype>    
#include <filesystem>
#include <fstream>
#include "service/algorithm/tspsolution.h"
#include "repository/configuration2/config/nearestinsertiongeneralsetting.h"
#include "repository/configuration2/config/nearestinsertioninstancesetting.h"
#include "repository/configuration2/config/nearestneighbourgeneralsetting.h"
#include "repository/configuration2/config/nearestneighbourinstancesetting.h"
#include "repository/configuration2/config/farthestinsertiongeneralsetting.h"
#include "repository/configuration2/config/farthestinsertioninstancesetting.h"


CsvWriter::CsvWriter(){
    registerWriteFuncs();
}

void CsvWriter::registerWriteFuncs(){

    algoWriters["NearestInsertion"] = [this](const std::string& filename, const auto& sols, const auto& configProvider){
        std::ofstream out(filename);

        out << "Problem,Dimension,Algorithm,Cost,Time(us),StartingNode\n";
        for(const auto& sol : sols){
            auto tspSol = std::dynamic_pointer_cast<TspSolution>(sol);
            auto ni_setting = std::dynamic_pointer_cast<NearestInsertionGeneralSetting>(configProvider->getNearestInsertionSettings());
            if (!tspSol || !tspSol->getPath()) continue;
            out << tspSol->getProblem()->getName() << ",";
            out << tspSol->getProblem()->getDimension() << ",";
            out << "NearestInsertion" << ",";
            out << tspSol->getPath()->getCost() << ",";
            out << tspSol->getExecutionTime() << ",";

            auto problem_setting = std::dynamic_pointer_cast<NearestInsertionInstanceSetting>(configProvider->getNearestInsertionSettings()->getInstance(tspSol->getProblem()->getName()));
            out << problem_setting->getStartingNode();
            out << "\n";
        }

    };

    algoWriters["NearestNeighbour"] = [this](const std::string& filename, const auto& sols, const auto& configProvider){
        std::ofstream out(filename);

        out << "Problem,Dimension,Algorithm,Cost,Time(us),StartingNode\n";
        for(const auto& sol : sols){
            auto tspSol = std::dynamic_pointer_cast<TspSolution>(sol);
            if (!tspSol || !tspSol->getPath()) continue;
    
            auto nn_setting = std::dynamic_pointer_cast<NearestNeighbourGeneralSetting>(configProvider->getNearestNeighbourSettings());

            out << tspSol->getProblem()->getName() << ",";
            out << tspSol->getProblem()->getDimension() << ",";
            out << "NearestNeighbour" << ",";
            out << tspSol->getPath()->getCost() << ",";
            out << tspSol->getExecutionTime() << ",";

            auto problem_setting = std::dynamic_pointer_cast<NearestNeighbourInstanceSetting>(configProvider->getNearestNeighbourSettings()->getInstance(tspSol->getProblem()->getName()));
            out << problem_setting->getStartingNode();
            out << "\n";
        }

    };

    algoWriters["FarthestInsertion"] = [this](const std::string& filename, const auto& sols, const auto& configProvider){
        std::ofstream out(filename);

        out << "Problem,Dimension,Algorithm,Cost,Time(us),StartingNode\n";
        for(const auto& sol : sols){
            auto tspSol = std::dynamic_pointer_cast<TspSolution>(sol);

            auto nn_setting = std::dynamic_pointer_cast<FarthestInsertionGeneralSetting>(configProvider->getFarthestInsertionSettings());


            if (!tspSol || !tspSol->getPath()) continue;
    
            out << tspSol->getProblem()->getName() << ",";
            out << tspSol->getProblem()->getDimension() << ",";
            out << "FarthestInsertion" << ",";
            out << tspSol->getPath()->getCost() << ",";
            out << tspSol->getExecutionTime() << ",";

            auto problem_setting = std::dynamic_pointer_cast<FarthestInsertionInstanceSetting>(configProvider->getFarthestInsertionSettings()->getInstance(tspSol->getProblem()->getName()));
            out << problem_setting->getStartingNode();

            out << "\n";
        }

    };

    algoWriters["Concorde"] = [this](const std::string& filename, const auto& sols, const auto& configProvider){
        std::ofstream out(filename);

        out << "Problem,Dimension,Algorithm,Cost,Time(us)\n";
        for(const auto& sol : sols){
            auto tspSol = std::dynamic_pointer_cast<TspSolution>(sol);
            if (!tspSol || !tspSol->getPath()) continue;
    
            out << tspSol->getProblem()->getName() << ",";
            out << tspSol->getProblem()->getDimension() << ",";
            out << "Concorde" << ",";
            out << tspSol->getPath()->getCost() << ",";
            out << tspSol->getExecutionTime() << ",";
            out << "\n";
        }

    };

    algoWriters["LKH3"] = [this](const std::string& filename, const auto& sols, const auto& configProvider){
        std::ofstream out(filename);

        out << "Problem,Dimension,Algorithm,Cost,Time(us)\n";
        for(const auto& sol : sols){
            auto tspSol = std::dynamic_pointer_cast<TspSolution>(sol);
            if (!tspSol || !tspSol->getPath()) continue;
    
            out << tspSol->getProblem()->getName() << ",";
            out << tspSol->getProblem()->getDimension() << ",";
            out << "LKH3" << ",";
            out << tspSol->getPath()->getCost() << ",";
            out << tspSol->getExecutionTime() << ",";
            out << "\n";
        }

    };

}

bool CsvWriter::canHandle(const std::string& content) const {
    std::string lowered = content;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowered == "csv";
}

bool CsvWriter::writeFile(std::string file_path, const std::shared_ptr<ISolutionCollector>& solutionCollector,const std::shared_ptr<IConfigProvider>& configProvider) const {
    namespace fs = std::filesystem;

    const auto& solutionsByAlgo = solutionCollector->getSolutions();

    fs::path output_dir = file_path;

    if(fs::exists(output_dir)){
        std::error_code ec;
        fs::remove_all(output_dir, ec);
        if(ec){
            std::cerr << "Errore durante la cancellazione della cartella: " << ec.message() << "\n";
            return false;
        }
    }
    std::error_code ec;
    fs::create_directories(output_dir, ec);
    if(ec){
        std::cerr << "Errore durante la cancellazione della cartella: " << ec.message() << "\n";
        return false;
    }

    for(const auto& [algoName, solutions] : solutionsByAlgo) {
        std::string filename = file_path + "/" + "results_" + algoName + ".csv";
        
        if (algoWriters.contains(algoName)) {
            algoWriters.at(algoName)(filename, solutions, configProvider);
        } else {
            std::cerr << "No CSV writer for algorithm: " << algoName << "\n";
        }
    }

    return true;

}