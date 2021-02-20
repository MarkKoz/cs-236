#include <iostream>
#include "roman.h"

romanType::romanType(const std::string& value)
    : romanNumeral{value}, arabicNumeral{toInteger()} { }

romanType::romanType(std::string&& value)
    : romanNumeral{std::move(value)}, arabicNumeral{toInteger()} { }

void romanType::printArabic() const {
    std::cout << "The equivalent of the Roman numeral " << romanNumeral << " is "
        << arabicNumeral << '\n';
}

void romanType::printRoman() const {
    std::cout << "The Roman numeral is " << romanNumeral << '\n';
}

unsigned int romanType::toInteger() const {
    unsigned int previous = UINT_MAX;  // Initialised to max to avoid subtraction at the start.
    unsigned int integer = 0;
    unsigned int value;

    for (const char character : romanNumeral) {
        value = romanToArabic.at(character);
        integer += value;

        if (previous < value) {
            // Subtract previous twice because it was already added.
            // Ex: IV would add 1 first but then need to add 3 to make the total 4.
            integer -= 2 * previous;
        }

        previous = value;
    }

    return integer;
}

std::unordered_map<char, unsigned int> romanType::romanToArabic {
    {'M', 1000},
    {'D', 500},
    {'C', 100},
    {'L', 50},
    {'X', 10},
    {'V', 5},
    { 'I', 1},
};
