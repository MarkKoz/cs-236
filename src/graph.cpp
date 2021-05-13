#include "graph.h"

#include <iostream>
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
    std::size_t length = 1;
    std::size_t shortest = vertices.size() + 1; // Initial value is intentionally impossible.
    std::set<std::size_t> visited;

    // The lambda needs a reference to itself in order to recurse.
    const auto dfs = [&](const auto& self, const std::size_t index) -> bool {
        if (length > shortest) {
            // Discard the current path because it's longer than the shortest known path.
            return false;
        }

        if (index == end) {
            // The end has been reached; save the path as the new shortest path.
            shortest = length;
            return true;
        }

        visited.insert(index); // Mark the node as visited.
        bool found_shorter = false;

        // Visit all unvisited neighbours.
        for (const auto neighbour : vertices[index].neighbours) {
            if (visited.count(neighbour) == 0) {
                ++length;
                found_shorter = self(self, neighbour);
                --length;

                if (found_shorter) {
                    // Store the parent vertex to enable traversing the shortest path later.
                    vertices[neighbour].previous = index;
                }

                // Vertices only need to be marked as visited to avoid cycles.
                // They must be unmarked once a path is traversed (or aborted).
                // The vertex could lead to a shorter path that will get traversed later.
                // If it's still marked as visited, it'll never go down that shorter path later.
                visited.erase(neighbour);
            }
        }

        return found_shorter;
    };

    dfs(dfs, start);
}

void print_shortest_path(
    std::vector<vertex>& vertices, const std::size_t start, const std::size_t end)
{
    find_shortest_path(vertices, start, end);

    std::size_t index = end;
    do {
        vertex v = vertices[index];
        std::cout << index + 1 << ' ' << v.name << "\n↑\n";
        index = v.previous;
    } while (index != start);

    std::cout << start + 1 << ' ' << vertices[start].name << '\n';
}
