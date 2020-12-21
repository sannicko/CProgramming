#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

/* This is a multi-process program, extending myshell.c program and Prompt is COP4338$ It will add pipelines and I/O redirections.
 * The shell will redirect different outputs from a command to a file.
 * Nick Jimenez
 * December 6 / 2020
 * */


#define TAB_ENTER " \t\n"
#define NUMBER_OF_ARGS 20
#define NAME_OF_FILE 256
#define SIZE_OF_BUFFER 1024


int argumentsNumber;
char inputFile[SIZE_OF_BUFFER];  // Variable for input file data
char pathShell[SIZE_OF_BUFFER];  // Variable for path
char shellPathTemp[SIZE_OF_BUFFER]; // Temporal variable for path
char filePath[SIZE_OF_BUFFER];  // Variable for file path
char * arguments[NUMBER_OF_ARGS];  // Variable for arguments passed through command
char fileRead[3][NAME_OF_FILE];
char ** argument;
extern char ** environ;
char * less_greater_char[3] = { ">", ">>", "<"};
char tokenFlag[3];


void execute();
void errorCheck(char * );
void inputOutputClose();
void BatchRead();
void pathUpdate();
void signalTemp();
void inputOutput(int);
void tokenization();

int main(int argc, char ** argv) {
    signal(SIGINT, SIG_IGN);
    getcwd(shellPathTemp, (-1) + SIZE_OF_BUFFER);  // Getting commands from command line
    strcpy(pathShell, shellPathTemp);  // Copy from temporal variable to path variable
    strcat(pathShell, "/myshell");  // Concatinating path wiht /myshell
    setenv("SHELL", pathShell, 1);  // Setting environment

    if (argc == 2) {  // If arguments number is 2 then run the program
        BatchRead(argv[1]);
    }
    else if (argc > 2){  // If there are more than 2 arguments then trigger an error
        errorCheck("Sorry, too many arguments.");
    }
    while (!feof(stdin)) {  // Read file
        pathUpdate();
        printf("COP4338$");
        if (fgets(inputFile, SIZE_OF_BUFFER, stdin)) {  // Read data from file and put to inputFile

            int check = 0;
            tokenization();
            int One = 1;

            if (!strcmp(arguments[argumentsNumber - One], "&") && One < argumentsNumber)  // If there is & argument in command
            {
                arguments[argumentsNumber - One] = (char* ) 0;  // Remove and process
                check = One;
            }

            if (!check) {  // If check == 0, execute the command
                execute();
            }
            else {
                pid_t pid2;
                pid2 = fork();  // Creating pipe

                switch (pid2) {
                    case 0:
                    setenv("PARENT", pathShell, One);
                    execute();
                    exit(0);
                    break;
                    case -1:
                    errorCheck("Oops.Error in creating fork.");
                    break;
                }
            }
        }
    }
    return 0;
}

void errorCheck(char errorMessage[SIZE_OF_BUFFER]) {  // Method to print error message
    printf("%s.\n", errorMessage);
    exit(1);
}

void tokenization() {  // Break the file in tokens
    int i = 0;

    char *temp, *pointer;  // Creating pointers

    while(i < 3){  // Loop to check <, > and >>

        tokenFlag[i] = 0;

        if ((pointer = strstr(inputFile, less_greater_char[i])) == NULL) {  // If file does not contain <, > or >> then ignore
        }
        else
        {
            temp = strtok(strlen(less_greater_char[i]) + pointer, TAB_ENTER);  // Putting lines if <, >> or > found
            strcpy(fileRead[i], temp);  // Copying the result in variable fileread
            tokenFlag[i] = 1;
            *pointer = '\0';
            if ((temp = strtok(NULL, TAB_ENTER)) == NULL){
            }
            else
            strcat(inputFile, temp);  // Concatenate the file with result
        }
        i++;
    }
    argument = arguments;
    *argument++ = strtok(inputFile, TAB_ENTER);  // Moving to next argument
    argumentsNumber = 1;

    while ((*argument++ = strtok(NULL, TAB_ENTER)))
    {
        argumentsNumber += 1;
    }
}

void pathUpdate() {  // Update path if commanded
    int one = 1;
    getcwd(filePath, SIZE_OF_BUFFER - one);  // Getting path from command line
}


void inputOutput(int ifRead) {  // Method to take input and output and redirect to each method
    if (1 == tokenFlag[0])
    {
        freopen(fileRead[0], "a", stdout);
    }
    if (1 == tokenFlag[1])
    {
        freopen(fileRead[1], "w", stdout);
    }
    if (ifRead == 1 && 1 == tokenFlag[2])
    {
        freopen(fileRead[2], "r", stdin);
    }
}


