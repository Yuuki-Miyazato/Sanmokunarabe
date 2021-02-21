#pragma once
#include "DxLib.h"
#include "Timer.h"
#include "Button.h"
#include "TurnDisp.h"
#include "ResultDisp.h"
#include "Board.h"
#include "BattleRecord.h"

class GameManager {
public:
	void init();
	void imageLoad();
	void update();
	void output();
private:
	// 画像ファイルの変数
	int imgTitle;
	int imgDraw;
	int imgEnd;
	int imgLose;
	int imgSelect;
	int imgStart;
	int imgWin;
	int imgWStone;
	int imgBStone;
	//int imgNumber[10];
	int imgNumber;

	Timer* time;
	Button* start;
	Button* end;
	TurnDisp* turn;
	ResultDisp* result;
	Board* board;
	BattleRecord* battleRecord;
};