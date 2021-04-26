#ifndef CS_236_02_SORT_H
#define CS_236_02_SORT_H

#include <cstddef>
#include <vector>

/**
 * @brief The type of algorithm to use to select a pivot for a quick sort.
 */
enum PivotSelection
{
    // Select the middle element of the sub-list.
    middle,
    // Select the median of the start, end, and middle of the sub-list.
    median,
};

/**
 * @brief Perform an insertion sort on the given range of elements in a vector of integers.
 *
 * @param vector The vector to sort.
 * @param start The index of the first item in the sub-vector to sort.
 * @param end The index of the last item in the sub-vector to sort.
 */
void insertion_sort(std::vector<int>& vector, std::size_t start, std::size_t end);

/**
 * @brief Partition a vector of integers around a pivot point for a quick sort.
 *
 * Partition items such that all items to the left are smaller than the pivot and all items to the
 * right are greater than the pivot.
 *
 * Use the item at the @c start index as the pivot.
 *
 * @param vector The vector to partition.
 * @param start The index of the first item in the sub-vector to partition.
 * @param end The index of the last item in the sub-vector to partition.
 *
 * @return The index of the pivot.
 */
std::size_t partition(std::vector<int>& vector, std::size_t start, std::size_t end);

/**
 * @brief Quick sort a sub-vector of integer..
 *
 * @param vector The vector to sort.
 * @param start The index of the first item in the sub-vector to sort.
 * @param end The index of the last item in the sub-vector to sort.
 * @param pivot_selection The way the pivot should be chosen.
 * @param use_insertion_sort @c true to use insertion sort on sub-vectors with < 20 items.
 */
void quick_sort(
    std::vector<int>& vector,
    std::size_t start,
    std::size_t end,
    PivotSelection pivot_selection,
    bool use_insertion_sort);

/**
 * @brief Quick sort a vector of integer.
 *
 * @param vector The vector to sort.
 * @param pivot_selection The way the pivot should be chosen.
 * @param use_insertion_sort @c true to use insertion sort on sub-vectors with < 20 items.
 */
void quick_sort(
    std::vector<int>& vector,
    PivotSelection pivot_selection = PivotSelection::middle,
    bool use_insertion_sort = false);

/**
 * @brief Selects the pivot to use to sort the given vector.
 *
 * Move the pivot item to the @c start index by swapping it with the element at @c start.
 *
 * @param vector The vector being sorted.
 * @param start The index of the first item in the sub-vector being sorted.
 * @param end The index of the last item in the sub-vector being sorted.
 * @param pivot_selection The way the pivot should be chosen.
 */
void select_pivot(
    std::vector<int>& vector, std::size_t start, std::size_t end, PivotSelection pivot_selection);

#endif
