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

std::size_t partition(std::vector<int>& array, std::size_t start, std::size_t end)
{
    int pivot = array[start];
    std::size_t low = start + 1;
    std::size_t high = end;

    // Keep swapping values on either side until the indices for the two sides meet.
    while (high > low) {
        // Move from left to right until low is greater than the pivot.
        while (low <= high && array[low] <= pivot) {
            ++low;
        }

        // Move from right to left until high is less than or equal to the pivot.
        while (low <= high && array[high] > pivot) {
            --high;
        }

        // Swap the values if the low/high indices haven't crossed.
        // low contains a value > than the pivot and high contains one <= the pivot.
        // Swapping them means the greater value will be moved ahead of the pivot and the smaller
        // value will be moved before the pivot.
        if (high > low) {
            std::swap(array[low], array[high]);
        }
    }

    std::swap(array[start], array[high]);
    return high;
}

void quick_sort(std::vector<int>& array, std::size_t start, std::size_t end)
{
    if (end > start) {
        std::size_t pivot = partition(array, start, end);

        // Avoid overflow since pivot is unsigned.
        if (pivot > 0) {
            quick_sort(array, start, pivot - 1);
        }

        quick_sort(array, pivot + 1, end);
    }
}

void quick_sort(std::vector<int>& array)
{
    quick_sort(array, 0, array.size() - 1);
}
