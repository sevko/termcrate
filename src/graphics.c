/*
 * Contains functions for graphics manipulation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
extern Message_t _messages[3];
extern char * _numberSprites[10];

extern int _numEnemies;
extern int _numBullets;
extern int _selectedButton;

extern char * pistolMessage;
extern char * shotgunMessage;
extern char * machinegunMessage;

void render(){
	clearScreen();
	renderMap();
	renderActors();
	renderScore();
	renderMessages();
	resetCursor();
}

void renderMenu(){
	clearScreen();

	xt_par0(XT_CH_BOLD);
	xt_par0(XT_BG_RED);
	xt_par0(XT_CH_YELLOW);
	drawString(SPRITE_MENU, 50, 3);
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

void renderMessages() {
	if(_messages[0].display) {
		drawMessage(&_messages[0]);
	}
	if(_messages[1].display) {
		drawMessage(&_messages[1]);
	}
	if(_messages[2].display) {
		drawMessage(&_messages[2]);
	}
}

void renderScore(){
	int score = _player.score;
	int numDig = (int)log10(score) + 1;

	int dig;
	xt_par0(XT_CH_WHITE);
	for(dig = numDig - 1; dig >= 0; dig--){
		int xPos = MAP_WIDTH / 2 + numDig * 5 / 2 - (numDig - dig - 1) * 5;
		drawString(_numberSprites[score % 10], xPos, MAP_HEIGHT * 0.1);
		score /= 10;
	}
	xt_par0(XT_CH_NORMAL);
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

void drawString(char * text, int x, int y) {
	int row = 0, col = 0 , len = 0;
	while(len < strlen(text)) {
		if(text[len] == '\n'){
			row++;
			col = 0;
		} else {
			xt_par2(XT_SET_ROW_COL_POS, y + row, x + col);
			printf("%c", text[len]);
			col++;
		}
		len++;
	}
}

void drawMessage(Message_t * message) {
    xt_par0(XT_CH_BOLD);
    xt_par0(XT_CH_RED);
    drawString(message->text, message->geo.x, message->geo.y);
    message->display -= 1;
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
