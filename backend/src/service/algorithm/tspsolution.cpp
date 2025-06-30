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
