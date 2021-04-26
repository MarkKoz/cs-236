#include "sort.h"

#include <cassert>
#include <stdexcept>

void insertion_sort(std::vector<int>& vector, std::size_t start, std::size_t end)
{
    // Start at 1 because the 0th element is already considered sorted.
    for (std::size_t unsorted_i = start + 1; unsorted_i <= end; ++unsorted_i) {
        int item = vector[unsorted_i];
        std::size_t sorted_i = unsorted_i; // One past the end of the sorted sub-list.

        // Start at the end of the sorted sublist and go backwards until the sorted position for
        // `item` is found or the start of the sub-list is reached.
        for (; sorted_i > start && vector[sorted_i - 1] > item; --sorted_i) {
            // Move back by one position to make space for `item` in the sorted sub-list.
            vector[sorted_i] = vector[sorted_i - 1];
        }

        // Insert the `item` into its correct position within the sorted sub-list.
        vector[sorted_i] = item;
    }
}

std::size_t partition(std::vector<int>& vector, std::size_t start, std::size_t end)
{
    int pivot = vector[start];
    std::size_t low = start + 1;
    std::size_t high = end;

    // Keep swapping values on either side until the indices for the two sides meet.
    while (true) {
        // Move from left to right until low is greater than the pivot.
        while (low <= high && vector[low] <= pivot) {
            ++low;
        }

        // Move from right to left until high is less than or equal to the pivot.
        while (low <= high && vector[high] > pivot) {
            --high;
        }

        // Swap the values if the low/high indices haven't crossed.
        // low contains a value > than the pivot and high contains one <= the pivot.
        // Swapping them means the greater value will be moved ahead of the pivot and the smaller
        // value will be moved before the pivot.
        if (high > low) {
            std::swap(vector[low], vector[high]);
        } else {
            break;
        }
    }

    std::swap(vector[start], vector[high]);
    return high;
}

void quick_sort(
    std::vector<int>& vector,
    std::size_t start,
    std::size_t end,
    PivotSelection pivot_selection,
    bool use_insertion_sort)
{
    if (end > start) {
        if (use_insertion_sort && end - start < 19) {
            insertion_sort(vector, start, end);
        } else {
            select_pivot(vector, start, end, pivot_selection);
            std::size_t pivot = partition(vector, start, end);

            // Avoid overflow since pivot is unsigned.
            if (pivot > 0) {
                quick_sort(vector, start, pivot - 1, pivot_selection, use_insertion_sort);
            }

            quick_sort(vector, pivot + 1, end, pivot_selection, use_insertion_sort);
        }
    }
}

void quick_sort(std::vector<int>& vector, PivotSelection pivot_selection, bool use_insertion_sort)
{
    quick_sort(vector, 0, vector.size() - 1, pivot_selection, use_insertion_sort);
}

void select_pivot(
    std::vector<int>& vector, std::size_t start, std::size_t end, PivotSelection pivot_selection)
{
    std::size_t pivot_index = start + ((end - start) / 2); // Calculate the middle.
    assert(pivot_index >= start);
    assert(pivot_index <= end);

    if (pivot_selection == PivotSelection::median) {
        // Quickly find the index for the median of the start, end, and middle.
        int delta = vector[start] - vector[end]; // Positive if start is greater.

        if (delta * (vector[end] - vector[pivot_index]) > 0) {
            pivot_index = end;
        } else if (delta * (vector[start] - vector[pivot_index]) < 0) {
            pivot_index = start;
        }
    } else if (pivot_selection != PivotSelection::middle) {
        throw std::invalid_argument("Unsupported PivotSelection.");
    }

    // Swap the pivot to the start.
    std::swap(vector[start], vector[pivot_index]);
}
