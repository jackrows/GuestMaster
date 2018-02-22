/**********************************
*	Guest Master game
*	Author	: Polychronopoulos
*	Nickname: cosm0sd3v
***********************************/

#include "GeneralFunctions.h"


int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("\n#Error - Wrong number of command line arguments.\n");
		printf("#Please specify only the whole path of the file.\n");
		return 1;
	}
	if(strcmp(argv[1], "Help") == 0 || (strcmp(argv[1], "help") == 0) || (strcmp(argv[1], "H") == 0) || (strcmp(argv[1], "h") == 0))
	{
		printf("\n#USAGE:\n");
		printf("#To run the game please specify an txt file with same words inside.\n");
		printf("#e.g.: $./GuestMaster /home/user/data.txt\n");
		return 1;
	}
	/*Variables*/
	char* filename = argv[1];		/*Assign the command line argument(path/filename) to string*/
	FILE* fp = NULL;				/*Open the file that user specify from command line*/
	char* hidden_word = NULL;		/*Store the word that user will try to find*/
	int	  option = -1;				/*Store the user's option*/
	int   ret_scanf = -1;			/*Store the return value of scanf, check invalid input from user*/
	/*char* ret_fget;					Store the return of fgets. */
	/*int seek = 0;					Store the seeking position to move the file to take the word*/	/*Other aproach is to use a array, store all file in it and take a random row*/
	
	fp = fopen(filename, "r");		/*Open the file for reading*/
	if(fp == NULL)	/*Check the fopen()*/
	{
		printf("\n#ERROR - Couldn't open the file [%s]\n", filename);
		printf("#Possible reasons - wrong path / wrong name / unknown file type.\n");
		return 1;
	}
	hidden_word = malloc(sizeof(char) * SIZE_WORD);
	if(hidden_word == NULL)	/*Check the above malloc*/
	{
		printf("\n#ERROR - Error in execution of alocation memory\n");
		return 1;
	}
	
	PrintEntry();
	PrintOption();
	while( (ret_scanf = scanf(" %d", &option)) == 1)
	{
		Flushing();
		switch (option) {
			case 1:;
				int check = -1;
				check = StartGame(fp, hidden_word);
				if(check == 0)	/*Win*/
				{
					printf("\n****************************************************************************************************\n");
					printf("\n\t\t#CONGRATULATION!!!\n");
					printf("\t\t#You did it, you found the secret word. Good Job!\n");
					printf("\n****************************************************************************************************\n");
					printf("\n#If you want to play again press 'y'\n");
					char ch;
					scanf(" %c", &ch);
					if(ch == 'y' || ch == 'Y')
					{
						PrintOption();
						continue;
					}	
					else
						break;
				}
				else if(check == 1)	/*Lose*/
				{
					printf("\n****************************************************************************************************\n");
					printf("\n\t\t#You need practice at your spiri rapper skills.\n");
					printf("\t\t#The secret word was: %s\n", hidden_word);
					printf("****************************************************************************************************\n");
					
					printf("\n#If you want to play again press 'y'\n");
					char ch;
					scanf(" %c", &ch);
					if(ch == 'y' || ch == 'Y')
					{
						PrintOption();
						continue;
					}
					else
						break;
				}
				break;
			case 2:
				Explanation();
				PrintOption();
				continue;
			case 3:
				break;
			default:
				printf("\n#Please input one of the available options.\n");
				continue;
		}
	
		if(option == 1 || option == 3)
			break;
	}
	
	if(ret_scanf == 0)	/*Handle for non integer input from user*/
	{
		printf("\n\t#You have input a non accesible character.\n");
		printf("\t#Please next time keyboard the apropriate input.\n");
		fclose(fp);
		free(hidden_word);
		return 1;
	}
	if(option == 1)
	{
		printf("\n#Exiting the game. Thank you for playing...");
	}
	else if(option == 3)
		printf("\n#Leaving the game...Hope see you soon.\n");
	
	/*fseek(fp, 0, SEEK_SET);		Move the cursor at the start of file*/		
	
	/*TakeSecretWord(fp, hidden_word);
	
	printf("secret word = %s\n", hidden_word);
	printf("%s\n", filename);*/
	
	fclose(fp);		/*Close the file*/
	free(hidden_word);
	return 0;
}
