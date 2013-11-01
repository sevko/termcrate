#include <stdio.h>

#include "src/termcrate.h"
#include "src/graphics.h"

#include "xterm/keyboard.h"
#include "xterm/xterm_control.h"

char mapBuf[MAP_HEIGHT][MAP_WIDTH];

void render(){
	clearScreen();

	int row;
	for(row = 0; row < MAP_HEIGHT; row++)
		printf("%s", mapBuf[row]);
}

void clearScreen(){
	xt_par2(XT_SET_ROW_COL_POS, 1, 1);
	xt_par0(XT_CLEAR_SCREEN);
}

void scanMap(){
	FILE * map = fopen(MAP_NAME, "r");

	int row = 0;
	while(fgets(mapBuf[row++], MAP_WIDTH, map));
}
