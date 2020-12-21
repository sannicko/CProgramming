#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

/* * This program will creates two child processes: one to execute 'ls -al' and the other to execute 'grep minishell.c'
 * * After the forks, the original partent process waits for both child processes to finish before it terminates.
 * * The parent should print out the pid of each child after it finishes.
 * * 
 * * Nick Jimenez
 * *  
 * * November 1 / 2020
 * * 
 * * */


char *firstCommand[] = { "/bin/ls", "-al", "/", 0 };
char *secondCommand[] = { "/bin/grep", "minishell.c", 0, 0 };

int main()
{
   int numberOfPipes = 2;  // Create pipe
   int pipes[numberOfPipes];
   pid_t firstPid;
   pid_t secondPid;
   pipe(pipes);
   firstPid = fork();
   switch (firstPid)
    {
        case 0:  // If child created
        dup2(pipes[1], 1);  // Duplicate the write end
        close(pipes[0]);  // Close the read end
        close(pipes[1]);  // Close the write end
        printf("Child Process 1 is executing grep ls -al \n");
        execvp(firstCommand[0], firstCommand); 
        printf("%s failed\n",firstCommand[0]);
        sleep(2);
        case -1:
        perror("Error in first child: "); 
        exit(1);
        default:  // Starts next child process
        secondPid = fork();
        switch (secondPid)
        {
            case 0:  // If child created
            close(0);
            dup(pipes[0]);  // Duplicate the write end
            close(pipes[0]);  // Close the read end
            close(pipes[1]);  // Close the write end
            printf("Child Process 2 is executing grep command \n");
            execvp(secondCommand[0], secondCommand);  // Grep minishell.c	
            printf("%s failed\n",secondCommand[0]);  // Return if failed   
            case -1:      
            printf("Error in creating second child");  
            exit(1);
            default:  // Starts parent
            close(pipes[0]);
            close(pipes[1]) ;
            printf("Parent waiting for children to finish\n");  // Parent Code
            sleep(2);  // Wait for children
            printf("\nPID of first child is %d\n" , firstPid);
            printf("PID of second child is %d\n" , secondPid);
            break; 
        }
    }
}

