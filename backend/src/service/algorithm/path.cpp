#include "path.h"

Path::Path(const std::vector<int>& nodes, double cost) : m_nodes(nodes), m_cost(cost)
{
    // Empty body
}

void Path::reset(){
    m_cost = 0.0;
    m_nodes.clear();
}

void Path::setNodes(const std::vector<int>& tour){
    m_nodes = tour;
}

const std::vector<int>& Path::nodes() const{
    return m_nodes;
}

void Path::setCost(double c){
    m_cost = c;
}

double Path::getCost() const{
    return m_cost;
}

int Path::getDimension() const {
    return m_nodes.size();
}
