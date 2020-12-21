#include<stdio.h>

/*This program will calculate student gpa based on 6 courses, credits and grades.
 * Nick Jimenez
 * September 17 / 2020
 * */


int main (int argc, char const *argv[])
{
   char *courses[6] = {"COP2210", "ENC1101", "COP4338", "COP4710", "CDA4101", "COP3530"}; // Array of string types with 6 elements courses
   int credits[6] = {3, 2, 1, 3, 4, 6}; // Array of integer types with 6 elements credits
   float grades [6] = {5.0, 4.0, 3.0, 2.0, 1.0}; // Array of float types with 6 elements grades
   float gpa;
   int i;
   int totalCredits;

      printf("%s%15s%15s%25s", "Course", "Credits", "Grade", "Grade Points Earned\n"); // Display header for the output
   for (i = 0; i < 6; ++i) // For loop to iterate courses and display courses information
   {
      printf("%s %10d %17.2f %23.2f\n", courses[i], credits[i], grades[i], credits[i]*grades[i]);
      gpa = gpa + credits[i] * grades[i]; //Adding values to gpa 
      totalCredits += credits[i]; // Sum total credits
   }
   printf("Total %12d\n", totalCredits); // Display total credits calculation
   printf("Current GPA: %2.2f\n", gpa); // Display pga calculation

   return 0;
}
