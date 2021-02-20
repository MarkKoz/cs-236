#ifndef CS_236_ROMAN_H
#define CS_236_ROMAN_H

#include <string>

/**
 * @brief Represents a Roman numeral value.
 *
 * Roman numerals have 7 digits, which have the following values:
 * - M: 1000
 * - D: 500
 * - C: 100
 * - L: 50
 * - X: 10
 * - V: 5
 * - I: 1
 *
 * A larger numeral preceding a smaller numeral means addition.
 * A smaller numeral preceding a larger numeral means subtraction.
 */
class romanType {
public:
    /**
     * @brief Construct a @c romanType from a string.
     *
     * Copy the string into the new object and then convert it to an integer.
     *
     * @param romanNumeral The string representing the Roman numeral value.
     */
    explicit romanType(const std::string& romanNumeral);

    /**
     * @brief Construct a @c romanType from a string.
     *
     * Move the string into the new object and then convert it to an integer.
     *
     * @param romanNumeral The string representing the Roman numeral value.
     */
    explicit romanType(std::string&& romanNumeral);

    /**
     * @brief Print the underlying value using Arabic numerals.
     */
    void printArabic() const;

    /**
     * @brief Print the underlying value using Roman numerals.
     */
    void printRoman() const;

private:
    /**
     * @brief Convert the Roman numeral to an integer.
     *
     * @return The integer representation of the Roman numeral.
     */
    unsigned int toInteger() const;

    std::string romanNumeral;
    unsigned int arabicNumeral;
};

#endif
