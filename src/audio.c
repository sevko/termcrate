/*
 *	Contains functions for audio manipulation.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void audio(char * filePath){
	char sysCommand[50] = "aplay --quiet ";
	strcat(sysCommand, filePath);
	strcat(sysCommand, " &"); 	//start in another thread
	if(system(sysCommand) == -1)
		exit(1);
}

void stopAudio(){
	if(system("killall -9 aplay") == -1)
		exit(1);
}