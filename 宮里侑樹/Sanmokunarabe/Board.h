#pragma once
#include"DxLib.h"
class Board {
public:
	Board(const int x, const int y, const int img1, const int img2);
	void update();
	void draw();
	void start();
	void stop();
	int getResult();
	int getTurn();
private:
	int posX;
	int posY;
	int imgBlack;
	int imgWhite;
	int tbl[5][5];
	int turn;
	int result;
	int boardX;
	int boardY;
	int boardcheck;
	bool isMouseOver;
	bool isMouseClick;
	bool isStart;

	void searchMove(int* x, int* y);
	void tblClear();
	void setStone(int x, int y);
	bool check(int x, int y);
	int countStone(int stone, int x, int y, int dx, int dy);
};