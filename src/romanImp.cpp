#include <iostream>
#include "roman.h"

romanType::romanType(const std::string& value)
    : romanNumeral(value), arabicNumeral(toInteger()) { }

romanType::romanType(std::string&& value)
    : romanNumeral(std::move(value)), arabicNumeral(toInteger()) { }

void romanType::printArabic() const {
    std::cout << "The equivalent of the Roman numeral " << romanNumeral << " is "
        << arabicNumeral << '\n';
}

void romanType::printRoman() const {
    std::cout << "The Roman numeral is " << romanNumeral << '\n';
}

unsigned int romanType::toInteger() const {
    return 0;
}
