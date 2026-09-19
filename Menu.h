#ifndef MENU_H
#define MENU_H

#include "Variables.h"

inline void drawMenu() {
	if (imgMenu >= 0) {
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgMenu);
	}
	else {
		iSetColor(20, 30, 45);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		iSetColor(240, 50, 50);
		iFilledRectangle(SCREEN_WIDTH / 2 - 230, SCREEN_HEIGHT - 145, 460, 70);
		iSetColor(255, 255, 255);
		drawText(SCREEN_WIDTH / 2 - 130, SCREEN_HEIGHT - 110, "SKY RESCUE", GLUT_BITMAP_TIMES_ROMAN_24);
		const char *buttons[6] = { "1. PLAY MISSION", "2. LEVEL SELECT", "3. HOW TO PLAY", "4. HIGH SCORES", "5. GAME DEVELOPERS", "6. EXIT" };
		for (int i = 0; i < 6; i++) {
			double by = 360 - i * 55;
			iSetColor(35, 45, 60);
			iFilledRectangle(350, by, 300, 42);
			iSetColor(80, 160, 240);
			iRectangle(350, by, 300, 42);
			iSetColor(255, 255, 255);
			drawText(400, by + 14, buttons[i], GLUT_BITMAP_HELVETICA_18);
		}
	}
}

inline void drawLevelSelect() {
	if (imgLevelSelect >= 0) {
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgLevelSelect);
	}
	else {
		iSetColor(16, 24, 36);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		iSetColor(255, 215, 0);
		drawText(SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT - 70, "SELECT MISSION LEVEL", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(180, 220, 255);
		drawText(SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT - 100, "CHOOSE YOUR PILOT DIFFICULTY TIER", GLUT_BITMAP_HELVETICA_12);

		const char *levels[3] = {
			"LEVEL 1: BEGINNER (FLOOD, MUD, THUNDER)",
			"LEVEL 2: INTERMEDIATE (HIGHER WINDS & SPEED)",
			"LEVEL 3: EXPERT (CRITICAL STORM MISSIONS)"
		};
		const char *subtitles[3] = {
			"Ideal for new pilots. Learn the basics of rescue.",
			"More challenges. Sharpen your rescue skills.",
			"For elite pilots. Extreme weather, critical missions."
		};

		for (int l = 0; l < 3; l++) {
			double ly = 375 - l * 110;
			iSetColor(25, 40, 60);
			iFilledRectangle(240, ly, 520, 75);
			iSetColor(50, 200, 255);
			iRectangle(240, ly, 520, 75);

			iSetColor(255, 220, 80);
			drawText(260, ly + 45, levels[l], GLUT_BITMAP_HELVETICA_18);
			iSetColor(180, 210, 230);
			drawText(260, ly + 20, subtitles[l], GLUT_BITMAP_HELVETICA_12);
		}

		iSetColor(50, 65, 85);
		iFilledRectangle(SCREEN_WIDTH / 2 - 120, 45, 240, 38);
		iSetColor(255, 255, 255);
		drawText(SCREEN_WIDTH / 2 - 80, 58, "ESC / CLICK: MENU", GLUT_BITMAP_HELVETICA_12);
	}
}

