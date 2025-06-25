#include "georeader.h"
#include <regex>
#include <cmath>
#include <sstream>
#include <iostream>

bool GeoReader::canHandle(const std::string& content) const {
    return content.find("EDGE_WEIGHT_TYPE") != std::string::npos &&
           content.find("GEO") != std::string::npos;
}

void GeoReader::parseHeader() {
    std::string line;
    while (std::getline(*input, line)) {
        if (line.find("NODE_COORD_SECTION") != std::string::npos) break;

        std::regex rx(R"(^\s*([^:]+)\s*:\s*(.*))");
        std::smatch match;
        if (std::regex_match(line, match, rx)) {
            std::string key = trim(match[1]);
            std::string value = trim(match[2]);
            if (key == "NAME") name = value;
            else if (key == "COMMENT") comment = value;
            else if (key == "TYPE") type = value;
            else if (key == "DIMENSION") dimension = std::stoi(value);
        }
    }
}

void GeoReader::parseBody() {
    std::string line;
    int id;
    double x, y;

    while (std::getline(*input, line)) {
        if (line.find("EOF") != std::string::npos) break;
        std::istringstream iss(line);
        if (!(iss >> id >> x >> y)) continue;
        nodes.emplace_back(id, x, y);
    }
}

double GeoReader::geoToRadians(double coord) {
    int deg = static_cast<int>(coord);
    double min = coord - deg;
    return M_PI * (deg + 5.0 * min / 3.0) / 180.0;
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

void GeoReader::buildGraph() {
    graph = std::make_shared<SymmetricGraph>();
    graph->init(dimension);

    for (int i = 0; i < dimension; ++i) {
        for (int j = i + 1; j < dimension; ++j) {
            int dist = static_cast<int>(geoDistance(nodes[i], nodes[j]));
            graph->setEdge(i, j, dist);
        }
    }
}

void GeoReader::buildProblem() {
    m_problem = std::make_shared<TspProblem>();
    m_problem->setName(name);
    m_problem->setComment(comment);
    m_problem->setType(type);
    m_problem->setDimension(dimension);
    m_problem->setCapacity(0);
    m_problem->setEdgeWeightType(EdgeWeightType::GEO);
    m_problem->setEdgeWeightFormat(EdgeWeightFormat::UNKNOWN);
    m_problem->setEdgeDataFormat(EdgeDataFormat::UNKNOWN);
    m_problem->setNodeCoordType(NodeCoordType::TWOD_COORDS);
    m_problem->setDisplayDataType(DisplayDataType::COORD_DISPLAY);
    m_problem->setGraph(graph);
}
