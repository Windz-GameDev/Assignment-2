#!/bin/sh
#SBATCH -o my_8procs_%j.stdout  # Output file
#SBATCH -e my_8procs_%j.stderr  # Error file
#SBATCH --time=5                # Time limit for the batch job (5 minutes)
#SBATCH -N 1                    # Number of nodes
#SBATCH -n 8                    # Number of tasks (processes)

mpirun find_prime_numbers_mpi
