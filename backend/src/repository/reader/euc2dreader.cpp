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
    m_problem->setCapacity(0);
    m_problem->setEdgeWeightType(EdgeWeightType::EUC_2D);
    m_problem->setEdgeWeightFormat(EdgeWeightFormat::UNKNOWN);
    m_problem->setEdgeDataFormat(EdgeDataFormat::UNKNOWN);
    m_problem->setNodeCoordType(NodeCoordType::TWOD_COORDS);
    m_problem->setDisplayDataType(DisplayDataType::COORD_DISPLAY);
    m_problem->setGraph(graph);
}