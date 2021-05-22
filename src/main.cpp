#include "graph.h"

#include <iostream>

int main()
{
    std::vector<edge> edges {{
        {'A', 'B', 6},
        {'B', 'C', 10},
        {'B', 'F', 8},
        {'C', 'D', 8},
        {'C', 'E', 10},
        {'D', 'E', 8},
        {'E', 'F', 12},
        {'F', 'A', 5},
        {'G', 'B', 7},
        {'G', 'C', 5},
        {'G', 'E', 7},
        {'G', 'F', 7},
    }};
    std::vector<edge> mst_edges = kruskals_mst(edges);
    std::size_t total_weight = 0;

    std::cout << "Finding MST using Kruskal's Algorithm\nEdges of MST are\n";
    for (const edge& edge : mst_edges) {
        std::cout << edge.endpoint_1 << " ↔ " << edge.endpoint_2 << " = " << edge.weight << '\n';
        total_weight += edge.weight;
    }

    std::cout << "Weight of MST is " << total_weight << '\n';

    return 0;
}
