#include "ceil2dreader.h"
#include "service/problem/tspproblem.h"
#include "service/graph/symmetricgraph.h"
#include <regex>
#include <cmath>
#include <sstream>
#include <iostream>

bool Ceil2dReader::canHandle(const std::string& content) const {
    return content.find("EDGE_WEIGHT_TYPE") != std::string::npos &&
           content.find("CEIL_2D") != std::string::npos;
}

std::shared_ptr<IProblem> Ceil2dReader::readInternal(std::istream& input) {
    auto [name, comment, type, dimension, ew_type, ew_format, ed_format, node_coord, disp_type, capacity] = parseHeader(input);
    auto nodes = parseBody(input, dimension);
    auto graph = buildGraph(nodes, dimension);
    return buildProblem(name, comment, type, dimension, ew_type, ew_format, ed_format, node_coord, disp_type, capacity, graph);
}

std::tuple<std::string, std::string, std::string, int,
           std::string, std::string, std::string, std::string, std::string, int>
           Ceil2dReader::parseHeader(std::istream& input) {
    std::string name, comment, type, ew_type, ew_format, ed_format, node_coord, disp_type;
    int dimension = 0, capacity = 0;
    std::string line;

    while (std::getline(input, line)) {
        if (line.find("NODE_COORD_SECTION") != std::string::npos) break;

        std::regex rx(R"(^\s*([^:]+)\s*:\s*(.*))");
        std::smatch match;
        if (std::regex_match(line, match, rx)) {
            std::string key = TspReader::trim(match[1]);
            std::string value = TspReader::trim(match[2]);

            if (key == "NAME") name = value;
            else if (key == "COMMENT") comment = value;
            else if (key == "TYPE") type = value;
            else if (key == "DIMENSION") dimension = std::stoi(value);
            else if (key == "EDGE_WEIGHT_TYPE") ew_type = value;
            else if (key == "EDGE_WEIGHT_FORMAT") ew_format = value;
            else if (key == "EDGE_DATA_FORMAT") ed_format = value;
            else if (key == "NODE_COORD_TYPE") node_coord = value;
            else if (key == "DISPLAY_DATA_TYPE") disp_type = value;
            else if (key == "CAPACITY") capacity = std::stoi(value);
        }
    }

    return {name, comment, type, dimension, ew_type, ew_format, ed_format, node_coord, disp_type, capacity};
}

std::vector<Node> Ceil2dReader::parseBody(std::istream& input, int dimension) {
    std::vector<Node> nodes;
    std::string line;
    int id;
    double x, y;

    while (std::getline(input, line)) {
        if (line.find("EOF") != std::string::npos || line.find("SECTION") != std::string::npos)
            break;  
        std::istringstream iss(line);
        if (!(iss >> id >> x >> y)) continue;
        nodes.emplace_back(Node{id, x, y});
    }

    if (nodes.size() != static_cast<size_t>(dimension)) {
        std::cerr << "[Ceil2dReader] Mismatch tra nodi letti e DIMENSION." << std::endl;
    }

    return nodes;
}

std::shared_ptr<IGraph> Ceil2dReader::buildGraph(const std::vector<Node>& nodes, int dimension) {
    auto graph = std::make_shared<SymmetricGraph>();
    graph->init(dimension);

    for (int i = 0; i < dimension; ++i) {
        for (int j = i + 1; j < dimension; ++j) {
            double dx = nodes[i].x - nodes[j].x;
            double dy = nodes[i].y - nodes[j].y;
            int dist = static_cast<int>(std::ceil(std::sqrt(dx * dx + dy * dy)));
            graph->setEdge(i, j, dist);
        }
    }

    for(int i=0; i<dimension; i++)
        graph->setEdge(i,i, 0);

    return graph;
}

std::shared_ptr<IProblem> Ceil2dReader::buildProblem(
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
    std::shared_ptr<IGraph> graph)
{
    auto tsp = std::make_shared<TspProblem>();
    tsp->setName(name);
    tsp->setComment(comment);
    tsp->setType(type);
    tsp->setDimension(dimension);
    tsp->setCapacity(capacity);
    tsp->setEdgeWeightType(tsp->parseEdgeWeightType(ew_type));
    tsp->setEdgeWeightFormat(tsp->parseEdgeWeightFormat(ew_format));
    tsp->setEdgeDataFormat(tsp->parseEdgeDataFormat(ed_format));
    tsp->setNodeCoordType(tsp->parseNodeCoordType(node_coord));
    tsp->setDisplayDataType(tsp->parseDisplayDataType(disp_type));
    tsp->setGraph(graph);
    return tsp;
}