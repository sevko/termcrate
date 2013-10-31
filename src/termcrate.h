#define LEFT 1
#define RIGHT 0

#define MOVE_UP KEY_UP
#define MOVE_LEFT KEY_LEFT
#define MOVE_RIGHT KEY_RIGHT

#define FIRE 'x'
#define QUIT KEY_F1

#define PAUSE (1000000 / 60)
#define XVEL 1
#define YVEL 2
#define G = 1

struct Enemy {
    int xPos, yPos;
    int dirMotion;
    int alive;
};

struct Bullet {
    int xPos, yPos;
    int dirMotion;
};

struct Crate {
    int xPos, yPos;
};

struct Player {
    int xPos, yPos;
    int yVel;
};

void game();
void config();
void render();
void tick();
void updateEnemies();
void updateBullet();
void updatePlayer();
void main();
