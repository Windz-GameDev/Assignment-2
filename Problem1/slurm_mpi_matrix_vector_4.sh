#!/bin/bash

# Specify the output file for the job's standard output
#SBATCH -o output_mpi_matrix_vector_4.txt

# Set a time limit for the batch job (5 minutes)
#SBATCH --time=00:05:00

# Request 4 tasks (processes) for this job
#SBATCH -n 4

# Source the configuration file to set environment variables
source config.sh

# Run the MPI program with the vector size specified in the configuration
mpirun mpi_matrix_vector $VECTOR_SIZE

