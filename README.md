# CS 236 - Homework 3

**Course Title:** Advanced Data Structures<br/>
**Semester:** Spring 2021<br/>

## AVL Tree Program

Write a program to build an AVL tree by accepting the integers input from users. For each input, balance the tree and display it on the screen; you then calculate the preorder, indorder, and postoder traversals as well. There should be a menu to drive the program. It should be similar as follows:

```
                 AVL Tree Implementation
A: Insert an integer to tree and show the balanced tree at each insertion.
B: Display the balanced tree and show preorder traversal.
C: Display the balanced tree and show inorder traversal.
D: Display the balanced tree and show postorder traversal.
E: Exit
```

To be sure, your program is correctly working, use the following data to test AVL tree:

```
15, 18, 10, 7, 57, 6, 13, 12, 9, 65, 19, 16, 23
```

You should perform more test with different data sets.

## Sample Output

<details>
<summary>Sample Output 1</summary>

```
                 AVL Tree Implementation
A: Insert an integer to tree and show the balanced tree at each insertion.
B: Display the balanced tree and show preorder traversal.
C: Display the balanced tree and show inorder traversal.
D: Display the balanced tree and show postorder traversal.
E: Exit

= A

Enter integer to be added to tree: 15
Node (15) inserted

15

--------------------------------------------------
                 AVL Tree Implementation
A: Insert an integer to tree and show the balanced tree at each insertion.
B: Display the balanced tree and show preorder traversal.
C: Display the balanced tree and show inorder traversal.
D: Display the balanced tree and show postorder traversal.
E: Exit

= A

Enter integer to be added to tree: 18
Node(18) inserted

15
 ^--V
   18

--------------------------------------------------
                 AVL Tree Implementation
A: Insert an integer to tree and show the balanced tree at each insertion.
B: Display the balanced tree and show preorder traversal.
C: Display the balanced tree and show inorder traversal.
D: Display the balanced tree and show postorder traversal.
E: Exit

= A

Enter integer to be added to tree: 10
Node(10) inserted

   15
 V--^--V
10    18
```
</details>

## File Structure

A header, implementation, and main file.
