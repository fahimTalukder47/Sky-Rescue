#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "Variables.h"

inline void loadHighScores() {
	FILE *fp = fopen("highscores.txt", "r");
	if (fp != NULL) {
		for (int i = 0; i < 5; i++) {
			if (fscanf(fp, "%31s %d", highNames[i], &highScores[i]) != 2) break;
		}
		fclose(fp);
	}
}

inline void saveHighScores() {
	FILE *fp = fopen("highscores.txt", "w");
	if (fp != NULL) {
		for (int i = 0; i < 5; i++) {
			fprintf(fp, "%s %d\n", highNames[i], highScores[i]);
		}
		fclose(fp);
	}
}

inline void updateHighScore(int newScore) {
	for (int i = 0; i < 5; i++) {
		if (newScore > highScores[i]) {
			for (int j = 4; j > i; j--) {
				highScores[j] = highScores[j - 1];
				strcpy(highNames[j], highNames[j - 1]);
			}
			highScores[i] = newScore;
			strcpy(highNames[i], playerName);
			saveHighScores();
			break;
		}
	}
}

// Database Persistence: Save Career Progress (Req #5)
inline void saveGameProgress() {
	FILE *fp = fopen("progress.txt", "w");
	if (fp != NULL) {
		fprintf(fp, "%s %d %d %d %d %d\n", playerName, selectedLevelTier, currentSector, score, careerRescues, careerMissionsCompleted);
		fclose(fp);
	}
}

// Database Persistence: Load Career Progress (Req #5)
inline void loadGameProgress() {
	FILE *fp = fopen("progress.txt", "r");
	if (fp != NULL) {
		int lvl = 1, sec = 1, sc = 0, cr = 0, cm = 0;
		char name[32] = "Pilot";
		if (fscanf(fp, "%31s %d %d %d %d %d", name, &lvl, &sec, &sc, &cr, &cm) == 6) {
			strcpy_s(playerName, sizeof(playerName), name);
			selectedLevelTier = lvl;
			currentSector = sec;
			score = sc;
			careerRescues = cr;
			careerMissionsCompleted = cm;
		}
		fclose(fp);
	}
}

#endif 
