#include "sort.h"

void insertion_sort(std::vector<int>& array)
{
    // Start at 1 because the 0th element is already considered sorted.
    for (std::size_t unsorted_i = 1; unsorted_i < array.size(); ++unsorted_i) {
        int item = array[unsorted_i];
        std::size_t sorted_i = unsorted_i; // One past the end of the sorted sub-list.

        // Start at the end of the sorted sublist and go backwards until the sorted position for
        // `item` is found or the start of the sub-list is reached.
        for (; sorted_i > 0 && array[sorted_i - 1] > item; --sorted_i) {
            // Move back by one position to make space for `item` in the sorted sub-list.
            array[sorted_i] = array[sorted_i - 1];
        }

        // Insert the `item` into its correct position within the sorted sub-list.
        array[sorted_i] = item;
    }
}
