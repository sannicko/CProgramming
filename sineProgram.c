/* Program that give sine of a value 
between 0 an 1 (non inclusive)
Sannick
June 17, 2020
*/


#include<stdio.h>

int main(void)
{ 
 double sine;
 double result;
 printf("Enter number between 0 and 0.99 to calculate sine value :");
 scanf("%lf", &sine);
 result = sin(sine);
printf("The sine value of (%lf) is = %.21f\n", sine, result);

return 0;
}