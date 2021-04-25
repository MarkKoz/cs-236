# CS 236 - Homework 5

**Course Title:** Advanced Data Structures<br/>
**Semester:** Spring 2021<br/>

## Quick Sort and Insertion Sort

Write a program to sort an array of random elements using quicksort as follows:

1. Sort the arrays using pivot as the middle element of the array.
2. Sort the arrays using pivot as the median of the first, last, and middle elements of the array.
3. Sort the arrays using pivot as the middle element of the array. However, when the size of any sub-list reduces to less than 20, sort the sub-list using insertion sort.
4. Sort the array using pivot as the median of the first, last, and middle elements of the array. When the size of any sub-list reduces to less than 20, sort the sub-list using insertion sort.
5. Calculate and display the CPU time for each of the preceding four steps.

Example of the median of the first, last, and middle elements:

```
1 2 3 4 5 6 7 8 0 (median of 1, 5, 0 is 1)
```
```
8 0 1 2 3 4 5 6 7 (median of 8, 3, 7 is 7)
```

To calculate the CPU time, use the header `<ctime>` and the `clock_t` type. It depends on the CPU of your computer; your number may not be the same as in the sample outputs below.

## Sample Output

<details>
<summary>Sample Output 1</summary>
```
Enter array size: 100000
Quick sort time, with pivot middle element = 28
Quick sort time, with pivot median element = 32
Quick sort time and insertion sort time, with pivot middle element = 30
Quick sort time and insertion sort time, with pivot median element = 28
Would you like to enter another Array size (Y / N)? Y
```
</details>

<details>
<summary>Sample Output 2</summary>
```
Enter array size: 300000
Quick sort time, with pivot middle element = 111
Quick sort time, with pivot median element = 110
Quick sort time and insertion sort time, with pivot middle element = 101
Quick sort time and insertion sort time, with pivot median element = 105
Would you like to enter another Array size (Y / N)? N
```
</details>
