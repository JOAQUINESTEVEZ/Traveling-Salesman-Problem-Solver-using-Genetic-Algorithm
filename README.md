# Traveling Salesman Problem Solver using Genetic Algorithm
// Author: Joaquin Estevez
// Year: 2023

## Overview

The Traveling Salesman Problem (TSP) is a classic optimization problem that has
practical applications in various fields, including logistics, transportation,
and manufacturing. In the TSP, a salesperson is tasked with finding the
shortest possible route that visits a set of cities and returns to the starting
city. The objective is to minimize the total distance traveled while ensuring
that each city is visited exactly once. This problem is known to be NP-hard,
meaning that finding the optimal solution becomes computationally infeasible as
the number of cities increases.

Various techniques and algorithms have been developed to tackle the TSP, and
one of the effective approaches is the use of Genetic Algorithms (GA). Genetic
Algorithms are heuristic optimization methods inspired by the principles of
natural selection and evolution. They provide a powerful means to search for
near-optimal solutions in complex and combinatorial optimization problems like
the TSP.

This project is dedicated to solving the Traveling Salesman Problem using a
Genetic Algorithm implemented in C++. The primary goal is to employ the GA to
find a near-optimal tour for the salesperson that minimizes the total distance
traveled. The project will include the development of a C++ program that reads
input data representing the city graph, applies the Genetic Algorithm to find
an approximate solution, and outputs the best tour found along with its total
distance.


## Project Description

### Traveling Salesman Problem (TSP)

The Traveling Salesman Problem (TSP) is a fundamental combinatorial optimization problem characterized by the following key aspects:

- **Shortest Possible Tour**: The primary objective of the TSP is to find the
  shortest possible tour that enables a salesperson to visit a predefined set
  of cities exactly once and return to the starting city. In this context, a
  "tour" refers to the sequence in which the cities are visited, forming a
  closed loop.

- **Cities as Nodes**: In the TSP, the cities are typically represented as
  nodes or vertices in a graph. Each city is connected to every other city
  through edges or arcs, and these connections define the distances or edge
  weights between cities. These distances represent the cost or distance
  associated with traveling from one city to another.

- **Permutation of Cities**: The fundamental goal of the TSP is to determine a
  permutation of cities that results in the minimum total distance traveled.
  This permutation represents the optimal order in which the cities should be
  visited to minimize the salesperson's travel distance. It is worth noting
  that the starting and ending point of the tour is usually the same city, as
  the salesperson returns to the initial location after visiting all cities.


### Genetic Algorithm (GA)

- The Genetic Algorithm is a heuristic optimization technique inspired by the process of natural selection.
- GA uses the principles of selection, crossover (recombination), mutation, and population evolution to search for optimal solutions.
- In this project, the GA is used to evolve and improve solutions to the TSP.

#### General Steps of Genetic Algorithm

The Genetic Algorithm (GA) employed to solve the Traveling Salesman Problem (TSP) follows a series of well-defined steps to iteratively evolve and improve candidate solutions:

1. **Initialization**: At the beginning of the GA process, an initial
   population of candidate solutions, also known as tours, is created. In the
   context of the TSP, this involves generating a set of random permutations of
   cities. Each permutation represents a different tour.

2. **Selection**: The selection step involves choosing parent solutions from
   the current population based on their fitness, which in the case of the TSP,
   corresponds to the shortness of the tour. The project employs the tournament
   selection method, where individuals are randomly grouped into tournaments,
   and the fittest individuals from each tournament are selected as parents for
   the next generation.

3. **Crossover (Recombination)**: In the crossover step, offspring solutions
   are created by combining genetic material from two parent solutions. For
   this project, ordered crossover (also known as partially mapped crossover)
   is used. It involves selecting a segment of one parent's tour and filling in
   the remaining cities with the order from the other parent's tour. The
   crossover rate parameter is used to control the likelihood of crossover
   occurring.

4. **Mutation**: Mutation introduces small random changes into some offspring
   solutions. In this project, swap mutation is applied, which means that with
   a certain mutation rate, two cities in the tour are randomly selected and
   swapped. This introduces diversity and helps avoid getting stuck in local
   optima.

5. **Replacement**: In the replacement step, old solutions in the current
   population are replaced with the new offspring solutions. The goal is to
   maintain the population size and replace less fit solutions with potentially
   better ones.

6. **Termination**: The iterative process of selection, crossover, mutation,
   and replacement is repeated for a fixed number of generations or until a
   termination criterion is met. The termination criterion could be a maximum
   number of generations, convergence of the best tour found, or a time limit.
   In this project, we will use the number of generations for simplicity.


### Input CSV File

To facilitate the Traveling Salesman Problem (TSP) solving process, it's
essential to efficiently handle the input CSV file containing connectivity
information. The following steps outline how to process the data:

1. **Input File Format**: The provided input CSV file has the following format:
   - The file contains 20 lines of 20 comma-separated double values.
   - The values represent distances or costs between cities in a symmetric
     manner over the diagonal line. It means that the city graph is an
     undirected graph.
   - Assuming that all cities are connected, there are no missing values in the
     matrix.


### Baseline Brute Force Algorithm

A baseline brute force algorithm and its driver have been provided as a
reference and for comparison purposes. The brute force algorithm exhaustively
explores all possible permutations of cities to find the optimal tour. While it
is not suitable for large instances of the TSP, it serves as a benchmark for
evaluating the effectiveness of the Genetic Algorithm (GA) solution.

In the provided codebase, the brute force algorithm is encapsulated in a class
and can be used for TSP problem-solving.

You can always find the best result using the brute force algorithm.


### USAGE
- Under WSL, run the "make" command.
- run "./main", followed by the csv file (a cities.csv is included in the project), and a number of cities parameter (n up to 20) to experience with different number of cities.
- Example: "./main cities.csv 6"
- Execute "make clean" after using the program.