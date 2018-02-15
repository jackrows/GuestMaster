/**********************************
*	Guest Master game
*	Author	: Polychronopoulos
*	Nickname: cosm0sd3v
***********************************/

#include "GeneralFunctions.h"

#define	SIZE_WORD 15
int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("\n#Error - Wrong number of command line arguments.\n");
		printf("#Please specify only the whole path of the file.\n");
		return 1;
	}
	
	/*Variables*/
	char* filename = argv[1];		/*Assign the command line argument(path/filename) to string*/
	FILE* fp = NULL;				/*Open the file that user specify from command line*/
	char* hidden_word = NULL;		/*Store the word that user will try to find*/
	/*int seek = 0;					Store the seeking position to move the file to take the word*/	/*Other aproach is to use a array, store all file in it and take a random row*/
	
	fp = fopen(filename, "r");		/*Open the file for reading*/
	if(fp == NULL)	/*Check the fopen()*/
	{
		printf("\n#ERROR - Couldn't open the file [%s]\n", filename);
		printf("#Possible reasons - wrong path / wrong name / unknown file type.\n");
		return 1;
	}
	hidden_word = malloc(sizeof(char) * SIZE_WORD);
	if(hidden_word == NULL)
	{
		printf("\n#ERROR - Error in execution of alocation memory\n");
		return 1;
	}
	fseek(fp, 10, SEEK_CUR);
	fgets(hidden_word, 50, fp);
	
	printf("secret word = %s\n", hidden_word);
	printf("%s\n", filename);
	
	fclose(fp);		/*Close the file*/
	return 0;
}
