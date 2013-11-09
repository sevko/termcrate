#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void audio(char * filePath){
	char sysCommand[50] = "aplay --quiet ";
	strcat(sysCommand, filePath);
	strcat(sysCommand, " &"); 		//start in another thread
	if(!system(sysCommand))
		exit(1);
}

void stopAudio(){
	if(!system("killall -9 aplay"))
		exit(1);
}