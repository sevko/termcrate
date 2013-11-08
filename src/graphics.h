#define MAP_NAME "res/lvl1.map"
#define MAP_WIDTH 176
#define MAP_BUF_WIDTH (176 + 2) 		//account for overflow
#define MAP_HEIGHT 44

#define SPRITE_ENEMY "X"
#define SPRITE_BULLET "·"
#define SPRITE_CRATE "I"
#define SPRITE_PLAYER "O"
#define SPRITE_MENU "\
\n\t\t\t\t\t\t _______  _______  ______    __   __  _______  ______    _______  _______  _______ \
\n\t\t\t\t\t\t|       ||       ||    _ |  |  |_|  ||       ||    _ |  |   _   ||       ||       |\
\n\t\t\t\t\t\t|_     _||    ___||   | ||  |       ||       ||   | ||  |  |_|  ||_     _||    ___|\
\n\t\t\t\t\t\t  |   |  |   |___ |   |_||_ |       ||       ||   |_||_ |       |  |   |  |   |___ \
\n\t\t\t\t\t\t  |   |  |    ___||    __  ||       ||      _||    __  ||       |  |   |  |    ___|\
\n\t\t\t\t\t\t  |   |  |   |___ |   |  | || ||_|| ||     |_ |   |  | ||   _   |  |   |  |   |___ \
\n\t\t\t\t\t\t  |___|  |_______||___|  |_||_|   |_||_______||___|  |_||__| |__|  |___|  |_______|"

#define COLOR_BUTTON XT_CH_BLUE
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