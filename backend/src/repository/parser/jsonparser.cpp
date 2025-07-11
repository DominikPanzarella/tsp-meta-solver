#include "jsonparser.h"

#include <fstream>
#include <sstream>

#include <nlohmann/json.hpp>


JSON JsonParser::read(const std::string& file_path){
    std::ifstream inFile(file_path);

    if(!inFile){
        throw std::runtime_error("Error in opening JSON file");
    }

    nlohmann::json parsed;

    inFile >> parsed;

    m_json = JSON(std::make_shared<JSONNodeImpl>(parsed));

    return m_json;
}

JSON JsonParser::getJson(){
    return m_json;
}
