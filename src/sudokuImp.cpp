#include "sudoku.h"

sudoku::sudoku() : grid_ {} { }

sudoku::sudoku(const grid_t& grid) : grid_ {grid} { }

bool sudoku::solve()
{
    return false;
}

std::ostream& operator<<(std::ostream& stream, const sudoku& puzzle)
{
    for (const auto& row : puzzle.grid_) {
        for (auto iterator = row.cbegin(); iterator != row.cend() - 1; ++iterator) {
            stream << *iterator << " ";
        }

        // Write the last element separately to avoid a trailing delimiter.
        stream << *(row.cend() -1) << '\n';
    }

    return stream;
}

bool sudoku::can_fill(const index_t row, const index_t column, const cell_t value) const
{
    return false;
}

bool sudoku::in_column(const index_t column, const cell_t value) const
{
    return false;
}

bool sudoku::in_row(const index_t row, const cell_t value) const
{
    return false;
}

bool sudoku::in_subgrid(const index_t row, const index_t column, const cell_t value) const
{
    return false;
}

constexpr bool sudoku::is_empty(const index_t row, const index_t column) const
{
    return grid_.at(row).at(column) == 0;
}
