#include <string>
#include <iostream>

int main() {
    bool stop = false;
    std::string selection;

    while (!stop) {
        std::cout << "Enter a roman numeral: ";
        std::getline(std::cin, selection);

        std::cout << "The equivalent of the roman numeral is \n";

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
