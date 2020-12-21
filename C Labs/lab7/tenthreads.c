#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* This program will use 10 threads to increment a shared variable. Each thread will loop 6 times, incrementing the
* shared variable by its Thread ID (tid) in every iteration of the loop. This number for the tid will be in single
* digits from 0-9. Once a thread has finished looping, it will print the ID of the thread displaying “The Thread [ID] has
* finished.”
*  
* Nick Jimenez
* * November 29 / 2020
* */

#define NUM_THREADS 10  // Let us create 10 threads

typedef struct strct_dataThread
{
  int tid;
  double threadNum;
} dataThread;

double sharedVariable;
pthread_mutex_t lock_sharedVariable;

void *myThreadFunc(void *arg)  // A normal C function that is executed as a thread when its name is specified
{
  int i;
  dataThread *data = (dataThread *)arg;
  pthread_mutex_lock(&lock_sharedVariable);
  for (i = 0; i < 6; i++)  // Let us loop 6 times
    sharedVariable += data->tid;  // Incrementing the shared variable by the Thread [ID]
  printf("The Thread ID: %d has finished. \n", data->tid);
  pthread_mutex_unlock(&lock_sharedVariable);
  pthread_exit(NULL);
  return 0;
}

int main(int argc, char **argv)
{
  pthread_t thr[NUM_THREADS];
  int i; 
  int rc;
  dataThread thr_data[NUM_THREADS];  // Create a dataThread argument array
  sharedVariable = 0;  // Initialize shared data
  pthread_mutex_init(&lock_sharedVariable, NULL);
  
  for (i = 0; i < NUM_THREADS; ++i)  // Create threads
  {
    thr_data[i].tid = i;
    thr_data[i].threadNum = (i + 1) * NUM_THREADS;
    if ((rc = pthread_create(&thr[i], NULL, myThreadFunc, &thr_data[i])))
    {
      fprintf(stderr, "Error: pthread_create, rc: %d\n", rc);
      return EXIT_FAILURE;
    }
  }
  
  for (i = 0; i < NUM_THREADS; ++i)  // Block until all threads complete
  {
    pthread_join(thr[i], NULL);
  }
  printf("\n");
  printf("Shared variable output value after incrementing: %.2f \n", sharedVariable);  // Output value shared variable after all threads have finished incrementing it
  printf("\n");
  
  return EXIT_SUCCESS;
}