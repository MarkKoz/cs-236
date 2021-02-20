#include <iostream>
#include <optional>
#include <string>
#include "roman.h"

int main() {
    bool stop = false;
    std::string selection;

    while (!stop) {
        std::optional<romanType> roman;
        std::cout << "Enter a roman numeral: ";

        while (true) {
            std::getline(std::cin, selection);
            try {
                roman = romanType(std::move(selection));
                break;
            } catch (const std::invalid_argument& error) {
                std::cerr << error.what() << " Please try again: ";
            }
        }

        roman->print_arabic(); // roman will always have a value once the loop ends.

        std::cout << "Try another number (y/n)? ";
        while (true) {
            std::getline(std::cin, selection);

            if (selection == "y" || selection == "Y") {
                break;
            } else if (selection == "n" || selection == "N") {
                std::cout << "Thank you!\n";
                stop = true;
                break;
            } else  {
                std::cerr << "Unknown value, try again: ";
            }
        }
    }

    return 0;
}
