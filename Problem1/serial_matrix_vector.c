#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate a random matrix and vector.
void generate_random_matrix_vector(int *matrix, int *vector, int rows, int cols)
{

    // Seed the random number generator using the current time
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

    // Make sure the correct number of arguments are passed
    if (argc != 2)
    {

        // Argv[0] contains the name of the program, we use it here to display the correct usage format
        printf("Usage: %s <vector_size>\n", argv[0]);

        // Return 1 to indicate an error
        return 1;
    }

    // Convert the second command-line argument, the first user given argument from a string to an integer
    int vector_size = atoi(argv[1]);

    // Assume a square matrix for simplicity
    int rows = vector_size;

    // Dynamically allocate memory for the matrix
    int *matrix = (int *)malloc(rows * vector_size * sizeof(int));

    // Dynamicallly allocate memory for the vector
    int *vector = (int *)malloc(vector_size * sizeof(int));

    // Dynamically allocate the result vector which has as many elements as the number of rows.
    int *result = (int *)malloc(rows * sizeof(int));

    // Call a helper function to fill the matrix and vector with random integers
    generate_random_matrix_vector(matrix, vector, rows, vector_size);

    // Print the original matrix and vector
    print_matrix(matrix, rows, vector_size);
    print_vector(vector, vector_size, "Original Vector");

    // Measure execution time
    clock_t start = clock();

    // Call a helper function to multiply the matrix and vector and store the result in the result array.
    matrix_vector_multiply(matrix, vector, result, rows, vector_size);

    clock_t end = clock();

    // Calculate the time taken
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the result vector
    print_vector(result, rows, "Result Vector");

    printf("Time taken for serial matrix-vector multiplication: %f seconds\n", time_taken);

    // Free dynamically allocated memory to prevent memory leaks
    free(matrix);
    free(vector);
    free(result);

    // Return 0 to indicate successful program execution
    return 0;
}