void signalTemp() {  // Method to push signal
    signal(SIGINT, SIG_IGN);
    putchar('\n');
}

void inputOutputClose() {  // Method to close redirection
    if (tokenFlag[1] || tokenFlag[0])  // If token flags are 1 then open
    {
        freopen("/dev/tty", "w", stdout);
    }
}

void execute() {  // Method to run the command

    if (!arguments[0]) {

    }
    else{
        if (!strcmp(arguments[0], "dir"))  // If command is of some directory
        {

            inputOutput(0);  // Opening file

            char temp[SIZE_OF_BUFFER];
            strcpy(temp, "ls -la ");  // Copying ls -la to temp

            if (!arguments[1]){

            }
            else
            {
                strcat(temp, arguments[1]);  // Copying argument to temp
            }

            system(temp);
            inputOutputClose();  // Closing input/output files at end

        }
        else if (!strcmp(arguments[0], "environ")) {  // If argument is environ
            inputOutput(0);
            char ** tempEnv = environ;
            while (*tempEnv) {
                printf("%s\n", *tempEnv);  // Print environment
                tempEnv += 1;
            }
            inputOutputClose();  // Closing input/output files at end

        }
        else if (!strcmp(arguments[0], "cd")) {  // If command is to move into folder
            if (arguments[1]) {  // If there is argument
                if (chdir(arguments[1])) {  // Check directory if exists
                    printf("%s: ", arguments[1]);  // Print error
                    printf(" Invalid directory.\n");
                }
                else {
                    pathUpdate();
                    setenv("PWD", filePath, 1);  // Set environment
                }
            }
            else {
                printf("%s\n", filePath);  // Print file path
            }
        }
        else if (!strcmp(arguments[0], "clr")) {  // If command is to clear screen
            system("clear");
        }
        else if (!strcmp(arguments[0], "help")) {  // If command is to get help, then print help
            inputOutput(1);
            char temp[SIZE_OF_BUFFER];
            strcpy(temp, "more ");
            strcat(temp, shellPathTemp);
            strcat(temp, "/readme");  // Copy readme from C library to temp tp print
            system(temp);  // Print readme
            putchar('\n');
            inputOutputClose();
        }
        else if (!strcmp(arguments[0], "quit"))  // If the command is to exit
        {
            exit(0);
        }
        else if (!strcmp(arguments[0], "echo")) {  // If the command is to echo
            inputOutput(0);
            char* data = (char*)malloc(SIZE_OF_BUFFER);
            strcpy(data, "");
            argument = &arguments[1];
            while (*argument)  // While there is argument
            {
                strcat(data, *argument++);  // Copy argument to data
                strcat(data, " ");
            }
            printf("%s\n", data);  // Print all the arguments
            memset(data, 0, SIZE_OF_BUFFER);
            free(data);  // Free data to empty memory
            inputOutputClose();
        }
        else if (!strcmp(arguments[0], "pause")) {  // If command is to pause
            getpass("Press Enter to continue\n");
        }
        else {
            pid_t pid1;
            int check;
            signal(SIGINT, signalTemp);
            pid1 = fork();  // Creating pipeline
            switch (pid1) {
                case 0:  // If pipeline is created successfully
                setenv("PARENT", pathShell, 1);
                inputOutput(1);
                if (!(execvp(arguments[0], arguments) != -1)){  // If command is invalid
                    errorCheck("Sorry, invalid command");
                }
                exit(1);
                break;
                case -1:  // If there is error
                errorCheck("Oops, there is an error in creating fork.");
                break;
            }
            fflush(stdout);  // Empty stdout to release memory
            waitpid(pid1, &check, 0);
        }
    }
}

void BatchRead(char filename[NAME_OF_FILE]) {  // Method to read the file

    int numberOfLine = 1;
    FILE* filePointer;
    filePointer = fopen(filename, "r");  // Open file
    if (filePointer != NULL){
    }
    else
    {
        errorCheck("Invalid batch file. It does not exists");
    }

    while (fgets(inputFile, SIZE_OF_BUFFER, filePointer))  // Get line from file
    {
        printf("%d. %s", numberOfLine++, inputFile);
        tokenization();
        execute();
        putchar('\n');
    }
    fclose(filePointer);  // Close the file in the end
    exit(0);
}
