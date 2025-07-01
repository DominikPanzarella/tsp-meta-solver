#include "matrixreader.h"
#include "../problem/tspproblem.h"
#include "../../service/graph/symmetricgraph.h"
#include "../../service/graph/node.h"

#include <sstream>
#include <regex>
#include <iostream>
#include <stdexcept>

bool MatrixReader::canHandle(const std::string& content) const {
    return content.find("EDGE_WEIGHT_TYPE") != std::string::npos &&
           content.find("EXPLICIT") != std::string::npos;
}

std::shared_ptr<IProblem> MatrixReader::readInternal(std::istream& input) {
    auto [name, comment, type, dimension, ew_type, ew_format, ed_format, node_coord, disp_type, capacity] = parseHeader(input);
    auto nodes = parseBody(input, dimension);
    auto graph = buildGraph(nodes, dimension);
    return buildProblem(name, comment, type, dimension, ew_type, ew_format, ed_format, node_coord, disp_type, capacity, graph);
}

std::tuple<std::string, std::string, std::string, int,
           std::string, std::string, std::string, std::string, std::string, int>
MatrixReader::parseHeader(std::istream& input) {
    std::string line;
    std::string name, comment, type, ew_type, ew_format, ed_format, node_coord, disp_type;
    int dimension = 0, capacity = 0;

    while (std::getline(input, line)) {
        if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos) break;

        std::regex rx(R"(^\s*([^:]+)\s*:\s*(.*))");
        std::smatch m;
        if (std::regex_match(line, m, rx)) {
            std::string key = TspReader::trim(m[1]);
            std::string val = TspReader::trim(m[2]);
            if      (key == "NAME")              name = val;
            else if (key == "COMMENT")           comment = val;
            else if (key == "TYPE")              type = val;
            else if (key == "DIMENSION")         dimension = std::stoi(val);
            else if (key == "CAPACITY")          capacity = std::stoi(val);
            else if (key == "EDGE_WEIGHT_TYPE")  ew_type = val;
            else if (key == "EDGE_WEIGHT_FORMAT")ew_format = val;
            else if (key == "EDGE_DATA_FORMAT")  ed_format = val;
            else if (key == "NODE_COORD_TYPE")   node_coord = val;
            else if (key == "DISPLAY_DATA_TYPE") disp_type = val;
        }
    }

    this->format = ew_format;

    return {name, comment, type, dimension, ew_type, ew_format, ed_format, node_coord, disp_type, capacity};
}

std::vector<Node> MatrixReader::parseBody(std::istream& input, int dimension) {
    weights.clear();
    std::string token;

    while (input >> token) {
        if (token == "EOF" || token.find("SECTION") != std::string::npos)
            break;

        try {
            int val = std::stoi(token);
            weights.push_back(val);
        } catch (const std::invalid_argument&) {
            // ignora eventuali token non numerici
        }
    }

    return {};
}



std::shared_ptr<IGraph> MatrixReader::buildGraph(const std::vector<Node>&, int dimension) {
    auto graph = std::make_shared<SymmetricGraph>();
    graph->init(dimension);

    const std::string& fmt = this->format;
    size_t k = 0;

    if (fmt == "FULL_MATRIX") {
        for (int i = 0; i < dimension; ++i)
            for (int j = 0; j < dimension; ++j)
                graph->setEdge(i, j, weights[k++]);
    }

    else if (fmt == "UPPER_ROW") {
        for (int i = 0; i < dimension; ++i)
            for (int j = i + 1; j < dimension; ++j) {
                int w = weights[k++];
                graph->setEdge(i, j, w);
            }
    }

    else if (fmt == "LOWER_ROW") {
        for (int i = 1; i < dimension; ++i)
            for (int j = 0; j < i; ++j) {
                int w = weights[k++];
                graph->setEdge(i, j, w);
            }
    }

    else if (fmt == "UPPER_DIAG_ROW") {
        for (int i = 0; i < dimension; ++i)
            for (int j = i; j < dimension; ++j) {
                int w = weights[k++];
                graph->setEdge(i, j, w);
                //if (i != j) graph->setEdge(j, i, w);
            }
    }

    else if (fmt == "LOWER_DIAG_ROW") {
        for (int i = 0; i < dimension; ++i)
            for (int j = 0; j <= i; ++j) {
                int w = weights[k++];
                graph->setEdge(i, j, w);
                //if (i != j) graph->setEdge(j, i, w);
            }
    }

    else if (fmt == "UPPER_COL") {
        for (int j = 1; j < dimension; ++j) {
            for (int i = 0; i < j; ++i) {
                int w = weights[k++];
                graph->setEdge(i, j, w);
            }
        }
    }
    
    else if (fmt == "LOWER_COL") {
        for (int j = 0; j < dimension - 1; ++j) {
            for (int i = j + 1; i < dimension; ++i) {
                int w = weights[k++];
                graph->setEdge(i, j, w);
            }
        }
    }

    else if (fmt == "UPPER_DIAG_COL") {
        for (int j = 0; j < dimension; ++j) {
            for (int i = 0; i <= j; ++i) {
                int w = weights[k++];
                graph->setEdge(i, j, w);
            }
        }
    }
    
    else if (fmt == "LOWER_DIAG_COL") {
        for (int j = 0; j < dimension; ++j) {
            for (int i = j; i < dimension; ++i) {
                int w = weights[k++];
                graph->setEdge(i, j, w);
            }
        }
    }
    

    else {
        throw std::runtime_error("Unsupported format");
    }

    if (k != weights.size()) {
        throw std::runtime_error("Parsed " + std::to_string(k) + " weights, but expected " + std::to_string(weights.size()));
    }


    if(fmt == "UPPER_ROW" || fmt == "LOWER_ROW" || fmt == "UPPER_COL" || fmt == "LOWER_COL"){
        for(int i=0; i<dimension; i++)
            graph->setEdge(i,i, 0);
    }

    return graph;
}



std::shared_ptr<IProblem> MatrixReader::buildProblem(
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
    std::shared_ptr<IGraph> graph) {

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
