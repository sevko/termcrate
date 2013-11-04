#include <stdio.h>
#include <stdlib.h>

#include "../src/termcrate.h"
#include "../src/graphics.h"

#include "../xterm/keyboard.h"
#include "../xterm/xterm_control.h"

extern char mapBuf[MAP_HEIGHT][MAP_WIDTH];

extern Actor_t _enemies[MAX_ENEMIES];
extern Actor_t _bullets[MAX_BULLETS];
extern Crate_t _crate;
extern Player_t _player;

extern int _numEnemies;
extern int _numBullets;

void render(){
    clearScreen();
    renderMap();
    renderActors();
}

void renderMap(){
    int row;
    for(row = 0; row < MAP_HEIGHT + 1; row++)
        printf("%s", mapBuf[row]);
}

void renderActors(){
    int enem;
    for(enem = 0; enem < _numEnemies; enem++){
        Actor_t mob = _enemies[enem];
        xt_par2(XT_SET_ROW_COL_POS, mob.geo.y, mob.geo.x);
        drawEnemy();
    }

    int bull;
    for(bull = 0; bull < _numBullets; bull++){
        Actor_t bullet = _bullets[bull];
        xt_par2(XT_SET_ROW_COL_POS, bullet.geo.y, bullet.geo.x);
        drawBullet();
    }

    xt_par2(XT_SET_ROW_COL_POS, _crate.geo.y, _crate.geo.x);
    drawCrate();

    xt_par2(XT_SET_ROW_COL_POS, _player.geo.y, _player.geo.x);
    drawPlayer();
}

void addActor(int enem, Actor_t newActor){
    if(enem && _numEnemies < MAX_ENEMIES) {
        _enemies[_numEnemies++] = newActor;
    }
    else if(_numBullets < _numBullets) {
        _bullets[_numBullets++] = newActor;
    }
}

void drawEnemy(){
    printf("X");
}

void drawBullet(){
    printf("-");
}

void drawCrate(){
    printf("I");
}

void drawPlayer(){
    printf("O");
}

void clearScreen(){
    resetCursor();
    xt_par0(XT_CLEAR_SCREEN);
}

void resetCursor(){
    xt_par2(XT_SET_ROW_COL_POS, 1, 1);
}

void scanMap(){
    FILE * map = fopen(MAP_NAME, "r");

    int row = 0;
    while(fgets(mapBuf[row++], MAP_WIDTH, map));
}        
