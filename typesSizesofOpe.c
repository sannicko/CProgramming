/* Types size of operator
    Sannick
    May, 29, 2020
*/

#include<stdio.h>

int main()
{
  int a = 5, b = 7, c = 6; //Declare and initialize
  double average = 0.0;  //Always double initialize with 0.0
  char ch = 'e'; 
  
  printf("On my system\n");
  printf("int is %lu bytes.\n", sizeof(int));
  printf("long int is %lu bytes. \n", sizeof(long int));
  printf("char is %lu bytes.\n", sizeof(ch ));
  printf("float is %lu bystes.\n", sizeof(float));
  printf("double is %lu bytes.\n", sizeof(double));
  printf("long double is %lu bytes. \n, '\a' ", sizeof(long double));  
  return 0;
}