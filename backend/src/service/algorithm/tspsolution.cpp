#include "tspsolution.h"

TspSolution::TspSolution(std::shared_ptr<IPath> path,std::shared_ptr<IProblem> problem) : m_path(std::move(path)), m_problem(std::move(problem))
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

int TspSolution::getDimension() const{
    return m_path->getDimension();
}

const std::shared_ptr<IProblem> TspSolution::getProblem() const{
    return m_problem;
}

void TspSolution::reset(){
    m_path->reset();
    m_executionTimeMs = 0;
}
