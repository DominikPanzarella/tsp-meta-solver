#pragma once

#include <iostream>
#include "repository/problem/iproblem.h"
#include "service/algorithm/isolution.h"
#include <unordered_map>
#include <sstream>
#include <fstream>

//Algorithm Interface
class IAlgorithm{
public:
    virtual std::shared_ptr<ISolution> execute(std::shared_ptr<IProblem> problem) = 0;

    virtual ~IAlgorithm() = default;

    virtual std::string name() const = 0;

    static std::unordered_map<std::string, int> loadOptima(const std::string& filePath){

        if(filePath.empty())        throw std::invalid_argument("filePath cannot be null");
    
        std::unordered_map<std::string, int> optima;
        std::ifstream file(filePath);
    
        if (!file.is_open()) {
            std::cerr << "[loadOptima] Error while opening the file: " << filePath << std::endl;
            return optima;
        }
    
        std::string line;
        bool firstLine = true;
        while(std::getline(file, line)){
    
            if (firstLine) { // salta intestazione
                firstLine = false;
                continue;
            }
    
            std::istringstream ss(line);
            std::string name;
            std::string costStr;
    
            if(!std::getline(ss, name, ','))        continue;;
            if(!std::getline(ss, costStr,',') )     continue;
    
            try{
                int cost = std::stoi(costStr);
                optima[name] = cost;
            }catch (const std::exception& e) {
                std::cerr << "[loadOptima] Errore nella conversione: " << e.what() << " per linea: " << line << std::endl;
            }
        }
    
        return optima;
    }

};