#include "DxLib.h"
#include <iostream>
#include <string>
#include <vector>
#include "MyClasses.h"
#include "consts.h"
#include "externs.h"
#include <array>

#include <algorithm>
#include <functional>

#include <cstdlib>
#include <ctime>

using namespace std;


bool speedOrder(Creature* a, Creature* b);



GameManager::GameManager(int stageLevel, int xSize, int ySize) {//コンストラクタ。
	turnNum = 0;
	score = 0;
	gameMode = 1;
	goNextFlag = 0;

	this->sizeX = xSize;
	this->sizeY = ySize;

	camera = new Camera(this);



	/*vector<vector<Grid>> board(xSize, vector<Grid>(ySize));*/
	//board.at(xSize).at(ySize);//要素数を超えてしまわないように警告してくれる。

	for (int ix = 0; ix < xSize; ix++) {
		vector<Grid> xVec;
		for (int iy = 0; iy < ySize; iy++) {
			Grid yVec(ix,iy);
			xVec.push_back(yVec);
		}
		board.push_back(xVec);
	}

	


	


	for (int ix = 0; ix < sizeX; ix++) {//Gridの状態をセット
		for (int iy = 0; iy < sizeY; iy++) {
			board[ix][0].state = ROCK;
			board[ix][sizeY - 1].state = ROCK;
			board[0][iy].state = ROCK;
			board[sizeX - 1][iy].state = ROCK;

			board[ix][iy].x = ix;
			board[ix][iy].y = iy;
			board[ix][iy].creature = NULL;

		}
	}

	for (int i = 0; i < 1024; i++) {
		shared_ptr <PenguinKids> kid = make_shared<PenguinKids>(PenguinKids(this));
		kids[i] = *kid;
	}


	shared_ptr <Emperor> Emperor1 = make_shared<Emperor>(Emperor(this));//インスタンス化
	Emperor1->setCharacter(red, 1, 0, 5, 5, 1001);
	handledCharacters[0] = *Emperor1;
	board[Emperor1->x][Emperor1->y].creature = &handledCharacters[0];//マス目に自分のポインタを代入。

	shared_ptr <Emperor> Emperor2 = make_shared<Emperor>(Emperor(this));
	//Emperor* Emperor2 = new Emperor();//インスタンス化
	Emperor2->setCharacter(blue, 0, 1, 7, 10, 1000);
	handledCharacters[1] = *Emperor2;
	board[Emperor2->x][Emperor2->y].creature = &handledCharacters[1];

	//gameBuf = this;
}




GameManager::~GameManager() {

	//for (int xi = 0; xi < sizeX; xi++) {//マス目を消す
	//	delete[] board[xi];
	//}
	//delete[] board;
	//delete Emperor1;
	//delete Emperor2;

};




int GameManager::BattleMode(GameManager* gameBuf) {

	if(gameMode == 1) {

		if (goNextFlag == 1) {
			GoNext(gameBuf);
			return 0;
		}
		else {








			if (rutine == 0) {
				if (moveCount >= 0 && moveCount < moveCharaNumber) {//エンペラーの数だけ実行
					if (handledCharacters[moveCount].HP > 0) {
						camera->actingX = handledCharacters[moveCount].x;
						camera->actingY = handledCharacters[moveCount].y;
						if (handledCharacters[moveCount].selectAction() == 1) {//行動終了である1が帰ってきたら次キャラへ
							moveCount++;
						};
					}
				}
				else {//エンペラーの数の分だけ繰り返したら,次からはrutine2のフェーズの各モブを動かしていく。
					moveCount = 0;
					rutine = 1;
				}
			}

			if (rutine == 1) {
				for (int i = 0; i < mobNum; i++) {//いったん代入する。
					if (kids[i].num >= 0) {//numがマイナス、つまり死後のキャラを除く。
						mobsSpeedOrder.push_back(&kids[i]);
					}
				}
				sort(mobsSpeedOrder.begin(), mobsSpeedOrder.end(), speedOrder);//mobの素早さ配列を完成させる。
				rutine = 2;
			}

			if (rutine == 2) {
				if (mobCount >= 0 && mobCount < mobsSpeedOrder.size()) {

					int actFlag = 0;


					//while (true) {
						actFlag = mobsSpeedOrder.at(mobCount)->selectAction();
						mobCount++;
						if (actFlag == 1) {
							goNextFlag = 1;
							//break;
						}
						if (mobCount == mobsSpeedOrder.size()) {
							//break;
						}
					//}

					//actFlag = ActMobs(gameBuf);//モブカウントの増加はこの関数の中で行われている。
					//if (actFlag = 1) {//行動したモブがいたら
					//	
					//}
				}
				else {//mob達全員が行動を完了したら
					turnNum++;
					mobCount = 0;
					rutine = 3;
					camera->actionMsg = "次のターン(" + std::to_string(turnNum) + ")へ進みます。";
				}
			}
			if (rutine == 3) {
				if (GoNext(gameBuf) == 0) {
					rutine = 0;
				}
			}


			camera->moveCamera(0, 0, FALSE);





			//if (rutine == 3) {
			//	GrowCrop();
			//	rutine = 4;
			//}

			//if (rutine == 4){
			//	if (GoNext(0, 0, FALSE == TRUE)) {
			//		moveCount = 4;//植物が成長して、それを確認するGoNextがTrueになってから
			//	}
			//}
		}
	}

	if (gameMode == 2) {//勝利判定とエンディング
		return 0;
	}

	camera->exhibitScreen(0, 0, FALSE);

	return 0;
}




// keyBuf[KEY_INPUT_SPACE]

int GameManager::GoNext(GameManager* gameBuf) {

	if (returnKey[1] == 1) {
		goNextFlag = 0;//フラグが降りる。
		return 0;//goNextFlagにこれが代入されて、永遠にGoNextが呼ばれ続ける状態が解除される。
	}
	else {
		return 1;
	}
}


int GameManager::GameOver(GameManager* gameBuf) {
	return 0;
}

int GameManager::GameClear(GameManager* gameBuf) {
	return 0;
}



//int GameManager::ActMobs(GameManager* gameBuf) {原因不明の例外が発生する悪魔の関数
//	if (mobCount >= 0 && mobCount < mobNum) {//モブカウントがモブの数より小さい間
//		int mobAct = 0;
//		mobAct = mobsSpeedOrder[mobCount]->selectAction();
//		mobCount++;
//		if (mobAct == 0) {//行動が発生しなかった場合
//			return 0;
//			if (mobCount >= 0 && mobCount < mobNum) {
//				return ActMobs(gameBuf);//最終的に行動するモブがいたら、1が返され続けて最後1が返る。
//			}
//		}
//		if (mobAct == 1) {//行動が発生してそれを表示しGoNextで待機する必要がある場合
//			camera->actingX = mobsSpeedOrder[mobCount]->x;
//			camera->actingY = mobsSpeedOrder[mobCount]->y;
//			goNextFlag = 1;
//			return 1;
//
//		}
//	}
//	return 0;
//}

int GameManager::FinishGame(GameManager* gameBuf) {
	return 0;
}





bool speedOrder(Creature* a, Creature* b) {

	if (a->speed == NULL) {
		a->speed = -1;
	}
	if (b->speed == NULL) {
		b->speed = -1;
	}
	return a->speed > b->speed;
}