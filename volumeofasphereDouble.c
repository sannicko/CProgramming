/* Volume of sphere using double
Sannick
June 15, 2020
*/


#include<stdio.h>
#define PI 3.14159

int main(void)
{ 
 double radius;
 printf("Enter radius:");
 scanf("%lf", &radius);
printf("The volume of the sphera is : %lf \n\n", 4/3.0 * PI *radius*radius*radius);
return 0;
}