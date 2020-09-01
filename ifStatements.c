/*
  This program test multiple distinct if statements
*/

#include <stdio.h>

int main(void) {
   int userAge;
   
   printf("Please enter your age: ");
   scanf("%d", &userAge);

   if (userAge < 16) {
      printf("Enjoy your early years.\n");
   }
   
   if (userAge > 15) {
      printf("You are old enough to learn how to drive.\n");
   }
   
   if (userAge > 17) {
      printf("You are old enough to vote.\n");
   }
   
   if (userAge > 24) {
      printf("Most car rental companies will rent to you.\n");
   }
   
   if (userAge > 34) {
      printf("You can run for president.\n");
   }

    if (userAge > 70) {
      printf("You should be in a paradise enjoying the retirement.\n");
   }

   
   return 0;
}