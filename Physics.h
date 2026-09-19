#ifndef PHYSICS_H
#define PHYSICS_H

#include "Variables.h"
#include "Leaderboard.h"
#include "Rescue.h"
#include "Hazards.h"

inline void resetHelicopter() {
	player.x = HELIPAD_X + 75.0;
	player.y = HELIPAD_Y + 44.0;
	player.targetX = player.x;
	player.vx = 0.0;
	player.vy = 0.0;
	player.tilt = 0.0;
	player.passengers = 0;
	player.fuel = 100.0;
	player.lives = 3;
	player.spells = 1;
	player.medkits = 3;
	player.isShielded = false;
	player.shieldTimer = 0;
	player.rotorAngle = 0;
	player.tailRotorAngle = 0;
	player.winchActive = false;
	player.winchLen = 0.0;
	player.cableAngle = 0.0;
	player.cableAngularVel = 0.0;
	player.blinkCounter = 0;
	isLifting = false;
	isWinchLowering = false;
	cameraX = 0.0;
}

inline void initSector(int sectorNum) {
	currentSector = sectorNum;
	sectorRescued = 0;
	countdownTimer = 180; // 3 Seconds Pre-flight Launch Timer
	resetHelicopter();

	for (int i = 0; i < MAX_OBSTACLES; i++) obstacles[i].active = false;
	for (int i = 0; i < 3; i++) fuelPickups[i].active = false;
	for (int i = 0; i < 2; i++) spellPickups[i].active = false;
	for (int m = 0; m < MAX_MEDKITS; m++) medkitDrops[m].active = false;
	for (int b = 0; b < MAX_BULLETS; b++) bullets[b].active = false;
	shockwave.active = false;

	// Initialize Sector 3 Enemy Helicopter
	if (sectorNum == 3) {
		boss.active = true;
		boss.hp = 18 + selectedLevelTier * 5;
		boss.maxHp = boss.hp;
		boss.x = 1320.0;
		boss.y = 430.0;
		boss.vx = -2.0;
		boss.vy = 0.55;
		boss.width = 150.0;
		boss.height = 62.0;
		boss.shootTimer = 0;
		boss.flashTimer = 0;
		boss.rotorAngle = 0;
		for (int p = 0; p < MAX_BOSS_PROJECTILES; p++) boss.projectiles[p].active = false;
	}
	else {
		boss.active = false;
		for (int p = 0; p < MAX_BOSS_PROJECTILES; p++) boss.projectiles[p].active = false;
	}

	
	double bX[7] = { 320.0, 580.0, 860.0, 1160.0, 1450.0, 1750.0, 2020.0 };
	double bW[7] = { 85.0, 95.0, 80.0, 100.0, 85.0, 90.0, 85.0 };
	double bH_sec1[7] = { 160.0, 130.0, 190.0, 145.0, 175.0, 135.0, 165.0 };
	double bH_sec2[7] = { 180.0, 140.0, 210.0, 160.0, 195.0, 145.0, 175.0 };
	double bH_sec3[7] = { 145.0, 165.0, 135.0, 175.0, 150.0, 180.0, 155.0 };

	for (int i = 0; i < MAX_BUILDINGS; i++) {
		cityBuildings[i].x = bX[i];
		cityBuildings[i].width = bW[i];
		if (sectorNum == 1) cityBuildings[i].height = bH_sec1[i];
		else if (sectorNum == 2) cityBuildings[i].height = bH_sec2[i];
		else cityBuildings[i].height = bH_sec3[i];
		cityBuildings[i].platformType = i % 3;
		cityBuildings[i].rescuesFromThisBuilding = 0;
	}

	for (int i = 0; i < MAX_SURVIVORS; i++) {
		spawnSurvivor(i);
	}

	for (int r = 0; r < MAX_RAINDROPS; r++) {
		raindrops[r].x = (double)(rand() % (SCREEN_WIDTH + 200));
		raindrops[r].y = (double)(rand() % (SCREEN_HEIGHT - 60));
		raindrops[r].speed = 5.0 + (rand() % 5);
		raindrops[r].length = 10.0 + (rand() % 8);
		raindrops[r].slant = -3.5 - ((rand() % 20) / 10.0);
	}

	for (int w = 0; w < MAX_WIND_PARTICLES; w++) {
		windParticles[w].x = (double)(rand() % SCREEN_WIDTH);
		windParticles[w].y = (double)(rand() % (SCREEN_HEIGHT - 70));
		windParticles[w].vx = -(1.5 + ((rand() % 20) / 10.0));
		windParticles[w].vy = -((rand() % 10) / 10.0);
		windParticles[w].size = 2.0 + (rand() % 4);
		windParticles[w].type = (w % 3);
	}
}

inline void startNewGame() {
	score = 0;
	isLifting = false;
	isWinchLowering = false;
	initSector(targetSectorToPlay);
	currentState = GAMEPLAY;
}

