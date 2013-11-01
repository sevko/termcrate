#include <stdio.h>
#include <unistd.h>

#include "src/termcrate.h"
#include "src/graphics.h"

#include "xterm/keyboard.h"
#include "xterm/xterm_control.h"


Actor * _enemies;
Actor * _bullets;

Crate _crate;
Player _player;

int _numEnemies;
int _numBullets;
int _gameLost;

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
}

void tick(){
    updatePlayer();
    updateBullets();
    updateEnemies();
}

//returns absolute value of val
int abs(int val){
    if(val < 0)
        return val * -1;
    return val;
}

//returns whether geo1 collided with geo2
int collision(Geometry g1, Geometry g2){
    int minDist = g1.rad + g2.rad;

    //poor readibility for lazy eval
    return abs(g1.y - g2.y) < minDist && abs(g1.x - g2.x) < minDist;
}

void updateEnemies(){
    int enem;
    for(enem = 0; enem < _numEnemies; enem++){
        Actor mob = _enemies[enem];
        if(collision(mob.geo, _player.geo)){
            _gameLost = 1; 	//player's dead
            break;
        }
        enemyMove(mob);
    }
}

void updateBullets(){
    int bull, enem;
    for(bull = 0; bull < _numBullets; bull++){
        for(enem = 0; enem < _numEnemies; enem++)
            if(collision(_bullets[bull].geo, _enemies[enem].geo))
                _enemies[enem].alive = _bullets[bull].alive = 0;
        bulletMove(_bullets[bull]);
    }
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
            _gameLost = 0;

        gravity();
    }
}

//Check if _player is on a surface or correct if near enough
int surfaceBottom(Geometry geo) {
}

//Check if _player is touching a sruface from the bottom or correct if near enough
int surfaceTop(Geometry geo) {
}

//Check if the _player is touching a surface on its left or correct if near enough
int surfaceLeft(Geometry geo) {
}

//Check if the _player is touching a surface on its right or correct if near enough
int surfaceRight(Geometry geo) {
}

void moveUp() {
    if(surfaceBottom(_player.geo)) {
        _player.yVel += PLAYER_YVEL;
    }
}

void moveLeft() {
    if(!surfaceLeft(_player.geo)) {
        _player.geo.x -= PLAYER_XVEL;
    }
}

void moveRight() {
    if(!surfaceRight(_player.geo)) {
        _player.geo.x += PLAYER_XVEL;
    }
}

void gravity() {
    if(!surfaceBottom(_player.geo)) {
        _player.geo.y += _player.yVel;
		_player.yVel -= G;
	} else {
        _player.yVel = 0;
    }
}

void fire(){
	//fire bullets
}

void enemyMove(Actor enem) {
    if(surfaceLeft(enem.geo) || surfaceRight(enem.geo)) {
        enem.dirMotion *= -1;
    } else if(!surfaceBottom(enem.geo)) {
        enem.geo.y -= ENEM_YVEL;
    }
    enem.geo.x += ENEM_XVEL * enem.dirMotion;
}

void bulletMove(Actor bull) {
    if(surfaceLeft(bull.geo) || surfaceRight(bull.geo)) {
        bull.alive = 0;
    }
    bull.geo.x += BULL_XVEL * bull.dirMotion;
}

void main(){
    game();
}
