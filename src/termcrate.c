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

char mapBuf[MAP_HEIGHT][MAP_BUF_WIDTH];
Weapon_t _weapons[NUM_WEAPONS];
Elements_t _elements;

Actor_t _enemies[MAX_ENEMIES + 1];
Actor_t _bullets[MAX_BULLETS + 1];
Crate_t _crate;
Player_t _player;
Keys_t _keys;

int _numEnemies, _numBullets;
int _gameLost, _tickCount;

void game(){
	config();
	while(!_gameLost){
		usleep(PAUSE);
		render();
		tick();
	}
	menu();
}

void tick(){
	updateBullets();
	updateEnemies();
	updatePlayer();
	updateCrate();
	_tickCount++;
}

void updateCrate(){
	if(!onSurface(_crate.geo))
		_crate.geo.y++;

	if(collision(_crate.geo, _player.geo)){
		_player.weapon = _crate.weapon;
		resetCrate();
	}
}

void resetCrate(){
	audio(CRATE);
	_crate.geo.x = rand() % MAP_WIDTH;
	_crate.geo.y = rand() % MAP_HEIGHT;
	_crate.weapon = _weapons[rand() % NUM_WEAPONS];
}

void updateEnemies(){
	int enem;
	for(enem = 0; enem < _numEnemies; enem++){
		Actor_t * mob = &_enemies[enem];
		if(collision(mob->geo, _player.geo)){
			_gameLost = 1;
			break;
		}
		enemyMove(mob);
	}
	spawnEnemy();
	expireActors(_enemies, &_numEnemies);
}

void spawnEnemy(){
	if(_tickCount % ENEMY_SPAWN_TICKS == 0 && _numEnemies < MAX_ENEMIES){
		Actor_t enemy = _elements.enemy;
		enemy.geo.x = 88;
		addActor(1, enemy);
	}
}

void enemyMove(Actor_t * enem) {
	if(_tickCount % ENEM_DELAY == 0) {
		if(enem->geo.y >= MAP_HEIGHT) {
			enem->geo.y = 0;
			enem->dirMotion *= -1;
		}

		if(enem->geo.x >= MAP_WIDTH - 1 || enem->geo.x <= 1) {
			enem->dirMotion *= -1;
		} 

		enem->geo.x += enem->dirMotion;

		if(!onSurface(enem->geo)) {
			enem->geo.y += G;
		}
	}
}

void updateBullets(){
	int bull, enem;
	for(bull = 0; bull < _numBullets; bull++){
		Actor_t * ammo = &_bullets[bull];
		for(enem = 0; enem < _numEnemies; enem++) {
			Actor_t * mob = &_enemies[enem];
			if(collision(ammo->geo, mob->geo))
				ammo->alive = mob->alive = 0;
		}
		bulletMove(ammo);
	}
	expireActors(_bullets, &_numBullets);
}

void spawnBullet(){
	audio(GUNSHOT);
	if(_numBullets < MAX_BULLETS) {
		Actor_t bull = _elements.bullet;
		bull.geo.x = _player.geo.x;
		bull.geo.y = _player.geo.y;
		bull.dirMotion = _player.dirMotion;
		addActor(0, bull);
		_player.reload = 0;
	}
}

void bulletMove(Actor_t * bull) {
	if(_tickCount % BULL_DELAY == 0) {
		int inSurface = mapBuf[bull->geo.y - 1][bull->geo.x] == SPRITE_SURFACE;

		if(bull->geo.x >= MAP_WIDTH || bull->geo.x <= 0 || inSurface) {
			bull->alive = 0;
		}

		bull->geo.x += bull->dirMotion;
	}
}

void updateKeys() {
	int key;
	while((key = getkey()) != KEY_NOTHING) {
		if(key == MOVE_UP)
			_keys.up = 1;

		if(key == MOVE_LEFT)
			_keys.left = 1;

		if(key == MOVE_RIGHT)
			_keys.right = 1;

		if(key == FIRE)
			_keys.fire = 1;

		if(key == QUIT)
			_gameLost = 1;
	}
}

void updatePlayer(){
	updateKeys();
	if(_tickCount % PLAYER_DELAY == 0) {
		if(_keys.up)
			moveUp();

		if(_keys.left)
			moveLeft();

		if(_keys.right)
			moveRight();

		if(_keys.fire && _player.reload >= _player.weapon.rof)
			spawnBullet(_player.dirMotion);

		clearKeys();
		_player.reload += 1;
	}
	gravity();
}

void moveUp() {
	if(onSurface(_player.geo) && _player.geo.y > 0) {
		audio(JUMP);
		_player.jumpTime = JUMP_HEIGHT;
	}
}

void moveLeft() {
	if(_player.geo.x > 1) {
		_player.geo.x -= 1;
		_player.dirMotion = LEFT;
	}
}

void moveRight() {
	if(_player.geo.x < MAP_WIDTH) {
		_player.geo.x += 1;
		_player.dirMotion = RIGHT;
	}
}

void moveDown() {
	if(!onSurface(_player.geo))
		_player.geo.y += G;
}

int main(){
	menu();
	return EXIT_SUCCESS;
}