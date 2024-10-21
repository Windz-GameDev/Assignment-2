# README for Problem 4: Find Prime Numbers Using MPI

## Introduction

This MPI program finds and prints all prime numbers up to a specified limit `n`. It distributes the work evenly across different processes, passing odd numbers to be checked for prime status in a round-robin fashion.

## Prerequisites

Before running the prime number finding program, ensure the following prerequisites are met:

- **C Compiler**: Ensure that a C compiler, such as `gcc`, is installed on your system. This is necessary for compiling the program.

- **MPI Library**: Install an MPI (Message Passing Interface) library, such as OpenMPI or MPICH. This is required for compiling and running the parallel version of the program using MPI.

- **SLURM Access**: Access to a SLURM-managed cluster is required for submitting batch jobs for the parallel version. Ensure you have the necessary permissions and access credentials.

- **Text Editor**: A text editor (e.g., `nano`, `vim`, or `gedit`) is needed to modify configuration files and source code if you wish to change parameters.

- **Basic Command Line Skills**: Familiarity with command-line operations is necessary to navigate directories, compile code, and submit batch jobs.

Ensure these prerequisites are fulfilled before proceeding with the setup and execution instructions.

## Setup

All files related to Problem 4 are located in the `Problem4` folder. Move this folder to the computing cluster you will be using to execute this code and `cd` into it before attempting to run any of the commands below.
.

## Running the Program

To run the program, submit any or all of the following SLURM batch jobs, where the number at the end of the batch file name reflects the number of processes you want to use:

```
sbatch slurm_find_prime_numbers_mpi_2.sh
sbatch slurm_find_prime_numbers_mpi_4.sh
sbatch slurm_find_prime_numbers_mpi_8.sh
sbatch slurm_find_prime_numbers_mpi_16.sh
```

Important Note: Make sure you are cd'd into the `Problem4` folder before attempting to run these commands.

## Viewing Job Outputs

After submitting your SLURM batch jobs, the output and error messages are captured in .stdout and .stderr files, respectively. These files are named according to the number of processes used and the specific job instance. Here's how you can view these outputs:

1. **Locate the Output Files**:

- The output files are named in the format `my_<number_of_processes>procs_<job_id>.stdout` for standard output and `my_<number_of_processes>_procs<job_id>.stderr` for standard error.
- For example, my_2procs_1112.stdout contains the standard output for a job run with 2 processes, and my_2procs_1112.stderr contains the standard error for the same job.

2. **View the Output**:

- Use the cat command to display the contents of these files in the terminal. For example:

```bash
cat my_2procs_1112.stdout
```

- This command will display the standard output of the job that ran with 2 processes.

3. **Check for Errors**:
   Similarly, you can view the standard error file to check for any errors or warnings that occurred during the job execution:

```bash
cat my_2procs_1112.stderr
```

4. **Example Commands**:

- Here are some example commands to view outputs for different numbers of processes:

```
cat my_4procs_1113.stdout
cat my_8procs_1115.stdout
cat my_16procs_1117.stdout
```
