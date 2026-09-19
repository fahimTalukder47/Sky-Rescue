#ifndef RESCUE_H
#define RESCUE_H

#include "Variables.h"
#include "Leaderboard.h"

inline void spawnSurvivor(int index) {
	if (index < 0 || index >= MAX_SURVIVORS) return;

	int targetBuilding = -1;
	int minOccupancy = 99;

	int startB = rand() % MAX_BUILDINGS;
	for (int step = 0; step < MAX_BUILDINGS; step++) {
		int b = (startB + step) % MAX_BUILDINGS;
		int countOnB = 0;
		for (int s = 0; s < MAX_SURVIVORS; s++) {
			if (s != index && survivors[s].active && survivors[s].state == 0 && survivors[s].buildingIndex == b) {
				countOnB++;
			}
		}
		if (countOnB < minOccupancy) {
			minOccupancy = countOnB;
			targetBuilding = b;
			if (minOccupancy == 0) break; 
		}
	}
	if (targetBuilding < 0) targetBuilding = rand() % MAX_BUILDINGS;

	double roofOffset = 0.0;
	int existingOnThisBuilding = 0;
	double otherOffset = 0.0;
	for (int s = 0; s < MAX_SURVIVORS; s++) {
		if (s != index && survivors[s].active && survivors[s].state == 0 && survivors[s].buildingIndex == targetBuilding) {
			existingOnThisBuilding++;
			otherOffset = survivors[s].x - cityBuildings[targetBuilding].x;
		}
	}

	if (existingOnThisBuilding == 0) {
		
		int rPos = (rand() % 3) - 1; // -1, 0, +1
		roofOffset = rPos * 20.0;
	}
	else {
		// Place on the opposite side of existing citizen
		if (otherOffset <= 0.0) roofOffset = 22.0;
		else roofOffset = -22.0;
	}

	survivors[index].active = true;
	survivors[index].state = 0;
	survivors[index].hasReceivedAid = false;
	survivors[index].waveAngle = rand() % 360;
	survivors[index].spriteVariant = rand() % 4; // Randomized from all 4 people sprites
	survivors[index].shoutVariant = rand() % 4;  // Varied distress messages
	survivors[index].buildingIndex = targetBuilding;
	survivors[index].walkOffset = roofOffset;
	survivors[index].walkSpeed = (rand() % 2 == 0) ? 0.35 : -0.35;

	survivors[index].x = cityBuildings[targetBuilding].x + roofOffset;
	survivors[index].y = cityBuildings[targetBuilding].height;
	survivors[index].baseHeight = cityBuildings[targetBuilding].height;
	survivors[index].baseWidth = cityBuildings[targetBuilding].width;
	survivors[index].platformType = cityBuildings[targetBuilding].platformType;
	survivors[index].originalY = cityBuildings[targetBuilding].height;
}

inline void dropMedkit() {
	if (countdownTimer > 0) return;
	if (player.medkits <= 0) return;

	for (int m = 0; m < MAX_MEDKITS; m++) {
		if (!medkitDrops[m].active) {
			medkitDrops[m].active = true;
			medkitDrops[m].x = player.x + 3.0;
			medkitDrops[m].y = player.y - 18.0;
			medkitDrops[m].vy = 2.4;
			medkitDrops[m].spriteVariant = rand() % 2;
			player.medkits--;
			playSoundEffect("pickup");
			break;
		}
	}
}

