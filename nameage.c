/* Circle and Area
    Sannick
    May, 5, 2020
*/

#include<stdio.h>

#define age 2020

int main(void)
{
  int age1 = 0; 
  int year = 0;
  char name[20];
  printf("Enter Your Name: ");
  scanf("%s", name);
  printf("Your name is %s\n" , name);
  printf("Enter Your Birth Year: ");
  scanf("%d", &age1);
  age1 = age - age1;
  printf("%s is %d years old\n", name, age1);
  return 0;
}