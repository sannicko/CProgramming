#include <stdio.h>

int main(void) {
   int userNum1;
   int userNum2;


   printf("Please enter an integer: \n");
   scanf("%d", &userNum1);
   
   printf("Please enter another integer: \n");
   scanf("%d", &userNum2);

   if(userNum1 < 0){
      
   printf("userNum1 is negative.\n");
   
   }
   
   if (userNum2 > 9){
      userNum2 = 5;
   }
   
   else{
      printf("userNum2 is less or equal 9.\n");
   }
   
   printf("userNum2 is %d.\n", userNum2);

   return 0;
}