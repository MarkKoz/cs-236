#include <array>

class sudoku
{
public:
    typedef unsigned int cell_t;
    typedef std::array<std::array<cell_t, 9>, 9> grid_t;

    /**
     * @brief Construct an empty @c sudoku puzzle.
     *
     * Initialise the grid with zeros.
     */
    sudoku();

    /**
     * @brief Construct a @c sudoku puzzle from a grid.
     *
     * Copy the grid into the new object.
     *
     * @param grid The 9×9 grid to use as the puzzle.
     */
    explicit sudoku(const grid_t& grid);

    // No rvalue constructor because grid_t is a trivially-copyable type.

    /**
     * @brief Print the sudoku grid.
     */
    void print() const;

    /**
     * @brief Solve the sudoku puzzle.
     *
     * @return @c true if the grid could be solved (a solution exists); @c false otherwise.
     */
    bool solve();

private:
    typedef grid_t::size_type index_t;

    /**
     * @brief Determine if filling a specific cell with a given value is valid.
     *
     * @param row The row the cell lies in.
     * @param column The column the cell lies in.
     * @param value The value to test.
     *
     * @return @c true if the value is valid; @c false otherwise.
     */
    bool can_fill(index_t row, index_t column, cell_t value) const;

    /**
     * @brief Determine if a value is in a column.
     *
     * @param column The column to search within.
     * @param value The value to search for.
     *
     * @return @c true if the value exists in the column; @c false otherwise.
     */
    bool in_column(index_t column, cell_t value) const;

    /**
     * @brief Determine if a value is in a row.
     *
     * @param row The row to search within.
     * @param value The value to search for.
     *
     * @return @c true if the value exists in the row; @c false otherwise.
     */
    bool in_row(index_t row, cell_t value) const;

    /**
     * @brief Determine if a value is in a subgrid.
     *
     * @param row The row the subgrid lies in. This is an index within the outer 3×3 grid.
     * @param column The column the subgrid lies in. This is an index within the outer 3×3 grid.
     * @param value The value to search for.
     *
     * @return @c true if the value exists in the subgrid; @c false otherwise.
     */
    bool in_subgrid(index_t row, index_t column, cell_t value) const;

    /**
     * @brief Determine if a cell is empty.
     *
     * @param row The row the cell lies in.
     * @param column The column the cell lies in.
     *
     * @raise std::out_of_range The row and/or column are not within the range of the grid.
     *
     * @return @c true if the cell is empty; @c false otherwise.
     */
    [[nodiscard]] constexpr bool is_empty(index_t row, index_t column) const;

    grid_t grid_;
};
