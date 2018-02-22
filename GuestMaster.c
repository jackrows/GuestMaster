/**********************************
*	Guest Master game
*	Author	: Polychronopoulos
*	Nickname: cosm0sd3v
***********************************/

#include "GeneralFunctions.h"


int main(int argc, char **argv)
{
	if(argc != 2)		/*Check the command line arguments to be equal with 2*/
	{
		printf("\n#Error - Wrong number of command line arguments.\n");
		printf("#Please specify only the whole path of the file.\n");
		return 1;
	}
	if(strcmp(argv[1], "Help") == 0 || (strcmp(argv[1], "help") == 0) || (strcmp(argv[1], "H") == 0) || (strcmp(argv[1], "h") == 0))	/*Accept the help as argument and display a usage message*/
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
	
	PrintEntry();		/*Entry graphics*/
	PrintOption();		/*Display the available user's option for the game*/
	
	while( (ret_scanf = scanf(" %d", &option)) == 1)	/*Main loop of the program*/
	{
		Flushing();		/*Clean up the stdin buffer*/
		
		switch (option) {
			case 1:;
				int check = -1;
				check = StartGame(fp, hidden_word);		/*Basic function that perfom the game and the interaction with the user*/
				
				if(check == 0)	/*Win*/
				{
					printf("\n****************************************************************************************************\n");
					printf("\n\t\t#CONGRATULATION!!!\n");
					printf("\t\t#You did it, you found the secret word. Good Job!\n");
					printf("\n****************************************************************************************************\n");
					printf("\n#If you want to play again press 'y'\n");
					
					char ch;	/*Temporary variable*/
					scanf(" %c", &ch);	/*The user decide to continue or not*/
					if(ch == 'y' || ch == 'Y')
					{
						PrintOption();
						continue;
					}	
					else	/*Every other input handled as no*/
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
					scanf(" %c", &ch);	/*The user decide to continue or not*/
					if(ch == 'y' || ch == 'Y')
					{
						PrintOption();
						continue;
					}
					else
						break;
				}
				else	/*Error occur*/
				{
					printf("\n#Error.\n");
					printf("#Possible at memory located.\n");
					printf("#Exiting...\n");
					break;
				}
				break;
			case 2:
				Explanation();		/*Display an short description about the game, how it works*/
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
		fclose(fp);			/*Close the file*/
		free(hidden_word);	/*Free memory from malloc*/
		return 1;
	}
	
	if(option == 1)		/*Exiting the game after a complete round*/
		printf("\n#Exiting the game. Thank you for playing...");
	else if(option == 3)	/*Exiting the game immediately*/
		printf("\n#Leaving the game...Hope see you soon.\n");
	
	fclose(fp);			/*Close the file*/
	free(hidden_word);	/*Free memory from malloc*/
	return 0;
}
