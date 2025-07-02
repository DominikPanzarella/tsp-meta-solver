#include "service/algorithm/solutioncollector.h"


void SolutionCollector::addSolution(const std::string& algorithm, std::shared_ptr<ISolution> solution) {
    std::lock_guard lock(m_mutex);
    m_solutionsByAlgo[algorithm].push_back(std::move(solution));
}


const std::unordered_map<std::string, std::vector<std::shared_ptr<ISolution>>>& SolutionCollector::getSolutions() const {
    return m_solutionsByAlgo;
}

void SolutionCollector::reset(){
    std::lock_guard lock(m_mutex);
    m_solutionsByAlgo.clear();
}

int SolutionCollector::size() const {
    std::lock_guard lock(m_mutex);
    int total = 0;
    for (const auto& [_, vec] : m_solutionsByAlgo)
        total += vec.size();
    return total;
}