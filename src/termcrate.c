#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "termcrate.h"
#include "graphics.h"
#include "audio.h"

#include "../xterm/keyboard.h"
#include "../xterm/xterm_control.h"

char mapBuf[MAP_HEIGHT][MAP_BUF_WIDTH];
Surface_t _surfaces[10];
Elements_t _elements;

Actor_t _enemies[MAX_ENEMIES + 1];
Actor_t _bullets[MAX_BULLETS + 1];
Crate_t _crate;
Player_t _player;
Keys_t _keys;

int _numEnemies;
int _numBullets;
int _numSurfaces;

int _gameLost;
int _tickCount;

void game(){
	config();
	while(!_gameLost){
		usleep(PAUSE);
		render();
		tick();
	}
}

void config(){
	_numEnemies = 0;
	_numBullets = 0;
	_numSurfaces = 0;
	_gameLost = 0;
	_tickCount = 0;

	loadMap();
	loadElements();
	resetCrate();

	_player = _elements.player;

	Keys_t keys = {
		.up = 0,
		.left = 0,
		.right = 0,
		.fire = 0
	};
	_keys = keys;

	audio(THEME);
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
	Weapon_t shotgun = { .ammo = 20, .rof = 30 };
	Weapon_t machineGun = { .ammo = 100, .rof = 2 };

	Crate_t crate = { .geo = geo };
	Player_t player = { .geo = geo, .weapon = pistol};

	_elements.enemy = actor;
	_elements.bullet = actor;
	_elements.crate = crate;
	_elements.player = player;

	_elements.pistol = pistol;
	_elements.shotgun = shotgun;
	_elements.machineGun = machineGun;
}

void tick(){
	updateBullets();
	updateEnemies();
	updatePlayer();
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
		if((*mob).alive == 0) {
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
	if(_tickCount % GRAVITY_DELAY_TICKS == 0)
		moveDown();
}

int onSurface(Geometry_t geo) {
	int i;
	for(i = 0; i < _numSurfaces; i++) {
		Surface_t surf = _surfaces[i];
		int diff = geo.y - surf.p1.y;
		int onLevel = (diff <= geo.rad && diff >= 0);
		int between = geo.x >= surf.p1.x && geo.x <= surf.p2.x;
		if(onLevel && between)
			return 1;
	}
	return 0;
}

void moveUp() {
	if(onSurface(_player.geo) && _player.geo.y > 0) {
		audio(JUMP);
		_player.geo.y -= JUMP_HEIGHT;
	}
}

void moveLeft() {
	crateCollision();
	if(_player.geo.x > 0) {
		_player.geo.x -= 1;
		_player.dirMotion = LEFT;
	}
}

void moveRight() {
	crateCollision();
	if(_player.geo.x < MAP_WIDTH) {
		_player.geo.x += 1;
		_player.dirMotion = RIGHT;
	}
}

void moveDown() {
	crateCollision();
	if(!onSurface(_player.geo)) {
		_player.geo.y += G;
	}
}

void crateCollision(){
	if(collision(_player.geo, _crate.geo)){
		_player.weapon = _crate.weapon;
		resetCrate();
	}
}


void resetCrate(){
	Surface_t randSurface = _surfaces[rand() % _numSurfaces];
	_crate.geo.x = randSurface.p1.x + rand() % (randSurface.p2.x - randSurface.p1.x);
	_crate.geo.y = (randSurface.p1.y);
	_crate.weapon = _elements.machineGun;
}

void enemyMove(Actor_t * enem) {
	if(_tickCount % ENEM_DELAY == 0) {
		if(enem->geo.y >= MAP_HEIGHT) {
			enem->geo.y = 0;
			enem->dirMotion *= -1;
		}

		if(enem->geo.x >= MAP_WIDTH || enem->geo.x <= 0) {
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
		Geometry_t newGeo = {
			.x = bull->geo.x,
			.y = bull->geo.y - 1
		};
		if(bull->geo.x >= MAP_WIDTH || bull->geo.x <= 0 || onSurface(newGeo)) {
			bull->alive = 0;
		}

		bull->geo.x += bull->dirMotion;
	}
}

void main(){
	menu();
}