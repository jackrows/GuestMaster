/********************************
*	Header of General functions
*********************************/

#ifndef __General_Functions_H__
#define __General_Functions_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define	SIZE_WORD	15
#define	TRIES		10	
#define MIN_INPUT	3

/*Declaration of functions*/
int		TakeSecretWord(FILE*, char*);		/*Take the secret word from the file*/
void	Flushing();							/*Flashing the stdin buffer*/
void	ResizeMemory(char*, FILE*, int);	/*Increase the original array if the word is too big*/
void	PrintEntry();						/*Display the entry simple graphics*/
void	Explanation();						/*Display a short description of the game*/
void	PrintOption();						/*Display user's options*/
int		StartGame(FILE*, char*);

#endif	/*GeneralFunction.h*/
