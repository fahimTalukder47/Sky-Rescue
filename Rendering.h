#ifndef RENDERING_H
#define RENDERING_H

#include "Variables.h"

inline void drawHelicopter(double hx, double hy, double tilt, int passengers, bool isShielded, double winchLen) {
	
	iSetColor(255, 255, 180);
	double lightStartX = hx + 28.0;
	double lightStartY = hy - 10.0;
	for (int l = 0; l <= 12; l++) {
		double lx = lightStartX + 40.0 + l * 7.0;
		double ly = lightStartY - 80.0 - l * 2.0;
		iLine(lightStartX, lightStartY, lx, ly);
	}

	int heliSprite = -1;
	if (tilt < -2.5 && imgHeliTiltLeft >= 0) {
		heliSprite = imgHeliTiltLeft;
	}
	else if (tilt > 2.5 && imgHeliTiltRight >= 0) {
		heliSprite = imgHeliTiltRight;
	}
	else if (imgHeliNeutral >= 0) {
		heliSprite = imgHeliNeutral;
	}
	else if (imgHelicopter >= 0) {
		heliSprite = imgHelicopter;
	}

	if (heliSprite >= 0) {
		// Scaled 76x44 compact helicopter profile
		drawTransparentImage((int)(hx - 38), (int)(hy - 22), 76, 44, heliSprite);

		double rRad = (player.rotorAngle * 3.14159 / 180.0);
		double span = 46.0;
		double mastY = hy + 10;
		if (heliSprite == imgHeliTiltRight) {
			mastY = hy + 7;
		}
		else if (heliSprite == imgHeliTiltLeft) {
			mastY = hy + 12;
		}

		// Rotor Mast Hub Connector (snug directly on cabin roof, 0 gap)
		iSetColor(35, 40, 50);
		iFilledRectangle(hx - 3, mastY - 4, 6, 5);
		iFilledCircle(hx, mastY, 3);

		// Spinning rotor blades
		iSetColor(220, 220, 225);
		iLine(hx - cos(rRad) * span, mastY - sin(rRad) * 2.5, hx + cos(rRad) * span, mastY + sin(rRad) * 2.5);
		iLine(hx - sin(rRad) * span, mastY + cos(rRad) * 2.5, hx + sin(rRad) * span, mastY - cos(rRad) * 2.5);

		// Warning tips on rotor tips
		iSetColor(220, 30, 30);
		iFilledCircle(hx + cos(rRad) * span, mastY + sin(rRad) * 2.5, 2);
		iFilledCircle(hx - cos(rRad) * span, mastY - sin(rRad) * 2.5, 2);

		if ((player.blinkCounter / 15) % 2 == 0) {
			iSetColor(255, 40, 40);
			iFilledCircle(hx - 36, hy + 8, 3);
			iSetColor(255, 255, 255);
			iFilledCircle(hx - 36, hy + 8, 1);
		}
	}
	else {
		
		iSetColor(50, 55, 60);
		iFilledRectangle(hx - 34, hy - 22, 68, 5); 
		iFilledRectangle(hx + 28, hy - 22, 7, 7);
		iLine(hx - 16, hy - 11, hx - 16, hy - 22);
		iLine(hx + 16, hy - 11, hx + 16, hy - 22);

		iSetColor(200, 35, 35);
		iFilledRectangle(hx - 70, hy - 4, 46, 11);
		iFilledRectangle(hx - 72, hy - 1, 8, 22);

		iSetColor(30, 30, 35);
		double trRad = (player.tailRotorAngle * 3.14159 / 180.0);
		iLine(hx - 72 + cos(trRad) * 11, hy + 16 + sin(trRad) * 11, hx - 72 - cos(trRad) * 11, hy + 16 - sin(trRad) * 11);
		iLine(hx - 72 - sin(trRad) * 11, hy + 16 + cos(trRad) * 11, hx - 72 + sin(trRad) * 11, hy + 16 - cos(trRad) * 11);

		iSetColor(220, 40, 40);
		iFilledCircle(hx - 7, hy, 18);
		iFilledCircle(hx + 13, hy, 18);
		iFilledRectangle(hx - 7, hy - 18, 20, 36);

		iSetColor(255, 255, 255);
		iFilledRectangle(hx - 8, hy - 10, 12, 20);
		iSetColor(220, 40, 40);
		iFilledRectangle(hx - 6, hy - 6, 6, 12);
		iFilledRectangle(hx - 8, hy - 3, 11, 6);

		iSetColor(70, 160, 220);
		iFilledCircle(hx + 20, hy + 3, 11);
		iSetColor(200, 240, 255);
		iLine(hx + 15, hy + 7, hx + 28, hy + 3);

		
		for (int p = 0; p < MAX_PASSENGERS; p++) {
			double winX = hx - 12 + p * 11;
			iSetColor(40, 70, 90);
			iFilledRectangle(winX, hy - 3, 8, 9);
			if (p < passengers) {
				iSetColor(255, 210, 170);
				iFilledCircle(winX + 4.0, hy + 4.0, 3);
				iSetColor(40, 180, 70);
				iFilledRectangle(winX + 1.0, hy - 3.0, 5, 4);
			}
		}
		iSetColor(40, 40, 45);
		iFilledRectangle(hx - 2, hy + 11, 6, 6);
		iFilledCircle(hx + 1, hy + 17, 4);

		iSetColor(25, 25, 30);
		double rRad = (player.rotorAngle * 3.14159 / 180.0);
		double span = 62.0;
		iLine(hx + 1 - cos(rRad) * span, hy + 17 - sin(rRad) * 3.5, hx + 1 + cos(rRad) * span, hy + 17 + sin(rRad) * 3.5);
		iLine(hx + 1 - sin(rRad) * span, hy + 17 + cos(rRad) * 3.5, hx + 1 + sin(rRad) * span, hy + 17 - cos(rRad) * 3.5);
		iSetColor(220, 30, 30);
		iFilledCircle(hx + 1 + cos(rRad) * span, hy + 17 + sin(rRad) * 3.5, 3);
		iFilledCircle(hx + 1 - cos(rRad) * span, hy + 17 - sin(rRad) * 3.5, 3);
	}

	
	if ((player.blinkCounter / 15) % 2 == 0) {
		iSetColor(255, 40, 40);
		iFilledCircle(hx - 40, hy + 15, 4);
		iSetColor(255, 255, 255);
		iFilledCircle(hx - 40, hy + 15, 2);
	}

	if (winchLen > 0) {
		double hookX = hx + 3.0 + sin(player.cableAngle) * winchLen;
		double hookY = hy - 16.0 - cos(player.cableAngle) * winchLen;

		iSetColor(255, 215, 0);
		iLine(hx + 3, hy - 16, hookX, hookY);
		iLine(hx + 2, hy - 16, hookX - 1, hookY);

		
		iSetColor(120, 130, 145);
		iFilledCircle(hookX, hookY + 2, 4);

	
		iSetColor(230, 235, 245);
		double baseAngOffset = player.cableAngle;
		for (int ang = 45; ang <= 315; ang += 15) {
			double angA = (double)ang * 3.14159265 / 180.0 + baseAngOffset;
			double angB = (double)(ang + 15) * 3.14159265 / 180.0 + baseAngOffset;
			double hR = 8.5;
			iLine(hookX + cos(angA) * hR, hookY - 7.0 + sin(angA) * hR, hookX + cos(angB) * hR, hookY - 7.0 + sin(angB) * hR);
			iLine(hookX + cos(angA) * (hR - 1.0), hookY - 7.0 + sin(angA) * (hR - 1.0), hookX + cos(angB) * (hR - 1.0), hookY - 7.0 + sin(angB) * (hR - 1.0));
		}

		
		iSetColor(255, 215, 0);
		iFilledCircle(hookX + cos(baseAngOffset) * 4.0, hookY - 3.0 + sin(baseAngOffset) * 4.0, 3);
		iSetColor(220, 40, 40);
		iLine(hookX + 3.0, hookY - 3.0, hookX - 3.0, hookY - 12.0);
	}

	
	if (isShielded) {
		iSetColor(80, 220, 255);
		iCircle(hx + 3, hy, 46);
		iSetColor(140, 240, 255);
		iCircle(hx + 3, hy, 48 + (player.blinkCounter % 4));
	}
}

