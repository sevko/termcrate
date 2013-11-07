#pragma once
#include "graphics.h"

#define NUM_BUTTONS 2
#define PLAY 0
#define EXIT 1

#define BUTTON_X (MAP_WIDTH / 2)

typedef struct {
	int x, y;
	int num;
	char name[10];
} Button_t;

void menu();
void configMenu();
void menuMoveUp();
void menuMoveDown();
void buttonFunction();