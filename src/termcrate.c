#include <stdio.h>
#include <unistd.h>

#include "../src/termcrate.h"
#include "../xterm/keyboard.h"
#include "../xterm/xterm_control.h"

struct Enemy * enemies;
struct Crate crate;

int gameLost;

void game(){
	config();
	while(!gameLost()){
		render();
		tick();
	}
}

void config(){
	gameLost = 0;
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

		else if(key == MOVE_DOWN)
			moveDown();

		else if(key == MOVE_LEFT)
			moveLeft();

		else if(key == MOVE_RIGHT)
			moveRight();

		else if(key == FIRE)
			fire();

		else if(key == QUIT)
			gameLost = 0;
	}
}

void main(){
	game();
}