inline void drawHospitalHelipad() {
	double hx = HELIPAD_X - cameraX;
	double hy = HELIPAD_Y;

	if (hx + HELIPAD_W < -50.0 || hx > SCREEN_WIDTH + 50.0) return;

	if (imgHelipad >= 0) {
		drawTransparentImage((int)hx, (int)hy - 25, 165, 75, imgHelipad);
	}
	else {
		iSetColor(45, 55, 70);
		iFilledRectangle(hx - 15, 0, HELIPAD_W + 30, hy);
		iSetColor(75, 85, 95);
		iFilledRectangle(hx, hy, HELIPAD_W, HELIPAD_H);
		iSetColor(230, 230, 40);
		for (int s = 0; s < HELIPAD_W; s += 20) {
			iFilledRectangle(hx + s, hy + HELIPAD_H - 4, 10, 4);
		}
		iSetColor(255, 255, 255);
		iCircle(hx + HELIPAD_W / 2, hy + HELIPAD_H / 2, 11);
		iFilledRectangle(hx + HELIPAD_W / 2 - 5, hy + HELIPAD_H / 2 - 6, 3, 12);
		iFilledRectangle(hx + HELIPAD_W / 2 + 2, hy + HELIPAD_H / 2 - 6, 3, 12);
		iFilledRectangle(hx + HELIPAD_W / 2 - 5, hy + HELIPAD_H / 2 - 2, 10, 3);
		iSetColor(255, 255, 255);
		iFilledCircle(hx + HELIPAD_W / 2, 24, 11);
		iSetColor(220, 30, 30);
		iFilledRectangle(hx + HELIPAD_W / 2 - 3, 16, 6, 16);
		iFilledRectangle(hx + HELIPAD_W / 2 - 8, 21, 16, 6);
	}

	if ((player.blinkCounter / 20) % 2 == 0) {
		iSetColor(50, 255, 80);
		iFilledCircle(hx + 8, hy + HELIPAD_H + 4, 4);
		iFilledCircle(hx + HELIPAD_W - 8, hy + HELIPAD_H + 4, 4);
	}
	iSetColor(255, 255, 255);
	drawText(hx + 10, 8, "BASE HELIPAD (SAFE DROP)", GLUT_BITMAP_HELVETICA_10);
}

inline void drawDetailedBuilding(double bx, double by, double bw, double bh, int type) {
	if (type == 0) {
		iSetColor(140, 50, 40);
		iFilledRectangle(bx - bw / 2, 0, bw, bh);
		iSetColor(100, 35, 25);
		iFilledRectangle(bx - bw / 2 - 4, bh - 6, bw + 8, 6); // Rooftop ledge flush with feet
	}
	else if (type == 1) {
		iSetColor(65, 55, 75);
		iFilledRectangle(bx - bw / 2, 0, bw, bh);
		iSetColor(45, 35, 55);
		iFilledRectangle(bx - bw / 2 - 3, bh - 6, bw + 6, 6);
	}
	else {
		iSetColor(50, 60, 75);
		iFilledRectangle(bx - bw / 2, 0, bw, bh);
		iSetColor(35, 45, 55);
		iFilledRectangle(bx - bw / 2 - 4, bh - 6, bw + 8, 6);
	}

	for (double wx = bx - bw / 2 + 8; wx < bx + bw / 2 - 10; wx += 16) {
		for (double wy = 25; wy < bh - 15; wy += 22) {
			iSetColor(20, 25, 35);
			iFilledRectangle(wx - 1, wy - 1, 10, 14);

			int winSeed = (int)(wx * 7 + wy * 13);
			if (winSeed % 3 == 0) iSetColor(255, 220, 110);
			else if (winSeed % 3 == 1) iSetColor(100, 210, 255);
			else iSetColor(40, 50, 65);

			iFilledRectangle(wx, wy, 8, 12);
			iSetColor(20, 25, 35);
			iLine(wx + 4, wy, wx + 4, wy + 12);
			iLine(wx, wy + 6, wx + 8, wy + 6);
		}
	}

	iSetColor(160, 170, 180);
	iLine(bx + bw / 2 - 8, bh, bx + bw / 2 - 8, bh + 22);
	iLine(bx + bw / 2 - 11, bh + 14, bx + bw / 2 - 5, bh + 14);
	if ((player.blinkCounter / 18) % 2 == 0) {
		iSetColor(255, 50, 50);
		iFilledCircle(bx + bw / 2 - 8, bh + 23, 3);
	}
}

inline void drawCityBuildings() {
	for (int b = 0; b < MAX_BUILDINGS; b++) {
		double bx = cityBuildings[b].x - cameraX;
		double bw = cityBuildings[b].width;
		if (bx + bw >= -50.0 && bx - bw <= SCREEN_WIDTH + 50.0) {
			drawDetailedBuilding(bx, 0, bw, cityBuildings[b].height, cityBuildings[b].platformType);
		}
	}
}

inline void drawSynchronizedFlock() {
	double leadX = flockX - cameraX;
	double leadY = flockY;

	double offX[5] = { 0.0, -32.0, -32.0, -64.0, -64.0 };
	double offY[5] = { 0.0, 16.0, -16.0, 32.0, -32.0 };

	for (int k = 0; k < 5; k++) {
		double bx = leadX + offX[k];
		double by = leadY + offY[k];

		if (bx > -50.0 && bx < SCREEN_WIDTH + 50.0) {
		
			double flap = sin(player.blinkCounter * 0.18 + k * 0.35) * 7.0;

			
			iSetColor(240, 245, 255);
			iFilledCircle(bx, by, 3);

			iSetColor(255, 255, 255);
			iLine(bx, by, bx - 10.0, by + flap);
			iLine(bx - 10.0, by + flap, bx - 18.0, by + flap * 0.5);
			iLine(bx, by + 1, bx - 10.0, by + 1 + flap);

			iLine(bx, by, bx + 10.0, by + flap);
			iLine(bx + 10.0, by + flap, bx + 18.0, by + flap * 0.5);
			iLine(bx, by + 1, bx + 10.0, by + 1 + flap);

			iSetColor(40, 45, 55);
			iLine(bx - 18.0, by + flap * 0.5, bx - 22.0, by + flap * 0.2);
			iLine(bx + 18.0, by + flap * 0.5, bx + 22.0, by + flap * 0.2);
		}
	}
}

