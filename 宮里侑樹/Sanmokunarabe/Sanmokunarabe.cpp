#include "DxLib.h"
#include "GameBase.h"
// プログラムの起動処理
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameBase gameBase;

	// ゲームの環境設定
	if (gameBase.init() == false) {
		return -1;
	}
	// ゲームループ
	gameBase.loop();
	// ゲーム終了処理
	gameBase.exit();
	// ソフトの終了
	return 0;
}