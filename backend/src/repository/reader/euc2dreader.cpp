//////////////
// #INCLUDE //
//////////////

#include "euc2dreader.h"
#include "../problem/tspproblem.h"
#include "../../service/graph/symmetricgraph.h"
#include "../../service/graph/node.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <cmath>

bool Euc2DReader::canHandle(const std::string& content) const {
    return content.find("EDGE_WEIGHT_TYPE") != std::string::npos &&
           content.find("EUC_2D") != std::string::npos;
}

void Euc2DReader::parseHeader() {
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

void Euc2DReader::parseBody() {
    std::string line;
    int id;
    double x, y;

    while (std::getline(*input, line)) {
        if (line.find("EOF") != std::string::npos) break;

        std::istringstream iss(line);
        if (!(iss >> id >> x >> y)) continue;
        nodes.emplace_back(id, x, y);
    }

    if (nodes.size() != static_cast<size_t>(dimension)) {
        std::cerr << "[Euc2DReader] Mismatch tra nodi letti e DIMENSION." << std::endl;
    }
}

void Euc2DReader::buildGraph() {
    graph = std::make_shared<SymmetricGraph>();
    graph->init(dimension);

    for (int i = 0; i < dimension; ++i) {
        for (int j = i + 1; j < dimension; ++j) {
            double dx = nodes[i].x - nodes[j].x;
            double dy = nodes[i].y - nodes[j].y;
            int dist = static_cast<int>(std::round(std::sqrt(dx * dx + dy * dy)));
            graph->setEdge(i, j, dist);
        }
    }
}

void Euc2DReader::buildProblem() {
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