inline void drawSurvivor(struct Survivor &s) {
	if (!s.active && s.state != 1) return;

	if (s.state == 0) {
	
		double px = s.x - cameraX;
		double py = s.y;

		if (px < -60.0 || px > SCREEN_WIDTH + 60.0) return;

		double heliScreenX = player.x - cameraX;
		double distHeli = fabs(heliScreenX - px);
		bool heliNearby = (distHeli < 140.0 && player.y < 400.0 && player.y > py);

		if (heliNearby) {
			double jumpY = fabs(sin(player.blinkCounter * 0.28)) * 8.0;
			py += jumpY;
		}
		else {
			py += sin((s.waveAngle + s.buildingIndex * 50) * 3.14159 / 180.0) * 1.5;
		}

		if (s.hasReceivedAid) {
			iSetColor(255, 220, 80);
			drawText(px - 14, py + 48, "+AID!", GLUT_BITMAP_HELVETICA_10);
		}

		int var = s.spriteVariant % 4;
		bool isWaving = heliNearby || ((player.blinkCounter / 30) % 2 == 1);
		int chosenSprite = isWaving ? imgPeopleWave[var] : imgPeopleIdle[var];
		if (chosenSprite < 0) chosenSprite = imgPeople[var];

		if (chosenSprite >= 0) {
			int pw = 24;
			int ph = 50;
			drawTransparentImage((int)(px - pw / 2), (int)(py), pw, ph, chosenSprite);

			if (!s.hasReceivedAid && (s.waveAngle / 20) % 2 == 0) {
				const char *msg = "HELP!";
				if (heliNearby) {
					const char *nearShouts[3] = { "LOWER HOOK!", "HERE!", "SAVED!" };
					msg = nearShouts[(player.blinkCounter / 30) % 3];
				}
				else {
					const char *shouts[4] = { "HELP!", "SOS!", "HERE!", "SAVE!" };
					msg = shouts[s.shoutVariant % 4];
				}
				iSetColor(255, 255, 255);
				iFilledRectangle(px - 16, py + 52, 36, 12);
				iSetColor(200, 20, 20);
				drawText(px - 14, py + 54, msg, GLUT_BITMAP_HELVETICA_10);
			}
		}
		else {
			if (s.spriteVariant == 0) iSetColor(230, 45, 45);       
			else if (s.spriteVariant == 1) iSetColor(245, 205, 30); 
			else if (s.spriteVariant == 2) iSetColor(35, 175, 80); 
			else iSetColor(255, 115, 20);                           

			iFilledRectangle(px - 5, py + 9, 10, 14);
			iSetColor(255, 210, 160);
			iFilledCircle(px, py + 26, 5);
			iSetColor(30, 50, 90);
			iFilledRectangle(px - 5, py, 4, 9);
			iFilledRectangle(px + 1, py, 4, 9);
			iSetColor(255, 210, 160);

			double waveOffset = sin(s.waveAngle * 3.14159 / 180.0) * 8.0;
			iLine(px - 5, py + 16, px - 12, py + 24 + waveOffset);
			iLine(px + 5, py + 16, px + 12, py + 24 - waveOffset);

			if (!s.hasReceivedAid && (s.waveAngle / 20) % 2 == 0) {
				const char *msg = heliNearby ? "LOWER HOOK!" : "HELP!";
				iSetColor(255, 255, 255);
				iFilledRectangle(px - 16, py + 34, 36, 12);
				iSetColor(200, 20, 20);
				drawText(px - 14, py + 36, msg, GLUT_BITMAP_HELVETICA_10);
			}
		}

		if (currentSector == 3) {
			iSetColor(255, 50, 30);
			iFilledCircle(px + 14, py + 26, 4);
			iSetColor(255, 220, 80);
			iFilledCircle(px + 14, py + 26, 2);
			if ((player.blinkCounter % 4) == 0) {
				iSetColor(255, 160, 40);
				iFilledCircle(px + 14 + ((rand() % 6) - 3), py + 30 + (rand() % 6), 2);
			}
		}
	}
	else if (s.state == 1) {
		double ropeStartX = (player.x - cameraX) + 3.0;
		double ropeStartY = player.y - 16.0;
		double hookX = ropeStartX + sin(player.cableAngle) * player.winchLen;
		double hookY = ropeStartY - cos(player.cableAngle) * player.winchLen;

		double px = hookX;
		double py = hookY - 20.0;

		iSetColor(50, 255, 120);
		drawText(px - 32, py + 48, "CLIMBING!", GLUT_BITMAP_HELVETICA_10);

		iSetColor(255, 215, 0);
		iLine(hookX, hookY, px, py + 28);

		int var = s.spriteVariant % 4;
		int chosenSprite = (imgPeopleWave[var] >= 0) ? imgPeopleWave[var] : imgPeople[var];

		if (chosenSprite >= 0) {
			int pw = 24;
			int ph = 50;
			
			double climbBob = sin(s.climbCycle * 0.4) * 3.0;
			drawTransparentImage((int)(px - pw / 2), (int)(py + climbBob), pw, ph, chosenSprite);
		}
		else {
			if (s.spriteVariant == 0) iSetColor(230, 45, 45);
			else if (s.spriteVariant == 1) iSetColor(245, 205, 30);
			else if (s.spriteVariant == 2) iSetColor(35, 175, 80);
			else iSetColor(255, 115, 20);

			double climbBob = sin(s.climbCycle * 0.4) * 2.0;
			iFilledRectangle(px - 5, py + 9 + climbBob, 10, 14);

			iSetColor(255, 210, 160);
			iFilledCircle(px, py + 26 + climbBob, 5);

			iSetColor(30, 50, 90);
			double legL = sin(s.climbCycle * 0.4) * 4.0;
			double legR = -sin(s.climbCycle * 0.4) * 4.0;
			iFilledRectangle(px - 5, py + climbBob + legL, 4, 9);
			iFilledRectangle(px + 1, py + climbBob + legR, 4, 9);

			iSetColor(255, 210, 160);
			double handL = sin(s.climbCycle * 0.4) * 7.0;
			double handR = -sin(s.climbCycle * 0.4) * 7.0;
			iLine(px - 5, py + 18 + climbBob, px, py + 28 + handL);
			iLine(px + 5, py + 18 + climbBob, px, py + 28 + handR);
		}
	}
}

inline void drawObstacle(struct Obstacle &obs) {
	if (!obs.active) return;
	double ox = obs.x - cameraX;
	double oy = obs.y;

	if (ox < -60.0 || ox > SCREEN_WIDTH + 60.0) return;

	if (obs.type == OBS_ROCK && imgObstacle1 >= 0) {
		drawTransparentImage((int)(ox - 18), (int)(oy - 18), 36, 36, imgObstacle1);
		return;
	}
	if (obs.type == OBS_DRONE) {
		int eagleCycle[4] = { 0, 1, 2, 1 };
		int fIdx = eagleCycle[abs((int)(obs.param * 3.5)) % 4];
		int eSprite = (obs.vx > 0) ? imgEagleRight[fIdx] : imgEagleLeft[fIdx];

		if (eSprite >= 0) {
			drawTransparentImage((int)(ox - 22), (int)(oy - 20), 44, 40, eSprite);
			return;
		}
		if (imgObstacle2 >= 0) {
			drawTransparentImage((int)(ox - 22), (int)(oy - 20), 44, 40, imgObstacle2);
			return;
		}
	}

	if (obs.type == OBS_BIRD) {
		int birdCycle[4] = { 0, 1, 2, 1 };
		int fIdx = birdCycle[abs((int)(obs.param * 3.5)) % 4];
		int bSprite = (obs.vx > 0) ? imgBirdRight[fIdx] : imgBirdLeft[fIdx];

		if (bSprite >= 0) {
			drawTransparentImage((int)(ox - 19), (int)(oy - 14), 38, 28, bSprite);
			return;
		}

		// Procedural fallback
		iSetColor(40, 40, 45);
		double wingAngle = sin(obs.param) * 8.0;
		iFilledCircle(ox, oy, 5);
		iLine(ox, oy, ox - 14, oy + wingAngle);
		iLine(ox - 14, oy + wingAngle, ox - 22, oy + wingAngle / 2);
		iLine(ox, oy, ox + 14, oy + wingAngle);
		iLine(ox + 11, oy + wingAngle, ox + 22, oy + wingAngle / 2);
		iSetColor(240, 160, 30);
		iLine(ox - 5, oy, ox - 9, oy - 1);
		return;
	}
	else if (obs.type == OBS_ROCK) {
		iSetColor(110, 95, 80);
		iFilledCircle(ox, oy, obs.width / 2);
		iSetColor(65, 55, 45);
		iLine(ox - 4, oy + 3, ox + 4, oy - 3);
		iCircle(ox, oy, obs.width / 2);
	}
	else if (obs.type == OBS_DRONE) {
		iSetColor(45, 50, 60);
		iFilledRectangle(ox - 13, oy - 6, 26, 12);
		iLine(ox - 16, oy + 6, ox + 16, oy - 6);
		iLine(ox - 16, oy - 6, ox + 16, oy + 6);
		iSetColor(180, 180, 190);
		iFilledCircle(ox - 16, oy + 6, 4);
		iFilledCircle(ox + 16, oy + 6, 4);
		iFilledCircle(ox - 16, oy - 6, 4);
		iFilledCircle(ox + 16, oy - 6, 4);
		iSetColor(255, 30, 30);
		iFilledCircle(ox, oy, 4);
		iLine(ox, oy - 6, ox + sin(obs.param) * 16, oy - 45);
	}
	else if (obs.type == OBS_LIGHTNING) {
		int strikeCycle[16] = { 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0 };
		int cIdx = strikeCycle[abs((int)(obs.param * 2.5)) % 16];
		int cSprite = imgCloudLightning[cIdx];

		if (cSprite >= 0) {
			int cw = 64;
			int ch = 110;
			drawTransparentImage((int)(ox - 32), (int)(oy + 15 - ch), cw, ch, cSprite);
			return;
		}

		iSetColor(70, 75, 90);
		iFilledCircle(ox - 11, oy + 8, 15);
		iFilledCircle(ox + 8, oy + 12, 17);
		iFilledCircle(ox + 23, oy + 6, 13);
		iFilledRectangle(ox - 18, oy - 2, 45, 12);
		iSetColor(255, 255, 120);
		iLine(ox + 3, oy, ox - 4, oy - 18);
		iLine(ox - 4, oy - 18, ox + 6, oy - 24);
		iLine(ox + 6, oy - 24, ox - 6, oy - 50);
	}
}

