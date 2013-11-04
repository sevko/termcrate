#include <stdio.h>

#include "../src/termcrate.h"
#include "../src/graphics.h"

#include "../xterm/keyboard.h"
#include "../xterm/xterm_control.h"

char mapBuf[MAP_HEIGHT][MAP_WIDTH];

extern Actor_t * _enemies;
extern Actor_t * _bullets;
extern Crate_t _crate;
extern Player_t _player;
extern Surface_t * _surfaces;

extern int _numEnemies;
extern int _numBullets;
extern int _numSurfaces;

void render(){
	clearScreen();
	renderMap();
	renderActors();
}

void renderMap(){
	int row;
	for(row = 0; row < MAP_HEIGHT; row++)
		printf("%s", mapBuf[row]);
}

void renderActors(){
	int enem;
	for(enem = 0; enem < _numEnemies; enem++){
		Actor_t mob = _enemies[enem];
		xt_par2(XT_SET_ROW_COL_POS, mob.geo.y, mob.geo.x);
		drawEnemy();
	}

	int bull;
	for(bull = 0; bull < _numBullets; bull++){
		Actor_t bullet = _bullets[bull];
		xt_par2(XT_SET_ROW_COL_POS, bullet.geo.y, bullet.geo.x);
		drawBullet();
	}

	xt_par2(XT_SET_ROW_COL_POS, _crate.geo.y, _crate.geo.x);
	drawCrate();

	xt_par2(XT_SET_ROW_COL_POS, _player.geo.y, _player.geo.x);
	drawPlayer();
}

void drawEnemy(){
	printf("X");
}

void drawBullet(){
	printf("-");
}

void drawCrate(){
	printf("^");
}

void drawPlayer(){
	printf("O");
}

void clearScreen(){
	resetCursor();
	xt_par0(XT_CLEAR_SCREEN);
}

void resetCursor(){
	xt_par2(XT_SET_ROW_COL_POS, 1, 1);
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
    surfaces = (Surface_t *)realloc(surfaces, (numSurface + 1) * sizeof(Surface_t));
    surfaces[numSurface] = newSurface;
}
