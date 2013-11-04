#define MAP_WIDTH 176
#define MAP_HEIGHT 44

#define MAP_NAME "res/lvl1.map"

extern Surface_t * _surfaces;
extern int _numSurfaces = 0;

void render();
void renderMap();
void renderActors();

void drawEnemy();
void drawBullet();
void drawCrate();
void drawPlayer();

void clearScreen();
void resetCursor();
void scanMap();
void addSurface();
