#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "termcrate.h"
#include "utils.h"
#include "graphics.h"
#include "audio.h"
#include "menu.h"

#include "../xterm/keyboard.h"
#include "../xterm/xterm_control.h"

extern char mapBuf[MAP_HEIGHT][MAP_BUF_WIDTH];
extern Weapon_t _weapons[NUM_WEAPONS];
extern Elements_t _elements;
extern Message_t _messages[3];

extern Crate_t _crate;
extern Player_t _player;
extern Keys_t _keys;

extern int _numEnemies, _numBullets;
extern int _gameLost, _tickCount;

void config(){
	_numEnemies = 0;
	_numBullets = 0;
	_gameLost = 0;
	_tickCount = 0;

	loadMap();
	loadElements();
	loadWeapons();
	loadMessages();
	resetCrate();

	_player = _elements.player;
	_crate = _elements.crate;

	Keys_t keys = { 0 };
	_keys = keys;

	audio(THEME);
}

void loadWeapons(){
	Weapon_t shotgun = { .ammo = 20, .rof = 30 };
	Weapon_t machineGun = { .ammo = 100, .rof = 2 };

	_weapons[0] = _elements.pistol;
	_weapons[1] = shotgun;
	_weapons[2] = machineGun;
}

void loadElements(){
	Geometry_t geo = {
		.x = 1, 
		.y = 5, 
		.rad = 1
	};

	Actor_t actor = {
		.geo = geo,
		.dirMotion = RIGHT,
		.alive = 1
	};

	Weapon_t pistol = { .ammo = 1000000, .rof = 15 };
	Crate_t crate = { .geo = geo, .weapon = pistol};

	Player_t player = { 
		.geo = geo,
		.dirMotion = RIGHT,
		.jumpTime = 0,
		.weapon = pistol
	};

	_elements.enemy = actor;
	_elements.bullet = actor;
	_elements.crate = crate;
	_elements.player = player;
	_elements.pistol = pistol;
}

void loadMessages(){
	Geometry_t geo = {
		.x = 50, 
		.y = 18, 
		.rad = 1
	};
	 
	Message_t pistol = {.text = PISTOL_MESSAGE, .display = 0, .geo = geo};
	Message_t shotgun = {.text = SHOTGUN_MESSAGE, .display = 0, .geo = geo};
	Message_t machinegun = {.text = MACHINEGUN_MESSAGE, .display = 0, .geo = geo};
	 
	_messages[0] = pistol;
	_messages[1] = shotgun;
	_messages[2] = machinegun;
}

int abs(int val){
	if(val < 0)
		return val * -1;
	return val;
}

int collision(Geometry_t g1, Geometry_t g2){
	int sumRad = g1.rad + g2.rad;
	return abs(g1.y - g2.y + 1) < sumRad && abs(g1.x - g2.x + 1) < sumRad;
}

int onSurface(Geometry_t geo) {
	return mapBuf[geo.y][geo.x - 1] == SPRITE_SURFACE;
}

int belowSurface(Geometry_t geo) {
	return mapBuf[geo.y - 2][geo.x - 1] == SPRITE_SURFACE;
}

void clearKeys() {
	Keys_t keys = {0};
	_keys = keys;
}

void expireActors(Actor_t * actors, int * numAct) {
	int act;
	for(act = 0; act < *numAct; act++)
		if(!actors[act].alive) {
			int shift;
			for(shift = act; shift <= *numAct; shift++)
				actors[shift] = actors[shift + 1];
			(*numAct)--;
		}
}

void gravity() {
	if(_tickCount % GRAVITY_DELAY_TICKS == 0) {
		if(belowSurface(_player.geo))
			_player.jumpTime = 0;

		if(_player.jumpTime) {
			_player.geo.y -= G;
			_player.jumpTime -= 1;
		} else if(!onSurface(_player.geo)) {
			_player.geo.y += G;
		}
	}
}
