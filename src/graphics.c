#include <stdio.h>
#include <stdlib.h>

#include "../src/termcrate.h"
#include "../src/graphics.h"

#include "../xterm/keyboard.h"
#include "../xterm/xterm_control.h"

extern char mapBuf[MAP_HEIGHT][MAP_BUF_WIDTH];
extern Surface_t _surfaces[10];

extern Actor_t _enemies[MAX_ENEMIES + 1];
extern Actor_t _bullets[MAX_BULLETS + 1];
extern Crate_t _crate;
extern Player_t _player;

extern int _numEnemies;
extern int _numBullets;
extern int _numSurfaces;

void render(){
	clearScreen();
	renderMap();
	renderActors();
	resetCursor();
}

void renderMap(){
	int row;
	xt_par0(XT_CH_YELLOW);
	for(row = 0; row < MAP_HEIGHT; row++)
		printf("%s", mapBuf[row]);
	xt_par0(XT_CH_NORMAL);
}

void renderActors(){
	int enem;
	for(enem = 0; enem < _numEnemies; enem++){
		Actor_t mob = _enemies[enem];
		xt_par2(XT_SET_ROW_COL_POS, mob.geo.y, mob.geo.x);
		drawSprite(SPRITE_ENEMY, COLOR_ENEMY);
	}

	int bull;
	for(bull = 0; bull < _numBullets; bull++){
		Actor_t bullet = _bullets[bull];
		xt_par2(XT_SET_ROW_COL_POS, bullet.geo.y, bullet.geo.x);
		drawSprite(SPRITE_BULLET, COLOR_BULLET);
	}

	//xt_par2(XT_SET_ROW_COL_POS, _crate.geo.y, _crate.geo.x);
	//drawSprite(SPRITE_CRATE, COLOR_CRATE);

	xt_par2(XT_SET_ROW_COL_POS, _player.geo.y, _player.geo.x);
	drawSprite(SPRITE_PLAYER, COLOR_PLAYER);
}

void addActor(int enem, Actor_t newActor){
	if(enem && _numEnemies < MAX_ENEMIES) {
		_enemies[_numEnemies++] = newActor;
	}
	else if(_numBullets < MAX_BULLETS) {
		_bullets[_numBullets++] = newActor;
	}
}

void drawSprite(char * sprite, char * color){
	xt_par0(XT_CH_BOLD);
	xt_par0(color);
	printf(sprite);
	xt_par0(XT_CH_NORMAL);
}

void clearScreen(){
	resetCursor();
	xt_par0(XT_CLEAR_SCREEN);
}

void resetCursor(){
	xt_par2(XT_SET_ROW_COL_POS, 1, 1);
}

void loadSurfaces(){
    int row, col, on = 0; 
    for(row = 0; row <= MAP_HEIGHT; row++) {
        Geometry_t p1 = {
            .x = -1,
            .y = -1
        };
        Geometry_t p2 = {
            .x = -1,
            .y = -1
        };

        for(col = 0; col <= MAP_WIDTH; col++) {
            if(!on && mapBuf[row][col] == '@') {
                on = 1;
                p1.x = col;
                p1.y = row;
            } else if(on && (mapBuf[row][col] != '@' || col >= MAP_WIDTH)) {
                on = 0;
                p2.x = col;
                p2.y = row;
                Surface_t surface = {
                    .p1 = p1,
                    .p2 = p2
                };
                _surfaces[_numSurfaces++] = surface;
            }
        }
    }
}

void loadMap(){
	FILE * map = fopen(MAP_NAME, "r");

	int row;
	for(row = 0; row < MAP_HEIGHT; row++)
		fgets(mapBuf[row], MAP_BUF_WIDTH, map);

        loadSurfaces();
}
