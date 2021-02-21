#pragma once
#include "DxLib.h"
class ResultDisp {
public:
	ResultDisp(const int x, const int y, const int img1, const int img2, const int img3);
	void update(int result);
	void draw();
private:
	int posX;
	int posY;
	int imgWin;
	int imgLose;
	int imgDraw;
	int result;
};