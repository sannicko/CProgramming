#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

/* This program will sort the lines of an input file or from standard input and print the sorted lines to an output file or standard output on screen.
 * Nick Jimenez
 * October 18 / 2020
 * */

typedef struct Node{  // Node structure
   int data;
   char *key;
   struct Node *right;
   struct Node *left;
} Node;

int strcmpForCaseSensitivity(char *line1,char *line2){  // Function for case sensitive
   char *firstPointer = line1;   
   char *secondPointer = line2;   
   
   while( (*firstPointer) != '\0' && (*secondPointer) != '\0'){  // Loop for enter or next line
       if((*firstPointer) < (*secondPointer))
       {
           return -1;  
       }
       else if((*firstPointer) > (*secondPointer))
       {
           return 1;
       }
       firstPointer++; 
       secondPointer++;
   }
   if((*firstPointer) == '\0' && (*secondPointer) == '\0'){
       return 0;
   }
   else if((*firstPointer) == '\0')
   {
       return -1;
   }
   else
   {
       return 1;
   }
}

void removingEnter(char *enterKey){
   char *pointer = &(enterKey[0]);   
   while(!(pointer == NULL))
   {
       if('\n' == (*pointer))
       {
           *pointer = '\0';
           break;
       } 
       pointer += 1;
   }
}

int strcmpForCaseInsensitivity(char *line1 , char *line2){  // Function for case insensitive
   char *firstPointer = line1;
   char *secondPointer = line2;   
   while(!((*firstPointer) == '\0' && (*secondPointer) == '\0')){
       char firstCharacter = *firstPointer;
       char secondCharacter = *secondPointer; 
       firstCharacter = tolower(firstCharacter); 
       secondCharacter = tolower(secondCharacter);
       if(firstCharacter < secondCharacter){
       return -1;
       }
       else if(firstCharacter > secondCharacter)
       {
           return 1;
           }
           firstPointer++;
           secondPointer++;
   }
   if((*firstPointer) == '\0' && (*secondPointer) == '\0' ){
       return 0;
   }
   else if((*firstPointer) == '\0' ){
       return -1;
   }
   else
   { 
       return 1;
   }
}

ssize_t getdelim(char **linep, size_t *n, int delim, FILE *fp){  // Function to get line as input, allocating size of objects in memory
    int ch;
    size_t i = 0;
    if(!linep || !n || !fp){
        errno = EINVAL;
        return -1;
    }
    if(*linep == NULL){
        if(NULL==(*linep = malloc(*n=128))){
            *n = 0;
            errno = ENOMEM;
            return -1;
        }
    }
    while((ch = fgetc(fp)) != EOF){
        if(i + 1 >= *n){
            char *temp = realloc(*linep, *n + 128);
            if(!temp){
                errno = ENOMEM;
                return -1;
            }
            *n += 128;
            *linep = temp;
        }
        (*linep)[i++] = ch;
        if(ch == delim)
            break;
    }
    (*linep)[i] = '\0';
    return !i && ch == EOF ? -1 : i;
}
ssize_t getline(char **linep, size_t *n, FILE *fp){
    return getdelim(linep, n, '\n', fp);
}

int comparingLines(bool ifSensitivity, char* line1, char* line2){  // Function to compare input strings
   if(ifSensitivity == false)
   {
       return strcmpForCaseInsensitivity(line1,line2);
   }   
   else
   {
       return strcmpForCaseSensitivity(line1,line2);
   }
}

void add(bool ifSensitivity, char* temp1, Node *root)  // Function to insert nodes in tree
{
   Node *parentNode = NULL;
   Node *temp2 = root;
   while(!(temp2 == NULL))
   {
       if(0 <comparingLines(ifSensitivity, temp2->key,temp1))
       {
           parentNode = temp2;
           temp2 = temp2->left;
        }
  else if(0 == comparingLines(ifSensitivity, temp2->key, temp1))
  {
  temp2->data += 1;
           return;
           }
  else
  {
      parentNode = temp2;
      temp2 = temp2->right;
      }
   }

   Node* lastNode = (Node*)malloc(sizeof(Node)*1);  // Creating note do add it in the binary tree
   lastNode->right = NULL;
   lastNode->left = NULL;
   lastNode->key = temp1;
   lastNode->data = 1;
   if(comparingLines(ifSensitivity, parentNode->key,temp1) < 0)
   {
       parentNode->right = lastNode;
   }
   else{
       parentNode->left = lastNode;
       }
}


