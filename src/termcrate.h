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
#define JUMP_HEIGHT 15

#define ENEM_DELAY 2
#define ENEMY_RADIUS 1

#define BULL_DELAY 1
#define BULLET_RADIUS 1

#define NUM_WEAPONS 3
#define MAX_BULLETS 50
#define MAX_ENEMIES 50

#define ENEMY_SPAWN_TICKS 200
#define GRAVITY_DELAY_TICKS 3

/*
 * Structs
 */

typedef struct {
	int x, y, rad;		//radius
} Geometry_t;

typedef struct {
	Geometry_t p1, p2;
} Surface_t;

typedef struct {
	Geometry_t geo;
	int dirMotion, alive;
} Actor_t;

typedef struct {
	int ammo, rof;
} Weapon_t;

typedef struct {
	Geometry_t geo;
	Weapon_t weapon;
} Crate_t;

typedef struct {
	Geometry_t geo;
	Weapon_t weapon;
	int dirMotion;
	int reload;
	int jumpTime;
} Player_t;

typedef struct {
	Actor_t enemy;
	Actor_t bullet;
	Crate_t crate;
	Player_t player;

	Weapon_t pistol;
	Weapon_t shotgun;
	Weapon_t machineGun;
} Elements_t;

typedef struct {
	int up, left, right;
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
void gravity();

//void crateCollision();
//void resetCrate();

void enemyMove(Actor_t * enem);
void bulletMove(Actor_t * bull);

void main();