inline void drawMedkitDrop(struct MedkitDrop &m) {
	if (!m.active) return;
	double mx = m.x - cameraX;
	double my = m.y;
	if (mx < -50.0 || mx > SCREEN_WIDTH + 50.0) return;

	int mImg = (m.spriteVariant == 0) ? imgMedi1 : imgMedi2;
	if (mImg >= 0) {
		drawTransparentImage((int)(mx - 16), (int)(my - 16), 32, 32, mImg);
	}
	else {
		iSetColor(245, 245, 245);
		iFilledRectangle(mx - 12, my - 12, 24, 24);
		iSetColor(220, 30, 30);
		iFilledRectangle(mx - 4, my - 10, 8, 20);
		iFilledRectangle(mx - 10, my - 4, 20, 8);
		iSetColor(40, 45, 55);
		iRectangle(mx - 12, my - 12, 24, 24);
	}
}

inline void drawBullet(struct Bullet &b) {
	if (!b.active) return;
	double bx = b.x - cameraX;
	double by = b.y;
	if (bx < -20.0 || bx > SCREEN_WIDTH + 20.0) return;

	iSetColor(255, 220, 50);
	iFilledCircle(bx, by, 4);
	iSetColor(255, 100, 30);
	iLine(bx, by, bx - 16, by);
	iLine(bx, by + 1, bx - 16, by + 1);
	iLine(bx, by - 1, bx - 16, by - 1);
}

inline void drawFuelPickup(struct FuelCan &f) {
	if (!f.active) return;
	double fx = f.x - cameraX;
	double fy = f.y;
	if (fx < -50.0 || fx > SCREEN_WIDTH + 50.0) return;

	int fImg = (f.spriteVariant == 0) ? imgFuel1 : imgFuel2;
	if (fImg >= 0) {
		drawTransparentImage((int)(fx - 18), (int)(fy - 18), 36, 36, fImg);
	}
	else {
		iSetColor(230, 40, 30);
		iFilledRectangle(fx - 12, fy - 16, 24, 32);
		iSetColor(170, 25, 20);
		iFilledRectangle(fx - 9, fy + 16, 7, 5);
		iFilledRectangle(fx - 12, fy + 9, 24, 5);
		iSetColor(255, 255, 255);
		drawText(fx - 9, fy - 5, "GAS", GLUT_BITMAP_HELVETICA_12);
	}
}

inline void drawSpellPickup(struct SpellOrb &sp) {
	if (!sp.active) return;
	double spx = sp.x - cameraX;
	double spy = sp.y;
	if (spx < -50.0 || spx > SCREEN_WIDTH + 50.0) return;

	double pulseR = 15.0 + sin(sp.pulse) * 4.0;

	int pImg = (sp.spriteVariant == 0) ? imgPower1 : imgPower2;
	if (pImg >= 0) {
		iSetColor(80, 200, 255);
		iCircle(spx, spy, pulseR + 5);
		drawTransparentImage((int)(spx - 20), (int)(spy - 20), 40, 40, pImg);
	}
	else {
		iSetColor(80, 200, 255);
		iCircle(spx, spy, pulseR + 4);
		iSetColor(160, 230, 255);
		iFilledCircle(spx, spy, pulseR);
		iSetColor(255, 255, 255);
		iFilledCircle(spx, spy, pulseR * 0.4);
		iLine(spx - pulseR, spy, spx + pulseR, spy);
		iLine(spx, spy - pulseR, spx, spy + pulseR);
		iSetColor(20, 40, 90);
		drawText(spx - 12, spy - 4, "EMP", GLUT_BITMAP_HELVETICA_12);
	}
}

inline void drawShockwave(struct Shockwave &sw) {
	if (!sw.active) return;
	double swx = sw.x - cameraX;
	double swy = sw.y;
	if (swx < -200.0 || swx > SCREEN_WIDTH + 200.0) return;

	double alpha = 1.0 - (sw.radius / sw.maxRadius);
	iSetColor(120 * alpha, 220 * alpha, 255 * alpha);
	iCircle(swx, swy, sw.radius);
	iCircle(swx, swy, sw.radius - 5);
}

inline void drawSunlightShafts() {
	if (currentSector != 1) return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	double pulse = sin(player.blinkCounter * 0.035) * 0.3 + 0.7;

	for (int b = 0; b < 4; b++) {
		double startX = 140.0 + b * 240.0 - (cameraX * 0.15);
		while (startX < -200.0) startX += SCREEN_WIDTH + 300.0;
		while (startX > SCREEN_WIDTH + 100.0) startX -= SCREEN_WIDTH + 300.0;

		double startY = (double)SCREEN_HEIGHT;
		double endX = startX + 170.0 + sin(b + player.blinkCounter * 0.015) * 25.0;
		double endY = 120.0;
		double beamW = 40.0 + b * 12.0;

		for (double w = -beamW; w <= beamW; w += 5.0) {
			double distFrac = 1.0 - (fabs(w) / beamW);
			int alpha = (int)(distFrac * 22.0 * pulse);
			if (alpha <= 0) continue;

			glColor4ub(255, 245, 185, (GLubyte)alpha);
			glBegin(GL_LINES);
			glVertex2f((float)(startX + w * 0.3), (float)startY);
			glVertex2f((float)(endX + w), (float)endY);
			glEnd();
		}
	}
	glDisable(GL_BLEND);
}

inline void drawAnimatedSkyClouds() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	struct CloudLayer {
		double baseOffset;
		double y;
		double width;
		double height;
		double speed;
		int alpha;
	};

	static CloudLayer clouds[5] = {
		{ 60.0, 515.0, 190.0, 52.0, 0.45, 170 },
		{ 360.0, 485.0, 230.0, 60.0, 0.30, 200 },
		{ 650.0, 540.0, 170.0, 46.0, 0.50, 150 },
		{ 890.0, 498.0, 210.0, 55.0, 0.38, 185 },
		{ 1150.0, 525.0, 250.0, 64.0, 0.28, 195 }
	};

	double driftBase = (cloudDriftX * 2.2);

	for (int c = 0; c < 5; c++) {
		double cx = fmod(clouds[c].baseOffset + driftBase * clouds[c].speed - (cameraX * 0.12), SCREEN_WIDTH + 320.0);
		if (cx < -160.0) cx += SCREEN_WIDTH + 320.0;
		cx -= 100.0;
		double cy = clouds[c].y + sin((player.blinkCounter * 0.02) + c) * 3.0;

		double w = clouds[c].width;
		double h = clouds[c].height;

		glColor4ub(205, 225, 245, (GLubyte)(clouds[c].alpha * 0.6));
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((float)cx, (float)(cy - 4.0));
		for (double a = 0; a <= 6.29; a += 0.35) {
			glVertex2f((float)(cx + cos(a) * (w * 0.46)), (float)(cy - 4.0 + sin(a) * (h * 0.36)));
		}
		glEnd();

		glColor4ub(255, 255, 255, (GLubyte)clouds[c].alpha);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((float)cx, (float)cy);
		for (double a = 0; a <= 6.29; a += 0.35) {
			glVertex2f((float)(cx + cos(a) * (w * 0.44)), (float)(cy + sin(a) * (h * 0.40)));
		}
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((float)(cx - w * 0.26), (float)(cy - h * 0.10));
		for (double a = 0; a <= 6.29; a += 0.35) {
			glVertex2f((float)(cx - w * 0.26 + cos(a) * (w * 0.28)), (float)(cy - h * 0.10 + sin(a) * (h * 0.32)));
		}
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((float)(cx + w * 0.26), (float)(cy - h * 0.08));
		for (double a = 0; a <= 6.29; a += 0.35) {
			glVertex2f((float)(cx + w * 0.26 + cos(a) * (w * 0.30)), (float)(cy - h * 0.08 + sin(a) * (h * 0.34)));
		}
		glEnd();

		glColor4ub(255, 255, 255, (GLubyte)(clouds[c].alpha + 40 > 255 ? 255 : clouds[c].alpha + 40));
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f((float)(cx - w * 0.05), (float)(cy + h * 0.15));
		for (double a = 0; a <= 6.29; a += 0.35) {
			glVertex2f((float)(cx - w * 0.05 + cos(a) * (w * 0.26)), (float)(cy + h * 0.15 + sin(a) * (h * 0.28)));
		}
		glEnd();
	}
	glDisable(GL_BLEND);
}

