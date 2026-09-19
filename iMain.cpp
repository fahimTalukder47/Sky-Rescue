#include "Variables.h"
#include "Leaderboard.h"
#include "Rescue.h"
#include "Hazards.h"
#include "Physics.h"
#include "Rendering.h"
#include "Menu.h"

GameState currentState = MENU;
struct Helicopter player;
struct Building cityBuildings[MAX_BUILDINGS];
struct Survivor survivors[MAX_SURVIVORS];
struct Obstacle obstacles[MAX_OBSTACLES];
struct FuelCan fuelPickups[3];
struct SpellOrb spellPickups[2];
struct MedkitDrop medkitDrops[MAX_MEDKITS];
struct Bullet bullets[MAX_BULLETS];
struct Shockwave shockwave;
// Sector 3 enemy helicopter / final enemy
struct BossVillain boss;
int careerRescues = 0;
int careerMissionsCompleted = 0;
struct Raindrop raindrops[MAX_RAINDROPS];
struct WindParticle windParticles[MAX_WIND_PARTICLES];
double cameraX = 0.0;
double distantBirdX = 120.0;
double cloudDriftX = 0.0;
double flockX = 140.0;
double flockY = 460.0;

int selectedLevelTier = 1; 
int currentSector = 1;      
int targetSectorToPlay = 1;
int score = 0;
int sectorRescued = 0;


int targetRescue[4][4] = {
	{ 0, 0, 0, 0 },
	{ 0, 15, 20, 25 },
	{ 0, 20, 25, 30 },
	{ 0, 25, 30, 35 }
};

int gameOverReason = 0;
bool isLifting = false;
bool isWinchLowering = false;
int lightningFlash = 0;
double waterWavePhase = 0.0;
int rescueNotificationTimer = 0;
char rescueNotificationText[64] = "";
int countdownTimer = 180;

char playerName[32] = "Pilot";
char inputBuffer[32] = "";
int nameLen = 0;

int highScores[5] = { 2500, 1800, 1200, 800, 400 };
char highNames[5][32] = { "Capt.Rafiq", "FlyerTanvir", "PilotAUST", "Skyhawk", "Rescuer" };

int imgMenu = -1;
int imgLevelSelect = -1;
int imgSectorSelect = -1;
int imgHowToPlay = -1;
int imgPilotReg = -1;
int imgLeaderboard = -1;
int imgDevelopers = -1;

int imgSector1 = -1;
int imgSector2 = -1;
int imgSector3 = -1;

int imgHeliNeutral = -1;
int imgHeliTiltLeft = -1;
int imgHeliTiltRight = -1;
int imgHelicopter = -1;

int imgBirdLeft[3] = { -1, -1, -1 };
int imgBirdRight[3] = { -1, -1, -1 };

int imgEagleLeft[3] = { -1, -1, -1 };
int imgEagleRight[3] = { -1, -1, -1 };

int imgCloudLightning[7] = { -1, -1, -1, -1, -1, -1, -1 };

int imgHelipad = -1;
int imgObstacle1 = -1;
int imgObstacle2 = -1;
int imgPower1 = -1;
int imgPower2 = -1;
int imgFuel1 = -1;
int imgFuel2 = -1;
int imgFuelBar = -1; // Battery-style fuel HUD frame
int imgMedi1 = -1;
int imgMedi2 = -1;
int imgPeople[4] = { -1, -1, -1, -1 };
int imgPeopleAnim[4][4] = {
	{ -1, -1, -1, -1 },
	{ -1, -1, -1, -1 },
	{ -1, -1, -1, -1 },
	{ -1, -1, -1, -1 }
};
int imgPeopleIdle[4] = { -1, -1, -1, -1 };
int imgPeopleWave[4] = { -1, -1, -1, -1 };

int imgCount3 = -1;
int imgCount2 = -1;
int imgCount1 = -1;
int imgCountPlay = -1;
int imgBoss = -1; // Sector 3 enemy helicopter

