#pragma once

#include <nlohmann/json.hpp>

class JSONNodeImpl{
    public:
    
        explicit JSONNodeImpl(const nlohmann::json& json) : data(json) {}
        
        explicit JSONNodeImpl(nlohmann::json&& json) : data(std::move(json)) {}

        nlohmann::json data;
    
};
