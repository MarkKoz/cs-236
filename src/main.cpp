#include "graph.h"
#include "io.h"

#include <vector>

int main()
{
    do {
        std::vector<vertex> vertices = read_file();
    } while (prompt_retry());

    return 0;
}
