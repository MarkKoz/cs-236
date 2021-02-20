#include <iostream>
#include "roman.h"

romanType::romanType(const std::string& romanNumeral)
    : romanNumeral(romanNumeral), arabicNumeral(toInteger()) { }

romanType::romanType(std::string&& romanNumeral)
    : romanNumeral(std::move(romanNumeral)), arabicNumeral(toInteger()) { }

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
