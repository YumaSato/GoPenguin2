#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"

//�v���g�^�C�v�錾
//void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

Emperor::Emperor() {//�c��̃R���X�g���N�^

}

Emperor::~Emperor() {

}


int Emperor::setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, GameManager* gameBuf) {
	status = EMPEROR;//�X�e�[�^�X���u�c��v���Ӗ�����4�ɕύX
	team = ParentTeam;

	giveExpPoint = 1500;

	if (ParentTeam == red) {//�ԃ`�[��(=1)�̍c��ł���ΐԍc���Ֆʏ㕔�ɃX�|�[��
		this->name = "�ԍc��";
		this->num = 0;
	}
	else if (ParentTeam == blue) {//�`�[��(=2)�̍c��ł���ΐc���Ֆʉ����ɃX�|�[��
		this->name = "�c��";
		this->num = 1;
	}

	this->speed = parentSpeed;
	this->x = ix;
	this->y = iy;
	SETdirection(DirectionX, DirectionY);
	this->status = EMPEROR;
	this->HP = 50;
	this->HP_Limit = 50;
	this->attackPower = 30;
	this->defensePower = 45;
	this->staminaRecoverAbility = 10;//���^�[���񕜂���X�^�~�i
	this->staminaLimit = 15;
	this->stamina = 15;

	return 0;
}


int Emperor::selectAction(GameManager* gameBuf) {

	bool finishFlag = false;

	gameBuf->camera->actionMsg = name + "�͉�������H";
	
	gameBuf->camera->actionMsg = "left0:" + std::to_string(leftKey[0]) + "   left1:" + std::to_string(leftKey[1]) + "  up0:" + std::to_string(upKey[0]) + "  up1:" + std::to_string(upKey[1]) + "\nright0:" + std::to_string(rightKey[0]) + "  right1:" + std::to_string(rightKey[1]) + "  down0:" + std::to_string(downKey[0]) + "  down1:" + std::to_string(downKey[1]) + "\nSHIFT:" + std::to_string(shiftKey[0]) + "  SPACE:" + std::to_string(spaceKey[0]) + "  Z:" + std::to_string(zKey[0]) + "\nnum1:" + std::to_string(numKey[1][0]) + "  num2:" + std::to_string(numKey[2][0]);

	changeDirection(gameBuf);

	if ( stamina > 0 ) {
		walk(gameBuf);
	}

	if (numKey[1][1] == 1) {
		finishFlag = setKids(gameBuf);
	}
	if (numKey[2][1] == 1) {
		finishFlag = castKids(gameBuf);
	}
	if (numKey[3][1] == 1) {
		finishFlag = attack(gameBuf);
	}


	if ( returnKey[1] == 1 || finishFlag == true) {
		stamina += staminaRecoverAbility;
		if (stamina > staminaLimit) {
			stamina = staminaLimit;
		}
		return 1;
	}
	return 0;
}


int Emperor::walk(GameManager* gameBuf) {
	if (shiftKey[0] == 0) {
		//gameBuf->camera->mainMsg = "���s�\���L�[�ҋ@";
		if (changeDirection(gameBuf) == 1) {//�����{�^���������ꂽ��
			int cx = x;
			int cy = y;
			int dx = 0;
			int dy = 0;
			GETdirectionXY(&dx, &dy);
			cx += dx;
			cy += dy;

			if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//��Q�����Ȃ���ΐi�ށB
				if (gameBuf->board.at(cx).at(cy).creature == nullptr) {
					gameBuf->board.at(x).at(y).creature = nullptr;
					x = cx;
					y = cy;
					gameBuf->board.at(cx).at(cy).creature = this;
					stamina--;
					return 1;
				}
			}
		}
	}
	return 0;

}
//|| (rightKey[0] == 1 && upKey[0] == 1)
// || (rightKey[0] == 1 && downKey[0] == 1)
// || (leftKey[0] == 1 && downKey[0] == 1)

