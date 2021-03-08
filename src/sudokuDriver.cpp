#include "sudoku.h"

int main()
{
    std::cout << "Enter a partially filled sudoku grid: ";

    sudoku::grid_t grid {};
    for (auto& row : grid) {
        for (unsigned int& cell : row) {
            // Fill in the grid with the user's input.
            // Assume the value for each cell is valid.
            std::cin >> std::ws >> cell;
        }
    }

    sudoku puzzle(grid);
    std::cout << "\nGrid before solution:\n\n" << puzzle << '\n';

    // Try to solve the puzzle.
    if (puzzle.solve()) {
        std::cout << "Solution:------------------\n\n" << puzzle;
    } else {
        std::cout << "No solutions.\n";
    }

    return 0;
}
