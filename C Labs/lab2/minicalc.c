#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>

/* This program will accept only the command line options. This calculator will only do addition, substraction, multiplication, division, and power of 2.
 *
 * Nick Jimenez
 * September 17 / 2020
 *
 * */



int main(int argc, char **argv)
{
   int err = 0;
   float value = 0.0;
   int add_num = 0;
   int divide_num = 1;
   int mult_num = 1;
   int subs_num = 0;
   int add_flag = 0;
   int division_flag = 0;
   int multiplication_flag = 0;
   int power_flag = 0;
   int subtraction_flag = 0;
   int c;

   opterr = 0; // Track errors by getopt function
   value = atof(argv[argc - 1]);
   if (value < 1 || value > 50) // Validate value, must be between 1 and 50 inclusive
   {
   	printf("The value should be an integer between 1 and 50 inclusive\n");
   	printf("Usage: [-a num] [-d num] [-m num] [-s num] [-x] value \n");
   	exit(1);
   }
        while ((c = getopt(argc, argv, "a:d:m:s:x")) != -1) // While loop iterates over each argument from command line
   {
        switch (c)
        {
        case 'a':
            add_flag = 1;
            add_num = atof(optarg);
            break;
        case 'd':
            division_flag = 1;
            divide_num = atof(optarg);
            break;
        case 'm':
            multiplication_flag = 1;
            mult_num = atof(optarg);
            break;
        case 's':
            subtraction_flag = 1;
            subs_num = atof(optarg);
            break;
        case 'x':
            power_flag = 1;
            break;
        }
   }
   if (err) 
   {
        printf("Usage: [-a num] [-d num] [-m num] [-s num] [-x] value \n");
        exit(1);
   }
   if (opterr)
   {
        printf("Usage: [-a num] [-d num] [-m num] [-s num] [-x] value \n");
        exit(1);
   }
   if (power_flag == 1) // If -x flag is used, raise value by power of 2
   {
        value = pow(value, 2);
   }
   if (multiplication_flag == 1) // If -m flag is used, multiply value by mult_num
   {
   if (mult_num < 1 || mult_num > 5)
        {
        printf("The integer to multiply should be a positive integer between 1 and 5 inclusive\n");
        exit(1);
        }
        value *= mult_num;
   }
   if (division_flag == 1) // If -d flag is used, divide value by divide_num
   {
    	if (divide_num < 1 || divide_num > 5)
        {
            printf("The integer to divide should be a positive integer between 1 and 5 inclusive\n");
            exit(1);
        }
        value = value / divide_num;
   }
   if (add_flag == 1) // If -a flag is used, add value by add_num
   {
        if (add_num < 1 || add_num > 500)
        {
            printf("The integer to add should be a positive integer between 1 and 500 inclusive\n");
            exit(1);
        }
        value += add_num;
   }
   if (subtraction_flag == 1) // If -s flag is used, subtract value by subs_num
   {
        if (subs_num < 1 || subs_num > 500)
        {
            printf("The integer to substract should be a positive integer between 1 and 500 inclusive\n");
            exit(1);
        }
        value -= subs_num;
   }
   printf("Output: %.2f\n", value); // Print output with exactly 2 decimal places.
   
   return 0;


}
