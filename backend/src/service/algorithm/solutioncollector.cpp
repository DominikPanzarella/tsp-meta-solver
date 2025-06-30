#include "service/algorithm/solutioncollector.h"


void SolutionCollector::addSolution(std::shared_ptr<ISolution> solution){
    m_solutions.push_back(std::move(solution));
}

const std::vector<std::shared_ptr<ISolution>>& SolutionCollector::getSolutions() const {
    return m_solutions;
}

void SolutionCollector::reset(){
    m_solutions.clear();
}

int SolutionCollector::size() const {
    return static_cast<int>(m_solutions.size());
}