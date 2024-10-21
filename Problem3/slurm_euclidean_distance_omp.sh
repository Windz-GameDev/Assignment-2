#!/bin/bash

# Specify the output file for the job's standard output
#SBATCH -o output_euclidean_distance_omp.txt

# Specify the error file for the job's standard error
#SBATCH -e error_euclidean_distance_omp.txt

# Set a time limit for the batch job (5 minutes)
#SBATCH --time=00:05:00

# Specify the number of nodes
#SBATCH -N 1

# Specify the number of CPU cores per task
#SBATCH --cpus-per-task=8

# Set the number of OpenMP threads
export OMP_NUM_THREADS=8

# Run the compiled OpenMP program
srun ./euclidean_distance_omp
    
