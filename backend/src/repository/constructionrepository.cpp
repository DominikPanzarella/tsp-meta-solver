#include "repository/construction/tspconstruction.h"
#include "repository/constructionrepository.h"


ConstructionRepository::ConstructionRepository(){
    m_ic = TspConstruction::getInstance();
}

void ConstructionRepository::construct(std::string path, const std::string& filename, const std::vector<std::vector<int>>& adjMatrix) const {
    m_ic->construct(path,filename,adjMatrix);
}
