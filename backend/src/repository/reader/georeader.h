#pragma once

//////////////
// #INCLUDE //
//////////////

#include "../../service/graph/node.h"
#include "../../service/graph/symmetricgraph.h"
#include "tspreader.h"

class GeoReader : public TspReader
{
public:

    GeoReader() = default;

protected:

    virtual bool canHandle(const std::string& content) const override;

    virtual void parseHeader() override;

    virtual void parseBody() override;

    virtual void buildGraph() override;

    virtual void buildProblem() override;

    double geoToRadians(double coord);
    
    double geoDistance(const Node& a, const Node& b);


private:
    std::string ew_format, ed_format, node_coord, disp_type;
    std::string name, comment, type, ew_type;
    int dimension = 0;
    std::vector<Node> nodes;
    std::shared_ptr<SymmetricGraph> graph;

};