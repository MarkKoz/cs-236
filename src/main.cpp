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

    } while (prompt_retry());

    return 0;
}