inline void drawSectorSelect() {
	if (imgSectorSelect >= 0) {
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgSectorSelect);
	}
	else {
		iSetColor(20, 28, 40);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		iSetColor(255, 220, 60);
		const char *lvlNames[4] = { "", "BEGINNER", "INTERMEDIATE", "EXPERT" };
		char titleStr[64];
		sprintf_s(titleStr, "LEVEL %d (%s): SELECT RESCUE SECTOR", selectedLevelTier, lvlNames[selectedLevelTier]);
		drawText(SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT - 70, titleStr, GLUT_BITMAP_TIMES_ROMAN_24);

		const char *secTitles[4] = { "", "SECTOR 1: FLOOD BASIN (sector1.bmp)", "SECTOR 2: MUD & LANDSLIDE (sector2.bmp)", "SECTOR 3: THUNDER STORM (sector3.bmp)" };
		const char *secDescs[4] = { "", "Submerged homes & stranded rooftop citizens", "Rushing mudflows & falling hill boulders", "Midnight lightning & violent turbulence" };

		for (int s = 1; s <= 3; s++) {
			double sy = 480 - s * 105;
			iSetColor(30, 45, 65);
			iFilledRectangle(200, sy, 600, 75);
			iSetColor(80, 220, 120);
			iRectangle(200, sy, 600, 75);

			char sLabel[80];
			sprintf_s(sLabel, "%s - QUOTA: %d", secTitles[s], targetRescue[selectedLevelTier][s]);
			iSetColor(255, 255, 255);
			drawText(230, sy + 44, sLabel, GLUT_BITMAP_HELVETICA_18);
			iSetColor(160, 220, 190);
			drawText(230, sy + 18, secDescs[s], GLUT_BITMAP_HELVETICA_12);
		}

		iSetColor(50, 65, 85);
		iFilledRectangle(SCREEN_WIDTH / 2 - 100, 30, 200, 35);
		iSetColor(255, 255, 255);
		drawText(SCREEN_WIDTH / 2 - 50, 42, "BACK [ESC]", GLUT_BITMAP_HELVETICA_12);
	}
}

