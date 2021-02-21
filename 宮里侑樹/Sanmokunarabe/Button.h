#pragma once
#include "DxLib.h"
class Button {
public:
	Button(const int x, const int y, const int img);
	bool update();
	void draw();
private:
	int posX;
	int posY;
	int imgButton;
	int width;
	int height;
	bool isMouseOver;
	bool isMouseClick;
};