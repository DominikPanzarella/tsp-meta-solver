#pragma once

//////////////
// #INCLUDE //
//////////////

#include "service/graph/node.h"
#include "tspreader.h"

class Ceil2dReader : public TspReader
{
public:

    Ceil2dReader() = default;

    ~Ceil2dReader() = default;

protected:

    virtual bool canHandle(const std::string& content) const override;

    std::shared_ptr<IProblem> readInternal(std::istream& input) override;

private:

    virtual std::tuple<std::string, std::string, std::string, int,
    std::string, std::string, std::string, std::string,std::string, int>
        parseHeader(std::istream& input) override;

    virtual std::vector<Node> parseBody(std::istream& input, int dimension) override;

    virtual std::shared_ptr<IGraph> buildGraph(const std::vector<Node>& nodes, int dimension) override;

    virtual std::shared_ptr<IProblem> buildProblem(
        const std::string& name,
        const std::string& comment,
        const std::string& type,
        int dimension,
        const std::string& ew_type,
        const std::string& ew_format,
        const std::string& ed_format,
        const std::string& node_coord,
        const std::string& disp_type,
        int capacity,
        std::shared_ptr<IGraph> graph) override;

};