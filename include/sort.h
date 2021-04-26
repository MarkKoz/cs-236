#ifndef CS_236_02_SORT_H
#define CS_236_02_SORT_H

#include <cstddef>
#include <vector>

enum PivotSelection
{
    middle,
    median
};

void insertion_sort(std::vector<int>& array, std::size_t start, std::size_t end);

std::size_t partition(std::vector<int>& array, std::size_t start, std::size_t end);

void quick_sort(
    std::vector<int>& array,
    std::size_t start,
    std::size_t end,
    PivotSelection pivot_selection,
    bool use_insertion_sort);

void quick_sort(
    std::vector<int>& array,
    PivotSelection pivot_selection = PivotSelection::middle,
    bool use_insertion_sort = false);

void select_pivot(
    std::vector<int>& array, std::size_t start, std::size_t end, PivotSelection pivot_selection);

#endif
