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

                // Store the parent vertex to enable traversing the shortest path later.
                vertices[neighbour].previous = index;

                // Vertices only need to be marked as visited to avoid cycles.
                // They must be unmarked once a path is traversed (or aborted).
                // The vertex could lead to a shorter path that will get traversed later.
                // If it's still marked as visited, it'll never go down that shorter path later.
                visited.erase(neighbour);
            }
        }

        --length;
    };

    dfs(dfs, start);
}
