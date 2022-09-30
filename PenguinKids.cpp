#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"

//プロトタイプ宣言
//void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

PenguinKids::PenguinKids() {//皇帝のコンストラクタ
}

PenguinKids::PenguinKids(GameManager* battle) {//皇帝のコンストラクタ
	gameBuf = battle;
}

PenguinKids::~PenguinKids() {
}

int PenguinKids::setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed) {
	team = ParentTeam;
	if (team == red) {
		name = "赤クローン";
	}
	else if (team == blue) {
		name = "青クローン";
	}
	SETdirection(DirectionX, DirectionY);
	x = ix;
	y = iy;
	speed = parentSpeed;
	HP_Limit = 50;
	HP = 50;
	defensePower = 30;
	attackPower = 30;
	num = gameBuf->mobNum;
	fishingTurn = 0;
	stamina = 10;
	
	return 0;
}

int PenguinKids::selectAction() {
	gameBuf->camera->markX = x;
	gameBuf->camera->markY = y;
	int actFlag = 0;
	
	if (item == nullptr) {
		actFlag = fishingItem();
	}
	if (actFlag == 0) {
		actFlag = attack();
	}
	if (item != nullptr) {
		if (HP_Limit - HP > item->recoverPower && item->recoverPower >0) {//所持アイテムの回復力が0以上で、蓄積ダメージがアイテムによる回復量を上回っている場合
			HP += item->recoverPower;
			gameBuf->camera->actionMsg += "\n" + item->name + "を食べた。";
			item = nullptr;
		}
	}
	
	
	//deliverItem();

	

	return actFlag;
}

int PenguinKids::attack() {

	int cx = 0;
	int cy = 0;
	int dx = 0;
	int dy = 0;
	int directRandom = 0;
	int diCheck[4] = {0,1,2,3};

	for (int i = 0; i < 4; i++) {
		int reorganize = GetRand(3-i)+i;
		int exchange = diCheck[i];
		diCheck[i] = diCheck[reorganize];
		diCheck[reorganize] = exchange;
	}
	for (int i = 0; i < 4; i++) {
		if (diCheck[i] == 0) {
			dx = 1;
			dy = 0;
		}
		if (diCheck[i] == 1) {
			dx = -1;
			dy = 0;
		}
		if (diCheck[i] == 2) {
			dx = 0;
			dy = 1;
		}
		if (diCheck[i] == 3) {
			dx = 0;
			dy = -1;
		}

		cx = x + dx;
		cy = y + dy;
		if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//マスの中で対象マスに生物が居たら。

			if (gameBuf->board.at(cx).at(cy).creature != nullptr) {
				if (gameBuf->board.at(cx).at(cy).creature->team != team) {//味方でなければ殴打。

					gameBuf->board.at(cx).at(cy).creature->HP -= 5 * attackPower / gameBuf->board.at(cx).at(cy).creature->defensePower;
					/*if (gameBuf->board.at(cx).at(cy).creature->HP <= 0) {
						gameBuf->board.at(cx).at(cy).creature->HP = 0;
					}*/
					//if (HP <= 0) {
					//	gameBuf->board.at(cx).at(cy).creature->num = -1;//numが-1なのは死んだキャラの証。
					//	gameBuf->board.at(cx).at(cy).creature = nullptr;
					//}
					if (gameBuf->board.at(cx).at(cy).creature->HP <= 0) {
						gameBuf->board.at(cx).at(cy).creature->HP = 0;
						gameBuf->board.at(cx).at(cy).creature->num = -1;//numが-1なのは死んだキャラの証。
						gameBuf->board.at(cx).at(cy).creature = nullptr;
					}

					gameBuf->camera->actionMsg = std::to_string(num) +"番の" + name + " X:" + std::to_string(x) + " Y:" + std::to_string(y) + "は攻撃した！";
					SETdirection(dx, dy);
					return 1;
				}
			}
		}	
	}
	return 0;
	
}



int PenguinKids::requestItem(int type, int x, int y) {
	return 0;
};

int PenguinKids::deliverItem() {
	return 0;
};

int PenguinKids::fishingItem() {
	int cx = 0;
	int cy = 0;
	int dx = 0;
	int dy = 0;
	int directRandom = 0;
	int diCheck[4] = { 0,1,2,3 };

	for (int i = 0; i < 4; i++) {
		int reorganize = GetRand(3 - i) + i;
		int exchange = diCheck[i];
		diCheck[i] = diCheck[reorganize];
		diCheck[reorganize] = exchange;
	}
	for (int i = 0; i < 4; i++) {
		if (diCheck[i] == 0) {
			dx = 1;
			dy = 0;
		}
		if (diCheck[i] == 1) {
			dx = -1;
			dy = 0;
		}
		if (diCheck[i] == 2) {
			dx = 0;
			dy = 1;
		}
		if (diCheck[i] == 3) {
			dx = 0;
			dy = -1;
		}

		cx = x + dx;
		cy = y + dy;
		if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//マスの中で対象マスに生物がいなければ
			if (gameBuf->board.at(cx).at(cy).creature == nullptr) {

				SETdirection(dx, dy);

				//fishingTurn += GetRand(2) + 1;
				//if (fishingTurn >= 3) {

					if (GetRand(5) % 5 == 0) {//レアな魚
						item = make_shared<Fish1>(Fish1());
						gameBuf->camera->actionMsg = item->name + "が釣れた！";
					}
					else {
						item = make_shared<Fish1>(Fish1());
						gameBuf->camera->actionMsg = item->name + "が釣れた！";
					}

					fishingTurn = 0;
					
				//}
				/*else {
					gameBuf->camera->actionMsg = name + "は、釣りをしている。";
				}*/
				return 1;
			}
		}
	}//全ての方向がふさがっていたら
	if (HP < HP_Limit / 2) {
		requestItem(0,x,y);//回復アイテムを周囲に要求
	}



	return 0;
};