#ifndef CS_236_06_GRAPH_H
#define CS_236_06_GRAPH_H

#include <string>
#include <vector>

struct vertex
{
    std::string name;
    std::vector<std::size_t> neighbours;
    std::size_t prev = 0;
};

#endif