inline void updateRescueMechanics() {
	if (countdownTimer > 0) return;

	bool loweringKey = isWinchLowering || ((GetAsyncKeyState('Q') & 0x8000) != 0);
	int hoistingIndex = -1;

	// Check if any survivor is currently being hoisted
	for (int i = 0; i < MAX_SURVIVORS; i++) {
		if (survivors[i].active && survivors[i].state == 1) {
			hoistingIndex = i;
			break;
		}
	}

	if (hoistingIndex >= 0) {
		// --- PHASE 2: AUTOMATIC REEL-IN HOISTING ---
		player.winchActive = true;
		player.winchLen -= 4.8;
		if (player.winchLen < 0.0) player.winchLen = 0.0;

		double hookX = player.x + 3.0 + sin(player.cableAngle) * player.winchLen;
		double hookY = player.y - 16.0 - cos(player.cableAngle) * player.winchLen;

		// Survivor hangs directly below the C-hook while climbing
		survivors[hoistingIndex].x = hookX;
		survivors[hoistingIndex].y = hookY - 20.0;
		survivors[hoistingIndex].climbCycle = (survivors[hoistingIndex].climbCycle + 1) % 360;

		if (player.winchLen <= 4.0 || survivors[hoistingIndex].y >= player.y - 26.0) {
			player.passengers++;
			int rescuedB = survivors[hoistingIndex].buildingIndex;
			cityBuildings[rescuedB].rescuesFromThisBuilding++;

			// DYNAMIC BUILDING EVOLUTION: After 3 rescues from this building, regenerate new structure!
			if (cityBuildings[rescuedB].rescuesFromThisBuilding >= 3) {
				cityBuildings[rescuedB].rescuesFromThisBuilding = 0;
				if (currentSector == 1) cityBuildings[rescuedB].height = 115.0 + (rand() % 80);
				else if (currentSector == 2) cityBuildings[rescuedB].height = 135.0 + (rand() % 90);
				else cityBuildings[rescuedB].height = 130.0 + (rand() % 55);

				cityBuildings[rescuedB].width = 75.0 + (rand() % 28);
				cityBuildings[rescuedB].platformType = (cityBuildings[rescuedB].platformType + 1 + (rand() % 2)) % 3;

				// Adjust any waiting survivors on this building to the new rooftop
				for (int s = 0; s < MAX_SURVIVORS; s++) {
					if (survivors[s].active && survivors[s].state == 0 && survivors[s].buildingIndex == rescuedB) {
						survivors[s].y = cityBuildings[rescuedB].height;
						survivors[s].baseHeight = cityBuildings[rescuedB].height;
						survivors[s].baseWidth = cityBuildings[rescuedB].width;
					}
				}
			}

			survivors[hoistingIndex].active = false;
			survivors[hoistingIndex].state = 0;
			player.winchLen = 0.0;
			player.winchActive = false;
			playSoundEffect("pickup");
			sprintf_s(rescueNotificationText, "RESCUED SURVIVOR (%d/3)! FLY TO HELIPAD (LEFT)!", player.passengers);
			rescueNotificationTimer = 85;
			spawnSurvivor(hoistingIndex);
		}
	}
	else {
		// --- PHASE 1: WINCH EXTENSION & SURVIVOR HOOKING ---
		if (loweringKey) {
			player.winchActive = true;
			if (player.winchLen < 290.0) {
				player.winchLen += 7.0;
				if ((player.blinkCounter % 8) == 0) playSoundEffect("winch");
			}

			double hookX = player.x + 3.0 + sin(player.cableAngle) * player.winchLen;
			double hookY = player.y - 16.0 - cos(player.cableAngle) * player.winchLen;

			// Check if C-hook catches any rooftop survivor
			if (player.passengers < MAX_PASSENGERS) {
				for (int i = 0; i < MAX_SURVIVORS; i++) {
					if (survivors[i].active && survivors[i].state == 0) {
						double sTargetX = survivors[i].x;
						double sTargetY = survivors[i].y + 20.0; // survivor torso/hands
						if (fabs(hookX - sTargetX) < 32.0 && fabs(hookY - sTargetY) < 22.0) {
							survivors[i].state = 1; // Hooked!
							playSoundEffect("pickup");
							sprintf_s(rescueNotificationText, "SURVIVOR HOOKED! REELING UP...");
							rescueNotificationTimer = 60;
							break;
						}
					}
				}
			}
		}
		else {
			// Retract cable if [Q] is released and no one is hooked
			if (player.winchLen > 0.0) {
				player.winchLen -= 10.0;
				if (player.winchLen <= 0.0) {
					player.winchLen = 0.0;
					player.winchActive = false;
				}
			}
		}
	}

	// Dynamic rooftop pacing & waving animation for waiting survivors
	for (int i = 0; i < MAX_SURVIVORS; i++) {
		if (survivors[i].active && survivors[i].state == 0) {
			survivors[i].waveAngle = (survivors[i].waveAngle + 10) % 360;

			int bIdx = survivors[i].buildingIndex;
			if (bIdx >= 0 && bIdx < MAX_BUILDINGS) {
				double maxOffset = (cityBuildings[bIdx].width / 2.0) - 16.0;
				survivors[i].walkOffset += survivors[i].walkSpeed;
				if (survivors[i].walkOffset > maxOffset) {
					survivors[i].walkOffset = maxOffset;
					survivors[i].walkSpeed = -fabs(survivors[i].walkSpeed);
				}
				else if (survivors[i].walkOffset < -maxOffset) {
					survivors[i].walkOffset = -maxOffset;
					survivors[i].walkSpeed = fabs(survivors[i].walkSpeed);
				}
				survivors[i].x = cityBuildings[bIdx].x + survivors[i].walkOffset;
				survivors[i].y = cityBuildings[bIdx].height;
			}
		}
	}

	// Medical Aid Supply Drops
	for (int m = 0; m < MAX_MEDKITS; m++) {
		if (medkitDrops[m].active) {
			medkitDrops[m].y -= medkitDrops[m].vy;

			for (int s = 0; s < MAX_SURVIVORS; s++) {
				if (survivors[s].active && !survivors[s].hasReceivedAid) {
					double dist = sqrt(pow(medkitDrops[m].x - survivors[s].x, 2) + pow(medkitDrops[m].y - (survivors[s].y + 15), 2));
					if (dist < 45.0) {
						survivors[s].hasReceivedAid = true;
						int aB = survivors[s].buildingIndex;
						cityBuildings[aB].rescuesFromThisBuilding++;

						if (cityBuildings[aB].rescuesFromThisBuilding >= 3) {
							cityBuildings[aB].rescuesFromThisBuilding = 0;
							if (currentSector == 1) cityBuildings[aB].height = 115.0 + (rand() % 80);
							else if (currentSector == 2) cityBuildings[aB].height = 135.0 + (rand() % 90);
							else cityBuildings[aB].height = 130.0 + (rand() % 55);
							cityBuildings[aB].width = 75.0 + (rand() % 28);
							cityBuildings[aB].platformType = (cityBuildings[aB].platformType + 1 + (rand() % 2)) % 3;
						}

						medkitDrops[m].active = false;
						score += 150;
						sectorRescued += 1;
						playSoundEffect("medkit");
						sprintf_s(rescueNotificationText, "+150 PTS! FIRST AID MEDKIT DELIVERED!");
						rescueNotificationTimer = 90;

						if (sectorRescued >= targetRescue[selectedLevelTier][currentSector]) {
							if (currentSector < 3) {
								currentState = SECTOR_COMPLETE;
							}
							else if (!boss.active) {
								updateHighScore(score);
								careerMissionsCompleted++;
								saveGameProgress();
								currentState = VICTORY;
							}
							else {
								sprintf_s(rescueNotificationText, "QUOTA MET! DESTROY THE ENEMY HELICOPTER!");
								rescueNotificationTimer = 100;
							}
						}
						break;
					}
				}
			}

			if (medkitDrops[m].y < 35.0) medkitDrops[m].active = false;
		}
	}
}