int Emperor::changeDirection(GameManager* gameBuf) {
	//bool diagonal = false;

	if (CheckHitKey(KEY_INPUT_Z) == 1) {
		if (leftKey[0] == 1) {
			if (upKey[1] == 1) {
				SETdirection(NW);
				return 1;
			}
			if (downKey[1] == 1) {
				SETdirection(SW);
				return 1;
			}
		}
		if (rightKey[0] == 1) {
			if (upKey[1] == 1) {
				SETdirection(NE);
				return 1;
			}
			if (downKey[1] == 1) {
				SETdirection(SE);
				return 1;
			}
		}
		if (upKey[0] == 1) {
			if (leftKey[1] == 1) {
				SETdirection(NW);
				return 1;
			}
			if (rightKey[1] == 1) {
				SETdirection(NE);
				return 1;
			}
		}
		if (downKey[0] == 1) {
			if (leftKey[1] == 1) {
				SETdirection(SW);
				return 1;
			}
			if (rightKey[1] == 1) {
				SETdirection(SE);
				return 1;
			}
		}
	}
	else {
		if (leftKey[1] == 1) {
			SETdirection(WW);
			return 1;
		}
		if (rightKey[1] == 1) {
			SETdirection(EE);
			return 1;
		}
		if (upKey[1] == 1) {
			SETdirection(NN);
			return 1;
		}
		if (downKey[1] == 1) {
			SETdirection(SS);
			return 1;
		}
	}




	//if (CheckHitKey(KEY_INPUT_SPACE == TRUE)) {
		//if (CheckHitKey(KEY_INPUT_UP) == TRUE) {//�΂ߏ㑤

	//if (CheckHitKey(KEY_INPUT_LEFT) == FALSE && CheckHitKey(KEY_INPUT_RIGHT) == FALSE && CheckHitKey(KEY_INPUT_UP) == FALSE && CheckHitKey(KEY_INPUT_DOWN) == FALSE) {
	//	pushingKey = 0;
	//}

	//if (spaceKey[0] == 1) {
	//	if (CheckHitKey(KEY_INPUT_LEFT) == TRUE && CheckHitKey(KEY_INPUT_UP) == TRUE && pushingKey == 0) {
	//		SETdirection(NW);
	//		pushingKey = 1;
	//		return 1;
	//	}
	//	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE && CheckHitKey(KEY_INPUT_UP) == TRUE && pushingKey == 0) {
	//		SETdirection(NE);
	//		pushingKey = 1;
	//		return 1;
	//	}
	//	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE && CheckHitKey(KEY_INPUT_DOWN) == TRUE && pushingKey == 0) {
	//		SETdirection(SE);
	//		pushingKey = 1;
	//		return 1;
	//	}
	//	if (CheckHitKey(KEY_INPUT_LEFT) == TRUE && CheckHitKey(KEY_INPUT_DOWN) == TRUE && pushingKey == 0) {
	//		SETdirection(SW);
	//		pushingKey = 1;
	//		return 1;
	//	}
	//}

	////}


	//if (CheckHitKey(KEY_INPUT_SPACE) == FALSE) {
	//	if (CheckHitKey(KEY_INPUT_UP) == TRUE  && pushingKey == 0) {
	//		SETdirection(NN);
	//		pushingKey = 1;
	//		return 1;
	//	}
	//	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE && pushingKey == 0) {
	//		SETdirection(EE);
	//		pushingKey = 1;
	//		return 1;
	//	}
	//	if (CheckHitKey(KEY_INPUT_DOWN) == TRUE && pushingKey == 0) {
	//		SETdirection(SS);
	//		pushingKey = 1;
	//		return 1;
	//	}
	//	if (CheckHitKey(KEY_INPUT_LEFT) == TRUE && pushingKey == 0) {
	//		SETdirection(WW);
	//		pushingKey = 1;
	//		return 1;
	//	}
	//}
	return 0;
}


int Emperor::attack(GameManager* gameBuf) {
	int cx = 0;
	int cy = 0;
	cx = x + directionX;
	cy = y + directionY;
	if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//�}�X�̒��őΏۃ}�X�ɐ�����������B
		if (gameBuf->board.at(cx).at(cy).creature != nullptr) {
			
			//int damageHP = 0;
			//damageHP = 8 * attackPower / gameBuf->board[cx][cy].creature->defensePower;
			//gameBuf->board.at(cx).at(cy).creature->HP -= 8 * attackPower / gameBuf->board[cx][cy].creature->defensePower;

			gameBuf->board.at(cx).at(cy).creature->HP -= 8 * attackPower / gameBuf->board.at(cx).at(cy).creature->defensePower;
			if (gameBuf->board.at(cx).at(cy).creature->HP <= 0) {
				gameBuf->board.at(cx).at(cy).creature->HP = 0;
				gameBuf->board.at(cx).at(cy).creature->num = -1;//num��-1�Ȃ͎̂��񂾃L�����̏؁B
				gameBuf->board.at(cx).at(cy).creature = nullptr;
			}

			return 1;
		}
	}

	return 0;
}

int Emperor::setKids(GameManager* gameBuf) {
	int cx = 0;
	int cy = 0;
	cx = x + directionX;
	cy = y + directionY;
	if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//��Q�����Ȃ���ΐݒu�B
		if (gameBuf->board.at(cx).at(cy).creature == nullptr) {

			//PenguinKids kid = PenguinKids();
			
			shared_ptr <PenguinKids> kid = make_shared<PenguinKids>(PenguinKids());

			gameBuf->kids[gameBuf->mobNum] = *kid;
			gameBuf->kids[gameBuf->mobNum].setCharacter(team, directionX, directionY, cx, cy, speed, gameBuf);
			gameBuf->board.at(cx).at(cy).creature = &gameBuf->kids[gameBuf->mobNum];
			gameBuf->mobNum++;

			return 1;
		}
	}
	return 0;
}

int Emperor::castKids(GameManager* gameBuf) {
	return 0;
}

int Emperor::useItem(GameManager* gameBuf) {
	return 0;
}

int Emperor::castItem(GameManager* gameBuf) {
	return 0;
}