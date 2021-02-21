#include "Board.h"
// コンストラクタ
Board::Board(const int x, const int y, const int img1, const int img2)
{
	// 表示位置
	posX = x;
	posY = y;
	// 画像番号
	imgBlack = img1;
	imgWhite = img2;
	// 最初の手番設定
	turn = 0; // 0:YOU 1:PC
	// 勝敗
	result = 0;
	// マウス操作
	boardX = 0;
	boardY = 0;
	boardcheck = 0;
	isMouseOver = false;
	isMouseClick = false;
	// 盤面テーブルの初期化
	tblClear();
	// ゲームスタート
	isStart = false;
}

// 更新
void Board::update()
{
	int x, y;
	if (!isStart) return;
	// YOU の手番
	if (turn == 0) {
		// マウスの位置を取得
		GetMousePoint(&x, &y);

		if(x>=320&&y>=100){
			boardX = (x - posX) / 160 + 1;
			boardY = (y - posY) / 160 + 1;

		}
		else {
			boardX = 0;
			boardY = 0;
		}
		// マウスが盤面の上かを調べる
		if ((boardX >= 1 && boardX <= 3) && (boardY >= 1 && boardY <= 3)) {
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
		// クリックでなおかつ空いているマスなら指定位置に石を設定
		if (isMouseClick) {
			if (tbl[boardY][boardX] == 0) {
				setStone(boardX, boardY);

				// 勝敗判定
				if (check(boardX, boardY)) {
					result = 1; // YOU の勝ち
					stop();
				}
				else if (boardcheck==9&&check(boardX,boardY)==false) {
					result = 3;
					stop();
				}
				else
				{
					turn = 1; // 手番を PC にする
				}
				
			}
			isMouseClick = false;
		}
	}
	else {
		// PC の手番

		// 指し手を決める
		searchMove(&boardX, &boardY);

		// 指定位置に石を設定
		if (tbl[boardY][boardX] == 0) {
			setStone(boardX, boardY);
			// 勝敗判定
			if (check(boardX, boardY)) {
				result = 2; // PC の勝ち
				stop();
			}
			else if (boardcheck == 9 && check(boardX, boardY) == false) {
				result = 3;
				stop();
			}
			else {
				turn = 0; // 手番を YOU にする
			}
		}
	}
}

// 指し手の評価と検索
void Board::searchMove(int* px, int* py)
{
	// 評価テーブルの作成
	int searchTbl[4][4];
	// 評価テーブルの初期化と評価を行う
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			// 壁ならば-99 を設定
			if (tbl[y][x] == -1) {
				searchTbl[y][x] = -99;
			}
			else if (tbl[y][x] != 0) {
				// 石が置かれていれば-1 を設定
				searchTbl[y][x] = -1;
			}
			else {
				searchTbl[y][x] = 0;
				// 1白石が直線上で 4 個以上なら、白石を置けば五連になり白の勝利となる
				if (
					// 上方向と下方向
					(countStone(2, x, y - 1, 0, -1) + countStone(2, x, y + 1, 0, 1)) >= 3 ||
					// 右上方向と左下方向
					(countStone(2, x + 1, y - 1, 1, -1) + countStone(2, x - 1, y + 1, -1, 1)) >= 3 ||
					// 右横方向と左横方向
					(countStone(2, x + 1, y, 1, 0) + countStone(2, x - 1, y, -1, 0)) >= 3 ||
					// 右下方向と左上方向
					(countStone(2, x + 1, y + 1, 1, 1) + countStone(2, x - 1, y - 1, -1, -1)) >= 3) {
					*px = x;
					*py = y;

					return;
				}
				// 2黒石が 4 以上になっている場所なら白石を置いて防ぐ
				if (
					// 上方向と下方向
					(countStone(1, x, y - 1, 0, -1) + countStone(1, x, y + 1, 0, 1)) >= 3 ||
					// 右上方向と左下方向
					(countStone(1, x + 1, y - 1, 1, -1) + countStone(1, x - 1, y + 1, -1, 1)) >= 3 ||
					// 右横方向と左横方向
					(countStone(1, x + 1, y, 1, 0) + countStone(1, x - 1, y, -1, 0)) >= 3 ||
					// 右下方向と左上方向
					(countStone(1, x + 1, y + 1, 1, 1) + countStone(1, x - 1, y - 1, -1, -1)) >= 3) {
					*px = x;
					*py = y;

					return;
				}
				// 3黒石が3なら白石を置いて4を防ぐ
				if (
					// 上方向と下方向
					(countStone(1, x, y - 1, 0, -1) + countStone(1, x, y + 1, 0, 1)) >= 2 ||
					// 右上方向と左下方向
					(countStone(1, x + 1, y - 1, 1, -1) + countStone(1, x - 1, y + 1, -1, 1)) >= 2 ||
					// 右横方向と左横方向
					(countStone(1, x + 1, y, 1, 0) + countStone(1, x - 1, y, -1, 0)) >= 2 ||
					// 右下方向と左上方向
					(countStone(1, x + 1, y + 1, 1, 1) + countStone(1, x - 1, y - 1, -1, -1)) >= 2) {
					*px = x;
					*py = y;
					
					return;
				}
				// 4白石が3なら4にする
				if (
					// 上方向と下方向
					(countStone(2, x, y - 1, 0, -1) + countStone(2, x, y + 1, 0, 1)) >= 2 ||
					// 右上方向と左下方向
					(countStone(2, x + 1, y - 1, 1, -1) + countStone(2, x - 1, y + 1, -1, 1)) >= 2 ||
					// 右横方向と左横方向
					(countStone(2, x + 1, y, 1, 0) + countStone(2, x - 1, y, -1, 0)) >= 2 ||
					// 右下方向と左上方向
					(countStone(2, x + 1, y + 1, 1, 1) + countStone(2, x - 1, y - 1, -1, -1)) >= 2) {
					*px = x;
					*py = y;
					
					return;
				}
				// 5上記以外なら周辺の石の数を数える
				// 上方向
				searchTbl[y][x] += countStone(1, x, y - 1, 0, -1);
				// 下方向
				searchTbl[y][x] += countStone(1, x, y + 1, 0, 1);
				// 右上方向
				searchTbl[y][x] += countStone(1, x + 1, y - 1, 1, -1);
				// 左下方向
				searchTbl[y][x] += countStone(1, x - 1, y + 1, -1, 1);
				// 右横方向
				searchTbl[y][x] += countStone(1, x + 1, y, 1, 0);
				// 左横方向
				searchTbl[y][x] += countStone(1, x - 1, y, -1, 0);
				// 右下方向
				searchTbl[y][x] += countStone(1, x + 1, y + 1, 1, 1);
				// 左上方向
				searchTbl[y][x] += countStone(1, x - 1, y - 1, -1, -1);
			}
		}
	}
	// 評価テーブルの中で最も大きな値が格納されている行列番号を求める
	int max = 0;
	// 評価テーブルの初期化と評価を行う
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (max < searchTbl[y][x]) {
				*px = x;
				*py = y;
				max = searchTbl[y][x];
			}
			
		}

	}
}

