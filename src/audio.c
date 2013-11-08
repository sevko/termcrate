#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void audio(char * filePath){
	char sysCommand[50] = "afplay ";
	strcat(sysCommand, filePath);
	strcat(sysCommand, " &"); 		//start in another thread
	system(sysCommand);
}

void stopAudio(){
	system("killall -9 afplay");
}
