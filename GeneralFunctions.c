/******************************************
*	Implementation of General Functions
*******************************************/

#include "GeneralFunctions.h"

/*Store a word from a file randomly
* Return the word*/
void TakeSecretWord(FILE* fp, char* secret_word)
{
	time_t t;
	srand((unsigned)time(&t));
	char* ret_fget;					/*Store the return of fgets. */
	int size = SIZE_WORD;			/*Assign the global variable, used also on resizing the array*/
	/*char* hidden_word = NULL;		Store the word that user will try to find*/
	
	while(!feof(fp))	/*Until the EOF*/
	{
		ret_fget = fgets(secret_word, SIZE_WORD, fp);	/*Keeping the return of fgets to check if reached the EOF before break occur*/
		
		if(ret_fget == NULL)	/*Check if EOF has reached before a random line select*/
			fseek(fp, 0, SEEK_SET);
			
		int i;
		for(i = 0; i < size; i++)	/*Access the characters of secret word*/
		{
			if(i == size - 1)	/*If is the last character of the string*/
				if(secret_word[i] != '\n')	/*Check if is equal with new line*/
				{
					/*printf("\n#realloc is needed\n");*/
					size *= 2;
					ResizeMemory(secret_word, fp, size);		/*Resize the string to fit in the word*/
					continue;
					/*printf("%s\n", hidden_word);*/
					break;
				}
			if(secret_word[i] == '\n')	/*The word fit in the located memory*/
			{
				/*printf("\n");*/
				break;
			}
			/*printf("%c", hidden_word[i]);*/
		}/*for*/
		if(i < 3)	/*Avoid too small words, empty lines*/
			continue;
			
		if((rand() % 100 ) >= 80)	/*Getting out of the loop randomly. This is used to store from file random word*/
			break;
		size = SIZE_WORD;
		/*Flushing();*/
	}/*while*/
	return;
}

/*Realloc the memory to store the word from the file*/
void ResizeMemory(char* hidden_word, FILE* fp, int size)
{
	hidden_word = realloc(hidden_word, size);
	char append[SIZE_WORD];
	fgets(append,SIZE_WORD, fp);	/*Get from the file the rest word*/
	strcat(hidden_word, append);	/*Append it to the rest word*/
	/*printf("%s\n", hidden_word);*/
}

/*Clean up the input buffer of stdin*/
void Flushing()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

/*Display some simple graphics at the begging*/
void PrintEntry()
{
	printf("\n");
	printf("\t\t--------------------------------------------------------------------------\n");
	printf("\t\t------------------------\t\t\t    ----------------------\n");
	printf("\t\t\t\t\t\tGUEST MASTER\n");
	printf("\t\t------------------------\t\t\t    ----------------------\n");
	printf("\t\t--------------------------------------------------------------------------\n");
	printf("\n\n");
	return;
}

/*Display a brief explanation of the game*/
void Explanation()
{
	printf("\n====================================================================================\n");
	printf(" Welcome to text game Guest Master. Prepare to discover your spirit rapper skills.\n");
	printf(" You will play against computer. Your opposer will keep a single word and your\n");
	printf(" goal is to find it. You have available %d. You have to insert a word with more\n", TRIES);
	printf(" %d letters, if any letters contain in secret word they will displayed.", MIN_INPUT);
	printf(" Good Luck!\n");
	printf("====================================================================================\n");
}

/*Display the available option for the user*/
void PrintOption()
{
	printf("\nPlease choose your action\n");
	printf(" 1 - Start Game\n");
	printf(" 2 - About\n");
	printf(" 3 - Exit\n");
	printf("\n");
}
