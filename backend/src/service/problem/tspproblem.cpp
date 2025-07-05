#include "tspproblem.h"
#include <iostream>

const std::string& TspProblem::getName() const{
    return m_name;
}

const std::string& TspProblem::getType() const
{
    return m_type;
}

const int TspProblem::getDimension() const {
    return m_dimension;
}

const int TspProblem::getCapacity() const {
    return m_capacity;
}


const std::string& TspProblem::getComment() const{
    return m_comment;
}

const EdgeWeightType TspProblem::getEdgeWeightType() const {
    return m_edgeWeightType;
}

const EdgeWeightFormat TspProblem::getEdgeWeightFormat() const{
    return m_edgeWeightFormat;
}

const EdgeDataFormat TspProblem::getEdgeDataFormat() const{
    return m_edgeDataFormat;
}

const NodeCoordType TspProblem::getNodeCoordType() const{
    return m_nodeCoordType;
}

const DisplayDataType TspProblem::getDisplayDataType() const{
    return m_displayDataType;
}


const IGraph& TspProblem::getGraph() const {
    return *m_graph.get(); 
}

void TspProblem::setName(const std::string& name){
    this->m_name = name;    
}

void TspProblem::setType(const std::string& type){
    this->m_type = type;
}

void TspProblem::setComment(const std::string& comment){
    this->m_comment = comment;
}

void TspProblem::setDimension(int dimension){
   this->m_dimension = dimension; 
}

void TspProblem::setCapacity(int capacity){
    this->m_capacity = capacity;
}

void TspProblem::setEdgeWeightType(EdgeWeightType ewt){
    this->m_edgeWeightType = ewt; 
}

void TspProblem::setEdgeWeightFormat(EdgeWeightFormat ewf){
    this->m_edgeWeightFormat = ewf;
}

void TspProblem::setEdgeDataFormat(EdgeDataFormat edf){
    this->m_edgeDataFormat = edf;
}

void TspProblem::setNodeCoordType(NodeCoordType nct){
    this->m_nodeCoordType = nct;
}

void TspProblem::setDisplayDataType(DisplayDataType ddt){
    this->m_displayDataType = ddt;
}

void TspProblem::setGraph(std::shared_ptr<IGraph> graph){
    this->m_graph = std::move(graph);
}


EdgeWeightType TspProblem::parseEdgeWeightType(const std::string& str) const{
    if(str == "EXPLICIT") return EdgeWeightType::EXPLICIT;
    else if(str == "EUC_2D") return EdgeWeightType::EUC_2D;
    else if(str == "EUC_3D") return EdgeWeightType::EUC_3D;
    else if(str == "CEIL_2D") return EdgeWeightType::CEIL_2D;
    else if(str == "ATT") return EdgeWeightType::ATT;
    else if(str == "GEO") return EdgeWeightType::GEO;
    else if(str == "MAN_2D") return EdgeWeightType::MAN_2D;
    else if(str == "MAN_3D") return EdgeWeightType::MAN_3D;
    else if(str == "MAX_2D") return EdgeWeightType::MAX_2D;
    else if(str == "MAX_3D") return EdgeWeightType::MAX_3D;
    else if(str == "XRAY1") return EdgeWeightType::XRAY1;
    else if(str == "XRAY2") return EdgeWeightType::XRAY2;
    else if(str == "SPECIAL") return EdgeWeightType::SPECIAL;
    else return EdgeWeightType::UNKNOWN;
}

EdgeWeightFormat TspProblem::parseEdgeWeightFormat(const std::string& str) const{
    if(str == "FUNCTION") return EdgeWeightFormat::FUNCTION;
    else if(str == "FULL_MATRIX") return EdgeWeightFormat::FULL_MATRIX;
    else if(str == "UPPER_ROW") return EdgeWeightFormat::UPPER_ROW;
    else if(str == "LOWER_ROW") return EdgeWeightFormat::LOWER_ROW;
    else if(str == "UPPER_DIAG_ROW") return EdgeWeightFormat::UPPER_DIAG_ROW;
    else if(str == "LOWER_DIAG_ROW") return EdgeWeightFormat::LOWER_DIAG_ROW;
    else if(str == "UPPER_COL") return EdgeWeightFormat::UPPER_COL;
    else if(str == "LOWER_COL") return EdgeWeightFormat::LOWER_COL;
    else if(str == "UPPER_DIAG_COL") return EdgeWeightFormat::UPPER_DIAG_COL;
    else if(str == "LOWER_DIAG_COL") return EdgeWeightFormat::LOWER_DIAG_COL;
    else return EdgeWeightFormat::UNKNOWN;
}

EdgeDataFormat TspProblem::parseEdgeDataFormat(const std::string& str) const{
    if(str == "EDGE_LIST") return EdgeDataFormat::EDGE_LIST;
    else if(str == "ADJ_LIST") return EdgeDataFormat::ADJ_LIST;
    else return EdgeDataFormat::UNKNOWN;
}

NodeCoordType TspProblem::parseNodeCoordType(const std::string& str) const{
    if(str == "TWOD_COORDS") return NodeCoordType::TWOD_COORDS;
    else if(str == "THREEED_COORDS") return NodeCoordType::THREEED_COORDS;
    else if(str == "NO_COORDS") return NodeCoordType::NO_COORDS;
    else return NodeCoordType::UNKNOWN;
}

DisplayDataType TspProblem::parseDisplayDataType(const std::string& str) const{
    if(str == "COORD_DISPLAY") return DisplayDataType::COORD_DISPLAY;
    else if(str == "TWOD_DISPLAY") return DisplayDataType::TWOD_DISPLAY;
    else if(str == "NO_DISPLAY") return DisplayDataType::NO_DISPLAY;
    else return DisplayDataType::UNKNOWN;

}

void TspProblem::PrintMatrix() const{
    auto adjacencyMatrix = m_graph->getMatrix();
    for(int i=0; i<m_dimension; i++){
        for(int j=0; j<m_dimension; j++)
            std::cout << adjacencyMatrix[i][j] << " ";
        std::cout << std::endl;
    }


}

const int TspProblem::getCost(int i,int j) const {
    if(m_graph == nullptr)          return -1;
    if(i<0 || i>=m_dimension)       return -1;
    if(j<0 || j>=m_dimension)       return -1;
    auto adjMatrix = m_graph->getMatrix();
    return adjMatrix[i][j];
}