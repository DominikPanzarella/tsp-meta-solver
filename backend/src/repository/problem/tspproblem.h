#pragma once

//////////////
// #INCLUDE //
//////////////

#include "iproblem.h"

class TspProblem : public IProblem{

public:

    /** Problem management **/

    //Default construcotr
    TspProblem() = default;

    //Destructor
    ~TspProblem() = default;

    //Copy Constructor
    TspProblem(const TspProblem& other) = default;

    // Copy Assignment Operator
    TspProblem& operator=(const TspProblem& other) = delete;

    // Move Constructor
    TspProblem(TspProblem&& other) = delete;


    /*
                //////////////
                // OVERIDE  //
                //////////////
    */

    /*      GETTER      */
    
    const std::string& getName() const override;

    const std::string& getType() const override;

    const std::string& getComment() const override;

    const EdgeWeightType getEdgeWeightType() const override;

    const EdgeWeightFormat getEdgeWeightFormat() const override;

    const EdgeDataFormat getEdgeDataFormat() const override;

    const NodeCoordType getNodeCoordType() const override;

    const DisplayDataType getDisplayDataType() const override;

    const IGraph& getGraph() const override;

    const int getDimension() const override;

    const int getCapacity() const override;

    /*      SETTER      */

    void setName(const std::string& name) override;

    void setType(const std::string& type) override;

    void setComment(const std::string& comment) override;

    void setDimension(int dimension) override;

    void setCapacity(int capacity) override;

    void setEdgeWeightType(EdgeWeightType ewt) override;

    void setEdgeWeightFormat(EdgeWeightFormat ewf) override;

    void setEdgeDataFormat(EdgeDataFormat edf) override;

    void setNodeCoordType(NodeCoordType nct) override;

    void setDisplayDataType(DisplayDataType ddt) override;
    
    void setGraph(std::shared_ptr<IGraph> graph) override;


    EdgeWeightType parseEdgeWeightType(const std::string& str) const;

    EdgeWeightFormat parseEdgeWeightFormat(const std::string& str) const; 

    EdgeDataFormat parseEdgeDataFormat(const std::string& str) const;

    NodeCoordType parseNodeCoordType(const std::string& str) const;

    DisplayDataType parseDisplayDataType(const std::string& str) const;


private:
    std::string m_name;

    std::string m_type;

    std::string m_comment;

    int m_dimension;

    int m_capacity;

    EdgeWeightType m_edgeWeightType;

    EdgeWeightFormat m_edgeWeightFormat;

    EdgeDataFormat m_edgeDataFormat;

    NodeCoordType m_nodeCoordType;

    DisplayDataType m_displayDataType;

    std::shared_ptr<IGraph> m_graph;

};