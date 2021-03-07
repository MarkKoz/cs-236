#include "sudoku.h"

sudoku::sudoku() : grid_ {} { }

sudoku::sudoku(const grid_t& grid) : grid_ {grid} { }

bool sudoku::solve()
{
    return solve_recursively(0, 0);
}

bool sudoku::solve_recursively(index_t row, index_t column)
{
    // Go to the next row when the end of the row is reached.
    if (column == 9) {
        ++row;
        column = 0;
    }

    if (row == 9) {
        // The puzzle is solved since the algorithm has gone through every cell.
        return true;
    }

    if (!is_empty(row, column)) {
        // The current cell is already filled; move on to the next cell.
        return solve_recursively(row, column + 1);
    }

    // Try filling the cell with every value from 1 to 9.
    for (cell_t value = 1; value <= 9; ++value) {
        if (can_fill(row, column, value)) {
            grid_.at(row).at(column) = value;

            if (solve_recursively(row, column + 1)) {
                // A solution was found using the current value; no need to try the next.
                return true;
            } else {
                // The current value didn't lead to a solution. Discard the set value to avoid
                // it interfering with the can_fill check for subsequent values.
                grid_.at(row).at(column) = 0;
            }
        }
    }

    // No valid value was found for the cell.
    // Therefore, the puzzle in unsolvable in its current state.
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
    return !in_row(row, value) && !in_column(column, value)
        && !in_subgrid(row / 3, column / 3, value);
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
