#include "graph.h"
#include "io.h"

#include <iostream>
#include <vector>

int main()
{
    std::vector<vertex> vertices = read_file();

    std::cout << "The Digraph's Adjacency-List Representation:\n";
    std::size_t index = 1;
    for (const auto& vertex : vertices) {
        std::cout << index++ << ": " << vertex << '\n';
    }

    do {
        std::cout << "\nEnter the number of the starting city: ";
        const std::size_t start = prompt_city(vertices.size()) - 1;

        std::cout << "Enter the number of the destination city: ";
        const std::size_t end = prompt_city(vertices.size()) - 1;

        std::cout << "\nShortest path from " << vertices[start].name
                  << " to " << vertices[end].name << " is:\n";

        print_shortest_path(vertices, start, end);
        std::cout << '\n';
    } while (prompt_retry());

    return 0;
}
