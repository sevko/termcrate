#define LEFT 1
#define RIGHT 0

#define MOVE_UP KEY_UP
#define MOVE_DOWN KEY_DOWN
#define MOVE_LEFT KEY_LEFT
#define MOVE_RIGHT KEY_RIGHT

#define FIRE 'x'
#define QUIT KEY_F1

#define PAUSE (1000000 / 60)

struct Enemy {
	int xPos, yPos;
	int dirMotion;
	int alive;
}

struct Bullet {
	int xPos, yPos;
	int dirMotion;
}

struct Crate {
	int xPos, yPos;
}

void game();
void config();
void render();
void tick();
void updateEnemies();
void updateBullet();
void updatePlayer();
void main();
