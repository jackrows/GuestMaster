/******************************************
*	Implementation of General Functions
*******************************************/

#include "GeneralFunctions.h"

/*Store a word from a file randomly
* Return the size of located(reallocated) memory*/
int TakeSecretWord(FILE* fp, char* secret_word)
{
	time_t t;
	srand((unsigned)time(&t));		/*Initialize the rand function*/
	
	char* ret_fget;					/*Store the return of fgets. */
	int size = SIZE_WORD;			/*Assign the global variable, used also on resizing the array*/
	
	while(!feof(fp))	/*Until the EOF*/
	{
		ret_fget = fgets(secret_word, SIZE_WORD, fp);	/*Keeping the return of fgets to check if reached the EOF before break occur(selected a word)*/
		
		if(ret_fget == NULL)	/*Check if EOF has reached before a random line select*/
			fseek(fp, 0, SEEK_SET);	/*Reset the file pointer at the begining of the file*/
			
		int i;
		for(i = 0; i < size; i++)	/*Access the characters of secret word*/
		{
			if(i == size - 1)	/*If is the last character of the string*/
				if(secret_word[i] != '\n')	/*Check if isn't equal with new line, then realloc needed*/
				{
					size *= 2;
					ResizeMemory(secret_word, fp, size);		/*Resize the string to fit in the word*/
					continue;
				}
			if(secret_word[i] == '\n')	/*The word fit in the located memory*/
				break;
		}/*for*/
		
		if(i <= 3)	/*Avoid too small words, empty lines*/
			continue;
			
		if((rand() % 100 ) >= 93)	/*Getting out of the loop randomly. This is used to store from file random word*/
			break;
			
		size = SIZE_WORD;	/*Assign again the size with global size to get the next line*/
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
}

/*Most important function for the game. Perfom the main operation
* Return 0 if found the secret word, 1 if not founed, -1 for error occurs */
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
	
	int founded[size];		/*Store the position of the founded characters, use the size that maybe change from TakeSecretWord()*/
	
	user_input = malloc(sizeof(char) * size * 2);
	if(user_input == NULL)
		return -1;	/*Error in malloc*/	
		
	for(i = 0; i < size; i++)	/*Initialize the array. -1 means that the letter doesn't founded*/
		founded[i] = -1;
		
	printf("\n- Write your inspiration\n");
	while(tries < TRIES)	/*User attemps*/
	{
		printf("%d / %d attemp\n", tries+1, TRIES);
		fgets(user_input, size, stdin);
		check_user = CheckUserInput(user_input);	/*Check the input of user, if is small, wrong.*/
		if(check_user == 1)	/*Small input text*/
		{
			printf("\n#Please keyboard a word contains more than %d characters.\n\n", MIN_INPUT);
			continue;
		}
		else if(check_user == 2)	/*Alphabetic*/
		{
			printf("\n#This input format is not acceptable.\n\n");
			continue;
		}
		
		/*Compare the user input with secret word*/
		CompareWords(secret_word, user_input, size, founded);
		
		/*Appear the existed letters*/
		DisplayFounded(secret_word, founded);
		
		returned = CheckGuesting(founded, size);	/*Check if the secret word founded*/
		if(returned == 0)	/*Found it!!!*/
		{
			returned = 0;
			break;
		}
		else				/*Missing characters*/
			tries++;
	}/*while*/
	
	/*Status of game(win, lose)*/
	if(returned == 0)	/*Win*/
		return returned;
	else
		returned = 1;	/*Lose*/
	return returned;
}/*function*/

/*Perform a compare every character from user with the secret word
* Update the founded array at StartGame()*/
void CompareWords(const char* secret, const char* user, const int size, int bingo[])
{
	int i,j;			/*Indexings*/
	int finded[size];	/*Temporary array for each attemp*/
		
	for(i = 0; i < size; i++)	/*Initialize the temp array*/
		finded[i] = -1;
			
	printf("\n");
	for(i = 0; i < size; i++)	/*Access the user input, every character separate*/
	{
		if(user[i] == '\n')		/*If reach the end of string*/
			break;
			
		for(j = 0; j < size; j++)	/*Access the secret word*/
		{
			if(secret[j] == '\n')	/*If reach the end of string*/
				break;
			
			if(bingo[j] != -1 || finded[j] != -1)	/*If the current character has been already founded*/
				continue;
			
			if(bingo[j] == size)	/*If the user input is smaller from the secret word, to avoid beyond array bound access*/
				break;
				
			if(user[i] == secret[j])	/*The letter exist in the secret word, change the specific value from -1*/
				finded[j] = j;
		}/*Inner for*/
	}/*Outer for*/
	
	for(i = 0; i < size; i++)	/*Update the founded array of StartGame()*/
	{
		if(bingo[i] == -1)
			bingo[i] = finded[i];
			
		if(secret[i] == '\n')	/*At the end of secret word*/
		{
			bingo[i] = size;	/*The founded characters end with the total characters size, this protect us if the secret word is smaller that the allocated memory*/
			break;
		}
	}
	return ;
}

/*Appear on the screen the finded characters so far*/
void DisplayFounded(const char* secret, int founded[])
{
	const char* index = secret;	
	int i = 0;
	printf("#Guesting so far :");
	for(; *index != '\n'; index++)	/*Access the string untill new line*/
	{
		if(founded[i] != -1)		/*The character has been founded and displayed*/
			printf("%c", *index);
		else						/*The character hasn't been founded and a space printed*/
			printf(" ");
		i++;
	}
	printf("\n\n");
}

/*Check if the secret word has been found
* Return 0 if found, 1 if not found*/
int CheckGuesting(int bingo[], int size)
{
	int i;
	int returned = 0;
	for(i = 0; i < size; i++)
	{
		if(bingo[i] == size)	/*Reach at the end of the secret word, because size memory located is bigger that the word in the file*/
			break;
			
		if(bingo[i] == -1)		/*At least one character doesn't found*/
		{
			returned = 1;	/*Not completed founded the word*/
			break;
		}
	}
	return returned;
}

/*Check the input by the user. Not accept small word(<MIN_INPUT), or alphabet
* Return 1 for short word, 2 for alphabet, 0 for right input*/
int CheckUserInput(const char* user)
{
	int i = 0;
	const char* index = user;
	for(; (*index != '\n') && (*index != '\0'); index++)
		i++;	/*Count the characters*/
		
	if(*index == '\0')	/*The last character is not new line so the stdin contains extra characters from fgets*/
		Flushing();		/*Clean up the stdin buffer*/
		
	if(i <= MIN_INPUT)
		return 1;	/*Short word input by the user*/
		
	if(strcmp(user, "abcdefghijklmnopqrstuvwxyz") == 0 || strcmp(user, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 0)
		return 2;	/*Not accept the alphabetic*/
	if(strncmp(user, "abcdefghijklmnopqrstuvwxyz", i) == 0 || strncmp(user, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", i) == 0)
		return 2;	/*Not accept the alphabetic*/
	if(strncmp(user, "zyxwvutsrqponmlkjihgfedcba", i) == 0 || strncmp(user, "ZYXWVUTSRQPONMLKJIHGFEDCBA", i) == 0)
		return 2;	/*Not accept the alphabetic reverse*/
	
	return 0;	/*Right format*/
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
