#ifndef CS_236_06_GRAPH_H
#define CS_236_06_GRAPH_H

#include <ostream>
#include <string>
#include <vector>

struct vertex
{
    std::string name;
    std::vector<std::size_t> neighbours;
    std::size_t previous = 0;

    friend std::ostream& operator<<(std::ostream& stream, const vertex& vertex);
};

void find_shortest_path(std::vector<vertex>& vertices, std::size_t start, std::size_t end);

#endif