inline void drawDistantSoaringBirds() {

	for (int e = 0; e < 2; e++) {
		double centerCX = (e == 0) ? 280.0 : 760.0;
		double centerCY = (e == 0) ? 515.0 : 475.0;
		double orbitR = 75.0 + e * 35.0;
		double angle = (player.blinkCounter * 0.012) + e * 3.14;

		double ex = centerCX + cos(angle) * orbitR - (cameraX * 0.08);
		while (ex < -50.0) ex += SCREEN_WIDTH + 100.0;
		while (ex > SCREEN_WIDTH + 50.0) ex -= SCREEN_WIDTH + 100.0;

		double ey = centerCY + sin(angle) * (orbitR * 0.35);

		double wingFlex = sin(player.blinkCounter * 0.06 + e) * 2.0;
		double bankSlope = -sin(angle) * 3.0;

		iSetColor(35, 45, 60);
		iFilledCircle(ex, ey, 2.5);
		iLine(ex, ey, ex - 12.0, ey + bankSlope + wingFlex);
		iLine(ex - 12.0, ey + bankSlope + wingFlex, ex - 18.0, ey + bankSlope + wingFlex * 0.5);
		iLine(ex, ey, ex + 12.0, ey - bankSlope + wingFlex);
		iLine(ex + 12.0, ey - bankSlope + wingFlex, ex + 18.0, ey - bankSlope + wingFlex * 0.5);
	}

	double flockBaseX = fmod(player.blinkCounter * 1.8 - cameraX * 0.20, SCREEN_WIDTH + 260.0);
	if (flockBaseX < -60.0) flockBaseX += SCREEN_WIDTH + 260.0;
	flockBaseX -= 50.0;

	double flockBaseY = 445.0 + sin(player.blinkCounter * 0.02) * 12.0;

	double bOffsets[5][2] = {
		{ 0.0, 0.0 },
		{ -22.0, 14.0 },
		{ -24.0, -12.0 },
		{ -45.0, 26.0 },
		{ -48.0, -22.0 }
	};

	for (int k = 0; k < 5; k++) {
		double bx = flockBaseX + bOffsets[k][0];
		double by = flockBaseY + bOffsets[k][1];

		if (bx > -30.0 && bx < SCREEN_WIDTH + 30.0) {
			double flap = sin(player.blinkCounter * 0.22 + k * 0.45) * 5.5;

			iSetColor(45, 55, 70);
			iFilledCircle(bx, by, 2.0);
			iLine(bx, by, bx - 8.0, by + flap);
			iLine(bx - 8.0, by + flap, bx - 14.0, by + flap * 0.5);
			iLine(bx, by + 1, bx - 8.0, by + 1 + flap);
			iLine(bx, by, bx + 8.0, by + flap);
			iLine(bx + 8.0, by + flap, bx + 14.0, by + flap * 0.5);
			iLine(bx, by + 1, bx + 8.0, by + 1 + flap);
		}
	}
}

inline void drawWaterBasinSurfaceWaves() {
	if (currentSector == 3) return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int layer = 0; layer < 4; layer++) {
		double layerY = 55.0 + layer * 38.0;
		double speed = 1.0 + layer * 0.4;
		double wavePhase = waterWavePhase * speed + layer * 1.5;

		for (double x = 0; x < SCREEN_WIDTH; x += 18.0) {
			double waveH = sin((x * 0.025) + wavePhase) * (3.5 + layer * 1.2);
			double wy = layerY + waveH;

			int alpha = (int)(25 + layer * 15 + sin(wavePhase + x * 0.05) * 12);
			if (alpha < 10) alpha = 10;
			if (alpha > 85) alpha = 85;

			glColor4ub(160, 225, 255, (GLubyte)alpha);
			glBegin(GL_LINES);
			glVertex2f((float)x, (float)wy);
			glVertex2f((float)(x + 16.0), (float)(wy + sin(((x + 16.0) * 0.025) + wavePhase) * (3.5 + layer * 1.2)));
			glEnd();
		}
	}

	for (int s = 0; s < 20; s++) {
		double gx = fmod(s * 58.0 + sin(s * 13.0) * 200.0 - cameraX * 0.35, SCREEN_WIDTH);
		if (gx < 0.0) gx += SCREEN_WIDTH;
		double gy = 65.0 + fmod(s * 27.0 + cos(s * 17.0) * 80.0, 140.0);

		double sparkle = sin(player.blinkCounter * 0.15 + s * 1.8);
		if (sparkle > 0.4) {
			int gAlpha = (int)((sparkle - 0.4) / 0.6 * 190.0);
			glColor4ub(255, 255, 240, (GLubyte)gAlpha);
			glBegin(GL_LINES);
			glVertex2f((float)(gx - 2.5), (float)gy);
			glVertex2f((float)(gx + 2.5), (float)gy);
			glVertex2f((float)gx, (float)(gy - 2.5));
			glVertex2f((float)gx, (float)(gy + 2.5));
			glEnd();
		}
	}

	glDisable(GL_BLEND);
}
inline void drawHelicopterWaterRipples() {
	double heliScreenX = player.x - cameraX;
	if (heliScreenX < -60.0 || heliScreenX > SCREEN_WIDTH + 60.0) return;

	double waterSurfaceY = 52.0;
	double altitude = player.y - waterSurfaceY;
	if (altitude > 340.0) return;

	double wakeIntensity = 1.0 - (altitude / 340.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int r = 0; r < 3; r++) {
		double progress = fmod((player.blinkCounter * 0.04) + r * 0.33, 1.0);
		double rx = 18.0 + progress * 75.0 * (1.0 + wakeIntensity);
		double ry = rx * 0.32;

		int alpha = (int)((1.0 - progress) * 160.0 * wakeIntensity);
		if (alpha <= 0) continue;

		glColor4ub(190, 235, 255, (GLubyte)alpha);
		glBegin(GL_LINE_LOOP);
		for (double a = 0; a <= 6.29; a += 0.25) {
			glVertex2f((float)(heliScreenX + 3.0 + cos(a) * rx), (float)(waterSurfaceY + sin(a) * ry));
		}
		glEnd();
	}

	for (int p = 0; p < 6; p++) {
		double pAngle = fmod(player.blinkCounter * 0.12 + p * 1.04, 6.28);
		double pDist = 20.0 + sin(p + player.blinkCounter * 0.08) * 35.0;
		double px = heliScreenX + 3.0 + cos(pAngle) * pDist;
		double py = waterSurfaceY + fabs(sin(pAngle)) * 8.0 + sin(player.blinkCounter * 0.2 + p) * 5.0;

		glColor4ub(220, 245, 255, (GLubyte)(140 * wakeIntensity));
		glBegin(GL_POINTS);
		glVertex2f((float)px, (float)py);
		glEnd();
	}

	glDisable(GL_BLEND);
}

