/* Program that use if statements
speed as sample
Sannick
June 17, 2020
*/


#include<stdio.h>

int main(void)
{ 
 double speed; 
printf("Enter the speed:");
 scanf("%lf", &speed);
 if (speed <65)
 printf("\nNo speeding Ticket for your %lf miles per hour speed\n", speed);
 else
 printf("\nYou got a speeding Ticket for your %lf miles per hour speed\n", speed); 
return 0;
}