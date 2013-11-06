#define MAP_NAME "res/lvl1.map"
#define MAP_WIDTH 176
#define MAP_BUF_WIDTH (176 + 2) 		//account for overflow
#define MAP_HEIGHT 44

void render();
void renderMap();
void renderActors();

void addActor(int enem, Actor_t newActor);
void drawEnemy();
void drawBullet();
void drawCrate();
void drawPlayer();

void clearScreen();
void resetCursor();
void scanMap();