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
        stream << *(row.cend() - 1) << '\n';
    }

    return stream;
}

bool sudoku::can_fill(const index_t row, const index_t column, const cell_t value) const
{
    return false;
}

bool sudoku::in_column(const index_t column, const cell_t value) const
{
    for (const auto& row : grid_) {
        if (row.at(column) == value) {
            return true;
        }
    }

    return false;
}

bool sudoku::in_row(const index_t row, const cell_t value) const
{
    for (unsigned int current_value : grid_.at(row)) {
        if (current_value == value) {
            return true;
        }
    }

    return false;
}

bool sudoku::in_subgrid(index_t row, index_t column, const cell_t value) const
{
    row *= 3;
    column *= 3;

    for (auto row_it = grid_.cbegin() + row; row_it != grid_.cbegin() + row + 3; ++row_it) {
        auto column_it = row_it->cbegin() + column;
        for (; column_it != row_it->cbegin() + column + 3; ++column_it) {
            if (*column_it == value) {
                return true;
            }
        }
    }

    return false;
}

constexpr bool sudoku::is_empty(const index_t row, const index_t column) const
{
    return grid_.at(row).at(column) == 0;
}
