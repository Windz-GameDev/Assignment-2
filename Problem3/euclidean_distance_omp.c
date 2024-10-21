#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <omp.h> // Included for OpenMP support and to parallelize the euclidean distance calculation

// Number of dimensions for both vectors representing N dimensional points
#define N 1000000 // Set to at least one million per assignment requirements

int main() {
    
    // Initialize loop counter
    int i;

    // Declare the two vectors representing our two N dimensional points
    int *P = (int *)malloc(N * sizeof(int));
    int *Q = (int *)malloc(N * sizeof(int));

    // Make sure memory allocation was successful
    if (P == NULL || Q == NULL) {

        // If allocation failed, display error message to the user
        fprintf(stderr, "Memory allocation failed\n");

        // Return 1 to indicate the program encountered an error and did not complete successfully
        return 1;

    }

    // Seed the random number generator with 42 for reproducibility
    srand(42);

    // Initialize both vectors where each element is between 0 and 99
    for (i = 0; i < N; i++) {
        P[i] = rand() % 100;
        Q[i] = rand() % 100;
    } 

    // Initialize the double that will hold the sum of accumulated squared differences to 0
    double sum = 0.0;

    // Start timing of the parallel computation
    double start_time = omp_get_wtime();

    // Calculate the sum of the squared differences in parallel.
    // For its assigned elements, each thread computes the square of the difference 
    // and sums these squared differences in it's own private sum double.
    // The private sum of each thread are then added together at the end into the
    // original sum double. 
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < N; i++) {
        
        // Calculate the difference between the points for the ith dimension and store it as a double.
        double difference = P[i] - Q[i];

        // Square the difference and add it to the accumulated sum
        sum += difference * difference;
    }

    // The square root of the accumulated sum of squared differences is the final Euclidean distance
    double euclidean_distance = sqrt(sum);

    // End timing of the parallel computation
    double end_time = omp_get_wtime();

    // Calculate execution time
    double execution_time = end_time - start_time;

    printf("Parallel execution results:\n");
    printf("Euclidean distance: %f\n", euclidean_distance);
    printf("Time taken: %f seconds\n", execution_time);

    // Free dynamically allocated memory for both vectors
    free(P);
    free(Q);

    // Return 0 to indicate successful execution
    return 0;
}