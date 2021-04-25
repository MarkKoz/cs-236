#ifndef CS_236_02_SORT_H
#define CS_236_02_SORT_H

#include <cstddef>
#include <vector>

void insertion_sort(std::vector<int>& array);

std::size_t partition(std::vector<int>& array, std::size_t start, std::size_t end);

void quick_sort(std::vector<int>& array, std::size_t start, std::size_t end);

void quick_sort(std::vector<int>& array);

#endif
