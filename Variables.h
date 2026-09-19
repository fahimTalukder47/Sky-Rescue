#ifndef VARIABLES_H
#define VARIABLES_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE

#include "iGraphics.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <windows.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600
#define WORLD_WIDTH 2200.0
#define MAX_PASSENGERS 3
#define MAX_OBSTACLES 6
#define MAX_BUILDINGS 7
#define MAX_SURVIVORS 8
#define MAX_RAINDROPS 65
#define MAX_BULLETS 8
#define MAX_MEDKITS 4


enum GameState {
	MENU,
	LEVEL_SELECT,
	SECTOR_SELECT,
	NAME_INPUT,
	INSTRUCTIONS,
	GAMEPLAY,
	PAUSED,
	SECTOR_COMPLETE,
	GAMEOVER,
	VICTORY,
	HIGHSCORES,
	DEVELOPERS
};


#define OBS_BIRD 0
#define OBS_ROCK 1
#define OBS_DRONE 2
#define OBS_LIGHTNING 3

struct Building {
	double x;                       
	double width;                 
	double height;                 
	int platformType;               
	int rescuesFromThisBuilding;    
};

struct Helicopter {
	double x, y;
	double targetX;
	double vx, vy;
	double tilt;
	int passengers;
	double fuel;
	int spells;
	int medkits;
	bool isShielded;
	int shieldTimer;
	int rotorAngle;
	int tailRotorAngle;
	bool winchActive;
	double winchLen;
	double cableAngle;
	double cableAngularVel;
	int lives;
	int blinkCounter;
};

#define MAX_BOSS_PROJECTILES 6
struct BossProjectile {
	double x, y;
	double vx, vy;
	bool active;
};

// Sector 3 Enemy Helicopter.  The old BossVillain name is kept internally
// so the existing project structure remains compatible.
struct BossVillain {
	double x, y;
	double vx, vy;
	int hp;
	int maxHp;
	bool active;
	int shootTimer;
	int flashTimer;
	int rotorAngle;
	double width, height;
	struct BossProjectile projectiles[MAX_BOSS_PROJECTILES];
};

struct Survivor {
	double x, y;
	double originalY;
	bool active;
	int state; // 0: Waiting on Roof, 1: Being Hoisted Up, 2: Aid Received
	int waveAngle;
	int platformType;
	double baseWidth;
	double baseHeight;
	int spriteVariant;
	int buildingIndex;
	int shoutVariant;
	double walkOffset;
	double walkSpeed;
	int climbCycle;
	bool hasReceivedAid;
};

struct Obstacle {
	double x, y;
	double vx, vy;
	int type;
	bool active;
	double width, height;
	double param;
	int spriteVariant;
};

struct FuelCan {
	double x, y;
	double vy;
	bool active;
	bool hasParachute;
	int spriteVariant;
};

struct SpellOrb {
	double x, y;
	double vy;
	bool active;
	double pulse;
	int spriteVariant;
};

struct MedkitDrop {
	double x, y;
	double vy;
	bool active;
	int spriteVariant;
};

struct Bullet {
	double x, y;
	double vx;
	bool active;
};

struct Shockwave {
	double x, y;
	double radius;
	double maxRadius;
	bool active;
};

struct Raindrop {
	double x, y;
	double speed;
	double length;
	double slant;
};

#define MAX_WIND_PARTICLES 24
struct WindParticle {
	double x, y;
	double vx, vy;
	double size;
	int type; 
};
extern GameState currentState;
extern struct Helicopter player;
extern struct Building cityBuildings[MAX_BUILDINGS];
extern struct Survivor survivors[MAX_SURVIVORS];
extern struct Obstacle obstacles[MAX_OBSTACLES];
extern struct FuelCan fuelPickups[3];
extern struct SpellOrb spellPickups[2];
extern struct MedkitDrop medkitDrops[MAX_MEDKITS];
extern struct Bullet bullets[MAX_BULLETS];
extern struct Shockwave shockwave;
extern struct BossVillain boss;
extern struct Raindrop raindrops[MAX_RAINDROPS];
extern struct WindParticle windParticles[MAX_WIND_PARTICLES];
extern double cameraX;
extern double distantBirdX;
extern double cloudDriftX;
extern double flockX, flockY;

extern int selectedLevelTier; 
extern int currentSector;      
extern int targetSectorToPlay;
extern int score;
extern int sectorRescued;
extern int careerRescues;
extern int careerMissionsCompleted;


extern int targetRescue[4][4];

extern int gameOverReason;
extern bool isLifting;
extern bool isWinchLowering;   
extern int lightningFlash;
extern double waterWavePhase;
extern int rescueNotificationTimer;
extern char rescueNotificationText[64];

