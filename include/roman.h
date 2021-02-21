#ifndef CS_236_ROMAN_H
#define CS_236_ROMAN_H

#include <string>
#include <unordered_map>

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
class romanType
{
public:
    /**
     * @brief Construct a @c romanType from a string.
     *
     * Copy the string into the new object and then convert it to an integer.
     *
     * @param value The string representing the Roman numeral value.
     *
     * @throw std::invalid_argument The roman numeral is empty or contains an invalid character.
     */
    explicit romanType(const std::string& value);

    /**
     * @brief Construct a @c romanType from a string.
     *
     * Move the string into the new object and then convert it to an integer.
     *
     * @param value The string representing the Roman numeral value.
     *
     * @throw std::invalid_argument The roman numeral is empty or contains an invalid character.
     */
    explicit romanType(std::string&& value);

    /**
     * @brief Print the underlying value using Arabic numerals.
     */
    void print_arabic() const;

    /**
     * @brief Print the underlying value using Roman numerals.
     */
    void print_roman() const;

private:
    /**
     * @brief Convert the Roman numeral to an integer.
     *
     * @throw std::invalid_argument The roman numeral is empty or contains an invalid character.
     * @return The integer representation of the Roman numeral.
     */
    [[nodiscard]] unsigned int to_integer() const;

    std::string roman_numeral_;
    unsigned int arabic_numeral_;

    static const std::unordered_map<char, unsigned int> ROMAN_TO_ARABIC;
};

#endif