void iDraw() {
	iClear();
	if (currentState == MENU) {
		drawMenu();
	}
	else if (currentState == LEVEL_SELECT) {
		drawLevelSelect();
	}
	else if (currentState == SECTOR_SELECT) {
		drawSectorSelect();
	}
	else if (currentState == NAME_INPUT) {
		drawNameInput();
	}
	else if (currentState == INSTRUCTIONS) {
		drawInstructions();
	}
	else if (currentState == HIGHSCORES) {
		drawHighScores();
	}
	else if (currentState == DEVELOPERS) {
		drawDevelopers();
	}
	else if (currentState == GAMEPLAY || currentState == PAUSED ||
		currentState == SECTOR_COMPLETE || currentState == GAMEOVER ||
		currentState == VICTORY) {
		drawEnvironment();
		drawHospitalHelipad();
		drawCityBuildings();
		for (int i = 0; i < MAX_SURVIVORS; i++) drawSurvivor(survivors[i]);
		for (int i = 0; i < MAX_OBSTACLES; i++) drawObstacle(obstacles[i]);
		for (int i = 0; i < 3; i++) drawFuelPickup(fuelPickups[i]);
		for (int i = 0; i < 2; i++) drawSpellPickup(spellPickups[i]);
		for (int m = 0; m < MAX_MEDKITS; m++) drawMedkitDrop(medkitDrops[m]);
		for (int b = 0; b < MAX_BULLETS; b++) drawBullet(bullets[b]);
		drawShockwave(shockwave);
		drawBossVillain();
		drawHelicopter(player.x - cameraX, player.y, player.tilt, player.passengers, player.isShielded, player.winchLen);
		drawHUD();
		if (currentState == PAUSED) drawPause();
		else if (currentState == SECTOR_COMPLETE) drawSectorComplete();
		else if (currentState == GAMEOVER) drawGameOver();
		else if (currentState == VICTORY) drawVictory();
	}
}

void iMouseMove(int mx, int my) {
	if (currentState == GAMEPLAY) {
		isLifting = true;
	}
}

void iPassiveMouseMove(int mx, int my) {

}

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (currentState == GAMEPLAY) {
			isLifting = true;
		}
		else if (currentState == MENU) {
			if (mx >= 320 && mx <= 680) {
				if (my >= 355 && my <= 415) {                 
					selectedLevelTier = 1;
					currentState = LEVEL_SELECT;
				}
				else if (my >= 295 && my <= 355) {            
					currentState = LEVEL_SELECT;
				}
				else if (my >= 240 && my <= 295) currentState = INSTRUCTIONS;
				else if (my >= 185 && my <= 240) currentState = HIGHSCORES;
				else if (my >= 130 && my <= 185) currentState = DEVELOPERS;
				else if (my >= 75 && my <= 130) exit(0);
			}
		}
		else if (currentState == LEVEL_SELECT) {
			if (mx >= 220 && mx <= 780) {
				if (my >= 360 && my <= 460) {                 
					selectedLevelTier = 1;
					currentState = SECTOR_SELECT;
				}
				else if (my >= 250 && my <= 350) {           
					selectedLevelTier = 2;
					currentState = SECTOR_SELECT;
				}
				else if (my >= 140 && my <= 240) {           
					selectedLevelTier = 3;
					currentState = SECTOR_SELECT;
				}
			}
			if (mx >= 330 && mx <= 670 && my >= 30 && my <= 95) {
				currentState = MENU;
			}
		}
		else if (currentState == SECTOR_SELECT) {
			if (mx >= 180 && mx <= 820) {
				if (my >= 365 && my <= 465) {                 
					targetSectorToPlay = 1;
					inputBuffer[0] = '\0';
					nameLen = 0;
					currentState = NAME_INPUT;
				}
				else if (my >= 255 && my <= 355) {            
					targetSectorToPlay = 2;
					inputBuffer[0] = '\0';
					nameLen = 0;
					currentState = NAME_INPUT;
				}
				else if (my >= 145 && my <= 245) {           
					targetSectorToPlay = 3;
					inputBuffer[0] = '\0';
					nameLen = 0;
					currentState = NAME_INPUT;
				}
			}

			if (mx >= 300 && mx <= 700 && my >= 20 && my <= 80) {
				currentState = LEVEL_SELECT;
			}
		}
		else if (currentState == NAME_INPUT) {
			if (mx >= 320 && mx <= 680 && my >= 185 && my <= 255) {
				if (nameLen > 0) strcpy_s(playerName, sizeof(playerName), inputBuffer);
				else strcpy_s(playerName, sizeof(playerName), "Pilot");
				isLifting = false;
				startNewGame();
			}
			else if (mx >= 370 && mx <= 630 && my >= 125 && my <= 175) {
				currentState = SECTOR_SELECT;
			}
		}
		else if (currentState == INSTRUCTIONS || currentState == HIGHSCORES || currentState == DEVELOPERS) {
			currentState = MENU;
		}
		else if (currentState == SECTOR_COMPLETE) {
			if (currentSector < 3) {
				initSector(currentSector + 1);
				currentState = GAMEPLAY;
			}
			else {
				updateHighScore(score);
				currentState = VICTORY;
			}
		}
		else if (currentState == GAMEOVER) {
			if (mx >= SCREEN_WIDTH / 2 - 130 && mx <= SCREEN_WIDTH / 2 + 130) {
				if (my >= SCREEN_HEIGHT / 2 - 65 && my <= SCREEN_HEIGHT / 2 - 20) startNewGame();
				else if (my >= SCREEN_HEIGHT / 2 - 115 && my <= SCREEN_HEIGHT / 2 - 70) currentState = MENU;
			}
		}
		else if (currentState == VICTORY) {
			currentState = MENU;
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (currentState == GAMEPLAY) isLifting = false;
	}
}