inline void updateHelipadOffload() {
	if (countdownTimer > 0) return;

	if (player.x >= HELIPAD_X - 10 && player.x <= HELIPAD_X + HELIPAD_W + 20 && player.y <= HELIPAD_Y + 85.0) {
		player.medkits = 3;

		if (player.passengers > 0) {
			int batch = player.passengers;
			int pts = batch * 100 + (batch == MAX_PASSENGERS ? 150 : 0);
			score += pts;
			sectorRescued += batch;
			careerRescues += batch;
			player.passengers = 0;
			playSoundEffect("deposit");
			sprintf_s(rescueNotificationText, "+%d PTS! RESCUED, 100%% REFUELED & RESTOCKED!", pts);
			rescueNotificationTimer = 90;

			player.fuel = 100.0;
			saveGameProgress();

			if (sectorRescued >= targetRescue[selectedLevelTier][currentSector]) {
				if (currentSector < 3) {
					currentState = SECTOR_COMPLETE;
					saveGameProgress();
				}
				else {
					// In Sector 3, defeat Boss for true Victory!
					if (!boss.active) {
						updateHighScore(score);
						careerMissionsCompleted++;
						saveGameProgress();
						currentState = VICTORY;
					}
					else {
						sprintf_s(rescueNotificationText, "QUOTA MET! DESTROY THE ENEMY HELICOPTER!");
						rescueNotificationTimer = 100;
					}
				}
			}
		}
	}
}

#endif // RESCUE_H