// 描画
void Board::draw()
{
	// 盤面の描画
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (tbl[y][x] == 1) {
				//DrawGraph(posX + (x - 1) * 6, posY + (y - 1) * 6, imgBlack, TRUE);
				DrawExtendGraph(posX + (x - 1) * 160, posY + (y - 1) * 160, posX + (x - 1) * 160 + 160, posY + (y - 1) * 160 + 160, imgBlack, TRUE);
			}
			if (tbl[y][x] == 2) {
				DrawExtendGraph(posX + (x - 1) * 160, posY + (y - 1) * 160, posX + (x - 1) * 160 + 160, posY + (y - 1) * 160 + 160, imgWhite, TRUE);
				//DrawGraph(posX + (x - 1) * 6, posY + (y - 1) * 6, imgWhite,					TRUE);

			}
		}
	}
	// マウスオーバーの位置を描画
	if (isMouseOver) {
		int x = posX + (boardX - 1) * 160 ;
		int y = posY + (boardY - 1) * 160 ;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(x, y, x + 160, y + 160, GetColor(255, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

// ゲームスタート
void Board::start()
{
	if (!isStart) {
		isStart = true;
		tblClear();

		// 最初の手番設定
		turn = 0; // 0:YOU 1:PC
		// 勝敗
		result = 0;
	}
}
// ゲームストップ
void Board::stop()
{
	if (isStart) {
		isStart = false;
	}
}
// 盤面のクリア
void Board::tblClear()
{
	// 盤面のクリア
	for (int y = 0; y < 4+1; y++) {
		for (int x = 0; x < 4+1; x++) {
			tbl[y][x] = 0;
			if (y == 0 || x == 0 || y == 4 || x == 4) {
				tbl[y][x] = -1;
			}
		}
	}
}
// 石の設定
void Board::setStone(int x, int y)
{
	if ((x < 1 || x > 3) || (y < 0 || y > 3)) return;
	if (turn == 0) {
		tbl[y][x] = 1;
	}
	else {
		tbl[y][x] = 2;
	}
}

// ゲーム終了判定
bool Board::check(int x, int y)
{
	int count;
	boardcheck = 0;
	// 上方向と下方向
	count = countStone(turn + 1, x, y, 0, -1);
	count += countStone(turn + 1, x, y + 1, 0, 1);
	if (count >= 3) return true;
	// 右上方向と左下方向
	count = countStone(turn + 1, x, y, 1, -1);
	count += countStone(turn + 1, x - 1, y + 1, -1, 1);
	if (count >= 3) return true;
	// 右横方向と左横方向
	count = countStone(turn + 1, x, y, 1, 0);
	count += countStone(turn + 1, x - 1, y, -1, 0);
	if (count >= 3) return true;
	// 右下方向と左上方向
	count = countStone(turn + 1, x, y, 1, 1);
	count += countStone(turn + 1, x - 1, y - 1, -1, -1);
	if (count >= 3) return true;

	//引き分け
	for (int y = 1; y < 4;y++) {
		for (int x = 1; x < 4; x++) {
			if (tbl[y][x] != 0) {
				boardcheck += 1;
			}
		}
	}

	printf("%d\n", boardcheck);

	return false;
}
// ゲーム結果を返す
int Board::getResult()
{
	return result;
}
// ターンを返す
int Board::getTurn()
{	return turn;
}

// 石が連続して並んでいる数を求める
int Board::countStone(int stone, int x, int y, int dx, int dy)
{
	int count;
	count = 0;
	for (int xx = x, yy = y; tbl[yy][xx] == stone; xx += dx, yy += dy) {
		count++;
	}
	return count;
}