bool g_glutKeyboardActive = false;

void iKeyboard(unsigned char key) {
	g_glutKeyboardActive = true;

	if (key == 27) { // ESC
		if (currentState == SECTOR_SELECT) currentState = LEVEL_SELECT;
		else if (currentState == LEVEL_SELECT) currentState = MENU;
		else if (currentState == NAME_INPUT) currentState = SECTOR_SELECT;
		else if (currentState == PAUSED) currentState = MENU;
		else if (currentState == GAMEPLAY) { currentState = MENU; isLifting = false; }
		else if (currentState == INSTRUCTIONS || currentState == HIGHSCORES || currentState == DEVELOPERS || currentState == GAMEOVER || currentState == VICTORY) currentState = MENU;
		return;
	}

	if (currentState == NAME_INPUT) {
		if (key == 13 || key == 10) {                  // ENTER
			if (nameLen > 0) strcpy_s(playerName, sizeof(playerName), inputBuffer);
			else strcpy_s(playerName, sizeof(playerName), "Pilot");
			isLifting = false;
			startNewGame();
			return;
		}

		if (key == 8) {                              
			if (nameLen > 0) {
				nameLen--;
				inputBuffer[nameLen] = '\0';
				if (nameLen > 0) strcpy_s(playerName, sizeof(playerName), inputBuffer);
				else strcpy_s(playerName, sizeof(playerName), "Pilot");
			}
			return;
		}

		if (key >= 32 && key <= 126) {               
			if (nameLen < 18) {
				inputBuffer[nameLen] = (char)key;
				nameLen++;
				inputBuffer[nameLen] = '\0';
				strcpy_s(playerName, sizeof(playerName), inputBuffer);
			}
			return;
		}
		return;
	}

	if (currentState == LEVEL_SELECT) {
		if (key == '1') { selectedLevelTier = 1; currentState = SECTOR_SELECT; }
		else if (key == '2') { selectedLevelTier = 2; currentState = SECTOR_SELECT; }
		else if (key == '3') { selectedLevelTier = 3; currentState = SECTOR_SELECT; }
		return;
	}

	if (currentState == SECTOR_SELECT) {
		if (key == '1') { targetSectorToPlay = 1; inputBuffer[0] = '\0'; nameLen = 0; currentState = NAME_INPUT; }
		else if (key == '2') { targetSectorToPlay = 2; inputBuffer[0] = '\0'; nameLen = 0; currentState = NAME_INPUT; }
		else if (key == '3') { targetSectorToPlay = 3; inputBuffer[0] = '\0'; nameLen = 0; currentState = NAME_INPUT; }
		return;
	}

	if (currentState == MENU) {
		if (key == '1') { selectedLevelTier = 1; currentState = LEVEL_SELECT; }
		else if (key == '2') { currentState = LEVEL_SELECT; }
		else if (key == '3') { currentState = INSTRUCTIONS; }
		else if (key == '4') { currentState = HIGHSCORES; }
		else if (key == '5') { currentState = DEVELOPERS; }
		else if (key == '6') { exit(0); }
		return;
	}

	if (currentState == GAMEPLAY) {
		if (key == 's' || key == 'S') dropMedkit();
		else if (key == 'f' || key == 'F' || key == 'x' || key == 'X') shootBullet();
		else if (key == 'e' || key == 'E') activateSkyBlast();
		else if (key == 'p' || key == 'P') currentState = PAUSED;
	}
	else if (currentState == PAUSED) {
		if (key == 'p' || key == 'P') currentState = GAMEPLAY;
	}
	else if (currentState == GAMEOVER || currentState == SECTOR_COMPLETE) {
		if (key == 'r' || key == 'R') startNewGame();
	}
}

