/* 
 * Macros
*/

#define MOVE_UP KEY_UP
#define MOVE_LEFT KEY_LEFT
#define MOVE_RIGHT KEY_RIGHT
#define FIRE 'x'
#define QUIT KEY_F1

#define PAUSE (1000000 / 60)

#define LEFT 1
#define RIGHT 0
#define G 1

#define PLAYER_XVEL 3
#define JUMP_HEIGHT 6
#define ENEM_XVEL 2
#define ENEM_YVEL 2

#define BULL_XVEL 8
#define BULLET_RADIUS 1

#define ENEMY_SPAWN_TICKS 300
#define GRAVITY_DELAY_TICKS 6 

/*
 * Structs
*/


typedef struct {
	int x, 
		y, 
		rad; 	//radius
} Geometry_t;

typedef struct {
	Geometry_t geo;
    int dirMotion;
    int alive;
} Actor_t;

typedef struct {
	Geometry_t geo;
} Crate_t;

typedef struct {
	Geometry_t geo;
} Player_t;

typedef struct {
	Geometry_t p1;
	Geometry_t p2;
} Surface_t;

/*
 * Functions
*/


void game();
void config();

void tick();

int abs(int val);
int collision(Geometry_t g1, Geometry_t g2);
void addActor(Actor_t * actors, Actor_t newActor, int numAct);

void updateEnemies();
void updateBullets();
void updateDeathFlags();
void updatePlayer();

int surfaceBottom(Geometry_t geo);
int surfaceTop(Geometry_t geo);
int surfaceLeft(Geometry_t geo);
int surfaceRight(Geometry_t geo);

void moveUp();
void moveLeft();
void moveRight();
void gravity();
void fire();

void enemyMove(Actor_t enem);
void bulletMove(Actor_t bull);

void main();
