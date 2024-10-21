#include <mpi.h> // Included for MPI functions
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> // Used for taking square root
#include <stdbool.h> // Used for boolean type
#include <time.h> // Used for timing function

bool is_prime(int num) {

    // Numbers 0 and 1 are not prime
    if (num <= 1) {
        return false;
    }

    // 2 is the only even prime number
    if (num == 2) {
        return true;
    }

    // If number number is even and not 2, it is not prime because all even numbers are divisible by 2.
    if (num % 2 == 0) {
        return false;
    }

    // See if num is divisible by any odd number in the range 3 to the square root of num.
    // We skip even numbers by incrementing by 2.
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) {
            return false; // Number is divisible by a number other than itself and one
        }
    }

    // Number is prime
    return true;
}

int main(int argc, char* argv[]) {
    
    // Declare the variables to store the process rank and the number of proccesses in the communicator.
    int rank, size;

    // Check the number of the prime numbers up to and including this number starting from 0
    int n = 2500000;

    // Number of prime numbers found by this node
    int count = 0;

    // Initialize the MPI environment and remove non user arguments from argc and argv.
    MPI_Init(&argc, &argv);

    // Get the rank of the current process in the communicator and store it in rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the total number of processes in the communicator and store it in size
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Declare timer variables for root process
    double start_time, end_time;

    // If the process is the master node, start the timer to measure performance
    if (rank == 0) {
        start_time = MPI_Wtime();

        // Two is the only even prime number so add it as a special case if n is two or greater
        if (n >= 2) {
            printf("Node %d found prime: %d\n", rank, 2);
            count++;
        }
    }

    // Use a round robin distribution to assign numbers to check to processes based on process rank.
    // All odd numbers from 1 to n are checked, where 2 is a special case handled seperately
    // In the first iteration of each process, the m proccesses will check the first m
    // odd numbers using the formula : (i = rank * 2 + 1) Multiplying by 2 and adding 1 ensures even numbers are skipped. 
    // Assume m = 4
    // Process 0 checks i = 1, process 1 checks i = 3, process 2 checks i = 5, and process 3 checks i = 7.
    // In the next iteration, each process's counter will be incremented by m * 2 (8) so 0 checks 9, 1 checks 11, etc.
    // Incrementing by m * 2 works because adding 2 to gets you to the next odd number. Adding by 2 m times will 
    // get you to the mth next odd number because the next m - 1 odd numbers have already been calculated by the other proceses.
    // This allows the proccesses to find all prime numbers up to n with a close to evenly distributed workload.
    for (int i = rank * 2 + 1; i <= n; i += size * 2)
    {
        if (is_prime(i)) {
            printf("Node %d found prime: %d\n", rank, i);
            count++;
        }
    }

    // Declare the variable that will store the total number of primes found across all processes
    int total_count;

    // MPI_Reduce will sum the counts across each process and store them in total_count
    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // On the master node print the time elapsed and number of primes found
    if (rank == 0) {
        end_time = MPI_Wtime();
        printf("Total primes found in the range [0, %d]: %d\n", n, total_count);
        printf("Time elapsed: %f seconds\n", end_time - start_time);
    }

    // Clean up the MPI environment
    MPI_Finalize();

    // Return 0 to indicate successful execution
    return 0;
}

