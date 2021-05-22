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
    std::vector<edge> mst = kruskals_mst(edges);

    std::cout << "Finding MST using Kruskal's Algorithm\nEdges of MST are\n";
    std::cout << "Weight of MST is " << '\n';

    return 0;
}
