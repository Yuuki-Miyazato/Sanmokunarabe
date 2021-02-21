//************************************
// GameBase:ゲームの土台
//************************************
#include "GameBase.h"
// public なメンバ関数
// 初期化(DX ライブラリと画面の基本設定)
bool GameBase::init()
{
	// タイトル
	SetMainWindowText("Sanmokunarabe");
	// Window サイズの設定
	SetGraphMode(800, 600, 32);
	// Window モード変更と初期化
	ChangeWindowMode(TRUE);
	if (DxLib_Init() != 0) {
		return false;
	}
	// 裏画面設定
	SetDrawScreen(DX_SCREEN_BACK);
	// ゲームマネージャ生成
	gm = new GameManager();

	// ゲームマネジャ初期化
	gm->init();

	//// 画像の読み込み
	//gm->imageLoad();
	return true;
}
// ゲームループ
void GameBase::loop()
{
	// 裏画面を表画面に反映、メッセージ処理、画面クリア
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		input();
		update();
		output();
		// ループ終了判定
		if (!isRunning) break;
	}
}
// 終了処理
void GameBase::exit()
{
	// DX ライブラリ終了処理
	DxLib_End();
}
// private なメンバ関数
// 入力処理
void GameBase::input()
{
	// 終了キーの処理と画面遷移
	if (CheckHitKey(KEY_INPUT_Q) == 1) {
		isRunning = FALSE;
	}
}
// ゲームオブジェクトの更新
void GameBase::update()
{
	gm->update();
}
// ゲームオブジェクトの描画
void GameBase::output()
{
	// ゲーム描画
	gm->output();
}