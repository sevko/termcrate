#include <stdio.h>
#include <stdlib.h>

#include "termcrate.h"
#include "menu.h"
#include "audio.h"

#include "../xterm/keyboard.h"

Button_t _buttons[NUM_BUTTONS];
int _selectedButton = 0;

void menu(){
	configMenu();
	renderMenu();
	
	int key;
	while(1){
		if((key = getkey()) != KEY_NOTHING){
			if(key == KEY_UP)
				menuMoveUp();

			else if(key == KEY_DOWN)
				menuMoveDown();

			else if(key == KEY_ENTER)
				buttonFunction();

			renderMenu(_selectedButton);
		}
	}
}

void configMenu(){
	Button_t play = {
		.x = (BUTTON_X - 2), //center, account for name length
		.y = 16,
		.name = "play"
	};

	Button_t exit = {
		.x = (BUTTON_X - 2),
		.y = 22,
		.name = "exit"
	};

	_buttons[0] = play;
	_buttons[1] = exit;

	audio(MENU_THEME);
}

void menuMoveUp(){
	if(_selectedButton > 0)
		_selectedButton--;
}

void menuMoveDown(){
	if(_selectedButton < NUM_BUTTONS - 1)
		_selectedButton++;
}

void buttonFunction(){
	stopAudio();
	if(_selectedButton == PLAY)
		game();

	if(_selectedButton == EXIT)
		exit(1);
}