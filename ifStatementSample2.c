/*
  This program test multiple distinct if else statements
*/

#include <stdio.h>

int main(void) {
   int carYear;

  printf("Please enter your car's model year: ");
   scanf("%d", &carYear);

   if (carYear < 1967) {
      printf("Probably has few safety features.\n");
   }
   
  if (carYear > 1969) {
      printf("Probably has seat belts.\n");
   }
   
  if (carYear > 1992) {
      printf("Probably has electronic stability control.\n");
   }
   
  if (carYear > 2000) {
      printf("Probably has tire-pressure monitor.\n");
   }
  
   return 0;
}