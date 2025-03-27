## README.md  
README.md will list each file submitted, together with a brief description of its role in the project.  
README.md is essentially a table of contents for the project, and nothing more.  

## List.c    
This C file implements the List Abstract Data Type (ADT) using a doubly linked list with a cursor. It includes constructor and destructor functions, as well as various access and data manipulation functions.  

## List.h  
This header file declares the functions defined in List.c.  

## Graph.c  
This C file implements the Graph structure using an adjacency list representation. It defines features such as vertices, edges, and arcs. The file includes constructor and destructor functions, access functions, and data manipulation functions. A Breadth-First Search (BFS) algorithm is implemented to explore vertex neighbors.  

## Graph.h  
This header file declares the functions defined in Graph.c.  

## GraphTest.c  
This C file tests the functionality of all functions implemented in Graph.c. The test format is based on Patrick Tantalo's GraphClient code.  

## FindPath.c  
This C file reads an input file and writes to an output file to process graph data, including vertices, edges, and arcs. It computes and outputs the shortest path between specified vertices. The file I/O system is adapted from Patrick Tantalo's FileIO code.  

## Makefile  
A Makefile is a file used by the make utility to automate the process of compiling and building a program. It defines rules for how to compile and link source code files into an executable.  
