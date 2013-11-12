#pragma once

#define MAP_NAME "res/lvl1.map"
#define MAP_WIDTH 176
#define MAP_BUF_WIDTH (176 + 2) 		//account for overflow
#define MAP_HEIGHT 44

#define SPRITE_SURFACE '@'
#define SPRITE_ENEMY "X"
#define SPRITE_BULLET "·"
#define SPRITE_CRATE "I"
#define SPRITE_PLAYER "O"

#define SPRITE_MENU "\
\n _______  _______  ______    __   __  _______  ______    _______  _______  _______ \
\n|       ||       ||    _ |  |  |_|  ||       ||    _ |  |   _   ||       ||       |\
\n|_     _||    ___||   | ||  |       ||       ||   | ||  |  |_|  ||_     _||    ___|\
\n  |   |  |   |___ |   |_||_ |       ||       ||   |_||_ |       |  |   |  |   |___ \
\n  |   |  |    ___||    __  ||       ||      _||    __  ||       |  |   |  |    ___|\
\n  |   |  |   |___ |   |  | || ||_|| ||     |_ |   |  | ||   _   |  |   |  |   |___ \
\n  |___|  |_______||___|  |_||_|   |_||_______||___|  |_||__| |__|  |___|  |_______|"
#define PISTOL_MESSAGE "\
\n _______  ___   _______  _______  _______  ___     \
\n|       ||   | |       ||       ||       ||   |    \
\n|    _  ||   | |  _____||_     _||   _   ||   |    \
\n|   |_| ||   | | |_____   |   |  |  | |  ||   |    \
\n|    ___||   | |_____  |  |   |  |  |_|  ||   |___ \
\n|   |    |   |  _____| |  |   |  |       ||       |\
\n|___|    |___| |_______|  |___|  |_______||_______|"
#define SHOTGUN_MESSAGE "\
\n _______  __   __  _______  _______  _______  __   __  __    _  __ \
\n|       ||  | |  ||       ||       ||       ||  | |  ||  |  | ||  |\
\n|  _____||  |_|  ||   _   ||_     _||    ___||  | |  ||   |_| ||  |\
\n| |_____ |       ||  | |  |  |   |  |   | __ |  |_|  ||       ||  |\
\n|_____  ||       ||  |_|  |  |   |  |   ||  ||       ||  _    ||__|\
\n _____| ||   _   ||       |  |   |  |   |_| ||       || | |   | __ \
\n|_______||__| |__||_______|  |___|  |_______||_______||_|  |__||__|"
#define MACHINEGUN_MESSAGE "\
\n __   __ _______ _______ __   __ ___ __    _ _______   _______ __   __ __    _ \
\n|  |_|  |   _   |       |  | |  |   |  |  | |       | |       |  | |  |  |  | |\
\n|       |  |_|  |       |  |_|  |   |   |_| |    ___| |    ___|  | |  |   |_| |\
\n|       |       |       |       |   |       |   |___  |   | __|  |_|  |       |\
\n|       |       |      _|       |   |  _    |    ___| |   ||  |       |  _    |\
\n| ||_|| |   _   |     |_|   _   |   | | |   |   |___  |   |_| |       | | |   |\
\n|_|   |_|__| |__|_______|__| |__|___|_|  |__|_______| |_______|_______|_|  |__|"

#define COLOR_BUTTON XT_CH_BLUE
#define COLOR_SELECTED_BUTTON XT_BG_RED
#define COLOR_ENEMY XT_CH_GREEN
#define COLOR_BULLET XT_CH_BLUE 
#define COLOR_CRATE XT_CH_YELLOW
#define COLOR_PLAYER XT_CH_MAGENTA

void render();
void renderMenu();
void renderMap();
void renderActors();
void renderMessages();

void addActor(int enem, Actor_t newActor);
void drawSprite(char * sprite, char * color);
void drawString(char * text, int x, int y);
void drawMessage(Message_t * message);

void clearScreen();
void resetCursor();
void loadMap();
