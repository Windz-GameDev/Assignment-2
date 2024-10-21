# README for Problem 3: Computing Euclidean Distance Using OpenMP

## Introduction

This problem code involves computing the Euclidean distance between two vectors in N-dimensional space using both serial and parallel approaches. The parallel version utilizes OpenMP for shared-memory parallelism.

## Prerequisites

- Ensure `gcc` is installed on your system.
- Access to a SLURM-managed cluster is required for running the parallel version.

## Setup

All files related to Problem 3 are located in the `Problem3` folder. Move this folder to the computing cluster you will be using to execute this code and `cd` into it before attempting to run any of the commands below.

## Running the Serial Version

To run the serial version of this assignment, use the following command:

```bash
./euclidean_distance_serial
```

## Important Notes

- Both vectors exist in N-dimensional space where N is one million. The seed used to generate random numbers for both vectors is 42.
- You can change N by opening `euclidean_distance_serial.c`, modify `N` to a number of your choice, and pass in a different seed to `srand()` to get different numbers in your vectors.

  - Once you have made your changes, recompile the code using the following command:

    ```bash
    gcc -o euclidean_distance_serial euclidean_distance_serial.c -lm
    ```

  - Now when you rerun the code, your new problem size and random number generator seed will be used.

## Running the Parallel Version

To run the parallel version of this assignment, submit the SLURM batch job using the following command:

```bash
sbatch slurm_euclidean_distance_omp.sh
```

**Important Note**: Make sure you are in the `Problem3` folder in the terminal and all relevant files are present.

## Viewing the Output

After the batch job has completed, you can view the output using the `cat` command:

```bash
cat output_euclidean_distance_omp.txt
```

## Important Notes for Parallel Version

- To change the vector size and random number generator seed for the parallel version, make the same code changes in `euclidean_distance_omp.c` as you did in `euclidean_distance_serial.c`.
- Recompile the OMP program using:

```bash
gcc -o euclidean_distance_omp euclidean_distance_omp.c -fopenmp -lm
```

- Now when you run the batch file again, your changes will be taken into account.
