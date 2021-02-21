#include "ResultDisp.h"

// コンストラクタ
ResultDisp::ResultDisp(const int x, const int y, const int img1, const int img2, const int img3)
{
	// 表示位置
	posX = x;
	posY = y;
	// 画像番号
	imgWin = img1;
	imgLose = img2;
	imgDraw = img3;
	// 最初の対戦結果
	result = 0; // 0:空白
}
// 更新
void ResultDisp::update(int result)
{
	this->result = result;
}
// 描画
void ResultDisp::draw()
{
	// 描画(0:空白 1:勝ち 2:負け 3:引分け)
	if (result == 0) {
	}
	else if (result == 1) {
		DrawGraph(posX, posY, imgWin, TRUE);
	}
	else if (result == 2) {
		DrawGraph(posX, posY, imgLose, TRUE);
	}
	else if (result == 3) {
		DrawGraph(posX - 10, posY, imgDraw, TRUE);
	}
}