#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "./termcrate.h"
#include "./graphics.h"

#include "../xterm/keyboard.h"
#include "../xterm/xterm_control.h"

Actor_t * _enemies;
Actor_t * _bullets;
Crate_t _crate;
Player_t _player;
Surface_t * _surfaces;

int _numEnemies;
int _numBullets;

int _gameLost;

int _numSurfaces;
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
    _gameLost = 0;
	scanMap();

	Geometry_t geo = {
		.x = 10, 
		.y = 42, 
		.rad = 1
	};

	Player_t player = {
		.geo = geo
	};
	
	_player = player;
}

void tick(){
    updatePlayer();
    updateBullets();
    updateEnemies();

	_tickCount++;
}

//returns absolute value of val
int abs(int val){
    if(val < 0)
        return val * -1;
    return val;
}

//returns whether geo1 collided with geo2
int collision(Geometry_t g1, Geometry_t g2){
    int sumRad = g1.rad + g2.rad;

    //poor readibility for lazy eval
    return abs(g1.y - g2.y + 1) < sumRad && abs(g1.x - g2.x + 1) < sumRad;
}

void addActor(Actor_t * actors, Actor_t newActor, int numAct){
	actors = realloc(actors, (numAct + 1) * sizeof(Actor_t));
	actors[numAct] = newActor;
}

void updateEnemies(){
    int enem;
    for(enem = 0; enem < _numEnemies; enem++){
        Actor_t mob = _enemies[enem];
        if(collision(mob.geo, _player.geo)){
            _gameLost = 1; 	//player's dead
            break;
        }
        enemyMove(mob);
    }

	if(_tickCount % ENEMY_SPAWN_TICKS == 0){
		Geometry_t geo = {
			.x = 88,
			.y = 1,
			.rad = 1
		};

		Actor_t enemy = {
			.geo = geo,
			.dirMotion = RIGHT,
			.alive = 1
		};

		addActor(_enemies, enemy, _numEnemies);
	}
}

void updateBullets(){
    int bull, enem;
	int deadBull = 0, deadEnem = 0;

    for(bull = 0; bull < _numBullets; bull++){
        for(enem = 0; enem < _numEnemies; enem++)
            if(collision(_bullets[bull].geo, _enemies[enem].geo) && _enemies[enem].alive){
				_bullets[bull].alive = _enemies[enem].alive = 0;
				deadBull++;
				deadEnem++;
			}
        bulletMove(_bullets[bull]);
    }

	updateDeathFlags(_bullets, _numBullets, deadBull);
	_numBullets -= deadBull;

	updateDeathFlags(_enemies, _numEnemies, deadEnem);
	_numEnemies -= deadEnem;
}

//removes dead Actor_ts from actors array
void updateDeathFlags(Actor_t ** oldActors, int numAct, int numDead){
	Actor_t * newActors[numAct - numDead];
	int oldAct, newAct = 0;

	for(oldAct = 0; oldAct < numAct; oldAct++){
		Actor_t mob = *oldActors[oldAct];
		if(mob.alive)
			newActors[newAct++] = oldActors[oldAct];
	}

	oldActors = newActors;
}

void updatePlayer(){
	int key;
    if((key = getkey()) != KEY_NOTHING){

        if(key == MOVE_UP)
            moveUp();

        else if(key == MOVE_LEFT)
            moveLeft();

        else if(key == MOVE_RIGHT)
            moveRight();

        else if(key == FIRE)
			fire();

        else if(key == QUIT)
            _gameLost = 1;

        gravity();
    }
}

int onSurface(Surface_t surface, Geometry_t geo) {
    return surface.p1.y == geo.y && (geo.x > surface.p1.x && geo.x < surface.p2.x) && geo.y < 44;
}

int onSurfaces(Geometry_t geo) {
    int surf;
    for(surf = 0; surf < _numSurfaces; surf++) {
        if(onSurface(_surfaces[surf], geo))
            return 1;
    }
    return 0;
}

void moveUp() {
    if(_player.geo.y > 0) {
        _player.geo.y += JUMP_HEIGHT;
    }
}

void moveLeft() {
    if(_player.geo.x > 0) {
        _player.geo.x -= PLAYER_XVEL;
    }
}

void moveRight() {
    if(_player.geo.x < 176) {
        _player.geo.x += PLAYER_XVEL;
    }
}

void gravity() {
    if(!onSurfaces(_player.geo)) {
        _player.geo.y -= G;
    }
}

void fire(){
	Geometry_t bullGeo = { 
		.x = _player.geo.x, 
		.y = _player.geo.y, 
		.rad = BULLET_RADIUS
	};

	Actor_t bull = { 
		.geo = bullGeo,
		.dirMotion = RIGHT, //placeholder
		.alive = 1
	};

	addActor(_bullets, bull, _numBullets);
}

void enemyMove(Actor_t enem) {
    if(surfaceLeft(enem.geo) || surfaceRight(enem.geo)) {
        enem.dirMotion *= -1;
    } else if(!onSurfaces(enem.geo)) {
        enem.geo.y -= ENEM_YVEL;
    }
    enem.geo.x += ENEM_XVEL * enem.dirMotion;
}

void bulletMove(Actor_t bull) {
    if(surfaceLeft(bull.geo) || surfaceRight(bull.geo)) {
        bull.alive = 0;
    }
    bull.geo.x += BULL_XVEL * bull.dirMotion;
}

void main(){
    game();
}
