/* 
 * Macros
 */

#define MOVE_UP 'w'
#define MOVE_LEFT 'a'
#define MOVE_RIGHT 'd'
#define FIRE 'j'
#define QUIT KEY_F1

#define PAUSE (1000000 / 60)

#define LEFT -1
#define RIGHT 1
#define G 1

#define PLAYER_DELAY 1
#define JUMP_HEIGHT 18

#define ENEM_DELAY 3
#define ENEMY_RADIUS 1
#define MAX_ENEMIES 50

#define BULL_DELAY 1
#define BULLET_RADIUS 1
#define FIRE_RATE 15
#define MAX_BULLETS 50

#define ENEMY_SPAWN_TICKS 300
#define GRAVITY_DELAY_TICKS 4

/*
 * Structs
 */


typedef struct {
    int x, 
        y, 
        rad; 	//radius
} Geometry_t;

typedef struct {
    Geometry_t p1,
               p2;
} Surface_t;

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
    int dirMotion;
    int reload;
} Player_t;

typedef struct {
	Actor_t enemy;
	Actor_t bullet;
	Crate_t crate;
	Player_t player;
} Elements_t;

typedef struct {
    int up;
    int left;
    int right;
    int fire;
} Keys_t;

/*
 * Functions
 */


void game();
void config();
void loadElements();

void tick();

int abs(int val);
int collision(Geometry_t g1, Geometry_t g2);

void updateEnemies();
void spawnEnemy();
void expireEnemies();

void updateBullets();
void spawnBullet();
void expireBullets();

void clearKeys();
void updateKeys();
void updatePlayer();

int surfaceBottom(Geometry_t geo);
int surfaceTop(Geometry_t geo);
int surfaceLeft(Geometry_t geo);
int surfaceRight(Geometry_t geo);

void moveUp();
void moveLeft();
void moveRight();
void moveDown();

void enemyMove(Actor_t * enem);
void bulletMove(Actor_t * bull);

void main();
