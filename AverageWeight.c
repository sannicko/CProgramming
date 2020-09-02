/* This program will fill array with the user's input and 
compute the average value of the array.

Nick_Nick
July 4, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{ 
  srand(time(NULL));  
  int sum, i, input;
  float average;
  sum = average = 0;

  printf("Type the value of your array : ");
  scanf("%d", &input);

  int array [input];  // placing the array after defining of 'input'
  //int size = sizeof (array) / sizeof(array[0]);

  printf("The size of your array is : %.2d \n", input);

  for (i = 0; i < input; i++)
  {
    array[i] = rand() % 100 + 1;
  }

  // loop for printing results

  for (i = 0; i < input; i++)
  {
    printf("Element %d; %d \n", i, array[i]);
  }
 
  for(i = 0; i < input; i ++){
    sum = sum + array[i];
  }

  average = (float)sum / i;
  printf("The average of array values is %.2f \n", average);
    
  return 0;
  };  