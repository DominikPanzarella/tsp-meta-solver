#include "tspsolution.h"

TspSolution::TspSolution(std::shared_ptr<IPath> path) : m_path(std::move(path))
{
    //Empty body constructor
}

void TspSolution::setPath(std::shared_ptr<IPath> path){
    m_path = std::move(path);
}

const std::shared_ptr<IPath>& TspSolution::getPath() const {
    return m_path; 
}

double TspSolution::getCost() const{
    return m_path->getCost();
}

void TspSolution::setExecutionTime(int ms){
    m_executionTimeMs = ms;
}
    
int TspSolution::getExecutionTime() const {
    return m_executionTimeMs;
}