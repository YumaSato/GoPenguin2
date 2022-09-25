#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"

//�v���g�^�C�v�錾
//void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

PenguinKids::PenguinKids() {//�c��̃R���X�g���N�^
}

PenguinKids::~PenguinKids() {
}

int PenguinKids::setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, GameManager* gameBuf) {
	team = ParentTeam;
	if (team == red) {
		name = "�ԃN���[��";
	}
	else if (team == blue) {
		name = "�N���[��";
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

int PenguinKids::selectAction(GameManager* gameBuf) {
	int actFlag = 0;
	actFlag = attack(gameBuf);
	return actFlag;
}

int PenguinKids::attack(GameManager* gameBuf) {
	int cx = 0;
	int cy = 0;
	cx = x + directionX;
	cy = y + directionY;
	if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//�}�X�̒��őΏۃ}�X�ɐ�����������B
		if (gameBuf->board.at(cx).at(cy).creature != nullptr) {
			if (gameBuf->board.at(cx).at(cy).creature->team != team) {//�����łȂ���Ή��ŁB

				gameBuf->board.at(cx).at(cy).creature->HP -= 8 * attackPower / gameBuf->board.at(cx).at(cy).creature->defensePower;
				if (gameBuf->board.at(cx).at(cy).creature->HP <= 0) {
					gameBuf->board.at(cx).at(cy).creature->HP = 0;
					gameBuf->board.at(cx).at(cy).creature->num = -1;//num��-1�Ȃ͎̂��񂾃L�����̏؁B
					gameBuf->board.at(cx).at(cy).creature = nullptr;
				}
				gameBuf->camera->actionMsg = name + "�͍U�������I";
				return 1;
			}
		}
	}

	return 0;
}



int PenguinKids::requestItem(int itemNum, int x, int y, GameManager* gameBuf) {
	return 0;
};

int PenguinKids::deliverItem(GameManager* gameBuf) {
	return 0;
};

int PenguinKids::fishingItem(GameManager* gameBuf) {
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