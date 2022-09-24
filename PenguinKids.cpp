#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"

//プロトタイプ宣言
//void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

PenguinKids::PenguinKids() {//皇帝のコンストラクタ
}

PenguinKids::~PenguinKids() {
}

int PenguinKids::setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, GameManager* gameBuf) {
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
	troopNum = 0;
	troopMemberNum = 0;
	defensePower = 30;
	attackPower = 30;
	num = gameBuf->mobNum;
	
	return 0;
}

int PenguinKids::selectAction(GameManager* gameBuf) {
	return 0;
}