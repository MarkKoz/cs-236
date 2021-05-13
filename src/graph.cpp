#include "graph.h"

#include <ostream>
#include <set>

std::ostream& operator<<(std::ostream& stream, const vertex& vertex)
{
    stream << vertex.name << " --";
    for (const auto neighbour : vertex.neighbours) {
        stream << ' ' << neighbour + 1;
    }

    return stream;
}

void find_shortest_path(
    std::vector<vertex>& vertices, const std::size_t start, const std::size_t end)
{
    std::size_t length = 0;
    std::size_t shortest = vertices.size() + 1; // Initial value is intentionally impossible.
    std::set<std::size_t> visited;

    // The lambda needs a reference to itself in order to recurse.
    const auto dfs = [&](const auto& self, const std::size_t index) -> void {
        ++length;

        if (length > shortest) {
            // Discard the current path because it's longer than the shortest known path.
            return;
        }

        if (index == end) {
            // The end has been reached; save the path as the new shortest path.
            shortest = length;
            return;
        }

        visited.insert(index); // Mark the node as visited.

        // Visit all unvisited neighbours.
        for (const auto neighbour : vertices[index].neighbours) {
            if (visited.count(neighbour) == 0) {
                self(self, neighbour);
                vertices[neighbour].previous = index;
            }
        }

        --length;
    };

    dfs(dfs, start);
}
