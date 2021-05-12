#ifndef CS_236_06_GRAPH_H
#define CS_236_06_GRAPH_H

#include <ostream>
#include <string>
#include <vector>

struct vertex
{
    std::string name;
    std::vector<std::size_t> neighbours;
    std::size_t prev = 0;

    friend std::ostream& operator<<(std::ostream& stream, const vertex& vertex);
};

#endif
