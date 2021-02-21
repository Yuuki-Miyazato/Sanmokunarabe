#include "TurnDisp.h"

// コンストラクタ
TurnDisp::TurnDisp(const int x, const int y, const int img)
{
	// 表示位置
	posX = x;
	posY = y;
	// 画像番号
	imgSelect = img;
	// 最初の手番
	turn = 0; // 0:YOU
}
// 更新
void TurnDisp::update(int turn)
{
	this->turn = turn;
}

// 描画
void TurnDisp::draw()
{
	// 描画(0:YOU 1:PC)
	if (turn == 0) {
		DrawGraph(posX, posY, imgSelect, TRUE);
	}
	else {
		DrawGraph(posX + 273, posY, imgSelect, TRUE);
	}
}