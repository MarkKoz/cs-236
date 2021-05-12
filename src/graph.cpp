#include "graph.h"

#include <ostream>

std::ostream& operator<<(std::ostream& stream, const vertex& vertex) {
    stream << vertex.name << " --";
    for (const auto neighbour : vertex.neighbours) {
        stream << ' ' << neighbour;
    }

    return stream;
}
