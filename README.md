# CS 236 - Homework 1

**Course Title:** Advanced Data Structures<br/>
**Semester:** Spring 2021<br/>

## Roman Converter Program

**Objectives:** Review object-oriented program and apply software engineering concepts.

Write a program that converts a number entered in Roman numerals to decimal form. Your program should consist of a class named `romanType`. An object of `romanType` should do the following:

* Store the number as a Roman numeral.
* Convert and store the number into decimal form.
* Print the number as a Roman numeral or decimal number as requested by the user.

#### Roman Numerals

* A larger numeral preceding a smaller numeral means addition, e.g. `LX` is `60`.
* A smaller numeral preceding a larger numeral means subtraction, e.g. `XL` is `40`.
* Test your program using the following Roman numerals: `MDCLXVI` and `MMMDCCXXIV`.

Roman | Arabic
------|-------
M | 1000
D | 500
C | 100
L | 50
X | 10
V | 5
I | 1

## Sample Output

```
Enter a roman number: MDCLXVI
The equivalent of the Roman numeral MDCLXVI is 1666
Try another number (y/n)?  Y
Enter a roman number: MMMDCCXXIV
The equivalent of the Roman numeral MMMDCCXXIV is 3724
Try another number (y/n)? N
Thank you!
```

## File Structure

```
roman.h
romanImp.cpp
romanDriver.cpp
```
