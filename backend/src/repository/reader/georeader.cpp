#include "georeader.h"
#include "service/problem/tspproblem.h"
#include "service/graph/symmetricgraph.h"
#include <regex>
#include <cmath>
#include <sstream>
#include <iostream>

bool GeoReader::canHandle(const std::string& content) const {
    return content.find("EDGE_WEIGHT_TYPE") != std::string::npos &&
           content.find("GEO") != std::string::npos;
}

std::shared_ptr<IProblem> GeoReader::readInternal(std::istream& input) {
    auto [name, comment, type, dimension, ew_type, ew_format, ed_format, node_coord, disp_type, capacity] = parseHeader(input);
    auto nodes = parseBody(input, dimension);
    auto graph = buildGraph(nodes, dimension);
    return buildProblem(name, comment, type, dimension, ew_type, ew_format, ed_format, node_coord, disp_type, capacity, graph);
}

std::tuple<std::string, std::string, std::string, int,
           std::string, std::string, std::string, std::string, std::string, int>
           GeoReader::parseHeader(std::istream& input) {
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

std::vector<Node> GeoReader::parseBody(std::istream& input, int dimension) {
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
        std::cerr << "[GeoReader] Mismatch tra nodi letti e DIMENSION." << std::endl;
    }

    return nodes;
}


double GeoReader::geoToRadians(double coord) {
    int deg = nint(coord);
    double min = coord - deg;
    return M_PI * (deg + (5.0 * min / 3.0)) / 180.0;
}



double GeoReader::geoDistance(const Node& a, const Node& b) {
    const double RRR = 6378.388;
    double lat_i = geoToRadians(a.x);
    double lon_i = geoToRadians(a.y);
    double lat_j = geoToRadians(b.x);
    double lon_j = geoToRadians(b.y);
    double q1 = std::cos(lon_i - lon_j);
    double q2 = std::cos(lat_i - lat_j);
    double q3 = std::cos(lat_i + lat_j);
    return static_cast<int>(RRR * std::acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0);
}

std::shared_ptr<IGraph> GeoReader::buildGraph(const std::vector<Node>& nodes, int dimension) {
    auto graph = std::make_shared<SymmetricGraph>();
    graph->init(dimension);

    for (int i = 0; i < dimension; ++i) {
        for (int j = i + 1; j < dimension; ++j) {
            int dist = static_cast<int>(geoDistance(nodes[i], nodes[j]));
            graph->setEdge(i, j, dist);
        }
    }


    for(int i=0; i<dimension; i++)
        graph->setEdge(i,i, 0);

    return graph;
}

std::shared_ptr<IProblem> GeoReader::buildProblem(
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
