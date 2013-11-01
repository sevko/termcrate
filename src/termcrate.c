#include <stdio.h>
#include <unistd.h>

#include "../src/termcrate.h"
#include "../xterm/keyboard.h"
#include "../xterm/xterm_control.h"

Actor * _enemies;
Actor * _bullets;

Crate _crate;
Player _player;

int _numEnemies;
int _numBullets;
int _gameLost;

void game(){
    config();
    while(!gameLost()){
        render();
        tick();
    }
}

void config(){
    _gameLost = 0;
}

void render(){
	//screen drawing
}

void tick(){
    updatePlayer();
    updateBullet();
    updateEnemies();
}

void updateEnemies(){
	int enem;

	for(enem = 0; enem < _numEnemies; enem++){
		mob = enemies[enem];
		if(collision(mob.geo, _player.geo)){
			_gameLost = 1; 	//player's dead
			break;
		}
		enemyMove(mob);
	}
}

//returns absolute value of val
int abs(int val){
	if(val < 0)
		return val * -1;
	return val;
}

//returns whether geo1 collided with geo2
int collision(Geometry g1, Geometry g2){
	int minDist = go1.radius + g2.radius;

	//poor readibility for lazy eval
	return abs(g1.yPos - g2.yPos) < minDist && abs(g1.xPos - g2.xPos) < minDist;
}

void updateBullet(){
	int bull, enem;
	for(bull = 0; bull < _numBullets; bull++){
		for(enem = 0; enem < _numEnemies; enem++)
			if(collision(_bullets[bull].geo, _enemies[enem].geo))
				_enemies[enem].alive = _bullets[bull].alive = 0;
	}
}

void updatePlayer(){
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
            _gameLost = 0;

        gravity();
    }
}

int onSurface() {
    //Check if _player is on a surface or correct if near enough
}

int touchLeft() {
    //Check if the _player is touching a surface on its left or correct if near enough
}

int touchLeft() {
    //Check if the _player is touching a surface on its right or correct if near enough
}

void moveUp() {
    if(onSurface()) {
        _player.yVel += YVEL;
    }
}

void moveLeft() {
    if(!touchLeft()) {
        _player.x -= XVEL;
    }
}

void moveRight() {
    if(!touchRight()) {
        _player.x += XVEL;
    }
}

void gravity() {
    if(!onSurface()) {
        _player.y += _player.yVel;
        _player.yVel -= G;
    } else {
        _player.yVel = 0;
    }
}

void main(){
    game();
}