inline void drawEnvironment() {
	// 1. Sector Background Custom Images with Parallax Movement
	int bgOffset = (int)(cameraX * 0.35) % SCREEN_WIDTH;
	if (bgOffset < 0) bgOffset += SCREEN_WIDTH;

	if (currentSector == 1 && imgSector1 >= 0) {
		iShowImage(-bgOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgSector1);
		iShowImage(-bgOffset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgSector1);
	}
	else if (currentSector == 2 && imgSector2 >= 0) {
		iShowImage(-bgOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgSector2);
		iShowImage(-bgOffset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgSector2);
	}
	else if (currentSector == 3 && imgSector3 >= 0) {
		iShowImage(-bgOffset, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgSector3);
		iShowImage(-bgOffset + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgSector3);
	}
	else {
		
		if (currentSector == 1) {
			iSetColor(60, 85, 110);
			iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			iSetColor(40, 65, 55);
			for (int h = -100; h < SCREEN_WIDTH + 200; h += 180) {
				double hillX = h - ((int)(cameraX * 0.2) % 180);
				iFilledCircle(hillX + 70, 40, 90);
			}
		}
		else if (currentSector == 2) {
			iSetColor(85, 75, 65);
			iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			iSetColor(65, 50, 40);
			for (int m = -100; m < SCREEN_WIDTH + 200; m += 200) {
				double mtnX = m - ((int)(cameraX * 0.25) % 200);
				iFilledCircle(mtnX + 80, 40, 110);
			}
		}
		else {
			iSetColor(15, 18, 28);
			iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

			int bWidths[7] = { 110, 95, 130, 100, 125, 105, 140 };
			int bHeights[7] = { 280, 380, 260, 320, 410, 290, 350 };
			double bgParaX = -(cameraX * 0.3);

			for (int rep = 0; rep < 3; rep++) {
				double currX = bgParaX + rep * 800.0;
				for (int b = 0; b < 7; b++) {
					if (currX + bWidths[b] >= 0 && currX <= SCREEN_WIDTH) {
						iSetColor(25, 30, 42);
						iFilledRectangle(currX, 0, bWidths[b], bHeights[b]);
						iSetColor(40, 48, 65);
						iRectangle(currX, 0, bWidths[b], bHeights[b]);

						for (int wx = currX + 8; wx < currX + bWidths[b] - 10; wx += 16) {
							for (int wy = 40; wy < bHeights[b] - 20; wy += 20) {
								int winSeed = (b * 19 + (int)wx * 11 + (int)wy * 17);
								if (winSeed % 4 == 0) {
									iSetColor(255, 220, 100);
									iFilledRectangle(wx, wy, 9, 11);
								}
								else if (winSeed % 4 == 1) {
									iSetColor(80, 210, 255);
									iFilledRectangle(wx, wy, 9, 11);
								}
								else {
									iSetColor(35, 42, 58);
									iFilledRectangle(wx, wy, 9, 11);
								}
							}
						}
					}
					currX += bWidths[b] + 12;
				}
			}
		}
	}

	
	drawSunlightShafts();

	
	drawAnimatedSkyClouds();

	drawDistantSoaringBirds();
	drawSynchronizedFlock();

	drawWaterBasinSurfaceWaves();

	drawHelicopterWaterRipples();

	if (currentSector == 1) {
		
		iSetColor(30, 70, 110);
		for (double wx = 0; wx < SCREEN_WIDTH; wx += 16.0) {
			double wy = 48.0 + sin((wx * 0.035) + waterWavePhase) * 6.0;
			iFilledRectangle(wx, 0, 17, wy);
		}
		iSetColor(180, 225, 255);
		for (double wx = 0; wx < SCREEN_WIDTH; wx += 16.0) {
			double wy1 = 48.0 + sin((wx * 0.035) + waterWavePhase) * 6.0;
			double wy2 = 48.0 + sin(((wx + 16.0) * 0.035) + waterWavePhase) * 6.0;
			iLine(wx, wy1, wx + 16.0, wy2);
			iLine(wx, wy1 - 1, wx + 16.0, wy2 - 1);
		}

		double buoyScreenX = 220.0 - cameraX * 0.5;
		if (buoyScreenX >= -20.0 && buoyScreenX <= SCREEN_WIDTH + 20.0) {
			double buoyY = 44.0 + sin((200.0 * 0.035) + waterWavePhase) * 5.0;
			iSetColor(245, 60, 40);
			iFilledCircle(buoyScreenX, buoyY, 7);
			iSetColor(255, 255, 255);
			iCircle(buoyScreenX, buoyY, 7);
		}
	}
	else if (currentSector == 2) {
		// Mountain Campfires & Rising Sparks
		int fireFlicker = (player.blinkCounter % 4);
		double f1X = 320.0 - cameraX * 0.4;
		double f2X = 1100.0 - cameraX * 0.4;
		if (f1X >= -20.0 && f1X <= SCREEN_WIDTH + 20.0) {
			iSetColor(255, 120, 20);
			iFilledCircle(f1X, 310 + fireFlicker, 5);
			iSetColor(255, 220, 80);
			iFilledCircle(f1X, 310 + fireFlicker, 2);
			// Rising campfire spark
			double spkY = 315 + (player.blinkCounter % 25);
			iSetColor(255, 200, 50);
			iFilledCircle(f1X + sin(spkY * 0.1) * 3.0, spkY, 1.5);
		}
		if (f2X >= -20.0 && f2X <= SCREEN_WIDTH + 20.0) {
			iSetColor(255, 120, 20);
			iFilledCircle(f2X, 280 + fireFlicker, 6);
			iSetColor(255, 220, 80);
			iFilledCircle(f2X, 280 + fireFlicker, 3);
			double spkY = 285 + (player.blinkCounter % 28);
			iSetColor(255, 200, 50);
			iFilledCircle(f2X + sin(spkY * 0.1) * 3.0, spkY, 1.5);
		}
	}
	else if (currentSector == 3) {
		
		if (lightningFlash > 0) {
			iSetColor(220, 235, 255);
			iLine(420, SCREEN_HEIGHT - 30, 435, SCREEN_HEIGHT - 120);
			iLine(435, SCREEN_HEIGHT - 120, 405, SCREEN_HEIGHT - 210);
			iLine(405, SCREEN_HEIGHT - 210, 450, SCREEN_HEIGHT - 300);
			iLine(435, SCREEN_HEIGHT - 120, 470, SCREEN_HEIGHT - 180);
			iLine(470, SCREEN_HEIGHT - 180, 490, SCREEN_HEIGHT - 260);

			iSetColor(255, 255, 255);
			iLine(421, SCREEN_HEIGHT - 30, 436, SCREEN_HEIGHT - 120);
			iLine(436, SCREEN_HEIGHT - 120, 406, SCREEN_HEIGHT - 210);
		}
	}

	for (int w = 0; w < MAX_WIND_PARTICLES; w++) {
		if (windParticles[w].type == 0) { // Leaves / green foliage
			iSetColor(70, 165, 60);
			iFilledCircle(windParticles[w].x, windParticles[w].y, windParticles[w].size);
		}
		else if (windParticles[w].type == 1) { // Atmospheric mist
			iSetColor(210, 230, 250);
			iFilledCircle(windParticles[w].x, windParticles[w].y, windParticles[w].size * 2.0);
		}
		else { // Water spray
			iSetColor(180, 220, 255);
			iLine(windParticles[w].x, windParticles[w].y, windParticles[w].x - 4, windParticles[w].y - 3);
		}
	}

	// 9. High-Visibility Angled Rain
	iSetColor(230, 245, 255);
	for (int r = 0; r < MAX_RAINDROPS; r++) {
		if (raindrops[r].y < SCREEN_HEIGHT - 50) {
			iLine(raindrops[r].x, raindrops[r].y, raindrops[r].x + raindrops[r].slant, raindrops[r].y - raindrops[r].length);
		}
	}
}

