#ifndef _GAME_DEFINES_H
#define _GAME_DEFINES_H

#define FRAMES_PER_SECOND_CAP 60

// Old ones
//#define WINDOW_WIDTH 800 // 1360 (X)
//#define WINDOW_HEIGHT 600 // 768 (Y)

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

#define WINDOW_NAME "Space shooter"

#define DEG2RAD 3.14159f / 180.0f

// Shared enum used in Enemy.cpp & Player.cpp
enum EnemyType
{
	ENEMY_TYPE_ASTEROID = 0,
	ENEMY_TYPE_SPACESHIP = 1,

	// Unused (currently)
	ENEMY_TYPE_CREATURE = 2,
	ENEMY_TYPE_ELITE = 3
};

#define MAX_LEVEL 256

const int xpForLevel[MAX_LEVEL] = { 38, 154, 381, 635, 819, 1281, 1819, 2504, 3349, 4018, 4739, 5714, 6891, 7354, 8419, 9110, 10011,  };

// Unused
//#define GROUND_HEIGHT 128 // This should be defined elsewhere I guess

#endif