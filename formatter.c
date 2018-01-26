/*---------------------------------------------------------------------- 
 * formatter.c:
 *
 * compilation: 
 *	gcc -o formatter formatter.c
 * usage:
 *	./formatter <input-file> <output-file> <width>
 * 
 *-----------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "list.h"

void formatter( FILE *, FILE *, int );
char* insertLetter(char*, const char, const int);
void printRepeated(const char c, const int limit, FILE *outfile );
void printWord(char* word, FILE *outfile );
void printWordList(int numWords, int listSize, int bufferSize, list_t* top, list_t* cur, FILE *outfile, int width);
	
main( int argc, char *argv[] )
{
	FILE *ifp, *ofp;
	clock_t begin_time, end_time;
	double time_used;


	if (argc < 4) {
	  fprintf(stderr,"Not enough arguments\n");
	  exit(1);
	}
	if (!(ifp = fopen(argv[1],"r"))) {
	  fprintf(stderr,"Cannot open file %s\n",argv[1]);
	  exit(1);
	}
	if (!(ofp = fopen(argv[2],"w"))) {
	  fprintf(stderr,"Cannot open file %s\n",argv[2]);
	  exit(1);
	}

	begin_time = clock();
	formatter( ifp, ofp, atoi(argv[3]));
	end_time = clock();
	time_used = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
	fprintf( stderr, "Time usage = %17.13f\n", time_used );

  	fclose(ifp);
  	fclose(ofp);
}

//----------------------------------------------------------------------------------------------------

void formatter( FILE *infile, FILE *outfile, int width ) {
	char c;// the next character to read from the file
	char* buffer = NULL;// the current word (buffer)
	int bufferSize = 0;// size of the current word (buffer)
	int listSize = 0;// length of the whole linked list including one space in between each word
	int numWords = 0;// number of words in linked list (i.e size)
	list_t *top, *cur = NULL; 
		
	// read each character from file 
	while ( (c = getc( infile )) != EOF ) {

		//check if the character is a space		
		if( isspace(c) ) {
			
			// if size of buffer is not 0, add word to linked list
			if(bufferSize != 0){
	
				if(top == NULL)// check if linked list is empty
					top = cur = make_list(buffer);
				else {
					cur->next = make_list(buffer);
					cur = cur->next;
				}		
				listSize += bufferSize+1;// +1 for space on right (accounted for in printWordList)	
				bufferSize = 0;
				buffer = NULL;
				++numWords;
			}
		}
		else {// add character to the current buffer
			buffer = insertLetter(buffer, c, bufferSize); 
			bufferSize++;
			
			// buffer size must stay less than the current word
			if(bufferSize > width) {
	  			fprintf(stderr,"Error: Word size must be less than %d.\n", width);
	  			exit(1);
			}		
		}
		// deal with sizing
		if(listSize-1 + bufferSize >= width) {
			--listSize;// get rid of extra space on end
			printWordList(numWords, listSize, bufferSize, top, cur, outfile, width);
			
			listSize = numWords = 0;
			freeList(top);
			top = cur = NULL;		
		}
	}
	--listSize;// get rid of extra space on end
	printWordList(numWords, listSize, bufferSize, top, cur, outfile, width);
	putc('\n', stderr);
	putc('\n', outfile);			
}

//----------------------------------------------------------------------------------------------------

void printWordList(int numWords, int listSize, int bufferSize, list_t* top, list_t* cur, FILE *outfile, int width) {
	if(numWords > 1) {
		
		if(bufferSize == 0) {
			cur = top;
			while(cur != NULL) {// iterate through linked list of words
				printWord(cur->c, outfile);
				putc(' ', outfile);
				cur = cur->next;				
			}
		}
		else {// calculate spaces
			int numLetters = listSize - 1*(numWords-1);
			int spacesRight = width - numLetters;
			int spacingWidth = spacesRight / (numWords-1);
			int extraSpaces = spacesRight % (numWords-1);
			cur = top;

			while(cur != NULL) {// iterate through linked list of words
				printWord(cur->c, outfile);
				
				// print spacing
				printRepeated(' ', spacingWidth, outfile);
				if(extraSpaces > 0){
					putc(' ', outfile);
					--extraSpaces;
				}
				
				cur = cur->next;
			}
		}
	}
	else {// single word to print
		assert(top->next == NULL);
		int spacesRight = width - listSize;
		printRepeated(' ', spacesRight, outfile);
		printWord(top->c, outfile);
	}
	putc('\n', outfile);
}

//----------------------------------------------------------------------------------------------------

void printWord(char* word, FILE *outfile ){
	for(int i = 0; word[i]!='\0'; ++i)
	 	putc(word[i], outfile);
}

//----------------------------------------------------------------------------------------------------

void printRepeated(const char c, const int limit, FILE *outfile ){
	for(int i = 0; i < limit; ++i)
		putc(c, outfile);
}

//----------------------------------------------------------------------------------------------------

char* insertLetter(char* word, const char c, const int size) {
	char* newWord = calloc(size+2, sizeof(char));
	for(int i = 0; i < size; ++i)
		newWord[i] = word[i];

	newWord[size] = c;
	newWord[size+1] = '\0';
	if(word != NULL)
		free(word);
	return newWord;
}				
