#include "io.h"

#include <fstream>

int main()
{
    do {
        const auto path = get_file_path();
        std::ifstream file(path);

    } while (prompt_retry());

    return 0;
}
