#include <string>
#include "DxLib.h"
#include "MyClasses.h"

using std::string;

Direction GETdirectionBYxy(int x, int y);
void GETxyBYdirection(int* x, int* y, Direction drctn);

Creature::Creature() {//コンストラクタ。チームと位置を受け取る。
	memset(&this->team, NULL, sizeof(this->team));//teamとstatusはintではなくenum型であるからNULLを代入できない。
	memset(&this->status, NULL, sizeof(this->status));//だからmemsetでteamのサイズ分の指定バイト数をNULLで埋めてる。
	memset(&this->directionX, NULL, sizeof(this->directionX));
	memset(&this->directionY, NULL, sizeof(this->directionY));
	memset(&this->x, NULL, sizeof(this->x));
	memset(&this->y, NULL, sizeof(this->y));
	memset(&this->HP, NULL, sizeof(this->HP));
	memset(&this->HP_Limit, NULL, sizeof(this->HP_Limit));
	memset(&this->attackPower, NULL, sizeof(this->attackPower));
	memset(&this->defensePower, NULL, sizeof(this->defensePower));
	memset(&this->speed, NULL, sizeof(this->speed));
	memset(&this->staminaRecoverAbility, NULL, sizeof(this->staminaRecoverAbility));
	//memset(&this->num, NULL, sizeof(this->num));

	num = -1;
	item = nullptr;
	name = "Somebody";
	giveExpPoint = 0;
	walking = 0;
	skip = FALSE;

	//this->team = NULL;
	//this->status = NULL;
	//this->directionX = NULL;
	//this->directionY = NULL;
	//this->x = NULL;
	//this->y = NULL;
	//this->HP = NULL;
	//this->HP_Limit = NULL;
	//this->stamina = NULL;
	//this->staminaLimit = NULL;
	//this->attackPower = NULL;
	//this->defensePower = NULL;
	//this->speed = NULL;
	//this->staminaRecoverAbility = NULL;
	//this->num = NULL;
}

Creature::~Creature() {
}


int Creature::setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed) {
	return 0;
}

int Creature::selectAction() {
	return 0;
}

int Creature::walk() {
	return 0;
}


int Creature::changeDirection() {
	return 0;
}

int Creature::attack() {
	return 0;
}

int Creature::setKids() {
	return 0;
}

int Creature::castKids() {
	return 0;
}

int Creature::useItem() {
	return 0;
};

int Creature::castItem() {
	return 0;
};

shared_ptr<Item> Creature::requestItem(int type, vector<Creature*> confirmed) {

	int cx = 0;
	int cy = 0;
	int dx = 0;
	int dy = 0;
	int directRandom = 0;
	int diCheck[4] = { 0,1,2,3 };
	bool throughFlag = false;

	for (int i = 0; i < 4; i++) {
		int reorganize = GetRand(3 - i) + i;
		int exchange = diCheck[i];
		diCheck[i] = diCheck[reorganize];
		diCheck[reorganize] = exchange;
	}
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 4; i++) {
			throughFlag = false;
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
			for (int cNum = 0; cNum < confirmed.size(); cNum++) {
				if (cx == confirmed.at(cNum)->x && cy == confirmed.at(cNum)->y) {//依頼主の方向は無視する。
					throughFlag = true;
				}
			}
			if (throughFlag == true) {
				continue;
			}

			if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//マスの中で対象マスに生物がいれば
				if (gameBuf->board.at(cx).at(cy).creature != nullptr) {

					if (gameBuf->board.at(cx).at(cy).creature->team == team && gameBuf->board.at(cx).at(cy).creature->status == NORMAL) {
						if (j == 0) {
							if (gameBuf->board.at(cx).at(cy).creature->item != nullptr) {
								if (gameBuf->board.at(cx).at(cy).creature->item->itemType == type) {//リクエストされたアイテムが発見されたら
									shared_ptr<Item> buf = gameBuf->board.at(cx).at(cy).creature->item;
									gameBuf->board.at(cx).at(cy).creature->item = nullptr;
									return buf;
								}
								//アイテムが見つかったのでreturn
							}

						}
						if (j == 1) {

							shared_ptr<Item> itemBuf = nullptr;
							PenguinKids* kidsBuf = static_cast<PenguinKids*>(gameBuf->board.at(cx).at(cy).creature);
							confirmed.push_back(kidsBuf);//もうすでに調べたからループさせないために調査対象除外リスト配列に、次のリクエスト主体をぶち込む。
							itemBuf = kidsBuf->requestItem(type, confirmed);
							if (itemBuf != nullptr) {//何かしらのアイテムが返ってきてたらreturnする
								return itemBuf;
							}
						}
					}

				}
			}
		}

	}
	return nullptr;
};

int Creature::deliverItem() {
	return 0;
};

int Creature::fishingItem() {
	return 0;
}



int Creature::killed() {//指定地点に生物がいる前提。攻撃の内容を実行。
	
	return 0;
}




void Creature::SETdirection(int xward, int yward) {
	this->directionX = xward;
	this->directionY = yward;
	this->compass = GETdirectionBYxy(xward, yward);
}

void Creature::SETdirection(Direction compass) {
	int tmp_x, tmp_y;
	GETxyBYdirection(&tmp_x, &tmp_y, compass);

	this->directionX = tmp_x;
	this->directionY = tmp_y;
	this->compass = compass;
}

void Creature::GETdirectionXY(int* xward, int* yward) {//方向の値を代入する変数のアドレスを受け取る
	*xward = directionX;
	*yward = directionY;//そのアドレスの中身に方向を代入。疑似的に値を返せる。
}

Direction Creature::GETdirection() {
	return compass;
}




//void Creature::DeleteCreature() {
//	memset(&this->team, NULL, sizeof(this->team));
//	memset(&this->status, NULL, sizeof(this->status));
//	memset(&this->directionX, NULL, sizeof(this->directionX));
//	memset(&this->directionY, NULL, sizeof(this->directionY));
//	memset(&this->x, NULL, sizeof(this->x));
//	memset(&this->y, NULL, sizeof(this->y));
//	memset(&this->HP, NULL, sizeof(this->HP));
//	memset(&this->HP_Limit, NULL, sizeof(this->HP_Limit));
//	memset(&this->levelUp, NULL, sizeof(this->levelUp));
//	memset(&this->expPoint, NULL, sizeof(this->expPoint));
//	memset(&this->attackPower, NULL, sizeof(this->attackPower));
//	memset(&this->defensePower, NULL, sizeof(this->defensePower));
//	memset(&this->speed, NULL, sizeof(this->speed));
//	memset(&this->staminaRecoverAbility, NULL, sizeof(this->staminaRecoverAbility));
//	memset(&this->num, NULL, sizeof(this->num));
//
//}




