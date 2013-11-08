#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "termcrate.h"
#include "graphics.h"
#include "audio.h"

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
Message_t _messages[3];

int _numEnemies;
int _numBullets;

int _gameLost;
int _tickCount;

char * pistolMessage = "______ _     _        _             __\n | ___ (_)   | |      | |    _      / /\n | |_/ /_ ___| |_ ___ | |   (_)    / / \n |  __/| / __| __/ _ \\| |         / /  \n | |   | \\__ \\ || (_) | |    _   / /   \n \\_|   |_|___/\\__\\___/|_|   (_) /_/    \n";
char * shotgunMessage = "_____ _           _                      _ \n /  ___| |         | |                    | |\n \\ `--.| |__   ___ | |_ __ _ _   _ _ __   | |\n `--. \\ '_ \\ / _ \\| __/ _` | | | | '_ \\  | |\n /\\__/ / | | | (_) | || (_| | |_| | | | | |_|\n \\____/|_| |_|\\___/ \\__\\__, |\\__,_|_| |_| (_)\n __/ |                \n |___/                 \n";
char * machinegunMessage = "___  ___           _     _              _____                _\n |  \\/  |          | |   (_)            |  __ \\              | |\n | .  . | __ _  ___| |__  _ _ __   ___  | |  \\/_   _ _ __    | |\n | |\\/| |/ _` |/ __| '_ \\| | '_ \\ / _ \\ | | __| | | | '_ \\   | |\n | |  | | (_| | (__| | | | | | | |  __/ | |_\\ \\ |_| | | | |  |_|\n \\_|  |_/\\__,_|\\___|_| |_|_|_| |_|\\___|  \\____/\\__,_|_| |_|  (_)\n";
void game(){
	config();
	while(!_gameLost){
		usleep(PAUSE);
		render();
		tick();
	}
	audio(DEAD);
}

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

	Keys_t keys = {
		.up = 0,
		.left = 0,
		.right = 0,
		.fire = 0
	};
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

//populates _elements with an instance of each 
//element struct with default variable initializations;
//makes future creation of new structs cleaner.
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
		.x = 60, 
		.y = 18, 
		.rad = 1
	};

	Message_t pistol = {.text = pistolMessage, .display = 0, .geo = geo};
	Message_t shotgun = {.text = shotgunMessage, .display = 0, .geo = geo};
	Message_t machinegun = {.text = machinegunMessage, .display = 0, .geo = geo};

	_messages[0] = pistol;
	_messages[1] = shotgun;
	_messages[2] = machinegun;
}

void tick(){
	updateBullets();
	updateEnemies();
	updatePlayer();
	updateCrate();
	_tickCount++;
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

void updateCrate(){
	if(!onSurface(_crate.geo))
		_crate.geo.y++;

	if(collision(_crate.geo, _player.geo)){
		_player.weapon = _crate.weapon;
		resetCrate();
	}
}

void resetCrate(){
	_crate.geo.x = rand() % MAP_WIDTH;
	_crate.geo.y = rand() % MAP_HEIGHT;
	_crate.weapon = _weapons[rand() % NUM_WEAPONS];
	if(_crate.weapon.rof == 2)
		_messages[2].display = 75;
	if(_crate.weapon.rof == 15)
		_messages[0].display = 75;
	if(_crate.weapon.rof == 30)
		_messages[1].display = 75;
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
	expireEnemies();
}

void spawnEnemy(){
	if(_tickCount % ENEMY_SPAWN_TICKS == 0 && _numEnemies < MAX_ENEMIES){
		Actor_t enemy = _elements.enemy;
		enemy.geo.x = 88;
		addActor(1, enemy);
	}
}

void expireEnemies() {
	int enem;
	for(enem = 0; enem < _numEnemies; enem++){
		Actor_t * mob = &_enemies[enem];
		if(mob->alive == 0) {
			int i;
			for(i = enem; i <= _numEnemies; i++)
				_enemies[i] = _enemies[i + 1];

			_numEnemies--;
		}
	}
}

void updateBullets(){
	int bull, enem;
	for(bull = 0; bull < _numBullets; bull++){
		Actor_t * ammo = &_bullets[bull];
		for(enem = 0; enem < _numEnemies; enem++) {
			Actor_t * mob = &_enemies[enem];
			if(collision(ammo->geo, mob->geo)){
				ammo->alive = mob->alive = 0;
			}
		}

		bulletMove(ammo);
	}

	expireBullets();
}

void expireBullets() {
	int bull;
	for(bull = 0; bull < _numBullets; bull++){
		Actor_t * ammo = &_bullets[bull];

		if(ammo->alive == 0) {
			int i;
			for(i = bull; i <= _numBullets; i++)
				_bullets[i] = _bullets[i + 1];

			_numBullets--;
		}
	}
}

void spawnBullet(int dir){
	audio(GUNSHOT);
	if(_numBullets < MAX_BULLETS) {
		Actor_t bull = _elements.bullet;
		bull.geo.x = _player.geo.x;
		bull.geo.y = _player.geo.y;
		bull.dirMotion = dir;
		addActor(0, bull);
	}
	_player.reload = 0;
}

void clearKeys() {
	Keys_t keys = {
		.up = 0,
		.left = 0,
		.right = 0,
		.fire = 0
	};
	_keys = keys;
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

		if(key == FIRE){
			_keys.fire = 1;
		}

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

int onSurface(Geometry_t geo) {
	return mapBuf[geo.y][geo.x - 1] == '@';
}

int belowSurface(Geometry_t geo) {
	return mapBuf[geo.y - 2][geo.x - 1] == '@';
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

void bulletMove(Actor_t * bull) {
	if(_tickCount % BULL_DELAY == 0) {
		int inSurface = mapBuf[bull->geo.y - 1][bull->geo.x] == '@';

		if(bull->geo.x >= MAP_WIDTH || bull->geo.x <= 0 || inSurface) {
			bull->alive = 0;
		}

		bull->geo.x += bull->dirMotion;
	}
}

void main(){
	menu();
}