// Pre-flight 3-2-1 Countdown Timer
extern int countdownTimer;

// Player Name Input Variables
extern char playerName[32];
extern char inputBuffer[32];
extern int nameLen;

// Leaderboard arrays
extern int highScores[5];
extern char highNames[5][32];

// Helipad Base Position
const double HELIPAD_X = 15.0;
const double HELIPAD_Y = 50.0;
const double HELIPAD_W = 165.0;
const double HELIPAD_H = 30.0;

extern int imgMenu;
extern int imgLevelSelect;
extern int imgSectorSelect;
extern int imgHowToPlay;
extern int imgPilotReg;
extern int imgLeaderboard;
extern int imgDevelopers;

// Sector Backgrounds
extern int imgSector1;
extern int imgSector2;
extern int imgSector3;

// Transparent Spritesheet Frames: Row 1 The Rescue Helicopter
extern int imgHeliNeutral;
extern int imgHeliTiltLeft;
extern int imgHeliTiltRight;
extern int imgHelicopter; // Legacy fallback

// Animated Bird Obstacle Sprites (3-Frame Flight Cycle from User Artwork)
extern int imgBirdLeft[3];
extern int imgBirdRight[3];

// Animated Eagle Obstacle Sprites (3-Frame Flight Cycle)
extern int imgEagleLeft[3];
extern int imgEagleRight[3];

// Animated Cloud Lightning Obstacle Sprites (7-Frame Strike Cycle)
extern int imgCloudLightning[7];

// Transparent Sprites
extern int imgHelipad;
extern int imgObstacle1;
extern int imgObstacle2;
extern int imgPower1;
extern int imgPower2;
extern int imgFuel1;
extern int imgFuel2;
extern int imgFuelBar; // Battery-style fuel HUD frame
extern int imgMedi1;
extern int imgMedi2;
extern int imgPeople[4];
extern int imgPeopleAnim[4][4];
extern int imgPeopleIdle[4];
extern int imgPeopleWave[4];

// Transparent Countdown Sprites (3.png, 2.png, 1.png, play.png)
extern int imgCount3;
extern int imgCount2;
extern int imgCount1;
extern int imgCountPlay;
extern int imgBoss;

// Safe wrapper for file existence check & image loader
inline int safeLoadImage(const char *filename) {
	if (filename == NULL) return -1;
	FILE *fp = fopen(filename, "rb");
	if (!fp) {
		return -1; // File does not exist on disk
	}
	fclose(fp);
	return iLoadImage((char*)filename);
}

// Safe wrapper for transparent image drawing (with OpenGL alpha blending)
inline void drawTransparentImage(int x, int y, int width, int height, int texture) {
	if (texture <= 0) return;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	iShowImage(x, y, width, height, texture);
	glDisable(GL_BLEND);
}

// Safe wrapper for iText
inline void drawText(double x, double y, const char *str, void *font = GLUT_BITMAP_8_BY_13) {
	if (str != NULL) {
		iText(x, y, (char*)str, font);
	}
}

// Sound Feedback
inline void playSoundEffect(const char *soundType) {
	if (strcmp(soundType, "pickup") == 0) {
		Beep(1200, 40);
	}
	else if (strcmp(soundType, "deposit") == 0) {
		Beep(800, 30);
		Beep(1400, 50);
	}
	else if (strcmp(soundType, "refuel") == 0) {
		Beep(600, 30);
		Beep(900, 40);
	}
	else if (strcmp(soundType, "spell") == 0) {
		Beep(1500, 60);
		Beep(2000, 80);
	}
	else if (strcmp(soundType, "shoot") == 0) {
		Beep(1600, 25);
	}
	else if (strcmp(soundType, "hit") == 0) {
		Beep(2200, 35);
	}
	else if (strcmp(soundType, "medkit") == 0) {
		Beep(1100, 40);
		Beep(1700, 60);
	}
	else if (strcmp(soundType, "winch") == 0) {
		Beep(950, 20);
	}
	else if (strcmp(soundType, "countdown") == 0) {
		Beep(1000, 50);
	}
	else if (strcmp(soundType, "go") == 0) {
		Beep(1800, 90);
	}
	else if (strcmp(soundType, "crash") == 0) {
		Beep(300, 120);
	}
	else if (strcmp(soundType, "life_lost") == 0) {
		Beep(500, 80);
		Beep(350, 100);
	}
	else if (strcmp(soundType, "boss_hit") == 0) {
		Beep(2400, 30);
	}
	else if (strcmp(soundType, "boss_defeat") == 0) {
		Beep(800, 60);
		Beep(1200, 80);
		Beep(1800, 140);
	}
}

#endif // VARIABLES_H