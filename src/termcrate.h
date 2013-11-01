#define LEFT 1
#define RIGHT 0

#define MOVE_UP KEY_UP
#define MOVE_LEFT KEY_LEFT
#define MOVE_RIGHT KEY_RIGHT

#define FIRE 'x'
#define QUIT KEY_F1

#define PAUSE (1000000 / 60)
#define PLAYER_XVEL 3
#define PLAYER_YVEL 2
#define ENEM_XVEL 2
#define ENEM_YVEL 2
#define BULL_XVEL 8
#define G = 1

typedef struct {
	int xPos, 
		yPos, 
		rad; 	//radius
} Geometry;

typedef struct {
	Geometry geo;
    int dirMotion;
    int alive;
} Actor;

typedef struct {
	Geometry geo;
} Crate;

typedef struct {
	Geometry geo;
    int yVel;
} Player;

void game();
void config();
void render();
void tick();
int abs(int val);
int collistion(Geometry g1, Geometry g2);
void updateEnemies();
void updateBullets();
void updatePlayer();
int surfaceBottom(Geometry geo);
int surfaceBottom(Geometry geo);
int surfaceLeft(Geometry geo);
int surfaceLeft(Gemoetry geo);
void moveUp();
void moveLeft();
void moveRight();
void gravity();
void enemyMove(Actor enem);
void bulletMove(Actor bull);
void main();
