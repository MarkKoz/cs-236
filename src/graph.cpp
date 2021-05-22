#include "graph.h"

#include "disjoint_set.h"
#include <algorithm>

std::vector<edge> kruskals_mst(std::vector<edge>& edges)
{
    std::vector<edge> mst_edges {};
    disjoint_set<char> dset {};

    // Sort edges by weight in ascending order.
    const auto comp = [&dset](const edge& edge_1, const edge& edge_2) -> bool {
        // Might as well generate the set while sorting,
        // since the sort has to go through every edge.
        dset.make_set(edge_1.endpoint_1);
        dset.make_set(edge_1.endpoint_2);
        dset.make_set(edge_2.endpoint_1);
        dset.make_set(edge_2.endpoint_2);

        return edge_1.weight < edge_2.weight;
    };

    std::sort(edges.begin(), edges.end(), comp);

    for (const edge& edge : edges) {
        if (dset.find(edge.endpoint_1) != dset.find(edge.endpoint_2)) {
            mst_edges.push_back(edge);
            dset.unite(edge.endpoint_1, edge.endpoint_2);
        }
    }

    return mst_edges;
}
