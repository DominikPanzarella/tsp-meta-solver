#pragma once

//////////////
// #INCLUDE //
//////////////

#include "../../service/graph/node.h"
#include "../../service/graph/symmetricgraph.h"
#include "tspreader.h"

class MatrixReader : public TspReader
{
public:

    MatrixReader() = default;

protected:

    virtual bool canHandle(const std::string& content) const override;

    virtual void parseHeader() override;

    virtual void parseBody() override;

    virtual void buildGraph() override;

    virtual void buildProblem() override;


private:
    std::string ew_format, ed_format, node_coord, disp_type;
    std::string name, comment, type, ew_type;
    int dimension = 0;
    int capacity = 0;
    std::vector<Node> nodes;
    std::shared_ptr<SymmetricGraph> graph;

};