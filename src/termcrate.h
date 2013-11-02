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
#define PLAYER_YVEL 2
#define ENEM_XVEL 2
#define ENEM_YVEL 2
#define BULL_XVEL 8

typedef struct {
	int x, 
		y, 
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

void tick();

int abs(int val);
int collision(Geometry g1, Geometry g2);

void updateEnemies();
void updateBullets();
void updateDeathFlags();
void updatePlayer();

int surfaceBottom(Geometry geo);
int surfaceTop(Geometry geo);
int surfaceLeft(Geometry geo);
int surfaceRight(Geometry geo);

void moveUp();
void moveLeft();
void moveRight();
void gravity();
void fire();

void enemyMove(Actor enem);
void bulletMove(Actor bull);

void main();
