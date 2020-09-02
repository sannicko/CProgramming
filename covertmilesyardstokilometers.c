/* Yards Conversion to Miles
    Sannick
    May, 26, 2020
*/

#include <stdio.h>
int main(void)
{
  int miles, yards;
  double kilometers;
  printf("Please enter the miles: ");
  scanf("%d", &miles);
  printf("Please enter the yards: ");
  scanf("%d", &yards);
  
  kilometers = 1.609 * (miles + yards/1760.0);
  printf("\n%d miles and %d yards are %lf kilometers\n", miles, yards, kilometers);

  /* scanf("%d", &fahrenheit);
  celsius = (fahrenheit - 32)/1.8; //note conversion
  printf("\n %d fahrenheit is %d celsius. \n", fahrenheit, celsius); */

  return 0;
}
