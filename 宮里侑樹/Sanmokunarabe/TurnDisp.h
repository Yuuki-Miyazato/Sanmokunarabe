#pragma once
#include "DxLib.h"
class TurnDisp {
public:
	TurnDisp(const int x, const int y, const int img);
	void update(int turn);
	void draw();
private:
	int posX;
	int posY;
	int imgSelect;
	int turn;
};