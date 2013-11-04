#include <stdio.h>

#include "../src/termcrate.h"
#include "../src/graphics.h"

#include "../xterm/keyboard.h"
#include "../xterm/xterm_control.h"

char mapBuf[MAP_HEIGHT][MAP_WIDTH];

Surface_t * _surfaces;
int _numSurfaces;

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
        
        int i = 0;
        while(i < MAP_HEIGHT) {
            int j = 0;
            int on_surface = 0;
            Geometry_t point1 = {
                .x = -1,
                .y = -1
            };
            Geometry_t point2 = {
                .x = -1,
                .y = -1
            };
            while (j < MAP_WIDTH) {
                if(mapBuf[i][j] != '@' && on_surface) {
                    on_surface = 0;
                    point2.x = j;
                    point2.y = i;
                    Surface_t newSurface = {
                        .p1 = point1,
                        .p2 = point2
                    };
                    addSurface(_surfaces, newSurface, _numSurfaces++);
                } else if(mapBuf[i][j] == '@' && !on_surface) {
                    on_surface = 1;
                    point1.x = j;
                    point1.y = i;
                }
                j++;
            }
            i++;
        }
}

void addSurface(Surface_t * surfaces, Surface_t newSurface, int numSurface) {
    surfaces = realloc(surfaces, (numSurface + 1) * sizeof(Surface_t));
    surfaces[numSurface] = newSurface;
}
