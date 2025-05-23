# 2021 Introductory C Course Work

This repository contains a compilation of assignments and projects completed for **CSE 13S: Introductory C** at the **University of California, Santa Cruz** in 2021.

The coursework covers foundational C programming concepts including:

- Basic syntax and data types  
- Control flow and functions  
- Pointers and memory management  
- File I/O  
- Structs and dynamic data structures  

This collection serves as both a record of progress and a reference for future C programming work.

---

## Assignments Overview

### Assignment 0: Hello World  
A simple introductory program that prints "Hello World" to the console, serving as the first step into C programming.

### Assignment 1: Pig Game Simulator  
This program simulates the dice game *Pigs* for 2 to 10 players. Players roll a weighted die called the "pig" and earn points based on the roll outcome. Rolling the pig on its side causes the player to lose their turn. The first player to reach or exceed 100 points wins.  
The implementation includes an enumerated `Position` type and a `Position` array as described in the assignment document.

### Assignment 2: Custom Math Library  
An implementation of six mathematical functions (`e.c`, `euler.c`, `madhava.c`, `bbp.c`, `viete.c`, and `sqrtnewton.c`) to approximate values of π and e. The program includes a test harness to compare these approximations against the standard C math library. It supports running individual or all tests, with an optional `-s` flag to display the number of terms used in each approximation.

### Assignment 3: Sorting Algorithm Comparison  
This assignment tests and compares multiple sorting algorithms under varying conditions such as array size and randomness seed. The program provides options for selecting which sorting algorithms to run, controlling output size, and viewing detailed help instructions. It also deepens understanding of pointers, structures, and abstract data types (ADTs).

### Assignment 4: Hamiltonian Path Finder  
This program uses Depth First Search (DFS) to find the shortest path through a set of locations, returning to the start vertex (Hamiltonian Path). Users can specify input/output files, enable verbose output to see every path explored, and access help documentation.

### Assignment 5: Huffman Encoder  
An implementation of the Huffman encoding algorithm for data compression, demonstrating efficient use of trees and priority queues in C.

---

Feel free to explore the code to gain insight into foundational C programming techniques and data structures.
