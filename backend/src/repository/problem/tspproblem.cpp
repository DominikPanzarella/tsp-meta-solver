#include "tspproblem.h"

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