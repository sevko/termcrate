#include <stdio.h>
#include <stdlib.h>

#include "termcrate.h"
#include "graphics.h"
#include "menu.h"

#include "../xterm/keyboard.h"
#include "../xterm/xterm_control.h"

extern char mapBuf[MAP_HEIGHT][MAP_BUF_WIDTH];
extern Button_t _buttons[NUM_BUTTONS];

extern Actor_t _enemies[MAX_ENEMIES + 1];
extern Actor_t _bullets[MAX_BULLETS + 1];
extern Crate_t _crate;
extern Player_t _player;

extern int _numEnemies;
extern int _numBullets;
extern int _selectedButton;

void render(){
	clearScreen();
	renderMap();
	renderActors();
	resetCursor();
}

void renderMenu(){
	clearScreen();

	xt_par0(XT_CH_BOLD);
	xt_par0(XT_BG_RED);
	xt_par0(XT_CH_YELLOW);
	xt_par2(XT_SET_ROW_COL_POS, 3, 50);
	printf("%s", SPRITE_MENU);
	xt_par0(XT_CH_NORMAL);

	int button;
	for(button = 0; button < NUM_BUTTONS; button++){
		Button_t but = _buttons[button];
		xt_par2(XT_SET_ROW_COL_POS, but.y, but.x);
		if(button == _selectedButton)
			xt_par0(COLOR_SELECTED_BUTTON);

		xt_par0(XT_CH_BOLD);
		xt_par0(COLOR_BUTTON);
		printf("%s", but.name);
		xt_par0(XT_CH_NORMAL);
	}
	xt_par2(XT_SET_ROW_COL_POS, 1, 1);
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

	xt_par2(XT_SET_ROW_COL_POS, _crate.geo.y, _crate.geo.x);
	drawSprite(SPRITE_CRATE, COLOR_CRATE);

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
	printf("%s", sprite);
	xt_par0(XT_CH_NORMAL);
}

void clearScreen(){
	resetCursor();
	xt_par0(XT_CLEAR_SCREEN);
}

void resetCursor(){
	xt_par2(XT_SET_ROW_COL_POS, 1, 1);
}

void loadMap(){
	FILE * map = fopen(MAP_NAME, "r");

	int row;
	for(row = 0; row < MAP_HEIGHT; row++)
		if(!fgets(mapBuf[row], MAP_BUF_WIDTH, map))
			break;
}