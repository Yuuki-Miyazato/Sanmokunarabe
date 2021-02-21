#pragma once
#include "DxLib.h"
#include "GameManager.h"
class GameBase {
public:
	bool init();
	void loop();
	void exit();
private:
	bool isRunning;
	GameManager* gm;
	void input();
	void update();
	void output();
};