#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#define MAXLINE 1000 // Maximum number of characters read within a file
#define MAX_ROWS (256)
#define MAX_COLUMNS (256)
#define TEMP_FILE "./temp"

/* This program will accept only the command line options. It will read a text file and print it to the display. It will find
 * the count of the number words in the file, the number of occurrences of a substring, and sort them lexicographically ASCII order.
 *
 * Nick Jimenez
 * October 4 / 2020
 * */

void write_buffer_text_file(const char *wordss[1000][50], unsigned int len); // Functions
void read_buffer_text_file();
void sort_words(int wordCount);
void display_sorted(int wordCound);
static char words[MAX_ROWS][MAX_COLUMNS] = {{'\0', '\0'}};

int search(char *filename, char *str) // Search function in text
{
   int num = 1;
   char word[50];
   FILE *sourceFile = fopen(filename, "r");
   if (sourceFile == NULL)
   {
   	printf("Missing File Check Source Path or Name\n");
   	exit(1);
   }
   while (fscanf(sourceFile, "%s", word) == 1)
   {
   	if (strstr(word, str) !=0)
   	{
   	   num++;
   	}
   }
   fclose(sourceFile);
   return num-1;
}

void read_buffer_text_file() // Read function temporary file
{
   FILE *readFilePointer = NULL;
   if (NULL == (readFilePointer = fopen(TEMP_FILE, "r")))
   {
   	perror("fopen failed");
   	exit(1);
}
   int i = 0;
   while (fgets(words[i], MAX_COLUMNS, readFilePointer))
   {
   	words[i][strlen(words[i]) - 1] = '\0';
   	i++;
   }
   fclose(readFilePointer);
}


void write_buffer_text_file(const char *words[1000][50], unsigned int len) // Write function temporary file
{
   FILE *writeFilePointer;
   int i;
   writeFilePointer = fopen(TEMP_FILE, "w");
   for (i = 0; i < len; i++)
  {
   	fprintf(writeFilePointer, "%s\n", words[i][0]);
   }
   fclose(writeFilePointer);
}


void sort_words(int wordCount) // Sort function bubble sort
{
   int outer_index; 
   int inner_index; 
   char swap[MAX_COLUMNS] = {'\0'};
   for (outer_index = 0; outer_index < (wordCount - 1); outer_index++)
   {
  	for (inner_index = 0; inner_index < (wordCount - outer_index - 1); inner_index++)
   	{
      	   if (0 < strcmp(words[inner_index], words[inner_index + 1]))
    	   { 
   		strcpy(swap, words[inner_index]);
   		strcpy(words[inner_index], words[inner_index + 1]);
   		strcpy(words[inner_index + 1], swap);
           } 
    	} 
   } 
}


void display_sorted(int wordCount) // Display function sorted text ASCII
{                                       
   int i; 
   printf("\n"); 
   for (i = 0; i < wordCount; i++)
   {
   	printf("%s ", words[i]);
   }
   printf("\n");
}


int main(int argc, char *argv[])
{
   int err = 0;
   int count = 0, i;
   char *substring;
   int countFlag = 0;
   int asciiFlag = 0;
   int substringFlag = 0;
   int choice;
   int wordCount;   
   int len;

   FILE *filePointer;
   char str[MAXLINE];
   char *fileName = argv[argc -1];

   filePointer = fopen(fileName, "r");
   if (filePointer == NULL)
   {
   	printf("Error missing file %s\n", fileName);
   	return 1;
   }
   
   printf("\n Source Text on File: \n");
   printf("\n");
   while (fgets(str, MAXLINE, filePointer) != NULL)
   	printf("%s\n", str);
   fclose(filePointer);
   
   opterr = 0; // Track errors by getopt function

   while ((choice = getopt(argc, argv, "scf:")) != -1) // While loop iterates over each argument from command line
   {
   	switch (choice)
   	{
   	case 's':
   	   asciiFlag = 1;
	   break;
   	case 'c':
   	   countFlag = 1;
   	   break;
   	case 'f':
   	   substringFlag = 1;
   	   substring = optarg;
   	   break;
   	}
   }

   if (err)
   {
   	printf("Usage: mywords [-cs] [-f substring] filename \n");
   	exit(1);
   }

   if (opterr)
   {
   	printf("Usage: mywords [-cs] [-f substring] filename \n");
   	exit(1);
   }

   if (substringFlag == 1) // Count
   {
   	wordCount = search(argv[argc - 1], substring); // Count occurrences of the given substring
   	printf(" Number of Occurrences \n");
   	printf("The substring: \"%s\" Appears: \"%d\" times in the file named: %s \n", substring, wordCount, fileName);
   	printf("\n");
   }

   if (asciiFlag == 1) // Sort
   {
   FILE *fp = fopen(fileName, "r");
   	len = 0;
   	printf("Sorted by ASCII Order \n");
   	char buf[1000][50];
   	const char *wordss[1000][50];
	while (fscanf(fp,"%s", buf[len]) != EOF)
   	{
   	   wordss[len][0] = buf[len];
   	   len++;
   	}

   	write_buffer_text_file(wordss, len);
   	read_buffer_text_file();

   	sort_words(len); // Sorting
   	display_sorted(len);
   	fclose(fp);
   	if (remove("./temp") == 0)
   	{
   	   printf("\n ");
   	}
   	else
   	   perror("Error: \n");
   	   return(1); 
   	}

   if (countFlag == 1) // Count words in file
   {
   	FILE *filp;
   	int count = 1;
   	char c;
   	filp = fopen(fileName, "r");
   	if (filp == NULL)
   	   printf("Missing File\n");
   	while((c = fgetc(filp)) != EOF)
   	{
   	   if( c == ' ' || c == '\n')
   	   	count++;
   	}
   	printf("The number of words in the file are: %d\n", count -1);
   	printf("\n");
   	fclose(filp);
   }
   return 0;
}   

