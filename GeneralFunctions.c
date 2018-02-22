/******************************************
*	Implementation of General Functions
*******************************************/

#include "GeneralFunctions.h"

/*Store a word from a file randomly
* Return the size of located(reallocated) memory*/
int TakeSecretWord(FILE* fp, char* secret_word)
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
		if(i <= 3)	/*Avoid too small words, empty lines*/
			continue;
			
		if((rand() % 100 ) >= 80)	/*Getting out of the loop randomly. This is used to store from file random word*/
			break;
		size = SIZE_WORD;
		/*Flushing();*/
	}/*while*/
	return size;
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

/**/
int StartGame(FILE* fp, char* secret_word)
{
	/*Variables*/
	int returned = -1;		/*Stored the return value*/
	int tries = 0;			/*Stored the guesting attemp*/
	int i;					/*Access arrays*/
	int size = SIZE_WORD;	/*Store the returned size of TakeSecretWord and used it on malloc*/
	char*	user_input;		/*Store the input word*/
	int		check_user;		/*Store the return from function CheckUserInput*/
	
	printf("\n#Picking a secret word... ");
	size = TakeSecretWord(fp, secret_word);		/*Take a random word from the file and store it to secret_word*/
	printf("Done\n");
	int founded[size];		/*Store the position of the founded characters*/
	
	user_input = malloc(sizeof(char) * size * 2);
	if(user_input == NULL)
		return 1;	/*Error in malloc*/	
		
	for(i = 0; i < size; i++)
		founded[i] = -1;
		
	printf("\n- Write your inspiration\n");
	while(tries < TRIES)	/*User attemps*/
	{
		printf("%d / %d attemp\n", tries+1, TRIES);
		fgets(user_input, size, stdin);
		check_user = CheckUserInput(user_input);
		if(check_user == 1)
		{
			printf("\n#Please keyboard a word contains more than %d characters.\n\n", MIN_INPUT);
			continue;
		}
		else if(check_user == 2)
		{
			printf("\n#This input format is not acceptable.\n\n");
			continue;
		}
		/*printf("user inputs %s\n", user_input);*/
		
		/*Compare the user guestign with secret word*/
		CompareWords(secret_word, user_input, size, founded);
		/*Appear the existed letters*/
		DisplayFounded(secret_word, founded);
		returned = CheckGuesting(founded, size);
		if(returned == 0)	/*Found it!!!*/
		{
			returned = 0;
			break;
		}
		else				/*Missing characters*/
			tries++;
	}
	
	/*Status of game(win, lose)*/
	if(returned == 0)	/*Win*/
		return returned;
	else
		returned = 1;	/*Lose*/
	return returned;
}

/**/
void CompareWords(const char* secret, const char* user, const int size, int bingo[])
{
	int i,j;
	int finded[size];
	for(i = 0; i < size; i++)
		finded[i] = -1;
			
	printf("\n");
	for(i = 0; i < size; i++)
	{
		if(user[i] == '\n')
		{
			break;
		}
		for(j = 0; j < size; j++)
		{
			if(secret[j] == '\n')
				break;
			
			if(bingo[j] != -1 || finded[j] != -1)
				continue;
			
			if(bingo[j] == size)
				break;
				
			if(user[i] == secret[j])
			{
				finded[j] = j;
				/*printf("%c", secret[j]);*/
			}
			/*else
				printf(" ");*/
		}
		/*printf("\n");*/
	}
	for(i = 0; i < size; i++)
	{
		if(bingo[i] == -1)
			bingo[i] = finded[i];
			
		if(secret[i] == '\n')
		{
			bingo[i] = size;
			break;
		}
	/*	if(bingo[i] != -1)
			printf("%c", secret[i]);
		else
			printf(" ");*/
	}
	/*printf("\n");*/
	return ;
}

/**/
void DisplayFounded(const char* secret, int founded[])
{
	const char* index = secret;
	int i = 0;
	printf("#Guesting so far :");
	for(; *index != '\n'; index++)
	{
		if(founded[i] != -1)
			printf("%c", *index);
		else
			printf(" ");
		i++;
	}
	printf("\n\n");
}

/**/
int CheckGuesting(int bingo[], int size)
{
	int i;
	int returned = 0;
	for(i = 0; i < size; i++)
	{
		if(bingo[i] == size)
		{
			break;
		}
		if(bingo[i] == -1)
		{
			returned = 1;	/*Not completed founded the word*/
			break;
		}
	}
	return returned;
}

/**/
int CheckUserInput(const char* user)
{
	int i = 0;
	const char* index = user;
	for(; (*index != '\n') && (*index != '\0'); index++)
	{
		i++;
	}
	if(*index == '\0')
		Flushing();
	if(i <= 3)
		return 1;	/*Short word input by the user*/
		
	if(strcmp(user, "abcdefghijklmnopqrstuvwxyz") == 0 || strcmp(user, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 0)
		return 2;	/*Not accept the alphabetic*/
	if(strncmp(user, "abcdefghijklmnopqrstuvwxyz", i) == 0 || strncmp(user, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", i) == 0)
		return 2;
	if(strncmp(user, "zyxwvuts"))
	return 0;
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
	printf(" goal is to find it. You have available %d attemps. You have to insert a word with more\n", TRIES);
	printf(" %d letters, if any letters contain in secret word they will displayed.\n", MIN_INPUT);
	printf(" Keep in mind that the characters isn't case sensitive.\n");
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
