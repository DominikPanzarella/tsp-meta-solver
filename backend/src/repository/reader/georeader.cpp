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
            else if (key == "EDGE_WEIGHT_TYPE") ew_type = value;
            else if (key == "EDGE_WEIGHT_FORMAT") ew_format = value;
            else if (key == "EDGE_DATA_FORMAT") ed_format = value;
            else if (key == "NODE_COORD_TYPE") node_coord = value;
            else if (key == "DISPLAY_DATA_TYPE") disp_type = value;
            else if (key == "CAPACITY") capacity = std::stoi(value);
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
    m_problem->setCapacity(capacity);
    m_problem->setEdgeWeightType(m_problem->parseEdgeWeightType(ew_type));
    m_problem->setEdgeWeightFormat(m_problem->parseEdgeWeightFormat(ew_format));
    m_problem->setEdgeDataFormat(m_problem->parseEdgeDataFormat(ed_format));
    m_problem->setNodeCoordType(m_problem->parseNodeCoordType(node_coord));
    m_problem->setDisplayDataType(m_problem->parseDisplayDataType(disp_type));    
    m_problem->setGraph(graph);
}
