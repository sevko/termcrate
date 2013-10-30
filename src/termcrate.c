#include <stdio.h>
#include <unistd.h>
#include <termcrate.c>

#include "../xterm/keyboard.h"
#include "../xterm/xterm_control.h"

void game(){
	while(!gameLost()){
		render();
		tick();
	}
}

void render(){

}

void tick(){
	update();
	updateEnemies();
}

void updateEnemies(){

}

void updateBullet(){

}

void updatePlayer(int key){

}

int gameLost(){

}

void main(){
	game();
}
