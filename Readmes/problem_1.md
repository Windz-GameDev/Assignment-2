# README for Problem 1 Matrix-Vector Multiplication

## Introduction

This problem involves performing matrix-vector multiplication, a fundamental operation in linear algebra, using both serial and parallel approaches. The parallel version leverages MPI (Message Passing Interface) to distribute the computation across multiple processes, enhancing performance on problem sizes. This README provides instructions on setting up, and running the code on a computing cluster.

## Prerequisites

Before running the matrix-vector multiplication program, ensure the following prerequisites are met:

- **C Compiler**: Ensure that a C compiler, such as `gcc`, is installed on your system. This is necessary for compiling the serial and parallel versions of the program.

- **MPI Library**: Install an MPI (Message Passing Interface) library, such as OpenMPI or MPICH. This is required for compiling and running the parallel version of the program using MPI.

- **SLURM Access**: Access to a SLURM-managed cluster is required for submitting batch jobs for the parallel version. Ensure you have the necessary permissions and access credentials.

- **Text Editor**: A text editor (e.g., `nano`, `vim`, or `gedit`) is needed to modify configuration files and source code if you wish to change the vector size or other parameters.

- **Basic Command Line Skills**: Familiarity with command-line operations is necessary to navigate directories, compile code, and submit batch jobs.

Ensure these prerequisites are fulfilled before proceeding with the setup and execution instructions.

## Setup

All files related to Problem 1 are located in the `Problem1` folder. Move this folder to the computing cluster you will be using to execute this code and `cd` into it before attempting to run any of the commands below.

## Running the Serial Version

To run the serial version of this assignment, use the following command:

```
./serial_matrix_vector <Vector Size>
```

- The `<Vector Size>` parameter determines the number of matrix columns and rows.

## Important Notes

- This program is designed to work correctly when the vector size is a power of 2 (e.g., 1024, 2048, 4096).
  - This ensures that the number of rows can be evenly divided by different numbers of processes (2, 4, 8, 16, 32).
  - Number of processes must also be less than the vector size.
- As a starting value, I recommend using 2^11 = 2048 for the `<Vector Size>`, as this is what I used to test the parallel versions.

## Running the Parallel Version

To run the parallel version of this assignment with the default `<Vector Size>` of 2048, run any or all of the commands below where the number at the end of the batch file name reflects the number of processes you want to use:

```
sbatch slurm_mpi_matrix_vector_2.sh
sbatch slurm_mpi_matrix_vector_4.sh
sbatch slurm_mpi_matrix_vector_8.sh
sbatch slurm_mpi_matrix_vector_16.sh
sbatch slurm_mpi_matrix_vector_32.sh
```

Important Note: Make sure the mpi_matrix_vector executable and config.sh are in the same directory as your batch files before executing them.

## Viewing the Output

After the batch jobs have completed, you can view the output using the cat command. The output files are named according to the number of processes used:

```
cat output_mpi_matrix_vector_2.txt
cat output_mpi_matrix_vector_4.txt
cat output_mpi_matrix_vector_8.txt
cat output_mpi_matrix_vector_16.txt
cat output_mpi_matrix_vector_32.txt
```

## Changing the Problem Size

To change the vector size for the parallel version, follow these steps:

1. Edit the Configuration File: Open the config.sh file in a text editor of your choice.

```
nano config.sh
```

2. Modify the Vector Size: Change the value of VECTOR_SIZE to your desired size. Ensure it is a power of 2 for optimal performance.

```
export VECTOR_SIZE=4096
```

3. Save and Close: Save the changes and close the editor.
4. Submit the Batch Jobs: Run the batch scripts as usual. The new vector size will be used automatically.

Alternatively, you can run the program directly with mpirun (not recommended for regular use):

```
mpirun -n <Number of Processes> mpi_matrix_vector <Your Vector Size>
```

- Replace <Number of Processes> with the desired number of processes and <Your Vector Size> with your desired vector size.
