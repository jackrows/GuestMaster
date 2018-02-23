/********************************
*	Header of General functions
*********************************/

#ifndef __General_Functions_H__
#define __General_Functions_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define	SIZE_WORD	15		/*Starting memory allocated size*/
#define	TRIES		10		/*Total attempts for the user*/
#define MIN_INPUT	3		/*Minimum word number accepted*/

/*Declaration of functions*/
int		TakeSecretWord(FILE*, char*);								/*Take the secret word from the file*/
void	Flushing();													/*Flashing the stdin buffer*/
void	ResizeMemory(char*, FILE*, int);							/*Increase the original array if the word is too big*/
void	PrintEntry();												/*Display the entry simple graphics*/
void	Explanation();												/*Display a short description of the game*/
void	PrintOption();												/*Display user's options*/
int		StartGame(FILE*, char*);									/*Basic functions that perfom the game*/
void 	CompareWords(const char*, const char*, const int, int[]);	/*Compare the secret word with the user guesting*/
void	DisplayFounded(const char*, const int []);					/*Appear on the screen the guested characters*/
int 	CheckGuesting(const int [], const int);						/*Check if the secret word has been found*/
int 	CheckUserInput(const char*);								/*Check of word that user input, to be bigger than MIN_INPUT, no whole alphabetic*/

#endif	/*GeneralFunction.h*/
