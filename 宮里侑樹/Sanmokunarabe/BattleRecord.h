#pragma once
#include "DxLib.h"
class BattleRecord {
public:
	BattleRecord(const int x, const int y, const int img); // 表示位置と画像
	void start();
	void stop();
	void win();
	void lose();
	void draw();
private:
	int imgNumber;
	int width, height;
	bool isRunning;
	int posX;
	int posY;
	int winCount;
	int loseCount;
};