/* Program that give sine and cosine of a value 
between 0 an 1
Sannick
June 20, 2020
*/


#include<stdio.h>
#include<math.h>  

int main(void)
{ 
 double input;
 double result1;
 double result2;
 double cosine;
 printf("Enter number between 0 and 1 to calculate sine and cosine value :");
 scanf("%lf", &input);
 result1 = sin(input);
 result2 = cos(input);
printf("The sine value of (%lf) is = %.4f and the cosine value of (%lf) is = %.3f\n", input, result1, input, result2);

return 0;
}