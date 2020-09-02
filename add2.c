/* Read in Two Floats and Print Sum
    Sannick
    May, 5, 2020
*/

#include<stdio.h>

int main(void)
{
  float a, b, sum;
  printf("Input two floats: ");
  scanf("%f%f", &a, &b);
  printf("a = %f, b = %f\n", a, b);
  sum = a + b;
  printf("sum = %f\n\n", sum);
  return 0;
}