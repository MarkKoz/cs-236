# CS 236 - Homework 2

**Course Title:** Advanced Data Structures<br/>
**Semester:** Spring 2021<br/>

## Solving Sudoku Puzzles

The goal of Sudoku is to assign digits to the empty cells so that every row, column, and sub-grid contains exactly one instance of the digits from 1 to 9. The starting cells are assigned to constrain the puzzle such that there is only one way to finish it. Sudoku solvers pride themselves on the fact that there is no need to "guess" to solve the puzzle, the careful application of logic will lead you to the solution.

### Recursive Backtracking Pseudocode

1. Find row, we find the first empty grid slot.
2. Next we find the first number, between 1 to 9, that can be placed in this slot.
    * Before placing a number in an empty slot, we must check that the number does not appear in the row, column, and the 3 x 3 grid containing the slot.
3. After placing a number the first empty slot, we find the next empty slot and try to place a number in that slot.
    * If a number cannot be placed in a slot, then we must backtrack to the previous slot, where the number was placed, place a different number, and continue.
4. If we arrive at a slot where no number can be placed, then the Sudoku problem has no solutions.

You are given the header file, you need to write an implementation file and a driver file. You can modify the `sudoku` class (header file) as you wish.

## Sample Output

<details>
<summary>Sample Output 1</summary>

```
Enter partially filled sudoku grid:

0 8 0 1 7 0 0 0 3
0 2 0 0 0 0 0 0 9
0 9 0 0 3 0 5 4 8
0 0 4 0 9 0 0 0 0
0 0 0 7 0 3 0 0 0
0 0 0 0 1 0 4 0 0
6 1 9 0 8 0 0 5 0
7 0 0 0 0 0 0 8 0
2 0 0 0 6 4 0 1 0

grid before solution:
0 8 0 1 7 0 0 0 3
0 2 0 0 0 0 0 0 9
0 9 0 0 3 0 5 4 8
0 0 4 0 9 0 0 0 0
0 0 0 7 0 3 0 0 0
0 0 0 0 1 0 4 0 0
6 1 9 0 8 0 0 5 0
7 0 0 0 0 0 0 8 0
2 0 0 0 6 4 0 1 0

Solution:------------------

4 8 5 1 7 9 6 2 3
3 2 6 4 5 8 1 7 9
1 9 7 6 3 2 5 4 8
8 3 4 2 9 5 7 6 1
5 6 1 7 4 3 8 9 2
9 7 2 8 1 6 4 3 5
6 1 9 3 8 7 2 5 4
7 4 3 5 2 1 9 8 6
2 5 8 9 6 4 3 1 7
```
</details>

<details>
<summary>Sample Output 2</summary>

```
Enter partially filled sudoku grid:

1 9 5 6 7 2 4 3 8
2 0 8 0 4 3 7 5 0
0 0 0 0 0 0 0 2 0
0 0 0 0 9 1 3 0 5
0 0 4 0 0 0 1 0 0
5 0 9 3 6 0 0 0 0
0 5 1 0 0 0 0 0 0
0 4 2 1 5 0 8 0 9
0 0 0 0 2 4 0 0 0

grid before solution:
1 9 5 6 7 2 4 3 8
2 0 8 0 4 3 7 5 0
0 0 0 0 0 0 0 2 0
0 0 0 0 9 1 3 0 5
0 0 4 0 0 0 1 0 0
5 0 9 3 6 0 0 0 0
0 5 1 0 0 0 0 0 0
0 4 2 1 5 0 8 0 9
0 0 0 0 2 4 0 0 0

Solution:------------------

1 9 5 6 7 2 4 3 8
2 6 8 9 4 3 7 5 1
4 7 3 5 1 8 9 2 6
8 2 7 4 9 1 3 6 5
6 3 4 2 8 5 1 9 7
5 1 9 3 6 7 2 8 4
7 5 1 8 3 9 6 4 2
3 4 2 1 5 6 8 7 9
9 8 6 7 2 4 5 1 3
```
</details>

<details>
<summary>Sample Output 3</summary>

```
Enter partially filled sudoku grid:

0 0 3 0 0 2 0 0 0
2 6 0 0 9 4 0 0 0
0 0 8 5 3 0 0 0 6
0 5 6 0 0 0 1 9 0
0 0 0 0 0 0 0 0 0
0 2 1 0 0 0 5 7 0
6 0 0 0 2 5 4 0 0
0 0 0 9 1 0 0 6 7
0 0 8 6 0 0 9 0 0

grid before solution:
0 0 3 0 0 2 0 0 0
2 6 0 0 9 4 0 0 0
0 0 8 5 3 0 0 0 6
0 5 6 0 0 0 1 9 0
0 0 0 0 0 0 0 0 0
0 2 1 0 0 0 5 7 0
6 0 0 0 2 5 4 0 0
0 0 0 9 1 0 0 6 7
0 0 8 6 0 0 9 0 0

No solutions.
```
</details>

## File Structure

```
sudoku.h
sudokuImp.cpp
sudokuDriver.cpp
```