void iSpecialKeyboard(unsigned char key) {
	if (key == GLUT_KEY_DOWN) {
		if (currentState == GAMEPLAY) dropMedkit();
	}
}

void fixedUpdate() {
	
	static bool escWasDown = false;
	bool escIsDown = (GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0 || (keyPressed[27] != 0);
	if (escIsDown && !escWasDown) {
		if (currentState == SECTOR_SELECT) currentState = LEVEL_SELECT;
		else if (currentState == LEVEL_SELECT) currentState = MENU;
		else if (currentState == NAME_INPUT) currentState = SECTOR_SELECT;
		else if (currentState == PAUSED) currentState = MENU;
		else if (currentState == GAMEPLAY) { currentState = MENU; isLifting = false; }
		else if (currentState == INSTRUCTIONS || currentState == HIGHSCORES || currentState == DEVELOPERS || currentState == GAMEOVER || currentState == VICTORY) currentState = MENU;
	}
	escWasDown = escIsDown;

	
	static bool pWasDown = false;
	bool pIsDown = (GetAsyncKeyState('P') & 0x8000) != 0 || (keyPressed['p'] != 0) || (keyPressed['P'] != 0);
	if (pIsDown && !pWasDown) {
		if (currentState == GAMEPLAY) currentState = PAUSED;
		else if (currentState == PAUSED) currentState = GAMEPLAY;
	}
	pWasDown = pIsDown;


	if (currentState == MENU || currentState == LEVEL_SELECT || currentState == SECTOR_SELECT) {
		static bool numWasDown[10] = { false };
		for (int d = 1; d <= 6; d++) {
			int vk = '0' + d;
			bool isDown = (GetAsyncKeyState(vk) & 0x8000) != 0 || (keyPressed[vk] != 0);
			if (isDown && !numWasDown[d]) {
				if (currentState == MENU) {
					if (d == 1) { selectedLevelTier = 1; currentState = LEVEL_SELECT; }
					else if (d == 2) { currentState = LEVEL_SELECT; }
					else if (d == 3) { currentState = INSTRUCTIONS; }
					else if (d == 4) { currentState = HIGHSCORES; }
					else if (d == 5) { currentState = DEVELOPERS; }
					else if (d == 6) { exit(0); }
				}
				else if (currentState == LEVEL_SELECT) {
					if (d >= 1 && d <= 3) { selectedLevelTier = d; currentState = SECTOR_SELECT; }
				}
				else if (currentState == SECTOR_SELECT) {
					if (d >= 1 && d <= 3) {
						targetSectorToPlay = d;
						inputBuffer[0] = '\0';
						nameLen = 0;
						currentState = NAME_INPUT;
					}
				}
			}
			numWasDown[d] = isDown;
		}
	}

	
	if (currentState == NAME_INPUT && !g_glutKeyboardActive) {
		
		static bool enterWasDown = false;
		bool enterIsDown = (GetAsyncKeyState(VK_RETURN) & 0x8000) != 0 || (keyPressed[13] != 0) || (keyPressed[10] != 0);
		if (enterIsDown && !enterWasDown) {
			if (nameLen > 0) strcpy_s(playerName, sizeof(playerName), inputBuffer);
			else strcpy_s(playerName, sizeof(playerName), "Pilot");
			isLifting = false;
			startNewGame();
		}
		enterWasDown = enterIsDown;

		
		static bool backWasDown = false;
		bool backIsDown = (GetAsyncKeyState(VK_BACK) & 0x8000) != 0 || (keyPressed[8] != 0);
		if (backIsDown && !backWasDown) {
			if (nameLen > 0) {
				nameLen--;
				inputBuffer[nameLen] = '\0';
				if (nameLen > 0) strcpy_s(playerName, sizeof(playerName), inputBuffer);
				else strcpy_s(playerName, sizeof(playerName), "Pilot");
			}
		}
		backWasDown = backIsDown;

		// SPACE
		static bool spaceWasDown = false;
		bool spaceIsDown = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0 || (keyPressed[' '] != 0);
		if (spaceIsDown && !spaceWasDown) {
			if (nameLen < 18) {
				inputBuffer[nameLen] = ' ';
				nameLen++;
				inputBuffer[nameLen] = '\0';
				strcpy_s(playerName, sizeof(playerName), inputBuffer);
			}
		}
		spaceWasDown = spaceIsDown;

		
		static bool alphaWasDown[26] = { false };
		bool shiftHeld = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
		for (int i = 0; i < 26; i++) {
			int vk = 'A' + i;
			bool isDown = (GetAsyncKeyState(vk) & 0x8000) != 0 || (keyPressed['a' + i] != 0) || (keyPressed['A' + i] != 0);
			if (isDown && !alphaWasDown[i]) {
				if (nameLen < 18) {
					char c = shiftHeld ? ('A' + i) : ('a' + i);
					inputBuffer[nameLen] = c;
					nameLen++;
					inputBuffer[nameLen] = '\0';
					strcpy_s(playerName, sizeof(playerName), inputBuffer);
				}
			}
			alphaWasDown[i] = isDown;
		}

		
		static bool digitWasDown[10] = { false };
		for (int i = 0; i < 10; i++) {
			int vk = '0' + i;
			bool isDown = (GetAsyncKeyState(vk) & 0x8000) != 0 || (keyPressed['0' + i] != 0);
			if (isDown && !digitWasDown[i]) {
				if (nameLen < 18) {
					inputBuffer[nameLen] = (char)('0' + i);
					nameLen++;
					inputBuffer[nameLen] = '\0';
					strcpy_s(playerName, sizeof(playerName), inputBuffer);
				}
			}
			digitWasDown[i] = isDown;
		}
	}

	if (currentState == GAMEOVER || currentState == SECTOR_COMPLETE) {
		static bool rWasDown = false;
		bool rIsDown = (GetAsyncKeyState('R') & 0x8000) != 0 || (keyPressed['r'] != 0) || (keyPressed['R'] != 0);
		if (rIsDown && !rWasDown) {
			startNewGame();
		}
		rWasDown = rIsDown;
	}
}

int main() {
	srand((unsigned int)time(NULL));
	initSector(1);
	currentState = MENU;
	loadHighScores();

	iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "SKY RESCUE: DISASTER RELIEF");

	// 1. Load Background Screens
	imgMenu = safeLoadImage("MainMenu.bmp");
	imgLevelSelect = safeLoadImage("levels.bmp");
	imgSectorSelect = safeLoadImage("SelectSector.bmp");
	imgHowToPlay = safeLoadImage("HowToPlay.bmp");
	imgPilotReg = safeLoadImage("PilotRegistration.bmp");
	imgLeaderboard = safeLoadImage("Leaderboard.bmp");
	imgDevelopers = safeLoadImage("developers.bmp");

	
	imgSector1 = safeLoadImage("sector1.bmp");
	if (imgSector1 == -1) imgSector1 = safeLoadImage("sector1.png");

	imgSector2 = safeLoadImage("sector2.bmp");
	if (imgSector2 == -1) imgSector2 = safeLoadImage("sector2.png");

	imgSector3 = safeLoadImage("sector3.bmp");
	if (imgSector3 == -1) imgSector3 = safeLoadImage("sector3.png");

	// 3. Load Transparent Helicopter Spritesheet Frames (Row 1 Cycle)
	imgHeliNeutral = safeLoadImage("spr_heli_neutral.png");
	if (imgHeliNeutral == -1) imgHeliNeutral = safeLoadImage("Images/spr_heli_neutral.png");

	imgHeliTiltLeft = safeLoadImage("spr_heli_tilt_left.png");
	if (imgHeliTiltLeft == -1) imgHeliTiltLeft = safeLoadImage("Images/spr_heli_tilt_left.png");

	imgHeliTiltRight = safeLoadImage("spr_heli_tilt_right.png");
	if (imgHeliTiltRight == -1) imgHeliTiltRight = safeLoadImage("Images/spr_heli_tilt_right.png");

	imgHelicopter = safeLoadImage("helicopter.png");
	if (imgHelicopter == -1) imgHelicopter = safeLoadImage("helicopter.jpg");

	// Load Transparent Bird Obstacle Sprites (Left-facing and Right-facing)
	imgBirdLeft[0] = safeLoadImage("spr_bird_left1.png");
	if (imgBirdLeft[0] == -1) imgBirdLeft[0] = safeLoadImage("Images/spr_bird_left1.png");
	imgBirdLeft[1] = safeLoadImage("spr_bird_left2.png");
	if (imgBirdLeft[1] == -1) imgBirdLeft[1] = safeLoadImage("Images/spr_bird_left2.png");
	imgBirdLeft[2] = safeLoadImage("spr_bird_left3.png");
	if (imgBirdLeft[2] == -1) imgBirdLeft[2] = safeLoadImage("Images/spr_bird_left3.png");

	imgBirdRight[0] = safeLoadImage("spr_bird_right1.png");
	if (imgBirdRight[0] == -1) imgBirdRight[0] = safeLoadImage("Images/spr_bird_right1.png");
	imgBirdRight[1] = safeLoadImage("spr_bird_right2.png");
	if (imgBirdRight[1] == -1) imgBirdRight[1] = safeLoadImage("Images/spr_bird_right2.png");
	imgBirdRight[2] = safeLoadImage("spr_bird_right3.png");
	if (imgBirdRight[2] == -1) imgBirdRight[2] = safeLoadImage("Images/spr_bird_right3.png");

	// Load Transparent Eagle Obstacle Sprites (Left-facing and Right-facing)
	imgEagleLeft[0] = safeLoadImage("spr_eagle_left1.png");
	if (imgEagleLeft[0] == -1) imgEagleLeft[0] = safeLoadImage("Images/spr_eagle_left1.png");
	imgEagleLeft[1] = safeLoadImage("spr_eagle_left2.png");
	if (imgEagleLeft[1] == -1) imgEagleLeft[1] = safeLoadImage("Images/spr_eagle_left2.png");
	imgEagleLeft[2] = safeLoadImage("spr_eagle_left3.png");
	if (imgEagleLeft[2] == -1) imgEagleLeft[2] = safeLoadImage("Images/spr_eagle_left3.png");

	imgEagleRight[0] = safeLoadImage("spr_eagle_right1.png");
	if (imgEagleRight[0] == -1) imgEagleRight[0] = safeLoadImage("Images/spr_eagle_right1.png");
	imgEagleRight[1] = safeLoadImage("spr_eagle_right2.png");
	if (imgEagleRight[1] == -1) imgEagleRight[1] = safeLoadImage("Images/spr_eagle_right2.png");
	imgEagleRight[2] = safeLoadImage("spr_eagle_right3.png");
	if (imgEagleRight[2] == -1) imgEagleRight[2] = safeLoadImage("Images/spr_eagle_right3.png");

	// Load Animated Cloud Lightning Obstacle Sprites (7-Frame Strike Cycle)
	for (int cl = 0; cl < 7; cl++) {
		char clName[64];
		sprintf_s(clName, "spr_cloud_lightning%d.png", cl + 1);
		imgCloudLightning[cl] = safeLoadImage(clName);
		if (imgCloudLightning[cl] == -1) {
			char clPath[64];
			sprintf_s(clPath, "Images/spr_cloud_lightning%d.png", cl + 1);
			imgCloudLightning[cl] = safeLoadImage(clPath);
		}
	}

	// 4. Load Other Transparent Sprites
	imgHelipad = safeLoadImage("helipad.png");
	if (imgHelipad == -1) imgHelipad = safeLoadImage("helipad.jpg");

	imgObstacle1 = safeLoadImage("obstacle1.png");
	if (imgObstacle1 == -1) imgObstacle1 = safeLoadImage("obstacle1.jpg");

	imgObstacle2 = safeLoadImage("obstacle2.png");
	if (imgObstacle2 == -1) imgObstacle2 = safeLoadImage("obstacle2.jpg");

	// Sector 3 enemy helicopter supplied for the final level.
	imgBoss = safeLoadImage("enemy.png");
	if (imgBoss == -1) imgBoss = safeLoadImage("Images/enemy.png");

	imgPower1 = safeLoadImage("power1.png");
	if (imgPower1 == -1) imgPower1 = safeLoadImage("power1.jpg");

	imgPower2 = safeLoadImage("power2.png");
	if (imgPower2 == -1) imgPower2 = safeLoadImage("power2.jpg");

	imgFuel1 = safeLoadImage("fuel1.png");
	if (imgFuel1 == -1) imgFuel1 = safeLoadImage("fuel1.jpg");

	imgFuel2 = safeLoadImage("fuel2.png");
	if (imgFuel2 == -1) imgFuel2 = safeLoadImage("fuel2.jpg");

	// Battery-style fuel HUD frame (transparent center; green fuel is drawn inside)
	imgFuelBar = safeLoadImage("fuel_bar_frame.png");

	imgMedi1 = safeLoadImage("medi1.png");
	if (imgMedi1 == -1) imgMedi1 = safeLoadImage("medi1.jpg");

	imgMedi2 = safeLoadImage("medi2.png");
	if (imgMedi2 == -1) imgMedi2 = safeLoadImage("medi2.jpg");

	imgPeople[0] = safeLoadImage("people1.png");
	if (imgPeople[0] == -1) imgPeople[0] = safeLoadImage("people.png");
	if (imgPeople[0] == -1) imgPeople[0] = safeLoadImage("people1.jpg");

	imgPeople[1] = safeLoadImage("people2.png");
	if (imgPeople[1] == -1) imgPeople[1] = safeLoadImage("people2.jpg");

	imgPeople[2] = safeLoadImage("people3.png");
	if (imgPeople[2] == -1) imgPeople[2] = safeLoadImage("people3.jpg");

	imgPeople[3] = safeLoadImage("people4.png");
	if (imgPeople[3] == -1) imgPeople[3] = safeLoadImage("people4.jpg");

	// Load Animated Survivor Sprites (4 variants x 4 frames)
	for (int p = 0; p < 4; p++) {
		for (int f = 0; f < 4; f++) {
			char pName[64];
			sprintf_s(pName, "spr_people%d_%d.png", p + 1, f + 1);
			imgPeopleAnim[p][f] = safeLoadImage(pName);
			if (imgPeopleAnim[p][f] == -1) {
				char pPath[64];
				sprintf_s(pPath, "Images/spr_people%d_%d.png", p + 1, f + 1);
				imgPeopleAnim[p][f] = safeLoadImage(pPath);
			}
		}
	}

	// Load Idle and Waving Character Poses (Boy, Girl, Elder, Injured)
	for (int c = 0; c < 4; c++) {
		char idleName[64], waveName[64];
		sprintf_s(idleName, "spr_char%d_idle.png", c + 1);
		sprintf_s(waveName, "spr_char%d_wave.png", c + 1);
		imgPeopleIdle[c] = safeLoadImage(idleName);
		if (imgPeopleIdle[c] == -1) {
			char idlePath[64];
			sprintf_s(idlePath, "Images/spr_char%d_idle.png", c + 1);
			imgPeopleIdle[c] = safeLoadImage(idlePath);
		}
		imgPeopleWave[c] = safeLoadImage(waveName);
		if (imgPeopleWave[c] == -1) {
			char wavePath[64];
			sprintf_s(wavePath, "Images/spr_char%d_wave.png", c + 1);
			imgPeopleWave[c] = safeLoadImage(wavePath);
		}
	}

	// 5. Load Transparent Countdown Sprites (3.png, 2.png, 1.png, play.png)
	imgCount3 = safeLoadImage("3.png");
	if (imgCount3 == -1) imgCount3 = safeLoadImage("3.jpg");

	imgCount2 = safeLoadImage("2.png");
	if (imgCount2 == -1) imgCount2 = safeLoadImage("2.jpg");

	imgCount1 = safeLoadImage("1.png");
	if (imgCount1 == -1) imgCount1 = safeLoadImage("1.jpg");

	imgCountPlay = safeLoadImage("play.png");
	if (imgCountPlay == -1) imgCountPlay = safeLoadImage("play.jpg");

	// 6. Start 60 FPS Physics & Spawner Timers
	iSetTimer(16, updatePhysicsEngine);
	iSetTimer(150, updateFuelAndSpawns);

	iStart();
	return 0;
}