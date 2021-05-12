# CS 236 - Homework 6

**Course Title:** Advanced Data Structures<br/>
**Semester:** Spring 2021<br/>

## Shortest Path in the Airline Network

Write a program to find the shortest route in an airline network from a given start city to a given destination city using Depth First Search. An unweighted digraph represented by its adjacency list is used for the network, and the information needed to construct is read from a network file.

### Network File

Content is in [`network_file.txt`](res/network_file.txt).

* The order of cities are arranged from LA(1), SAN(2), DEN(3), CHI(4), BOS(5), NYK(6), MIA(7), NOL(8).
* The first digit is the number of out-degrees; other digits are the destinations of out-degrees.
    * Example: New Orleans - 2 1 7: New Orleans connects to LA (1) and MIA (7).

## Sample Output

<details>
<summary>Sample Output 1</summary>

```
Enter name of network file: c:\networkfile.txt
The Digraph's Adjacency-List Representation:
1: Los_Angeles--3  4  6
2: San_Francisco--1  3  4
3: Denver--1  2  3
4: Chicago--3  8
5: Boston--4  6
6: New_York--4  7  8
7: Miami--8  3  5
8: New_Orleans--1  7

Number of start city? 1
Number of destination? 2
Shortest path from Los Angeles to San Francisco is:
  1 Los_Angeles
      |
      v
  3 Denver
      |
      v
  2 San_Francisco
      |
      v
  2 San_Francisco

More (Y or N)?Y
Number of start city? 6
Number of destination? 4
Shortest path from New York to Chicago is:
  6 New_York
      |
      v
  4 Chicago
      |
      v
  4 Chicago

More (Y or N)? n
```
</details>
