#include "GameManager.h"

void GameManager::init()
{
	imageLoad();
	// 経過時間オブジェクト生成と計測開始
	time = new Timer(19, 144, imgNumber);

	// 戦績オブジェクト生成
	battleRecord = new BattleRecord(19, 394, imgNumber);

	// ボタンオブジェクトの生成
	start = new Button(14, 525, imgStart);
	end = new Button(180, 525, imgEnd);

	// 手番表示オブジェクトの生成
	turn = new TurnDisp(297, 36, imgSelect);

	// 対戦結果表示オブジェクトの生成
	result = new ResultDisp(94, 280, imgWin, imgLose, imgDraw);

	// 盤面オブジェクトの生成
	board = new Board(302, 102, imgBStone, imgWStone);
	//time->start();
}

// 画像の読み込み
void GameManager::imageLoad()
{
	// 画像ファイルの読みこみ
	imgTitle = LoadGraph("images/title(3).png");
	imgDraw = LoadGraph("images/draw.png");
	imgEnd = LoadGraph("images/end.png");
	imgLose = LoadGraph("images/lose.png");
	imgSelect = LoadGraph("images/select.png");
	imgStart = LoadGraph("images/start.png");
	imgWin = LoadGraph("images/win.png");
	imgWStone = LoadGraph("images/white_stone.png");
	imgBStone = LoadGraph("images/black_stone.png");
	imgNumber = LoadGraph("images/number.png");
	// 数字画像を分割読み込み
	//LoadDivGraph("images/number.png", 10, 10, 1, 49, 67, imgNumber);
}

// ゲーム更新
void GameManager::update()
{
	// 経過時間の更新
	time->update();
	// ボタンの状態更新
	if (start->update()) {
		time->start();
		board->start();
		battleRecord->start();
	}
	if (end->update()) {
		time->stop();
		board->stop();
		battleRecord->stop();
	}
	// 手番表示のテスト
	static int count = 0;
	static int sw = 0;
	// 2 秒ごとに表示を切り替える
	if (++count > 120) {
		sw = (sw + 1) % 2;
		count = 0;
	}
	turn->update(sw); // 0:YOU 1:PC


	// 手番表示の設定
	turn->update(board->getTurn()); // 0:YOU 1:PC
// 対戦結果表示の設定(空白以外なら表示を更新して時計を停止する)
	if (board->getResult() != 0) {
		result->update(board->getResult()); // 0:空白 1:勝ち 2:負け 3:引分け
		if (board->getResult() == 1) {
			battleRecord->win();
		}
		else if(board->getResult()==2){
			battleRecord->lose();
		}
		else if(board->getResult()==3){

		}
		time->stop();
		battleRecord->stop();
	}
	// 盤面の更新
	board->update();
}

// ゲーム画面の出力
void GameManager::output()
{
	// 背景画面の描画
	DrawGraph(0, 0, imgTitle, FALSE);

	//nt coler = (0, 0, 0);

	//DrawBox(0, 0, 800, 600, coler, TRUE);

	// 経過時間の描画
	time->draw();

	// ボタンの描画
	start->draw();
	end->draw();

	// 手番表示
	turn->draw();

	// 対戦結果表示
	result->draw();

	// 戦績表示
	battleRecord->draw();

	// 盤面表示
	board->draw();

}