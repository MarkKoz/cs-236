#include "sort.h"

#include <algorithm>
#include <cassert>
#include <ctime>
#include <iostream>
#include <random>

/**
 * @brief Prompt for whether to convert another input.
 *
 * Keep prompting for an input until a valid input ('y' or 'n', case-insensitive) is given.
 *
 * @return @c true to prompt again; @c false otherwise.
 */
bool prompt_retry();

/**
 * @brief Run a quick sort and return the approximate processor time taken to execute it.
 *
 * @tparam Args The type of the arguments to forward.
 * @param args The arguments to forwards to @c quick_sort.
 *
 * @return The approximate processor time, in nanoseconds, taken to execute the sort.
 */
template<class... Args>
double benchmark_quick_sort(Args&&... args);

int main()
{
    // Use a constant seed to get consistent data for benchmarks.
    std::minstd_rand random_engine(1);
    std::size_t size = 0;

    do {
        std::cout << "Enter array size: ";
        std::cin >> std::ws >> size;

        // Fill a vector with random values.
        std::vector<int> array(size);
        std::generate(array.begin(), array.end(), random_engine);

        // Save a copy so the value can be restored.
        std::vector<int> array_copy = array;

        double time = benchmark_quick_sort(array, PivotSelection::middle, false);
        std::cout << "Quick sort time, with pivot middle element = " << time << " ms\n";
        assert(std::is_sorted(array.cbegin(), array.cend()));

        array = array_copy;
        time = benchmark_quick_sort(array, PivotSelection::middle, true);
        std::cout << "Quick sort time, with pivot median element = " << time << " ms\n";
        assert(std::is_sorted(array.cbegin(), array.cend()));

        array = array_copy;
        time = benchmark_quick_sort(array, PivotSelection::median, false);
        std::cout << "Quick + insertion sort time, with pivot middle element = " << time << " ms\n";
        assert(std::is_sorted(array.cbegin(), array.cend()));

        array = array_copy;
        time = benchmark_quick_sort(array, PivotSelection::median, true);
        std::cout << "Quick + insertion sort time, with pivot median element = " << time << " ms\n";
        assert(std::is_sorted(array.cbegin(), array.cend()));
    } while (prompt_retry());

    return 0;
}

template<class... Args>
double benchmark_quick_sort(Args&&... args)
{
    std::clock_t start = std::clock();
    quick_sort(std::forward<Args>(args)...);

    // Convert to milliseconds.
    // It may already be in milliseconds, but this is not a guarantee (implementation-defined).
    return 1000.0 * (std::clock() - start) / CLOCKS_PER_SEC;
}

bool prompt_retry()
{
    std::string selection;

    std::cout << "Would you like to enter another array size (y/n)? ";
    while (true) {
        std::cin >> std::ws >> selection;

        if (selection == "y" || selection == "Y") {
            return true;
        } else if (selection == "n" || selection == "N") {
            return false;
        } else {
            std::cerr << "Unknown value, try again: ";
        }
    }
}
