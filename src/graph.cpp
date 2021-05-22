#include "graph.h"

#include <algorithm>

std::vector<edge> kruskals_mst(std::vector<edge>& edges)
{
    // Sort edges by weight in ascending order.
    const auto comp = [](const edge& edge_1, const edge& edge_2) -> bool {
        return edge_1.weight < edge_2.weight;
    };
    std::sort(edges.begin(), edges.end(), comp);



    return {};
}
