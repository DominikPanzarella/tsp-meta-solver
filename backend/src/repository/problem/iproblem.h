#pragma once

//////////////
// #INCLUDE //
//////////////

//C/C++

#include <string>
#include <vector>

//Graph

#include "../../service/graph/igraph.h"
#include "displaydatatype.h"
#include "edgeweighttype.h"
#include "edgeweightformat.h"
#include "edgedataformat.h"
#include "nodecoordtype.h"

class IProblem {
public:

        // GET
        virtual const std::string& getName() const =0;

        virtual const std::string& getType() const =0;

        virtual const std::string& getComment() const =0;

        virtual const int getDimension() const =0;

        virtual const int getCapacity() const =0;

        virtual const EdgeWeightType getEdgeWeightType() const = 0;

        virtual const EdgeWeightFormat getEdgeWeightFormat() const = 0;

        virtual const EdgeDataFormat getEdgeDataFormat() const = 0;

        virtual const NodeCoordType getNodeCoordType() const = 0;

        virtual const DisplayDataType getDisplayDataType() const = 0;

        virtual const IGraph& getGraph() const = 0;

        // SET
        virtual void setName(const std::string& name) = 0;

        virtual void setType(const std::string& type) = 0;

        virtual void setComment(const std::string& comment) = 0;

        virtual void setDimension(int dimension) = 0;

        virtual void setCapacity(int capacity) = 0;
    
        virtual void setEdgeWeightType(EdgeWeightType ewt) = 0;

        virtual void setEdgeWeightFormat(EdgeWeightFormat ewf) = 0;

        virtual void setEdgeDataFormat(EdgeDataFormat edf) = 0;

        virtual void setNodeCoordType(NodeCoordType nct) = 0;

        virtual void setDisplayDataType(DisplayDataType ddt) = 0;
        
        virtual void setGraph(std::shared_ptr<IGraph> graph) = 0;
};