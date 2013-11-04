#define MAP_WIDTH 176
#define MAP_HEIGHT 44

#define MAP_NAME "res/lvl1.map"

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
