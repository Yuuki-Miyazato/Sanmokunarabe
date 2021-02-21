#include "Timer.h"
// コンストラクタ
Timer::Timer(const int x, const int y, const int img)
{
	// 表示位置
	posX = x;
	posY = y;
	// 数字画像、文字単位の幅と高さ
	imgNumber = img;
	GetGraphSize(imgNumber, &width, &height);
	width = width / 10;
	// 経過時間の初期化
	nowTime = 0;
	startTime = GetNowCount();
	isRunning = false;
}

// 経過時間の計測開始
void Timer::start()
{
	if (isRunning == false) {
		isRunning = true;
		startTime = GetNowCount();
	}
}
// 経過時間の計測停止
void Timer::stop()
{
	if (isRunning == true) {
		isRunning = false;
	}
}
// 経過時間の計測更新
void Timer::update()
{
	if (isRunning) {
		nowTime = GetNowCount() - startTime;
	}
	else {
		//nowTime = 0;
	}
}
// 経過時間の描画
void Timer::draw()
{
	int m1, m2, s1, s2;
	// 4 桁の時刻に変換
	m1 = (nowTime / 60000) / 10;
	m2 = (nowTime / 60000) % 10;
	s1 = ((nowTime / 1000) % 60) / 10;
	s2 = ((nowTime / 1000) % 60) % 10;
	// 経過時間4桁の表示
	DrawRectGraph(posX, posY, width * m1, 0, width, height, imgNumber, TRUE, FALSE);
	DrawRectGraph(posX + 55, posY, width * m2, 0, width, height, imgNumber, TRUE, FALSE);
	DrawRectGraph(posX + 139, posY, width * s1, 0, width, height, imgNumber, TRUE, FALSE);
	DrawRectGraph(posX + 195, posY, width * s2, 0, width, height, imgNumber, TRUE, FALSE);
}