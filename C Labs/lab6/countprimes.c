#include "mpi.h"
#include <stdio.h>
#include <unistd.h>

/* This program will will count the number of prime numbers in the numbers
 * * from 1 to n inclusive where n is a long integer. The value for n is set as a constant 50,000.
 * * Then it will print out any primes and count the actual prime number found.
 * * Then it will print print out the total amount of time taken to find all the primes.
 * * 
 * * Nick Jimenez
 * * 
 * * November 22 / 2020
 * * 
 * * */


#define N 50000

int primeNumber(int id, long int n)  // Function to find if a number is prime or not
{
  if (n == 0 || n == 1)
  {
    return 0;
  }
  int i;

  for (i = 2; i <= n / 2; i++)  // Checking even numbers
  {
    if (n % i == 0)
    {
      return 0;
    }
  }
  printf("Process %d) %ld is a prime number\n", id, n);
  fflush(stdout);
  return 1;
}

int main(int argc, char *argv[])
{
  int count = 0;
  double timeElapsed;
  int countTotal;
  int id;
  int i;
  int p;

  MPI_Init(&argc, &argv);  // Getting MPI information
  MPI_Comm_rank(MPI_COMM_WORLD, &id);  // Determines the rank of the calling process in the communicator
  MPI_Comm_size(MPI_COMM_WORLD, &p);  //  Returns the size of the group associated with a communicator
  MPI_Barrier(MPI_COMM_WORLD);  // Start timer
  timeElapsed = - MPI_Wtime();

  for (i = id; i <= N; i += p)
    count += primeNumber(id, i);

  MPI_Reduce(&count, &countTotal, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  timeElapsed += MPI_Wtime();  // End timer

  if (!id)
  {
    printf("\nThe total number of primes is: %d \n", countTotal);  // Printing total count of prime numbers
  }
  MPI_Finalize();  
  if (!id)
  {
    printf("\nThe total amount of time taken to find all the primes is: %8.6f seconds\n", timeElapsed);  // Timer results
    printf("\n");
    fflush(stdout);
    return 0;
  }
}
