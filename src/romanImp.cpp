#include "roman.h"

#include <iostream>

romanType::romanType(const std::string& value)
    : roman_numeral_ {value}, arabic_numeral_ {to_integer()}
{ }

romanType::romanType(std::string&& value)
    : roman_numeral_ {std::move(value)}, arabic_numeral_ {to_integer()}
{ }

void romanType::print_arabic() const
{
    std::cout << "The equivalent of the Roman numeral " << roman_numeral_ << " is "
              << arabic_numeral_ << '\n';
}

void romanType::print_roman() const
{
    std::cout << "The Roman numeral is " << roman_numeral_ << '\n';
}

unsigned int romanType::to_integer() const
{
    if (roman_numeral_.empty()) {
        throw std::invalid_argument("Roman numeral string must not be empty.");
    }

    // Initialised to max to avoid subtraction at the start.
    unsigned int previous = ROMAN_TO_ARABIC.at('M');
    unsigned int integer = 0;
    unsigned int value = 0;

    for (const char character : roman_numeral_) {
        try {
            value = ROMAN_TO_ARABIC.at(character);
        } catch (const std::out_of_range&) {
            // to_integer always needs to be called to initialise arabic_numeral_. Since it needs to
            // iterate characters anyway, may as well perform the validation here too.
            throw std::invalid_argument("Roman numeral contains an invalid character.");
        }

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

const std::unordered_map<char, unsigned int> romanType::ROMAN_TO_ARABIC {
    {'M', 1000},
    {'D', 500},
    {'C', 100},
    {'L', 50},
    {'X', 10},
    {'V', 5},
    {'I', 1},
};
