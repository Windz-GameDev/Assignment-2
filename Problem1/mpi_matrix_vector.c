#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Function to generate a random matrix and vector.
void generate_random_matrix_vector(int *matrix, int *vector, int rows, int cols)
{

    // Use a consistent seed for reproducibility and comparison with serial code
    srand(42);

    // Assign every matrix element to a random number between 0 and 9
    for (int i = 0; i < rows * cols; i++)
    {
        matrix[i] = rand() % 10;
    }

    // Assign every vector element to a random number between 0 and 9
    for (int i = 0; i < cols; i++)
    {
        vector[i] = rand() % 10;
    }
}

// Function to perform matrix-vector multiplication
void matrix_vector_multiply(int *matrix, int *vector, int *result, int rows, int cols)
{

    // Take the dot product of each row in the matrix with the original vector and store it at the corresponding result array index.
    for (int i = 0; i < rows; i++)
    {
        result[i] = 0;
        for (int j = 0; j < cols; j++)
        {
            // i * cols calculates the starting index of the ith row, and adding j gets us to the current location in the ith row.
            result[i] += matrix[i * cols + j] * vector[j];
        }
    }
}

// Function to print a matrix
void print_matrix(int *matrix, int rows, int cols)
{
    printf("Matrix:\n");

    // Iterate through each row
    for (int i = 0; i < rows; i++)
    {

        // Iterate through every column in the row
        for (int j = 0; j < cols; j++)
        {

            // Multiply row number * row length to get starting index of row then add j to get position in row
            printf("%d ", matrix[i * cols + j]);
        }

        // Print newline at end of row
        printf("\n");
    }
}

// Function to print a vector
void print_vector(int *vector, int size, const char *name)
{
    printf("%s:\n", name);
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", vector[i]);
    }
}

int main(int argc, char *argv[])
{

    // Initialize the MPI environment, must be called before any other MPI functions.
    // Takes argc and argv so the MPI library can parse and remove any arguments that are specific to MPI from mpirun or mpiexec
    MPI_Init(&argc, &argv);

    // Declare variables to store the rank of teh current process and the total number of processes.
    int rank, size;

    // Determine the rank (ID) of the calling process within the communicator MPI_COMM_WORLD.
    // The rank is stored in the rank variable.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Determine the total number of processes in the communicator MPI_COMM_WORLD.
    // The size is stored in the size variable.
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Make sure the correct number of arguments are passed
    if (argc != 2)
    {

        // Ensure only the root process (rank 0) prints the usage message to avoid redundant output.
        if (rank == 0)
        {
            // Argv[0] contains the name of the program, we use it here to display the correct usage format
            printf("Usage: %s <vector_size>\n", argv[0]);
        }

        // Clean up the MPI environment if the program exits early due to incorrect arguments.
        MPI_Finalize();

        // Return 1 to indicate an error
        return 1;
    }

    // Convert the second command-line argument, the first user given argument from a string to an integer
    int vector_size = atoi(argv[1]);

    // Assume a square matrix for simplicity
    int rows = vector_size;

    // Check if the number of rows is divisible by the number of processes
    if (rows % size != 0)
    {
        if (rank == 0)
        {
            printf("Error: The number of rows (%d) is not divisible by the number of processes (%d).\n", rows, size);
        }

        // Ensure all processes reach this point and can print their own messages if needed, i.e. rank 0
        MPI_Finalize();
        return 1;
    }

    // Declare a pointer for the full matrix, initialized to NULL. Only the root process will allocate memory for the full matrix.
    int *matrix = NULL;

    // Declare a pointer for the result vector, intialized to NULL. Only the root process will allocate memory for the full result.
    int *result = NULL;

    // Dynamicallly allocate memory for the vector which is needed by all processes.
    int *vector = (int *)malloc(vector_size * sizeof(int));

    // Each process handles (Total number of rows / # Number of processes) rows and their dot products.
    int *local_matrix = (int *)malloc((rows / size) * vector_size * sizeof(int));

    // Each process will handle the same number of elements in the result vector as the # of rows in its local matrix.
    int *local_result = (int *)malloc((rows / size) * sizeof(int));

    // Ensure only the root process performs these operations.
    if (rank == 0)
    {

        // Allocate memory for the entire matrix on the root process.
        matrix = (int *)malloc(rows * vector_size * sizeof(int));

        // Allocate memory for the entire result vector on the root process.
        result = (int *)malloc(rows * sizeof(int));

        // Call a helper function to fill the matrix and vector with random integers
        generate_random_matrix_vector(matrix, vector, rows, vector_size);

        // Print the original matrix and vector
        print_matrix(matrix, rows, vector_size);
        print_vector(vector, vector_size, "Original Vector");
    }

    // Broadcast the vector from the root process to all other processes in the communicator.
    MPI_Bcast(vector, vector_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Distribute portions of the matrix to each process. Each process recieves a block of rows.
    MPI_Scatter(matrix, (rows / size) * vector_size, MPI_INT, local_matrix, (rows / size) * vector_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Synchronize proccesses before starting the timer
    MPI_Barrier(MPI_COMM_WORLD);

    // Set the start time
    double start_time = MPI_Wtime();

    // Call a helper function to multiply the matrix and vector and store the result in the result array.
    matrix_vector_multiply(local_matrix, vector, local_result, rows / size, vector_size);

    // Collect data from all local results and assemble it into a single result array on the root process.
    MPI_Gather(local_result, rows / size, MPI_INT, result, rows / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Synchronize proccesses after computation
    MPI_Barrier(MPI_COMM_WORLD);

    // Set the end time
    double end_time = MPI_Wtime();

    // Calculate the local time taken
    double local_duration = end_time - start_time;

    // Declare the maximum time taken by any process
    double global_duration;

    // Find the maximum time taken by any process and store it in global_duration
    MPI_Reduce(&local_duration, &global_duration, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    // Print the result on root and free its allocated memory.
    if (rank == 0)
    {
        // Print the max time taken and result vector
        print_vector(result, rows, "Result Vector");
        printf("Time taken for MPI matrix-vector multiplication: %f seconds\n", global_duration);

        // Free the allocated memory for the matrix and result vector on the root process.
        free(matrix);
        free(result);
    }

    // Free the allocated memory for the vector, local matrix, and local result on all processes.
    free(vector);
    free(local_matrix);
    free(local_result);

    // Clean up the MPI environment. This should be called after all MPI functions are complete.
    MPI_Finalize();

    // Return 0 to indicate successful program execution
    return 0;
}