inline void updatePhysicsEngine() {
	player.blinkCounter++;
	waterWavePhase += 0.05;

	
	distantBirdX -= 0.7;
	if (distantBirdX < -120.0) distantBirdX = SCREEN_WIDTH + 100.0;
	cloudDriftX += 0.25;
	if (cloudDriftX > SCREEN_WIDTH) cloudDriftX = 0.0;

	if (rescueNotificationTimer > 0) {
		rescueNotificationTimer--;
	}

	
	for (int r = 0; r < MAX_RAINDROPS; r++) {
		raindrops[r].y -= raindrops[r].speed;
		raindrops[r].x += raindrops[r].slant;
		if (raindrops[r].y < 0 || raindrops[r].x < -50) {
			raindrops[r].y = SCREEN_HEIGHT - 52.0;
			raindrops[r].x = (double)(rand() % (SCREEN_WIDTH + 150));
		}
	}

	for (int w = 0; w < MAX_WIND_PARTICLES; w++) {
		windParticles[w].x += windParticles[w].vx;
		windParticles[w].y += windParticles[w].vy;
		if (windParticles[w].x < -30 || windParticles[w].y < 35) {
			windParticles[w].x = SCREEN_WIDTH + (rand() % 60);
			windParticles[w].y = 50.0 + (rand() % (SCREEN_HEIGHT - 120));
		}
	}

	if (currentState != GAMEPLAY && currentState != PAUSED) return;

	static bool escGameHeld = false;
	if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) || (keyPressed[27] != 0)) {
		if (!escGameHeld) {
			currentState = MENU;
			isLifting = false;
			escGameHeld = true;
		}
	}
	else { escGameHeld = false; }

	// 2. Pause toggle
	static bool pKeyHeld = false;
	bool pPressed = (GetAsyncKeyState('P') & 0x8000) != 0 || (keyPressed['p'] != 0) || (keyPressed['P'] != 0);
	if (pPressed) {
		if (!pKeyHeld) {
			if (currentState == GAMEPLAY) currentState = PAUSED;
			else if (currentState == PAUSED) currentState = GAMEPLAY;
			pKeyHeld = true;
		}
	}
	else { pKeyHeld = false; }

	if (currentState == PAUSED) return;

	// Manual [Q] Key Winch Lowering
	isWinchLowering = (GetAsyncKeyState('Q') & 0x8000) != 0 || (keyPressed['q'] != 0) || (keyPressed['Q'] != 0);

	// In-Flight Hotkeys (Debounced)
	static bool sKeyHeld = false;
	bool sDown = (GetAsyncKeyState('S') & 0x8000) != 0 || (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0 || (keyPressed['s'] != 0) || (keyPressed['S'] != 0);
	if (sDown) {
		if (!sKeyHeld) {
			dropMedkit();
			sKeyHeld = true;
		}
	}
	else { sKeyHeld = false; }

	static bool fKeyHeld = false;
	bool fDown = (GetAsyncKeyState('F') & 0x8000) != 0 || (GetAsyncKeyState('X') & 0x8000) != 0 || (keyPressed['f'] != 0) || (keyPressed['F'] != 0) || (keyPressed['x'] != 0) || (keyPressed['X'] != 0);
	if (fDown) {
		if (!fKeyHeld) {
			shootBullet();
			fKeyHeld = true;
		}
	}
	else { fKeyHeld = false; }

	static bool eKeyHeld = false;
	bool eDown = (GetAsyncKeyState('E') & 0x8000) != 0 || (keyPressed['e'] != 0) || (keyPressed['E'] != 0);
	if (eDown) {
		if (!eKeyHeld) {
			activateSkyBlast();
			eKeyHeld = true;
		}
	}
	else { eKeyHeld = false; }

	// Spin Rotors
	player.rotorAngle = (player.rotorAngle + 30) % 360;
	player.tailRotorAngle = (player.tailRotorAngle + 45) % 360;

	// Handle 3-2-1 Countdown (Helicopter stays parked safely on helipad)
	if (countdownTimer > 0) {
		countdownTimer--;
		if (countdownTimer == 179 || countdownTimer == 119 || countdownTimer == 59) playSoundEffect("countdown");
		else if (countdownTimer == 1) playSoundEffect("go");
		player.y = HELIPAD_Y + 44.0;
		player.vy = 0.0;
		player.vx = 0.0;
		player.tilt = 0.0;
		player.targetX = player.x;
		return;
	}

	// 3. Helicopter Lift & Altitude Physics
	bool keyLift = (GetAsyncKeyState(VK_SPACE) & 0x8000) ||
		(GetAsyncKeyState('W') & 0x8000) ||
		(GetAsyncKeyState(VK_UP) & 0x8000) ||
		(keyPressed[' '] != 0) ||
		(keyPressed['w'] != 0) ||
		(keyPressed['W'] != 0);

	double gravity = 0.20;
	if (keyLift || isLifting) {
		player.vy += 0.44;
		if (player.vy > 4.6) player.vy = 4.6;
	}
	else {
		player.vy -= gravity;
		if (player.vy < -4.2) player.vy = -4.2;
	}
	player.y += player.vy;

	// 4. Smooth, Responsive Horizontal Steering with Aerodynamic Damping
	bool moveLeft = (GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000) || (keyPressed['a'] != 0) || (keyPressed['A'] != 0);
	bool moveRight = (GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000) || (keyPressed['d'] != 0) || (keyPressed['D'] != 0);

	if (moveLeft && !moveRight) {
		player.vx -= 0.38;
		if (player.vx < -5.5) player.vx = -5.5;
	}
	else if (moveRight && !moveLeft) {
		player.vx += 0.38;
		if (player.vx > 5.5) player.vx = 5.5;
	}
	else {
		// Natural aerodynamic air resistance gently coasts to stop
		player.vx *= 0.90;
		if (fabs(player.vx) < 0.04) player.vx = 0.0;
	}

	player.x += player.vx;
	player.targetX = player.x;

	// Natural flight banking tilt proportional to horizontal speed
	player.tilt = (player.vx * 2.5);
	if (player.tilt > 15.0) player.tilt = 15.0;
	if (player.tilt < -15.0) player.tilt = -15.0;

	// World horizontal & ceiling boundaries
	if (player.x < 45.0) { player.x = 45.0; player.vx = 0.0; }
	if (player.x > WORLD_WIDTH - 45.0) { player.x = WORLD_WIDTH - 45.0; player.vx = 0.0; }
	if (player.y > SCREEN_HEIGHT - 65.0) {
		player.y = SCREEN_HEIGHT - 65.0;
		player.vy = 0.0;
	}

	// 5. Dynamic Camera Tracking across the 2200px Cityscape
	double targetCamX = player.x - 350.0;
	if (targetCamX < 0.0) targetCamX = 0.0;
	if (targetCamX > WORLD_WIDTH - SCREEN_WIDTH) targetCamX = WORLD_WIDTH - SCREEN_WIDTH;
	cameraX += (targetCamX - cameraX) * 0.14;

	// 6. Dynamic Pendulum Rope Physics (Swings with velocity, tilt & wind)
	double cableTargetAngle = -(player.vx * 0.07) + (player.tilt * 0.015) + sin(player.blinkCounter * 0.08) * 0.05;
	double springForce = (cableTargetAngle - player.cableAngle) * 0.18;
	player.cableAngularVel += springForce;
	player.cableAngularVel *= 0.88; // Damping
	player.cableAngle += player.cableAngularVel;
	if (player.cableAngle > 0.60) player.cableAngle = 0.60;
	if (player.cableAngle < -0.60) player.cableAngle = -0.60;

	// Synchronized Bird Flock Motion
	flockX += 2.0;
	flockY = 460.0 + sin(player.blinkCounter * 0.035) * 20.0;
	if (flockX > WORLD_WIDTH + 200.0) flockX = -200.0;

	// 7. Building Collision & Terrain Handling (Scaled 76x44 hitbox)
	for (int b = 0; b < MAX_BUILDINGS; b++) {
		double bLeft = cityBuildings[b].x - cityBuildings[b].width / 2.0;
		double bRight = cityBuildings[b].x + cityBuildings[b].width / 2.0;
		double bTop = cityBuildings[b].height;

		if (player.x + 20.0 > bLeft && player.x - 20.0 < bRight && player.y - 12.0 < bTop) {
			player.y = bTop + 20.0;
			player.vy = 2.4;
			playerTakeDamage(0);
			if (currentState == GAMEOVER) return;
		}
	}

	// 8. Ground Collision & Safe Helipad Landing
	if (player.y < 50.0) {
		if (player.x >= HELIPAD_X - 15.0 && player.x <= HELIPAD_X + HELIPAD_W + 15.0) {
			player.y = HELIPAD_Y + 44.0;
			player.vy = 0.0;
		}
		else {
			player.y = 54.0;
			player.vy = 2.4;
			playerTakeDamage(0);
			if (currentState == GAMEOVER) return;
		}
	}

	// 9. Update Game Entities
	updateHelipadOffload();
	updateRescueMechanics();
	updateObstaclesAndPickups();
}

// Faster, Engaging Fuel Depletion Ticker
inline void updateFuelAndSpawns() {
	if (currentState != GAMEPLAY || countdownTimer > 0) return;

	// Fuel drain (~55-70 seconds per tank)
	double drain = 0.16 + (selectedLevelTier * 0.05);
	if (isLifting || (GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState('W') & 0x8000)) drain += 0.08;
	player.fuel -= drain;

	if (player.fuel <= 0) {
		player.fuel = 0;
		gameOverReason = 1;
		updateHighScore(score);
		saveGameProgress();
		playSoundEffect("crash");
		currentState = GAMEOVER;
		return;
	}

	updateHazardSpawns();
}

#endif // PHYSICS_H