#define MAP_NAME "res/lvl1.map"
#define MAP_WIDTH 176
#define MAP_BUF_WIDTH (176 + 2) 		//account for overflow
#define MAP_HEIGHT 44

#define SPRITE_ENEMY "X"
#define SPRITE_BULLET "·"
#define SPRITE_CRATE "I"
#define SPRITE_PLAYER "O"

#define COLOR_BUTTON XT_CH_GREEN
#define COLOR_SELECTED_BUTTON XT_BG_RED
#define COLOR_ENEMY XT_CH_GREEN
#define COLOR_BULLET XT_CH_BLUE 
#define COLOR_CRATE XT_CH_YELLOW
#define COLOR_PLAYER XT_CH_MAGENTA

void render();
void renderMap();
void renderActors();

void addActor(int enem, Actor_t newActor);
void drawSprite(char * sprite, char * color);

void clearScreen();
void resetCursor();
void loadMap();
