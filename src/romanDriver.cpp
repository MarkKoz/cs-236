#include <iostream>
#include <optional>
#include <string>
#include "roman.h"

/**
 * @brief Prompt for a Roman numeral input and display its Arabic equivalent.
 *
 * Keep prompting for an input until a valid input is given.
 */
void prompt_convert();

/**
 * @brief Prompt for whether to convert another input.
 *
 * Keep prompting for an input until a valid input ('y' or 'n', case-insensitive) is given.
 *
 * @return @c true to prompt again; @c false otherwise.
 */
bool prompt_retry();

int main() {
    do {
        prompt_convert();
    } while (prompt_retry());

    return 0;
}

void prompt_convert() {
    std::string selection;
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
}

bool prompt_retry() {
    std::string selection;

    std::cout << "Try another number (y/n)? ";
    while (true) {
        std::getline(std::cin, selection);

        if (selection == "y" || selection == "Y") {
            return true;
        } else if (selection == "n" || selection == "N") {
            std::cout << "Thank you!\n";
            return false;
        } else  {
            std::cerr << "Unknown value, try again: ";
        }
    }
}