inline void drawCountdownOverlay() {
	if (countdownTimer <= 0) return;

	iSetColor(255, 215, 0);
	drawText(SCREEN_WIDTH / 2 - 165, SCREEN_HEIGHT / 2 + 80, ">> MISSION PRE-FLIGHT <<", GLUT_BITMAP_HELVETICA_18);

	if (countdownTimer > 120) {
		if (imgCount3 >= 0) {
			drawTransparentImage(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 40, 120, 120, imgCount3);
		}
		else {
			iSetColor(255, 60, 60);
			drawText(SCREEN_WIDTH / 2 - 15, SCREEN_HEIGHT / 2, "3", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iSetColor(255, 230, 230);
		drawText(SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 - 50, "SPOOLING ROTOR ENGINES...", GLUT_BITMAP_HELVETICA_12);
	}
	else if (countdownTimer > 60) {
		if (imgCount2 >= 0) {
			drawTransparentImage(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 40, 120, 120, imgCount2);
		}
		else {
			iSetColor(255, 200, 40);
			drawText(SCREEN_WIDTH / 2 - 15, SCREEN_HEIGHT / 2, "2", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iSetColor(255, 240, 200);
		drawText(SCREEN_WIDTH / 2 - 95, SCREEN_HEIGHT / 2 - 50, "PRESS [Q] TO LOWER WINCH", GLUT_BITMAP_HELVETICA_12);
	}
	else {
		if (imgCount1 >= 0) {
			drawTransparentImage(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 40, 120, 120, imgCount1);
		}
		else {
			iSetColor(50, 255, 140);
			drawText(SCREEN_WIDTH / 2 - 15, SCREEN_HEIGHT / 2, "1", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		iSetColor(80, 255, 255);
		drawText(SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 50, "PLAY! RESCUE LAUNCH!", GLUT_BITMAP_HELVETICA_12);
	}
}

// Render Sector 3 Enemy Helicopter
inline void drawBossVillain() {
	if (!boss.active || currentSector != 3 || countdownTimer > 0) return;

	double bx = boss.x - cameraX;
	double by = boss.y;

	if (bx < -180.0 || bx > SCREEN_WIDTH + 180.0) return;

	// Enemy projectiles: bright red/yellow missiles drawn procedurally.
	for (int p = 0; p < MAX_BOSS_PROJECTILES; p++) {
		if (boss.projectiles[p].active) {
			double px = boss.projectiles[p].x - cameraX;
			double py = boss.projectiles[p].y;
			double speed = sqrt(boss.projectiles[p].vx * boss.projectiles[p].vx + boss.projectiles[p].vy * boss.projectiles[p].vy);
			double ux = (speed > 0.0) ? boss.projectiles[p].vx / speed : -1.0;
			double uy = (speed > 0.0) ? boss.projectiles[p].vy / speed : 0.0;

			iSetColor(255, 230, 80);
			iFilledCircle(px, py, 5);
			iSetColor(255, 80, 30);
			iFilledCircle(px - ux * 7.0, py - uy * 7.0, 3);
			iSetColor(255, 255, 255);
			iLine(px - ux * 12.0, py - uy * 12.0, px - ux * 3.0, py - uy * 3.0);
		}
	}

	// Hit flash.
	if (boss.flashTimer > 0 && (boss.flashTimer % 4 < 2)) {
		iSetColor(255, 255, 255);
		iFilledRectangle((int)(bx - boss.width / 2), (int)(by - boss.height / 2),
			(int)boss.width, (int)boss.height);
	}
	else if (imgBoss >= 0) {
		// The supplied enemy.png already has transparency; preserve its wide aspect ratio.
		drawTransparentImage((int)(bx - boss.width / 2.0), (int)(by - boss.height / 2.0),
			(int)boss.width, (int)boss.height, imgBoss);
	}
	else {
		// Fallback if enemy.png cannot be found.
		iSetColor(235, 210, 30);
		iFilledRectangle((int)(bx - 55), (int)(by - 18), 100, 30);
		iSetColor(220, 220, 225);
		iFilledCircle(bx - 38, by, 18);
		iSetColor(35, 45, 55);
		iFilledCircle(bx - 42, by + 3, 8);
	}

	// Draw the main rotor separately.  It is NOT part of enemy.png.
	double rotorAngle = boss.rotorAngle * 3.141592653589793 / 180.0;
	double rotorX = bx - 3.0;
	double rotorY = by + boss.height * 0.39;
	double bladeLength = 47.0;
	double bladeThickness = 2.8;

	iSetColor(35, 35, 40);
	iLine((int)(rotorX - cos(rotorAngle) * bladeLength),
		(int)(rotorY - sin(rotorAngle) * bladeThickness),
		(int)(rotorX + cos(rotorAngle) * bladeLength),
		(int)(rotorY + sin(rotorAngle) * bladeThickness));
	iLine((int)(rotorX - sin(rotorAngle) * bladeLength),
		(int)(rotorY + cos(rotorAngle) * bladeThickness),
		(int)(rotorX + sin(rotorAngle) * bladeLength),
		(int)(rotorY - cos(rotorAngle) * bladeThickness));

	// Rotor tips and hub.
	iSetColor(220, 220, 225);
	iFilledCircle((int)(rotorX + cos(rotorAngle) * bladeLength), (int)(rotorY + sin(rotorAngle) * bladeThickness), 2);
	iFilledCircle((int)(rotorX - cos(rotorAngle) * bladeLength), (int)(rotorY - sin(rotorAngle) * bladeThickness), 2);
	iSetColor(255, 210, 30);
	iFilledCircle((int)rotorX, (int)rotorY, 4);

	// Small tail-rotor effect, also drawn rather than taken from the image.
	double tailAngle = boss.rotorAngle * 2.0 * 3.141592653589793 / 180.0;
	double tailX = bx + boss.width * 0.46;
	double tailY = by - 2.0;
	double tailLength = 10.0;
	iSetColor(55, 55, 60);
	iLine((int)(tailX - cos(tailAngle) * tailLength), (int)(tailY - sin(tailAngle) * tailLength),
		(int)(tailX + cos(tailAngle) * tailLength), (int)(tailY + sin(tailAngle) * tailLength));
	iLine((int)(tailX - sin(tailAngle) * tailLength), (int)(tailY + cos(tailAngle) * tailLength),
		(int)(tailX + sin(tailAngle) * tailLength), (int)(tailY - cos(tailAngle) * tailLength));

	// Enemy HP display: ONLY the red HP bar and text. No unnecessary outer box.
	int barW = 250;
	int barH = 12;
	int barX = (int)bx - barW / 2;
	int barY = (int)(by + boss.height / 2.0 + 42.0);
	if (barY > SCREEN_HEIGHT - 70) barY = SCREEN_HEIGHT - 70;

	double hpPct = (boss.maxHp > 0) ? (double)boss.hp / (double)boss.maxHp : 0.0;
	if (hpPct < 0.0) hpPct = 0.0;
	if (hpPct > 1.0) hpPct = 1.0;

	// Small dark track only behind the red HP fill.
	iSetColor(45, 45, 50);
	iFilledRectangle(barX, barY, barW, barH);
	iSetColor(235, 45, 55);
	iFilledRectangle(barX + 2, barY + 2, (int)((barW - 4) * hpPct), barH - 4);

	char hpTxt[64];
	sprintf_s(hpTxt, "ENEMY HELICOPTER   %d/%d HP", boss.hp, boss.maxHp);
	iSetColor(255, 255, 255);
	drawText(barX + 8, barY + 17, hpTxt, GLUT_BITMAP_HELVETICA_10);
}

inline void drawHUD() {
	iSetColor(20, 25, 32);
	iFilledRectangle(0, SCREEN_HEIGHT - 45, SCREEN_WIDTH, 45);
	iSetColor(60, 70, 85);
	iLine(0, SCREEN_HEIGHT - 45, SCREEN_WIDTH, SCREEN_HEIGHT - 45);

	// 1. 3-Lives System with Helicopter Icons (Professor Req #6 Image HUD)
	drawText(10, SCREEN_HEIGHT - 20, "LIVES:", GLUT_BITMAP_HELVETICA_10);
	for (int l = 0; l < 3; l++) {
		double lx = 50 + l * 26;
		if (l < player.lives) {
			if (imgHeliNeutral >= 0) {
				drawTransparentImage((int)lx, SCREEN_HEIGHT - 38, 24, 14, imgHeliNeutral);
			}
			else {
				iSetColor(40, 220, 80);
				iFilledCircle(lx + 8, SCREEN_HEIGHT - 22, 6);
				iSetColor(255, 255, 255);
				iFilledCircle(lx + 8, SCREEN_HEIGHT - 22, 2);
			}
		}
		else {
			iSetColor(70, 75, 85);
			iCircle(lx + 8, SCREEN_HEIGHT - 22, 6);
		}
	}

	// 2. Battery-style Fuel / Stamina Bar.
	// The supplied battery image is the outer frame; the green fuel fill is drawn INSIDE it.
	const int fuelX = 145;
	const int fuelY = SCREEN_HEIGHT - 43;
	const int fuelW = 110;
	const int fuelH = 42;

	iSetColor(220, 220, 220);
	drawText(fuelX, SCREEN_HEIGHT - 12, "FUEL", GLUT_BITMAP_HELVETICA_10);

	// Inner area of the 120x46 source battery image after scaling to 110x42.
	int innerX = fuelX + 7;
	int innerY = fuelY + 7;
	int innerW = fuelW - 14;
	int innerH = fuelH - 14;
	int fillW = (int)(innerW * (player.fuel / 100.0));
	if (fillW < 0) fillW = 0;
	if (fillW > innerW) fillW = innerW;

	if (player.fuel > 20.0) {
		iSetColor(40, 220, 70);
	}
	else if (player.fuel > 8.0) {
		iSetColor(240, 200, 40);
	}
	else {
		if ((player.blinkCounter / 10) % 2 == 0) iSetColor(255, 40, 40);
		else iSetColor(120, 20, 20);
	}
	if (fillW > 0) {
		iFilledRectangle(innerX, innerY, fillW, innerH);
	}

	// Draw the battery frame LAST so the fill stays visually inside the gray battery.
	if (imgFuelBar >= 0) {
		drawTransparentImage(fuelX, fuelY, fuelW, fuelH, imgFuelBar);
	}
	else {
		iSetColor(120, 120, 120);
		iRectangle(fuelX, fuelY, fuelW, fuelH);
	}

	// 3. Passenger Capacity Hold with Character Portrait Icons (Req #6)
	iSetColor(220, 220, 220);
	drawText(265, SCREEN_HEIGHT - 20, "HOLD:", GLUT_BITMAP_HELVETICA_10);
	for (int p = 0; p < MAX_PASSENGERS; p++) {
		double slotX = 305 + p * 24;
		if (p < player.passengers) {
			if (imgPeople[p] >= 0) {
				drawTransparentImage((int)slotX, SCREEN_HEIGHT - 38, 18, 24, imgPeople[p]);
			}
			else {
				iSetColor(40, 220, 70);
				iFilledCircle(slotX + 8, SCREEN_HEIGHT - 22, 6);
			}
		}
		else {
			iSetColor(65, 70, 80);
			iCircle(slotX + 8, SCREEN_HEIGHT - 22, 6);
		}
	}

	// 4. Sector & Rescued Quota
	iSetColor(220, 220, 220);
	char quotaStr[64];
	const char *secNames[4] = { "", "FLOOD", "MUD", "THUNDER" };
	sprintf_s(quotaStr, "LVL %d-%s: %d/%d", selectedLevelTier, secNames[currentSector], sectorRescued, targetRescue[selectedLevelTier][currentSector]);
	drawText(390, SCREEN_HEIGHT - 20, quotaStr, GLUT_BITMAP_HELVETICA_12);

	// 5. Medkits with Image Icon (Req #6)
	if (imgMedi1 >= 0) {
		drawTransparentImage(525, SCREEN_HEIGHT - 36, 18, 18, imgMedi1);
	}
	char medStr[32];
	sprintf_s(medStr, "[S]: %d", player.medkits);
	iSetColor(80, 220, 255);
	drawText(547, SCREEN_HEIGHT - 20, medStr, GLUT_BITMAP_HELVETICA_10);

	// 6. Flare Ready Indicator
	iSetColor(255, 220, 100);
	drawText(605, SCREEN_HEIGHT - 20, "FLARE [F]: READY", GLUT_BITMAP_HELVETICA_10);

	// 7. Score
	char scoreStr[48];
	sprintf_s(scoreStr, "%d PTS", score);
	iSetColor(255, 220, 80);
	drawText(730, SCREEN_HEIGHT - 20, scoreStr, GLUT_BITMAP_HELVETICA_18);

	// 8. EMP Power with Image Icon (Req #6)
	if (imgPower1 >= 0) {
		drawTransparentImage(835, SCREEN_HEIGHT - 36, 18, 18, imgPower1);
	}
	char spellStr[32];
	sprintf_s(spellStr, "EMP [E]: %d", player.spells);
	iSetColor(120, 220, 255);
	drawText(857, SCREEN_HEIGHT - 20, spellStr, GLUT_BITMAP_HELVETICA_10);
	if (player.isShielded) {
		char shieldStr[48];
		sprintf_s(shieldStr, "SHIELD: %0.1fs", player.shieldTimer / 60.0);
		iSetColor(80, 255, 255);
		drawText(857, SCREEN_HEIGHT - 34, shieldStr, GLUT_BITMAP_HELVETICA_10);
	}

	// 9. Enemy helicopter HP is drawn above the enemy in drawBossVillain().

	// 10. Action Guide Banner
	if (rescueNotificationTimer > 0) {
		iSetColor(50, 255, 120);
		drawText(240, SCREEN_HEIGHT - 68, rescueNotificationText, GLUT_BITMAP_HELVETICA_18);
	}
	else if (countdownTimer <= 0) {
		if (player.passengers == 0) {
			iSetColor(255, 255, 180);
			drawText(170, SCREEN_HEIGHT - 68, ">> PRESS [Q] TO LOWER WINCH HOOK | [S] TO AIR-DROP MEDKIT | [F] TO SHOOT <<", GLUT_BITMAP_HELVETICA_12);
		}
		else if (player.passengers < MAX_PASSENGERS) {
			iSetColor(80, 230, 255);
			drawText(180, SCREEN_HEIGHT - 68, ">> SURVIVOR ONBOARD! PRESS [Q] TO HOIST MORE OR FLY LEFT TO HELIPAD <<", GLUT_BITMAP_HELVETICA_12);
		}
		else {
			iSetColor(255, 80, 80);
			drawText(180, SCREEN_HEIGHT - 68, ">> CAPACITY FULL (3/3)! RETURN TO BASE (LEFT) OR AIR-DROP MEDKITS [S]! <<", GLUT_BITMAP_HELVETICA_12);
		}
	}

	// 11. Directional Base / Disaster Zone Navigation Indicators
	if (countdownTimer <= 0) {
		if (player.passengers > 0 && cameraX > 80.0) {
			if ((player.blinkCounter / 15) % 2 == 0) iSetColor(50, 255, 100);
			else iSetColor(255, 215, 0);
			drawText(15, SCREEN_HEIGHT - 65, "<<< BASE HELIPAD (OFFLOAD)", GLUT_BITMAP_HELVETICA_12);
		}
		else if (player.passengers < MAX_PASSENGERS && cameraX < 800.0) {
			if ((player.blinkCounter / 15) % 2 == 0) iSetColor(80, 220, 255);
			else iSetColor(255, 255, 255);
			drawText(SCREEN_WIDTH - 240, SCREEN_HEIGHT - 65, "SURVIVORS AHEAD >>>", GLUT_BITMAP_HELVETICA_12);
		}
	}

	drawCountdownOverlay();
}

#endif // RENDERING_H