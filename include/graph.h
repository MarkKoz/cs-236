#ifndef CS_236_07_GRAPH_H
#define CS_236_07_GRAPH_H

#include <vector>

/**
 * @brief An edge of a weighted, undirected graph.
 */
struct edge {
    /**
     * @brief One of the two vertices joined by the edge.
     */
    char endpoint_1;

    /**
     * @brief One of the two vertices joined by the edge.
     */
    char endpoint_2;

    /**
     * @brief The weight of the edge.
     */
    std::size_t weight;
};

/**
 * @brief Find the edges of the minimum spanning tree (MST) of a graph using Kruskal's algorithm.
 *
 * @param edges The edges of a connected, undirected, weighted graph for which to find the MST.
 *
 * @return The edges of the minimum spanning tree.
 */
std::vector<edge> kruskals_mst(std::vector<edge>& edges);

#endif
