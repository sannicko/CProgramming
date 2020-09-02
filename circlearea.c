/* Circle and Area
    Sannick
    May, 5, 2020
*/

#include<stdio.h>

#define PI 3.14159

int main()
{
  double area = 0.0, radious = 0.0; /* area in KM*/
  printf("Enter Radius: ");
  scanf("%lf", &radious);
  area = PI * radious * radious; // Clasic formula
  printf("Radius of %lf meters; area is %lf sq. meters\n", radious, area);
  return 0;
}