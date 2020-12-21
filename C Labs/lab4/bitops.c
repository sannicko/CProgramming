#include <stdio.h>
#include <stdlib.h>

/* This program will either set or clear a single bit in a number entered by the user using the binary representation of the number. 
 * The user should input the original integer value between 1 and 1000 inclusive using a scanf. 
 * The user will select input 1 to set a bit OR input 2 to clear a bit.
 * The bit to clear should be a number between 0 and 31.
 * 
 * Nick Jimenez
 * 
 * October 25 / 2020
 * 
 * */


int main()
{
   unsigned int original_value;
   unsigned int bit_operation;
   unsigned int bit_position;
   unsigned int answer;
   char run_again = 'y';

   while (run_again == 'y' || run_again == 'Y')
   {
       printf("Enter integer value between 1 and 1000 (Inclusive): ");  // Capture initial user input
       scanf("%u", &original_value);
       if (original_value > 1000 || original_value < 1)
       {
           printf("Invalid input. It should be between 1 and 1000 (Inclusive)");
           printf("\nYou entered ** %u ** input out of range\n", original_value);
           exit(1);
       }        
       printf("Enter 1 to set a bit OR 2 to clear a bit: ");  // Set bit operation
       scanf("%u", &bit_operation);

       if (bit_operation != 1 && bit_operation != 2)  // Validation input
       {
           printf("Invalid input. It should be 1 for select OR 2 to clear\n");
           printf("\nYou entered ** %u ** input out of range\n", bit_operation);
           exit(1);
       }
        
       printf("Enter a bit position between 0 and 31: \n");  // Input bit position
       scanf("%u", &bit_position);

       if(bit_position > 31 || bit_position < 0){  // Perform bit position validation
           printf("Invalid input. It should be between 0 and 31\n");
           printf("\nYou entered ** %u ** input out of range\n", bit_position);
           exit(1);
       }

       if (bit_operation == 1)  // Perform bitwise operation
       {
           answer = original_value | (1 << bit_position);
           printf("\nNumber before switch %u\nNumber after switch %u", original_value, answer);
       }
       else if (bit_operation == 2)
       {
           answer = original_value & ~(1 << bit_position);
           printf("\nNumber before switch %u\nNumber after switch %u", original_value, answer);
       }

       printf("\nDo you want to run the program again (Y/N): \n");
       scanf(" %c", &run_again);

       if (run_again == 'n' || run_again == 'N')
       {
           printf("Exit\n");
       }
       else if (run_again == 'y' || run_again == 'Y')
       {
           run_again = 'y';
       }
       else
       {
           printf("Invalid entry.\n Please type Y or N \nExit");
           exit(1);
       }
       printf("\n");
   }
   return 0;
}
