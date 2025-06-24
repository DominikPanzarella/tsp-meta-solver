#include <gtest/gtest.h>
#include "service/graph/symmetricgraph.h"

// Test di inizializzazione del grafo
TEST(SymmetricGraphTest, InitGraph) {
    SymmetricGraph graph;
    graph.init(3);
    EXPECT_EQ(graph.size(), 3);
}

// Test dell'inserimento e lettura degli archi
TEST(SymmetricGraphTest, EdgeInsertion) {
    SymmetricGraph graph;
    graph.init(3);
    graph.setEdge(0, 1, 42);
    EXPECT_EQ(graph.getEdge(0, 1), 42);
    EXPECT_EQ(graph.getEdge(1, 0), 42);  // Simmetrico
}

// Test della completezza
TEST(SymmetricGraphTest, Completeness) {
    SymmetricGraph graph;
    graph.init(3);
    graph.setEdge(0, 1, 1);
    graph.setEdge(1, 2, 1);
    graph.setEdge(0, 2, 1);
    EXPECT_TRUE(graph.isComplete());
}

// Test della simmetria
TEST(SymmetricGraphTest, Symmetry) {
    SymmetricGraph graph;
    graph.init(2);
    graph.setEdge(0, 1, 5);
    EXPECT_TRUE(graph.isSymmetric());
}
