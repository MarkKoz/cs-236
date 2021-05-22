#ifndef CS_236_07_GRAPH_H
#define CS_236_07_GRAPH_H

#include <vector>

struct edge {
    char endpoint_1;
    char endpoint_2;
    std::size_t weight;
};

std::vector<edge> kruskals_mst(std::vector<edge>& edges);

#endif
