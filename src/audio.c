#include <stdio.h>

void audio(char * filePath){
	char sysCommand[50] = "aplay --quiet ";
	strcat(sysCommand, filePath);
	strcat(sysCommand, " &");
	system(sysCommand);
}