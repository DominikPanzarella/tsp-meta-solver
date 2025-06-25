#pragma once

//////////////
// #INCLUDE //
//////////////

#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "reader.h"
#include "../problem/tspproblem.h"

class TspReader : public Reader{
public:


    //template method
    virtual void read(const std::string& file_path) override{
        std::ifstream file(file_path);
        if (!file.is_open()) {
            std::cerr << "[TspReader] Impossibile aprire il file: " << file_path << std::endl;
            return;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        std::istringstream input(content);

        if (canHandle(content)) {
            this->input = &input; // memorizziamo temporaneamente lo stream
            parseHeader();
            parseBody();
            buildGraph();
            buildProblem();
        } else if (successor) {
            successor->read(file_path);
            m_problem = successor->getProblem();
        } else {
            std::cerr << "[TspReader] Nessun reader compatibile trovato per: " << file_path << std::endl;
        }

    }

    void set_successor(std::shared_ptr<TspReader> next){
        successor = std::move(next);
    }

    std::shared_ptr<TspReader> getSuccessors() {
        return successor;
    }

    std::shared_ptr<TspProblem> getProblem() {
        return m_problem;
    }


protected:
    std::shared_ptr<TspReader> successor;

    std::shared_ptr<TspProblem> m_problem;
    
    std::istream* input = nullptr;

    // Fasi del Template Method (da override nelle subclassi)
    virtual bool canHandle(const std::string& content) const = 0;

    virtual void parseHeader() = 0;

    virtual void parseBody() = 0;

    virtual void buildGraph() = 0;

    virtual void buildProblem() = 0;

    static inline std::string trim(const std::string& s) {
        auto start = s.find_first_not_of(" \t\r\n");
        auto end = s.find_last_not_of(" \t\r\n");
        return (start == std::string::npos || end == std::string::npos) ? "" : s.substr(start, end - start + 1);
    }
    
};