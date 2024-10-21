# Parallel Computing Project

This repository contains solutions to various parallel computing problems using MPI and OpenMP. These projects were completed as part of Prof. Scott Piersall's Parallel Computing course (COP6616) in Fall 2024 at the University of North Florida (UNF).

## Overview

The repository includes solutions to the following problems:
1. **Problem 1: Matrix-Vector Multiplication Using MPI**
   - Implement an MPI program to perform matrix-vector multiplication, utilizing MPI's `Scatter` and `Gather` operations. Analyze the speedup achieved through parallelization.

2. **Problem 3: Computing Euclidean Distance Using OpenMP**
   - Compute the Euclidean distance between two N-dimensional points using parallel processing to enhance performance.

3. **Problem 4: Finding Prime Numbers Using MPI**
   - Develop an MPI program to find and print all prime numbers up to 2,500,000, distributing the workload evenly among processes and analyzing performance improvements.

Detailed instructions for running each solution can be found in the `readme` directory.

## Prerequisites

To run these programs, you will need access to a computing cluster with the following installed:
- **GCC**: A C compiler for compiling the programs.
- **OpenMPI**: An implementation of the Message Passing Interface for running MPI programs.
- **SLURM**: A workload manager for submitting and managing batch jobs.

## Purpose

The purpose of this assignment is to explore how parallelization can enhance the efficiency of serial programs. It also examines the potential overhead introduced by using an excessive number of processes relative to the problem size.

## Getting Started

1. **Clone the Repository**:
```bash
git clone https://github.com/Windz-GameDev/COP6616_Assignment2_MPI_Experiments cd COP6616_Assignment2_MPI_Experiments
```

2. **Navigate to the Problem Directory**:
   - Each problem has its own directory with specific instructions in the corresponding README file in the readme directory.

3. **Follow the Instructions**:
   - Refer to the README files for each problem for detailed setup and execution instructions.
