# CS 236 - Homework 4

**Course Title:** Advanced Data Structures<br/>
**Semester:** Spring 2021<br/>

## Red-Black Tree Insertion

Write a program to insert a set of integers into an empty Red-Black tree by applying the Red-Black tree insertion algorithm that we have learned in class (see the PDF lecture file). The program should display the final tree on the screen.

## Sample Output

<details>
<summary>Sample Output 1</summary>

Given integers: 9, 18, 7, 14, 17, 45, 26, 35, 50, 2, 1, 60  (you can terminate the input with a negative integer i.e. -1 or -9)

```
Inserting nodes into an empty Red Black Tree.
9 18 7 14 17 45 26 35 50 2 1 60

Final balanced red-black tree:

ROOT----17(BLACK)
           L----9(BLACK)
           |  L----2(BLACK)
           |  |  L----1(RED)
           |  |  R----7(RED)
           |  R----14(BLACK)
           R----26(BLACK)
              L----18(BLACK)
              R----45(RED)
                 L----35(BLACK)
                 R----50(BLACK)
                    R----60(RED)
```
</details>

## File Structure

A header, implementation, and main file.
