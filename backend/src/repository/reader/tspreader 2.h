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
#include "service/graph/node.h"

class TspReader : public Reader{
public:


    //template method
    virtual std::shared_ptr<IProblem> read(const std::string& file_path) override{
        std::ifstream file(file_path);
        if (!file.is_open()) {
            std::cerr << "[TspReader] Impossibile aprire il file: " << file_path << std::endl;
            return nullptr;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        std::istringstream input(content);

        if (canHandle(content)) {
            return readInternal(input);
        } else if (successor) {
            successor->read(file_path);
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



protected:

    virtual std::shared_ptr<IProblem> readInternal(std::istream& input) =0;


    std::shared_ptr<TspReader> successor;

    //std::shared_ptr<TspProblem> m_problem    
    std::istream* input = nullptr;

    // Fasi del Template Method (da override nelle subclassi)

    virtual bool canHandle(const std::string& content) const =0;

    virtual std::tuple<std::string, std::string, std::string, int,
    std::string, std::string, std::string, std::string, std::string, int>
        parseHeader(std::istream& input) = 0;

    virtual std::vector<Node> parseBody(std::istream& input, int dimension) =0;

    virtual std::shared_ptr<IGraph> buildGraph(const std::vector<Node>& nodes, int dimension) =0;

    virtual std::shared_ptr<IProblem> buildProblem(
        const std::string& name,
        const std::string& comment,
        const std::string& type,
        int dimension,
        const std::string& ew_type,
        const std::string& ew_format,
        const std::string& ed_format,
        const std::string& node_coord,
        const std::string& disp_type,
        int capacity,
        std::shared_ptr<IGraph> graph) =0;


    static inline std::string trim(const std::string& s) {
        auto start = s.find_first_not_of(" \t\r\n");
        auto end = s.find_last_not_of(" \t\r\n");
        return (start == std::string::npos || end == std::string::npos) ? "" : s.substr(start, end - start + 1);
    }
    
};