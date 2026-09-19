#ifndef HAZARDS_H
#define HAZARDS_H

#include "Variables.h"
#include "Leaderboard.h"

inline void shootBullet() {
	if (countdownTimer > 0) return;

	for (int b = 0; b < MAX_BULLETS; b++) {
		if (!bullets[b].active) {
			bullets[b].active = true;
			bullets[b].x = player.x + 35.0;
			bullets[b].y = player.y - 4.0;
			bullets[b].vx = 11.0;
			playSoundEffect("shoot");
			break;
		}
	}
}

inline void activateSkyBlast() {
	if (countdownTimer > 0) return;

	if (player.spells > 0 && !shockwave.active) {
		player.spells--;
		shockwave.active = true;
		shockwave.x = player.x;
		shockwave.y = player.y;
		shockwave.radius = 20.0;
		shockwave.maxRadius = 450.0;
		player.isShielded = true;
		player.shieldTimer = 360;
		player.fuel = (player.fuel + 30.0 > 100.0) ? 100.0 : player.fuel + 30.0;
		for (int i = 0; i < MAX_OBSTACLES; i++) {
			if (obstacles[i].active) {
				obstacles[i].active = false;
				score += 50;
			}
		}
		playSoundEffect("spell");
	}
}

// Safe Damage Handling with 3-Lives System (Professor Req)
inline void playerTakeDamage(int reason) {
	if (player.isShielded) return;
	player.lives--;
	playSoundEffect("life_lost");
	if (player.lives > 0) {
		player.isShielded = true;
		player.shieldTimer = 180; // 3 seconds invulnerability
		player.vy = 2.4; // Safe bounce
		sprintf_s(rescueNotificationText, "WARNING! DAMAGE TAKEN! %d LIVES REMAINING!", player.lives);
		rescueNotificationTimer = 90;
	}
	else {
		player.lives = 0;
		gameOverReason = reason;
		updateHighScore(score);
		saveGameProgress();
		playSoundEffect("crash");
		currentState = GAMEOVER;
	}
}

// Sector 3 Enemy Helicopter AI & Combat Logic
inline void defeatEnemyHelicopter() {
	if (!boss.active) return;

	boss.hp = 0;
	boss.active = false;
	for (int p = 0; p < MAX_BOSS_PROJECTILES; p++) boss.projectiles[p].active = false;

	score += 600;
	careerMissionsCompleted++;
	saveGameProgress();
	playSoundEffect("boss_defeat");
	sprintf_s(rescueNotificationText, "ENEMY HELICOPTER DESTROYED! +600 PTS! FLY TO HELIPAD!");
	rescueNotificationTimer = 120;
}

inline void updateBossVillain() {
	if (!boss.active || currentSector != 3) return;

	if (boss.flashTimer > 0) boss.flashTimer--;
	boss.rotorAngle = (boss.rotorAngle + 35) % 360;

	// Enemy helicopter patrols the open Sector 3 skyline.
	boss.x += boss.vx;
	boss.y += boss.vy;

	if (boss.x < cameraX + 360.0) {
		boss.x = cameraX + 360.0;
		boss.vx = 2.4 + (selectedLevelTier * 0.35);
	}
	else if (boss.x > cameraX + SCREEN_WIDTH - 90.0) {
		boss.x = cameraX + SCREEN_WIDTH - 90.0;
		boss.vx = -(2.4 + (selectedLevelTier * 0.35));
	}

	if (boss.y < 280.0) {
		boss.y = 280.0;
		boss.vy = 0.8;
	}
	else if (boss.y > SCREEN_HEIGHT - 120.0) {
		boss.y = SCREEN_HEIGHT - 120.0;
		boss.vy = -0.8;
	}

	// Slowly vary altitude so the enemy does not fly in a perfectly straight line.
	if (boss.shootTimer % 120 == 0) {
		boss.vy += ((rand() % 5) - 2) * 0.12;
		if (boss.vy > 1.0) boss.vy = 1.0;
		if (boss.vy < -1.0) boss.vy = -1.0;
	}

	// Enemy helicopter fires guided projectiles toward the player.
	boss.shootTimer++;
	int fireInterval = 100 - (selectedLevelTier * 15);
	if (fireInterval < 50) fireInterval = 50;

	if (boss.shootTimer >= fireInterval) {
		boss.shootTimer = 0;
		for (int p = 0; p < MAX_BOSS_PROJECTILES; p++) {
			if (!boss.projectiles[p].active) {
				boss.projectiles[p].active = true;
				// The supplied enemy.png faces left, so fire from its nose.
				boss.projectiles[p].x = boss.x - boss.width * 0.42;
				boss.projectiles[p].y = boss.y - 2.0;

				double dx = player.x - boss.projectiles[p].x;
				double dy = player.y - boss.projectiles[p].y;
				double len = sqrt(dx * dx + dy * dy);
				if (len > 0.0) {
					boss.projectiles[p].vx = (dx / len) * 5.0;
					boss.projectiles[p].vy = (dy / len) * 5.0;
				}
				else {
					boss.projectiles[p].vx = -5.0;
					boss.projectiles[p].vy = 0.0;
				}
				playSoundEffect("shoot");
				break;
			}
		}
	}

	// Enemy projectile movement and player collision.
	for (int p = 0; p < MAX_BOSS_PROJECTILES; p++) {
		if (boss.projectiles[p].active) {
			boss.projectiles[p].x += boss.projectiles[p].vx;
			boss.projectiles[p].y += boss.projectiles[p].vy;

			double pDist = sqrt(pow(boss.projectiles[p].x - player.x, 2) + pow(boss.projectiles[p].y - player.y, 2));
			if (pDist < 30.0) {
				boss.projectiles[p].active = false;
				playerTakeDamage(0);
			}

			if (boss.projectiles[p].x < cameraX - 80.0 || boss.projectiles[p].x > cameraX + SCREEN_WIDTH + 80.0 ||
				boss.projectiles[p].y < 0.0 || boss.projectiles[p].y > SCREEN_HEIGHT) {
				boss.projectiles[p].active = false;
			}
		}
	}

	// EMP/Sky Blast can damage the enemy helicopter.
	if (shockwave.active) {
		double sDist = sqrt(pow(boss.x - shockwave.x, 2) + pow(boss.y - shockwave.y, 2));
		if (sDist <= shockwave.radius + 55.0 && boss.flashTimer == 0) {
			boss.hp -= 2;
			boss.flashTimer = 15;
			score += 100;
			playSoundEffect("boss_hit");
			if (boss.hp <= 0) defeatEnemyHelicopter();
		}
	}
}

