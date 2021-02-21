#pragma once
#include "DxLib.h"
class Timer {
public:
	Timer(const int x, const int y, const int img); // 表示位置と画像
	void start();
	void stop();
	void update();
	void draw();
private:
	int imgNumber;
	int width, height;
	bool isRunning;
	int posX;
	int posY;
	int startTime;
	int nowTime;
};