void sortedData(Node* current){  // Function to display sorted strings
   if(current == NULL){
       return;
   }   
   sortedData(current->left);
   printf("%d %s\n", current->data, current->key);
   sortedData(current->right);
}


void printToFile(FILE *writeFilePointer, Node *current){ // Function to file print sorted strings
    if(current == NULL){
        return;
        }
        printToFile(writeFilePointer, current->left);
        fprintf(writeFilePointer, "%d %s\n", current->data, current->key);
        printToFile(writeFilePointer, current->right);
}


int main(int argc,char** argv){

   int err = 0;
   int arrayIndex;  
   char *outputFile = "";
   char *inputFile = "";   
   bool ifSensitivity = false;
   int isOutput = 0;
   int choice;
   int j;
   int invalidCommand = 0;

opterr = 0; // Track errors by getopt function

static char usage[] = "Usage: bstsort [-c] [-o output_file_name] [input_file_name]\n"; // Read command from command line
   while((choice = getopt(argc, argv, "co:")) != -1){
       switch(choice)
       {
           case 'c':
               ifSensitivity = true;
               break;
           case 'o':
                isOutput = 1;
                outputFile = optarg;
               break;
           case 'i':
                inputFile = optarg;
                break;
       }
   }

    if (err)
   {
   	printf("Usage: bstsort [-c] [-o output_file_name] [input_file_name]\n");
   	exit(1);
   }

    if (opterr)
   {
   	printf("Usage: bstsort [-c] [-o output_file_name] [input_file_name]\n");
   	exit(1);
   }

    if (invalidCommand == 1)
    {
        printf("***Error*** Check your input. %s \n", argv[0]);
        exit(1);
    }
   int arrayLength = 100;  //Assign size of array of characters
   char **charArray = (char**)(malloc(sizeof(char*)*arrayLength));
   for (arrayIndex = optind; arrayIndex < argc; arrayIndex++)
   {
      inputFile = argv[arrayIndex];
   }
   int index = 0;
   if(0 == strcmp(inputFile ,"")){ 
       printf("Please enter lines to be sorted, hit enter to add a new line and hit enter twice to exit.\n");
       printf("\n");
       size_t sizeOfLine;
       char *sentence = (char*)malloc(100*sizeof(char));      
       while(!(getline(&sentence, &sizeOfLine, stdin) == -1))
       {
           if(0 == strcmp(sentence,"\n"))
           {
               break;
            }
          removingEnter(sentence);
          charArray[index++] = sentence;
          sentence = (char*)malloc(100*sizeof(char));
        }
   }
   else{      
      char *sentence=(char*)malloc(100*sizeof(char));  // Getting input file name
      FILE *input = fopen(inputFile ,"r");
      size_t sizeOfLine;
      if(input == NULL)
      {
          printf("Missing file %s Check Source Path or Name.\n", inputFile);
          printf("\n");
          exit(1);
      }
      else{
          while(getline(&sentence,&sizeOfLine,input)!= -1)
          {
   	   char *pointer = &(sentence[0]);  // Empty line found break
   	   if(*pointer == '\n')
   	   {
   	   	break;
   	   }
           else if(!(feof(input)))
              {
                  removingEnter(sentence);
                  charArray[index++] = sentence;
                  sentence = (char*)malloc(100*sizeof(char));
               }
   	   }
      fclose(input);
      }	  
   }
   Node *root;
   int treeSize = 0;
   for(j = index-1 ; j >=0 ; j--){
      char *temp = charArray[j];
      if(treeSize != 0){
          add(ifSensitivity, temp,root);
      }
      else{
          Node *newNode = (Node*)malloc(1*sizeof(Node));  // Allocating memory
          newNode->key=temp;
          newNode->data = 1;
          newNode->right = NULL;
          newNode->left = NULL;
          root = newNode;
      }
       treeSize++;
       }
    if(isOutput ==  1)
    {
        FILE *writeFilePointer;
        int i;
        writeFilePointer = fopen(outputFile, "w");  // Writing data on file
        printToFile(writeFilePointer, root);
        printf("Sorted lines are printed on file name %s\n.", outputFile);
    }
    else{
       sortedData(root);
    }
exit(0);
}

