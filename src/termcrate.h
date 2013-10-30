#define LEFT 1
#define RIGHT 0

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

void game()
void render()
void tick()
void updateEnemies()
void updateBullet()
void updatePlayer(int key)
int gameLost()
void main()
