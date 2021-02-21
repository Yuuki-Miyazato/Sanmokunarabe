#include "BattleRecord.h"
// コンストラクタ
BattleRecord::BattleRecord(const int x, const int y, const int img)
{
	// 表示位置
	posX = x;
	posY = y;
	// 数字画像、文字単位の幅と高さ
	imgNumber = img;
	GetGraphSize(imgNumber, &width, &height);
	width = width / 10;
	// 勝敗の初期化
	winCount = 0;
	loseCount = 0;
	isRunning = false;
}
// 戦績の更新開始
void BattleRecord::start()
{
	if (isRunning == false) {
		isRunning = true;
	}
}

// 戦績の更新停止
void BattleRecord::stop()
{
	if (isRunning == true) {
		isRunning = false;
	}
}
// 勝ち数のカウントアップ
void BattleRecord::win()
{
	if (isRunning == true) {
		winCount++;
	}
}
// 負け数のカウントアップ
void BattleRecord::lose()
{
	if (isRunning == true) {
		loseCount++;
	}
}
// 戦績の描画
void BattleRecord::draw()
{
	int w1, w2, l1, l2;
	// 桁の画像番号に変換
	w1 = winCount / 10;
	w2 = winCount % 10;
	l1 = loseCount / 10;
	l2 = loseCount % 10;
	// 戦績4桁の表示
	DrawRectGraph(posX, posY, width * w1, 0, width, height, imgNumber, TRUE, FALSE);
	DrawRectGraph(posX + 55, posY, width * w2, 0, width, height, imgNumber, TRUE, FALSE);
	DrawRectGraph(posX + 139, posY, width * l1, 0, width, height, imgNumber, TRUE, FALSE);
	DrawRectGraph(posX + 195, posY, width * l2, 0, width, height, imgNumber, TRUE, FALSE);
}