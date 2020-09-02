/* While loop deep love

Sannick
June 18, 2020
*/

#include<stdio.h>

int main(void)
{ 
  int repeat = 0;
  
  printf("How deep is your love from 1 to 100? : ");
  scanf("%d", &repeat);
  printf("\nMy Love is deep ");
  while (repeat > 0)
  {
    printf("\n deeper, deeper than %d", repeat);
    repeat--;
  };
  printf(" Oceans in the universe. \n\n");
  
return 0;
}