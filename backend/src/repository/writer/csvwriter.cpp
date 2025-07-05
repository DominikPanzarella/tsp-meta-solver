#include "csvwriter.h"

#include <algorithm>
#include <cctype>    
#include <filesystem>
#include <fstream>
#include "service/algorithm/tspsolution.h"

bool CsvWriter::canHandle(const std::string& content) const {
    std::string lowered = content;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowered == "csv";
}

bool CsvWriter::writeFile(const std::shared_ptr<ISolutionCollector>& solutionCollector) const {
    namespace fs = std::filesystem;

    const auto& solutionsByAlgo = solutionCollector->getSolutions();

    for(const auto& [algoName, solutions] : solutionsByAlgo) {
        std::string filename = "results_"+algoName+".csv";
        std::ofstream out(filename);

        if(!out.is_open())
        {
            std::cerr << "Errore nell'apertura del file: " << filename << "\n";
            continue;
        }

        out << "Problem,Dimension,Cost,Time(us),TourLength,Ratio" << std::endl;       //the algo name is missing

        for (const auto& sol : solutions) {
            auto tspSol = std::dynamic_pointer_cast<TspSolution>(sol);
            if (!tspSol || !tspSol->getPath()) continue;

            out << tspSol->getProblem()->getName() << ",";
            out << tspSol->getProblem()->getDimension() << ",";
            out << tspSol->getPath()->getCost() << ",";
            out << tspSol->getExecutionTime() << ",";
            out << tspSol->getPath()->getDimension();
            out << "\n";
        }

        out.close();

    }

    return true;

}