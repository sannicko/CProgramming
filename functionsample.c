/* Function Sample using while loop

Sannick
June 30, 2020
*/

#include<stdio.h>

// first write the function 

void wrt_howdeep(int count)
{
  while (count > 0)
  {
    printf("\n very %d", count);
    count--;
  }
  printf(" Oceans in the universe. \n\n");
}

// main program

int main(void)
{ 
  int repeat = 0;  
  printf("How deep is your love from 1 to 100? : ");
  scanf("%d", &repeat);
  printf("\nMy Love is deep ");
  wrt_howdeep(repeat);
  return 0;
  };  