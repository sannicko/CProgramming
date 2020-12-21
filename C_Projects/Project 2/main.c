#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bmplib.h"

/* This program will manipulate image from a 24-bit uncompressed bmp file. It will flips the image vertically, enlarge the image by an integer scale factor and
 * rotate the image either clockwise or counter-clockwise by a certain degree (Which must be a multiple of 90) depending wether the rotation degree is
 * positive or negative. Positive is clockwise and negative is counterclockwise.
 *
 * Nick Jimenez
 * November 22 / 2020
 */
/*
 * This method enlarges a 24-bit, uncompressed .bmp file
 * that has been read in using readFile()
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the original number of rows
 * cols     - the original number of columns
 *
 * scale    - the multiplier applied to EACH OF the rows and columns, e.g.
 *           if scale=2, then 2* rows and 2*cols
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows (scale*rows)
 * newcols  - the new number of cols (scale*cols)
 */
 int enlarge(PIXEL* original, int rows, int cols, int scale,
	 PIXEL** new, int* newrows, int* newcols)
	 {
		 int row, col;
		 *newrows=rows*scale;
		 *newcols=cols*scale;
		 if ((rows <= 0) || (cols <= 0)) return -1;

		 *new = (PIXEL*)malloc(scale*scale*rows*cols*sizeof(PIXEL));

		 for (row=0; row < rows; row++){
			 for (col=0; col < cols; col++) {
				 PIXEL* o = original + row*cols + col;
				 PIXEL* n = (*new) + (row*scale)*(*newcols) + (col*scale);
				 *n = *o;
			 }
		 }
		 return 0;
	 }
/*
 * This method rotates a 24-bit, uncompressed .bmp file that has been read
 * in using readFile(). The rotation is expressed in degrees and can be
 * positive, negative, or 0 -- but it must be a multiple of 90 degrees
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 * rotation - a positive or negative rotation,
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows
 * newcols  - the new number of cols
 */

 int rotate(PIXEL* original, int rows, int cols, int rotation,
	 PIXEL** new, int* newrows, int* newcols)
	 {
		 PIXEL* copy=original;
		 int row, col;
		 *newrows=rows;
		 *newcols=cols;
		 int turns=(int)rotation/90;
		 turns=turns%4;
		 printf("%d:%d:%d",rotation,turns,12);
		 while(turns>0 ){
			 if ((rows <= 0) || (cols <= 0)) return -1;
			 *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));
			 for (row=0; row < rows; row++){
				 for (col=0; col < cols; col++) {
					 PIXEL* o = copy + row*cols + col;
					 PIXEL* n = (*new) + ((rows-1-col)*cols)+row;
					 *n = *o;
				 }
			 }
			 turns--;
			 copy=*new;
		 }
		 while(turns<0){
			 if ((rows <= 0) || (cols <= 0)) return -1;
			 *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

			 for (row=0; row < rows; row++){
				 for (col=0; col < cols; col++) {
					 PIXEL* o = copy + row*cols + col;
					 PIXEL* n = (*new) + (rows-row-1)+(cols*col);
					 *n = *o;
				 }
			 }
			 turns++;
			 copy=*new;
		 }
		 return 0;
	 }

/*
 * This method Vertically flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile().
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */

 int verticalflip (PIXEL *original, PIXEL **new, int rows, int cols)
 {
	 int row, col;

	 if ((rows <= 0) || (cols <= 0)) return -1;

	 *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

	 for (row=0; row < rows; row++){
		 for (col=0; col < cols; col++) {
			 PIXEL* o = original + row*cols + col;
			 PIXEL* n = (*new) + (rows-row-1)*cols + (col);
			 *n = *o;
		 }
	 }
	 return 0;
 }

