#include "Button.h"
// コンストラクタ
Button::Button(const int x, const int y, const int img)
{
	// 表示位置
	posX = x;
	posY = y;
	// 画像番号、幅と高さ
	imgButton = img;
	GetGraphSize(imgButton, &width, &height);
	// マウスの状態
	isMouseOver = false;
	isMouseClick = false;
}
// 更新
bool Button::update()
{
	int x, y;
	// マウスの位置を取得
	GetMousePoint(&x, &y);
	// マウスオーバーかを調べる
	if ((posX < x && posX + width > x && (posY < y && posY + height > y))) {
		isMouseOver = true;
	}
	else {
		isMouseOver = false;
	}
	// マウスオーバーの時の右クリックの状態を取得
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		// 押されている
		if (isMouseOver) {
			isMouseClick = true;
		}
	}
	else
	{
		// 押されていない
		isMouseClick = false;
	}
	// マウスクリックならボタンオンを通知
	if (isMouseClick) {
		return true;
	}
	return false;
}
// 描画
void Button::draw()
{
	// 描画(マウスオーバーなら拡大表示)
	if (isMouseOver) {
		DrawExtendGraph(posX - 3, posY - 3, posX + width + 3, posY + height + 3, imgButton, TRUE);
	}
	else {
		DrawGraph(posX, posY, imgButton, TRUE);
	}
}