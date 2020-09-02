/* Assignment Week 3
Sannick
June 21, 2020
*/




#include<stdio.h>
#include<math.h> /* has  sin(), abs(), and fabs() */

int main(void)
{ 
double interval;
int i;

printf("Type your interval as a double: ");
scanf("%lf", &interval);
for(i = 0; i <30; i++)
{
 interval = i/10.0;
 printf("sin( %lf ) = %lf \t", interval, fabs(sin(interval))); 
 }
 

printf("\n+++++++++++\n");
return 0;
}