/*
 * This method horizontally flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile().
 *
 * THIS IS GIVEN TO YOU SOLELY TO LOOK AT AS AN EXAMPLE
 * TRY TO UNDERSTAND HOW IT WORKS
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */
 int flip (PIXEL *original, PIXEL **new, int rows, int cols)
 {
	 int row, col;

	 if ((rows <= 0) || (cols <= 0)) return -1;

	 *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

	 for (row=0; row < rows; row++){
		 for (col=0; col < cols; col++) {
			 PIXEL* o = original + row*cols + col;
			 PIXEL* n = (*new) + row*cols + (cols-1-col);
			 *n = *o;
		 }
	 }
	 return 0;
 }


 int main(int argc, char *argv[])
 {
	 int r, c;
	 int scale=0;
	 int rotation=0;
	 PIXEL *b, *nb;
	 PIXEL **copy;
	 int newr=0;
	 int newc=0;
	 char* input="example.bmp";
	 char* output="output.bmp";
	 int checkflip=0;
	 int checkvflip=0;
	 int oflag=0;
	 int iflag=0;

	 // Checking input arguments
	 if(argc<=1){
		 printf("Check your input, arguments required as: [-s scale | -r degree | -f | -v ] [-o output_file] [input_file] \n");
		 return -1;
	 }

	 int j;
	 for (j=1;j<argc;j++){  // Reading each argument
		 if(*argv[j]=='-'){
			 if (*(argv[j]+2)=='\0'){
				 switch (*(argv[j]+1)){
					 case 's':  // Scale image
					 scale=atoi(argv[j+1]);
					 printf("%d : Is the scale\n",scale);
					 if((j!=argc-2)&&(*(argv[j+2])!='-')){
						 input=argv[j+2];
						 iflag=1;
					 }
					 break;
					 case 'r':  // Rotate image
					 rotation=atoi(argv[j+1]);
					 printf("%d : Is the rotation\n",rotation);
					 if((j!=argc-2)&&(*(argv[j+2])!='-')){
						 input=argv[j+2];
						 iflag=1;
					 }
					 break;
					 case 'f':
					 checkflip=1;  // Flip image
                                         printf("Flip Image\n");
					 if((j!=argc-1)&&(*(argv[j+1])!='-')){
						 input=argv[j+1];
						 iflag=1;
					 }
					 break;
					 case 'v':  // Vertical flip
					 checkvflip=1;
					 printf("Vertical Flip\n");
					 if((j!=argc-1)&&(*(argv[j+1])!='-')){
						 input=argv[j+1];
						 iflag=1;
					 }
					 break;
					 case 'o':  // Output bmp file
					 output=argv[j+1];
					 oflag=1;
					 if((j+2)!=argc){
						 input=argv[j+2];
						 iflag=1;
					 }
					 default:
					 break;
				 }
			 }
		 }
	 }
         if(rotation<90 && rotation>-90){  // Check if the rotation input is multiple of 90
                 printf("Check your input rotation input must be a multiple of 90\n");
                 return 0;
         }

	 if(iflag!=0){
		 readFile(input, &r, &c, &b);  // Check if no input file is provided
	 }else{
		 readFile("example.bmp", &r, &c, &b);
	 }
	 copy=&b;
	 if(scale!=0){
		 enlarge(*copy,r,c,2,&nb,&newr,&newc);
		 copy=&nb;
		 r=newr;
		 c=newc;
	 }
	 if(rotation!=0||((rotation/90)%4)!=0){  // Check if rotation is not set or rotation is complete rotation
		 rotate(*copy,r,c,rotation,&nb,&newr,&newc);
		 copy=&nb;
	 }
	 if(checkflip!=0){  // Horizontal flip image
		 flip(*copy, &nb, r, c);
		 copy=&nb;
	 }
	 if(checkvflip!=0){  // Vertical flip image
		 verticalflip(*copy,&nb, r,c);

	 }
	 if(oflag!=0){  // Final Output image
		 writeFile(output, r, c, nb);
	 }else{
		 writeFile("result.bmp", r, c, nb);
	 }

	 free(b);
	 free(nb);
	 return 0;
 }
