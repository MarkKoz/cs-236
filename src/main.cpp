#include "rb_tree.h"

#include <iostream>

int main()
{
    rb_tree<int> tree;

    std::cout << "Enter a space-delimited sequence of integers to insert into a red-black tree:\n";
    std::string input_line;
    std::getline(std::cin, input_line);

    int input_int = 0;
    std::istringstream input_stream(input_line);

    while (input_stream >> input_int) {
        tree.insert(input_int);
    }

    std::cout << "Final balanced red-black tree:" << tree;
    return 0;
}
