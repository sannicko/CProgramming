/* Yards Conversion to Miles
    Sannick
    May, 19, 2020
*/

#include <stdio.h>
int main(void)
{
  int miles = 26, yards = 385;
  double kilometers;

  kilometers = 1.609 * (miles + yards/1760.0);
  printf("\nA marathon is %lf kilometers.\n", kilometers);

  /* scanf("%d", &fahrenheit);
  celsius = (fahrenheit - 32)/1.8; //note conversion
  printf("\n %d fahrenheit is %d celsius. \n", fahrenheit, celsius); */

  return 0;
}
