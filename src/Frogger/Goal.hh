#pragma once

struct Goal {
	Sprite winnerFrog;
	Sprite insecte;
	int x, y;
	int w = 66;
	int h = 41;
	int printX, printY;
	bool in = false;
	bool insectON = false;
};