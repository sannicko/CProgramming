/* Ternary Operator Sample
    condition?exp1:exp2
Sannick
June 21, 2020
*/

#include<stdio.h>

int main(void)
{ 
  int speed;
  printf("Enter your speed as an integer: ");
  scanf("%d", &speed);
  speed = (speed <= 65)? (65)  : (speed <= 70)? (70) : (90);
  switch (speed)
  {
    case 65: printf("\nNo Speeding Ticket, very good speed %d  \n\n", speed);break;  
    case 70: printf("\nYes Speeding Ticket, your speed was %d \n\n", speed);break;
    case 90: printf("\nYes Very Expensive Ticket, your speed was %d\n\n", speed);break;
    default: printf("\nIncorrect Speed\n\n");
  }
  
 
return 0;
}