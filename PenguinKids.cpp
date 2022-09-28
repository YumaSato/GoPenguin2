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
	speed = parentSpeed;
	HP_Limit = 50;
	HP = 50;
	defensePower = 30;
	attackPower = 30;
	num = gameBuf->mobNum;
	fishingTurn = 0;
	
	return 0;
}

int PenguinKids::selectAction() {
	int actFlag = 0;
	actFlag = attack();
	//deliverItem(gameBuf);
	return actFlag;
}

int PenguinKids::attack() {
	int cx = 0;
	int cy = 0;
	cx = x + directionX;
	cy = y + directionY;
	if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//マスの中で対象マスに生物が居たら。

		//if (gameBuf->board.at(cx).at(cy).creature != NULL) {
		//	if (gameBuf->board.at(cx).at(cy).creature->team != team) {//味方でなければ殴打。

		//		gameBuf->board.at(cx).at(cy).creature->HP -= 8 * attackPower / gameBuf->board.at(cx).at(cy).creature->defensePower;
		//		if (gameBuf->board.at(cx).at(cy).creature->HP <= 0) {
		//			gameBuf->board.at(cx).at(cy).creature->HP = 0;
		//			gameBuf->board.at(cx).at(cy).creature->num = -1;//numが-1なのは死んだキャラの証。
		//			gameBuf->board.at(cx).at(cy).creature = NULL;
		//		}
		//		gameBuf->camera->actionMsg = name + "は攻撃した！";
		//		return 1;
		//	}
		//}
	}
	return 0;
}



int PenguinKids::requestItem(int itemNum, int x, int y) {
	return 0;
};

int PenguinKids::deliverItem() {
	return 0;
};

int PenguinKids::fishingItem() {
	fishingTurn += GetRand(2) + 1;
	if (fishingTurn >= 3) {
		
		if (GetRand(5) % 5 == 0) {
			item = make_shared<Fish2>(Fish2());
		}
		else {
			item = make_shared<Fish1>(Fish1());
		}
		
		fishingTurn = 0;
		return 0;
	}
};