inline void drawNameInput() {
	if (imgPilotReg >= 0) {
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgPilotReg);

		iSetColor(50, 255, 120);
		iRectangle(300, 275, 400, 56);
		iRectangle(301, 276, 398, 54);
	}
	else {
		
		iSetColor(18, 26, 38);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		iSetColor(30, 45, 65);
		iFilledRectangle(SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - 170, 560, 340);
		iSetColor(80, 200, 255);
		iRectangle(SCREEN_WIDTH / 2 - 280, SCREEN_HEIGHT / 2 - 170, 560, 340);

		iSetColor(255, 215, 0);
		drawText(SCREEN_WIDTH / 2 - 165, SCREEN_HEIGHT / 2 + 115, "PILOT REGISTRATION", GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(180, 220, 245);
		drawText(SCREEN_WIDTH / 2 - 185, SCREEN_HEIGHT / 2 + 80, "ENTER YOUR CALLSIGN TO LOG FLIGHT DATA", GLUT_BITMAP_HELVETICA_12);

		iSetColor(12, 20, 30);
		iFilledRectangle(300, 275, 400, 56);
		iSetColor(50, 255, 120);
		iRectangle(300, 275, 400, 56);

		iSetColor(40, 180, 90);
		iFilledRectangle(345, 195, 310, 48);
		iSetColor(255, 255, 255);
		drawText(395, 212, "LAUNCH MISSION [ENTER]", GLUT_BITMAP_HELVETICA_12);

		iSetColor(50, 65, 80);
		iFilledRectangle(395, 140, 210, 32);
		iSetColor(200, 210, 220);
		drawText(450, 150, "BACK [ESC]", GLUT_BITMAP_HELVETICA_12);
	}

	char displayStr[64];
	if ((player.blinkCounter / 15) % 2 == 0) {
		sprintf_s(displayStr, sizeof(displayStr), "%s_", inputBuffer);
	}
	else {
		sprintf_s(displayStr, sizeof(displayStr), "%s ", inputBuffer);
	}

	if (nameLen == 0) {
		iSetColor(120, 160, 180);
		drawText(320, 298, "Type Name & Hit ENTER...", GLUT_BITMAP_HELVETICA_18);
	}
	else {
		iSetColor(50, 255, 120);
		drawText(320, 296, displayStr, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

inline void drawInstructions() {
	if (imgHowToPlay >= 0) {
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgHowToPlay);
	}
	else {
		iSetColor(20, 28, 40);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		iSetColor(255, 220, 60);
		drawText(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT - 60, "HOW TO PLAY", GLUT_BITMAP_TIMES_ROMAN_24);

		iSetColor(255, 255, 255);
		drawText(200, 480, "FLIGHT CONTROLS:", GLUT_BITMAP_HELVETICA_18);
		drawText(220, 445, "- [SPACE] / [W] / [UP ARROW]: Hold to Lift Off | Mouse / [A][D]: Steer", GLUT_BITMAP_HELVETICA_12);
		drawText(220, 415, "- Hover above citizens & HOLD [Q] to lower winch cable & 'C'-hook", GLUT_BITMAP_HELVETICA_12);
		drawText(220, 385, "- Return to BASE HELIPAD on the left to offload citizens & 100% REFUEL", GLUT_BITMAP_HELVETICA_12);
		drawText(220, 355, "- [S] or [DOWN ARROW]: Air-drop FIRST AID MEDKITS (medi1/medi2.png)", GLUT_BITMAP_HELVETICA_12);
		drawText(220, 325, "- [F] or [X]: Shoot RESCUE FLARES to destroy incoming hazards & drones", GLUT_BITMAP_HELVETICA_12);
		drawText(220, 295, "- [E]: Trigger SKY BLAST EMP shockwave to eliminate all on-screen hazards", GLUT_BITMAP_HELVETICA_12);
		drawText(220, 265, "- [P]: Pause / Unpause Mission | [R]: Retry on Game Over", GLUT_BITMAP_HELVETICA_12);

		iSetColor(50, 65, 85);
		iFilledRectangle(SCREEN_WIDTH / 2 - 100, 40, 200, 35);
		iSetColor(255, 255, 255);
		drawText(SCREEN_WIDTH / 2 - 50, 52, "BACK [ESC]", GLUT_BITMAP_HELVETICA_12);
	}
}

inline void drawHighScores() {
	if (imgLeaderboard >= 0) {
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgLeaderboard);
	}
	else {
		iSetColor(18, 24, 34);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		iSetColor(255, 215, 0);
		drawText(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT - 70, "PILOT LEADERBOARD", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	for (int i = 0; i < 5; i++) {
		char scoreVal[32];
		sprintf_s(scoreVal, "%d PTS", highScores[i]);
		if (i == 0) iSetColor(255, 215, 0);
		else if (i == 1) iSetColor(220, 220, 220);
		else if (i == 2) iSetColor(205, 127, 50);
		else iSetColor(180, 220, 255);
		double rowY = 395 - i * 60;
		drawText(380, rowY, highNames[i], GLUT_BITMAP_HELVETICA_18);
		drawText(650, rowY, scoreVal, GLUT_BITMAP_HELVETICA_18);
	}
}

inline void drawDevelopers() {
	if (imgDevelopers >= 0) {
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, imgDevelopers);
	}
	else {
		iSetColor(16, 22, 32);
		iFilledRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		iSetColor(255, 255, 255);
		drawText(SCREEN_WIDTH / 2 - 120, 450, "GAME CREATOR & TEAM", GLUT_BITMAP_TIMES_ROMAN_24);
		drawText(SCREEN_WIDTH / 2 - 100, 390, "MD Fahim Talukder", GLUT_BITMAP_HELVETICA_18);
		drawText(SCREEN_WIDTH / 2 - 100, 350, "Hasibul Hasan Shuvo", GLUT_BITMAP_HELVETICA_18);
		drawText(SCREEN_WIDTH / 2 - 100, 310, "Rafsan Sarker", GLUT_BITMAP_HELVETICA_18);
		drawText(SCREEN_WIDTH / 2 - 75, 100, "PRESS ESC / CLICK", GLUT_BITMAP_HELVETICA_12);
	}
}

inline void drawPause() {
	iSetColor(20, 30, 45);
	iFilledRectangle(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 75, 300, 150);
	iSetColor(80, 200, 255);
	iRectangle(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 75, 300, 150);
	iSetColor(255, 255, 255);
	drawText(SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 + 30, "GAME PAUSED", GLUT_BITMAP_TIMES_ROMAN_24);
	drawText(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 5, "Press 'P' to Resume Mission", GLUT_BITMAP_HELVETICA_12);
	drawText(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 - 30, "Press 'ESC' for Main Menu", GLUT_BITMAP_HELVETICA_12);
}

inline void drawSectorComplete() {
	iSetColor(20, 35, 50);
	iFilledRectangle(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 120, 440, 240);
	iSetColor(40, 220, 80);
	iRectangle(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 120, 440, 240);
	iSetColor(255, 255, 255);
	drawText(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 70, "SECTOR CLEARED!", GLUT_BITMAP_TIMES_ROMAN_24);
	char sumStr[80];
	sprintf_s(sumStr, "Great job %s! You rescued %d citizens in Sector %d!", playerName, targetRescue[selectedLevelTier][currentSector], currentSector);
	iSetColor(180, 240, 200);
	drawText(SCREEN_WIDTH / 2 - 185, SCREEN_HEIGHT / 2 + 25, sumStr, GLUT_BITMAP_HELVETICA_12);
	char scStr[64];
	sprintf_s(scStr, "CURRENT SCORE: %d", score);
	iSetColor(255, 220, 80);
	drawText(SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 - 5, scStr, GLUT_BITMAP_HELVETICA_18);
	iSetColor(40, 180, 90);
	iFilledRectangle(SCREEN_WIDTH / 2 - 130, SCREEN_HEIGHT / 2 - 80, 260, 36);
	iSetColor(255, 255, 255);
	drawText(SCREEN_WIDTH / 2 - 95, SCREEN_HEIGHT / 2 - 67, "CONTINUE TO NEXT SECTOR", GLUT_BITMAP_HELVETICA_12);
}

inline void drawGameOver() {
	iSetColor(35, 20, 20);
	iFilledRectangle(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 130, 440, 260);
	iSetColor(240, 40, 40);
	iRectangle(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 - 130, 440, 260);
	iSetColor(255, 50, 50);
	drawText(SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 + 75, "MISSION FAILED", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(240, 200, 200);
	if (gameOverReason == 0) {
		drawText(SCREEN_WIDTH / 2 - 165, SCREEN_HEIGHT / 2 + 35, "CAUSE: Helicopter collided with hazard / ground!", GLUT_BITMAP_HELVETICA_12);
	}
	else {
		drawText(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 35, "CAUSE: Fuel depleted! Helicopter lost power!", GLUT_BITMAP_HELVETICA_12);
	}
	char finalScoreStr[64];
	sprintf_s(finalScoreStr, "PILOT: %s | FINAL SCORE: %d", playerName, score);
	iSetColor(255, 220, 80);
	drawText(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 + 5, finalScoreStr, GLUT_BITMAP_HELVETICA_18);
	iSetColor(180, 50, 50);
	iFilledRectangle(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 60, 240, 34);
	iSetColor(255, 255, 255);
	drawText(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 48, "PRESS 'R' TO RETRY", GLUT_BITMAP_HELVETICA_12);
	iSetColor(50, 60, 75);
	iFilledRectangle(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 105, 240, 34);
	iSetColor(220, 220, 220);
	drawText(SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 - 93, "PRESS 'ESC' FOR MENU", GLUT_BITMAP_HELVETICA_12);
}

inline void drawVictory() {
	iSetColor(20, 35, 55);
	iFilledRectangle(SCREEN_WIDTH / 2 - 240, SCREEN_HEIGHT / 2 - 140, 480, 280);
	iSetColor(255, 215, 0);
	iRectangle(SCREEN_WIDTH / 2 - 240, SCREEN_HEIGHT / 2 - 140, 480, 280);
	iSetColor(255, 215, 0);
	drawText(SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT / 2 + 80, "VALIANT HERO OF SKY!", GLUT_BITMAP_TIMES_ROMAN_24);
	char vicMsg[80];
	const char *lvlTiers[4] = { "", "Beginner", "Intermediate", "Expert" };
	sprintf_s(vicMsg, "Salute to Pilot %s! You completed Level %d (%s) & saved Chattogram!", playerName, selectedLevelTier, lvlTiers[selectedLevelTier]);
	iSetColor(220, 240, 255);
	drawText(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 + 38, vicMsg, GLUT_BITMAP_HELVETICA_12);
	char finSc[64];
	sprintf_s(finSc, "HEROIC SCORE: %d PTS", score);
	iSetColor(255, 220, 80);
	drawText(SCREEN_WIDTH / 2 - 85, SCREEN_HEIGHT / 2 + 5, finSc, GLUT_BITMAP_HELVETICA_18);
	iSetColor(40, 180, 90);
	iFilledRectangle(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 70, 240, 36);
	iSetColor(255, 255, 255);
	drawText(SCREEN_WIDTH / 2 - 75, SCREEN_HEIGHT / 2 - 55, "PRESS ESC FOR MENU", GLUT_BITMAP_HELVETICA_12);
}

#endif // MENU_H