/* For loop sample

Sannick
June 21, 2020
*/

#include<stdio.h>

int main(void)
{ 
  int repeat = 0;
  int i;
  
  printf("How deep is your love from 1 to 100? : ");
  scanf("%d", &repeat);
  printf("\nMy Love is deep ");
  for (i=1; i<=repeat; i++)
  {
    printf("\n deeper, deeper than %d", repeat);
    
  };
  printf(" Oceans in the universe. \n\n");
  
return 0;
}