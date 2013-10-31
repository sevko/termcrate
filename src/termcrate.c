#include <stdio.h>
#include <unistd.h>

#include "../src/termcrate.h"
#include "../xterm/keyboard.h"
#include "../xterm/xterm_control.h"

struct Enemy * _enemies;
struct Crate _crate;
struct Player _player;

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

}

void tick(){
    updatePlayer();
    updateBullet();
    updateEnemies();
}

void updateEnemies(){

}

void updateBullet(){

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
