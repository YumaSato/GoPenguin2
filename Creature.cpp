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
	memset(&this->num, NULL, sizeof(this->num));

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


int Creature::setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, GameManager* gameBuf) {
	return 0;
}

int Creature::selectAction(GameManager* gameBuf) {
	return 0;
}

int Creature::walk(GameManager* gameBuf) {
	return 0;
}


int Creature::changeDirection(GameManager* gameBuf) {
	return 0;
}

int Creature::attack(GameManager* gameBuf) {
	return 0;
}

int Creature::setKids(GameManager* gameBuf) {
	return 0;
}

int Creature::castKids(GameManager* gameBuf) {
	return 0;
}

int Creature::useItem(GameManager* gameBuf) {
	return 0;
};

int Creature::castItem(GameManager* gameBuf) {
	return 0;
};

int Creature::requestItem(int itemNum, int x, int y, GameManager* gameBuf) {
	return 0;
};

int Creature::deliverItem(GameManager* gameBuf) {
	return 0;
};
int Creature::fishingItem(GameManager* gameBuf) {
	return 0;
}



int Creature::killed(GameManager* gameBuf) {//指定地点に生物がいる前提。攻撃の内容を実行。
	
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