inline void updateObstaclesAndPickups() {
	if (countdownTimer > 0) return;

	updateBossVillain();

	if (shockwave.active) {
		shockwave.radius += 12.0;
		if (shockwave.radius >= shockwave.maxRadius) {
			shockwave.active = false;
		}
	}

	if (player.isShielded) {
		player.shieldTimer--;
		if (player.shieldTimer <= 0) {
			player.isShielded = false;
		}
	}

	for (int b = 0; b < MAX_BULLETS; b++) {
		if (bullets[b].active) {
			bullets[b].x += bullets[b].vx;

			// Check bullet hits Boss
			if (boss.active && currentSector == 3) {
				double bDist = sqrt(pow(bullets[b].x - boss.x, 2) + pow(bullets[b].y - boss.y, 2));
				if (bDist < 72.0) {
					bullets[b].active = false;
					boss.hp--;
					boss.flashTimer = 12;
					score += 40;
					playSoundEffect("boss_hit");
					if (boss.hp <= 0) {
						defeatEnemyHelicopter();
					}
					continue;
				}
			}

			for (int i = 0; i < MAX_OBSTACLES; i++) {
				if (obstacles[i].active) {
					double dist = sqrt(pow(bullets[b].x - obstacles[i].x, 2) + pow(bullets[b].y - obstacles[i].y, 2));
					if (dist < 26.0) {
						obstacles[i].active = false;
						bullets[b].active = false;
						score += 60;
						playSoundEffect("hit");
						sprintf_s(rescueNotificationText, "+60 PTS! HAZARD DESTROYED!");
						rescueNotificationTimer = 65;
						break;
					}
				}
			}

			if (bullets[b].x > cameraX + SCREEN_WIDTH + 100.0) bullets[b].active = false;
		}
	}

	for (int i = 0; i < MAX_OBSTACLES; i++) {
		if (obstacles[i].active) {
			obstacles[i].x += obstacles[i].vx;
			obstacles[i].y += obstacles[i].vy;
			obstacles[i].param += 0.05;
			if (obstacles[i].type == OBS_BIRD) {
				obstacles[i].y += sin(obstacles[i].param) * 1.2;
			}
			if (shockwave.active) {
				double sDist = sqrt(pow(obstacles[i].x - shockwave.x, 2) + pow(obstacles[i].y - shockwave.y, 2));
				if (sDist <= shockwave.radius) {
					obstacles[i].active = false;
					score += 40;
					continue;
				}
			}
			double dist = sqrt(pow(obstacles[i].x - player.x, 2) + pow(obstacles[i].y - player.y, 2));
			if (dist < 26.0) {
				if (player.isShielded) {
					obstacles[i].active = false;
					score += 30;
				}
				else {
					obstacles[i].active = false;
					playerTakeDamage(0);
					if (currentState == GAMEOVER) return;
				}
			}
			if (obstacles[i].x < cameraX - 100.0 || obstacles[i].x > cameraX + SCREEN_WIDTH + 120.0 || obstacles[i].y < -40.0) {
				obstacles[i].active = false;
			}
		}
	}

	for (int f = 0; f < 3; f++) {
		if (fuelPickups[f].active) {
			fuelPickups[f].y -= fuelPickups[f].vy;
			double fDist = sqrt(pow(fuelPickups[f].x - player.x, 2) + pow(fuelPickups[f].y - player.y, 2));
			if (fDist < 42.0) {
				player.fuel = (player.fuel + 40.0 > 100.0) ? 100.0 : player.fuel + 40.0;
				fuelPickups[f].active = false;
				playSoundEffect("refuel");
			}
			if (fuelPickups[f].y < 40) fuelPickups[f].active = false;
		}
	}
	for (int s = 0; s < 2; s++) {
		if (spellPickups[s].active) {
			spellPickups[s].y -= spellPickups[s].vy;
			spellPickups[s].pulse += 0.1;
			double sDist = sqrt(pow(spellPickups[s].x - player.x, 2) + pow(spellPickups[s].y - player.y, 2));
			if (sDist < 42.0) {
				player.spells++;
				spellPickups[s].active = false;
				playSoundEffect("refuel");
			}
			if (spellPickups[s].y < 40) spellPickups[s].active = false;
		}
	}
}

