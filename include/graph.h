#ifndef CS_236_06_GRAPH_H
#define CS_236_06_GRAPH_H

#include <ostream>
#include <string>
#include <vector>

/**
 * @brief A vertex of a directed graph.
 */
struct vertex
{
    /**
     * @brief Name of the vertex.
     */
    std::string name;

    /**
     * @brief Indices of vertices which have an edge from this vertex to them.
     */
    std::vector<std::size_t> neighbours;

    /**
     * @brief Index of the vertex along the shortest path which has an edge to this vertex.
     */
    std::size_t previous = 0;

    /**
     * @brief Stream insertion operator.
     *
     * Insert a string representation of the vertex into the stream.
     * A string representation contains the vertex's name and the indices of its neighbours.
     *
     * @param stream The output stream in which to insert the tree.
     * @param vertex The vertex to insert.
     *
     * @return The given output stream.
     */
    friend std::ostream& operator<<(std::ostream& stream, const vertex& vertex);
};

/**
 * @brief Find the shortest path between two vertices in an unweighted, directed graph.
 *
 * @param vertices The vertices of the graph.
 * @param start The index of the start vertex in @p vertices.
 * @param end The index of the end vertex in @p vertices.
 */
void find_shortest_path(std::vector<vertex>& vertices, std::size_t start, std::size_t end);

/**
 * @brief Print to stdout the shortest path between two vertices in an unweighted, directed graph.
 *
 * List the destination first, and then the vertex leading to it.
 *
 * @param vertices The vertices of the graph.
 * @param start The index of the start vertex in @p vertices.
 * @param end The index of the end vertex in @p vertices.
 */
void print_shortest_path(std::vector<vertex>& vertices, std::size_t start, std::size_t end);

#endif