inline void updateHazardSpawns() {
	if (countdownTimer > 0) return;

	double speedMult = 1.0 + (selectedLevelTier - 1) * 0.40;
	int maxActive = selectedLevelTier + (currentSector > 1 ? 1 : 0);
	int currentActive = 0;
	for (int i = 0; i < MAX_OBSTACLES; i++) {
		if (obstacles[i].active) currentActive++;
	}

	if (currentActive < maxActive && rand() % 100 < 35) {
		for (int i = 0; i < MAX_OBSTACLES; i++) {
			if (!obstacles[i].active) {
				obstacles[i].active = true;
				obstacles[i].param = 0;
				obstacles[i].spriteVariant = rand() % 2;

				if (currentSector == 1) {
					obstacles[i].type = OBS_BIRD;
					obstacles[i].x = cameraX + SCREEN_WIDTH + 25.0;
					obstacles[i].y = 170 + (rand() % 280);
					obstacles[i].vx = -(1.5 + ((rand() % 5) / 10.0)) * speedMult;
					obstacles[i].vy = 0;
					obstacles[i].width = 22;
				}
				else if (currentSector == 2) {
					if (rand() % 2 == 0) {
						obstacles[i].type = OBS_ROCK;
						obstacles[i].x = cameraX + 150.0 + (rand() % (SCREEN_WIDTH - 250));
						obstacles[i].y = SCREEN_HEIGHT + 15;
						obstacles[i].vx = -(0.6 + ((rand() % 5) / 10.0)) * speedMult;
						obstacles[i].vy = -(2.0 + ((rand() % 7) / 10.0)) * speedMult;
						obstacles[i].width = 24;
					}
					else {
						obstacles[i].type = OBS_BIRD;
						obstacles[i].x = cameraX + SCREEN_WIDTH + 25.0;
						obstacles[i].y = 150 + (rand() % 290);
						obstacles[i].vx = -(1.8 + ((rand() % 5) / 10.0)) * speedMult;
						obstacles[i].vy = 0;
						obstacles[i].width = 22;
					}
				}
				else {
					if (rand() % 2 == 0) {
						obstacles[i].type = OBS_DRONE;
						obstacles[i].x = cameraX + SCREEN_WIDTH + 25.0;
						obstacles[i].y = 160 + (rand() % 290);
						obstacles[i].vx = -(2.2 + ((rand() % 7) / 10.0)) * speedMult;
						obstacles[i].vy = 0;
						obstacles[i].width = 26;
					}
					else {
						obstacles[i].type = OBS_LIGHTNING;
						obstacles[i].x = cameraX + 180.0 + (rand() % (SCREEN_WIDTH - 280));
						obstacles[i].y = SCREEN_HEIGHT - 90;
						obstacles[i].vx = -0.8 * speedMult;
						obstacles[i].vy = 0;
						obstacles[i].width = 30;
					}
				}
				break;
			}
		}
	}

	int activeFuel = 0;
	for (int f = 0; f < 3; f++) if (fuelPickups[f].active) activeFuel++;

	if (activeFuel == 0 && (player.fuel < 70.0 || (rand() % 100 < 2))) {
		for (int f = 0; f < 3; f++) {
			if (!fuelPickups[f].active) {
				fuelPickups[f].active = true;
				fuelPickups[f].x = cameraX + 180.0 + (rand() % (SCREEN_WIDTH - 320));
				fuelPickups[f].y = SCREEN_HEIGHT - 45;
				fuelPickups[f].vy = 1.1;
				fuelPickups[f].hasParachute = true;
				fuelPickups[f].spriteVariant = rand() % 2;
				break;
			}
		}
	}

	int activeSpells = 0;
	for (int s = 0; s < 2; s++) if (spellPickups[s].active) activeSpells++;

	if (activeSpells == 0 && player.spells <= 1 && (rand() % 100 < 1)) {
		for (int s = 0; s < 2; s++) {
			if (!spellPickups[s].active) {
				spellPickups[s].active = true;
				spellPickups[s].x = cameraX + 200.0 + (rand() % (SCREEN_WIDTH - 350));
				spellPickups[s].y = SCREEN_HEIGHT - 55;
				spellPickups[s].vy = 0.9;
				spellPickups[s].pulse = 0;
				spellPickups[s].spriteVariant = rand() % 2;
				break;
			}
		}
	}

	if (currentSector == 3 && rand() % 100 < (selectedLevelTier * 5)) {
		lightningFlash = 3;
	}
	else if (lightningFlash > 0) {
		lightningFlash--;
	}
}

#endif 