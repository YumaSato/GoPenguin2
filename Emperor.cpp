#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"

//�v���g�^�C�v�錾
//void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

Emperor::Emperor() {
	
}

Emperor::Emperor(GameManager* battle) {//�c��̃R���X�g���N�^
	gameBuf = battle;
}

Emperor::~Emperor() {

}


int Emperor::setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed) {
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
	casting = false;
	pointX = -1;
	pointY = -1;

	return 0;
}


int Emperor::selectAction() {

	bool finishFlag = false;
	

	gameBuf->camera->markX = x;
	gameBuf->camera->markY = y;

	gameBuf->camera->actionMsg = name + "�͉�������H";
	
	gameBuf->camera->actionMsg = "left0:" + std::to_string(leftKey[0]) + "   left1:" + std::to_string(leftKey[1]) + "  up0:" + std::to_string(upKey[0]) + "  up1:" + std::to_string(upKey[1]) + "\nright0:" + std::to_string(rightKey[0]) + "  right1:" + std::to_string(rightKey[1]) + "  down0:" + std::to_string(downKey[0]) + "  down1:" + std::to_string(downKey[1]) + "\nSHIFT:" + std::to_string(shiftKey[0]) + "  SPACE:" + std::to_string(spaceKey[0]) + "  Z:" + std::to_string(zKey[0]) + "\nnum1:" + std::to_string(numKey[1][0]) + "  num2:" + std::to_string(numKey[2][0]) + "\n��pointX:" + std::to_string(gameBuf->handledCharacters[1].pointX) + " Y:" + std::to_string(gameBuf->handledCharacters[1].pointY);

	

	if (casting == true) {
		finishFlag = castKids();
		if (finishFlag == false) {
			return 0;
		}
	}
	else {
		changeDirection();

		if (stamina > 0) {
			walk();
		}

		if (numKey[1][1] == 1) {
			finishFlag = setKids();
		}
		if (numKey[2][1] == 1) {
			if (casting == false) {
				castStart(1);//cast���s�����Ӗ�����casting�Ƃ�����́AcastKids���ŏ����������I���Ă���ς���
				casting = true;
			}
		}




		if (numKey[3][1] == 1) {
			finishFlag = attack();
		}

	}
	if (returnKey[1] == 1 || finishFlag == true) {
		stamina += staminaRecoverAbility;
		if (stamina > staminaLimit) {
			stamina = staminaLimit;
		}
		casting = false;
		pointX = x;
		pointY = y;
		return 1;
	}
	return 0;
}


int Emperor::walk() {
	if (shiftKey[0] == 0) {
		//gameBuf->camera->mainMsg = "���s�\���L�[�ҋ@";
		if (changeDirection() == 1) {//�����{�^���������ꂽ��
			int cx = x;
			int cy = y;
			int dx = 0;
			int dy = 0;
			GETdirectionXY(&dx, &dy);
			cx += dx;
			cy += dy;

			if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//��Q�����Ȃ���ΐi�ށB
				if (gameBuf->board.at(cx).at(cy).creature == nullptr && gameBuf->board.at(cx).at(cy).state == VACANT) {
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

int Emperor::changeDirection() {
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


int Emperor::attack() {
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

int Emperor::setKids() {
	int cx = 0;
	int cy = 0;
	cx = x + directionX;
	cy = y + directionY;
	if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//��Q�����Ȃ���ΐݒu�B
		if (gameBuf->board.at(cx).at(cy).creature == nullptr && gameBuf->board.at(cx).at(cy).state == VACANT) {

			//PenguinKids kid = PenguinKids();
			
			//shared_ptr <PenguinKids> kid = make_shared<PenguinKids>(PenguinKids());

			//gameBuf->kids[gameBuf->mobNum] = *kid;
			gameBuf->kids[gameBuf->mobNum].setCharacter(team, directionX, directionY, cx, cy, speed);
			gameBuf->board.at(cx).at(cy).creature = &gameBuf->kids[gameBuf->mobNum];
			gameBuf->mobNum++;

			return 1;
		}
	}
	return 0;
}

int Emperor::castKids() {
	int cx = x;
	int cy = y;
	bool finish = false;

	if (casting == true && numKey[2][1] == 1) {//�L���X�g�����s�����I������Ƃ�
		casting = false;
		castStart(0);
		gameBuf->camera->subMarkFlag = 0;
		return 0;
	}


	if (pointX == x && pointY == y && (pointX < gameBuf->sizeX && pointX >= 0 && pointY < gameBuf->sizeY && pointY >= 0)) {//�ŏ��ɕ��������߂�i�K
		if (changeDirection() == 1) {//�����{�^���������ꂽ��

			pointX = x + directionX;
			pointY = y + directionY;
			gameBuf->camera->subMarkX = pointX;
			gameBuf->camera->subMarkY = pointY;
			gameBuf->camera->subMarkFlag = 1;
			gameBuf->camera->mainMsg = "���������m��";
		}
	}
	else if ((pointX < gameBuf->sizeX && pointX >= 0 && pointY < gameBuf->sizeY && pointY >= 0)) {
		if (upKey[1] == 1 || downKey[1] == 1 || leftKey[1] == 1 || rightKey[1] == 1) {
			gameBuf->camera->mainMsg = "���̕����Ɉړ�";
			cx = pointX + directionX;
			cy = pointY + directionY;
			if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {
				if (gameBuf->board.at(pointX + directionX).at(pointY + directionY).visual == 1) {
					pointX += directionX;
					pointY += directionY;
					gameBuf->camera->subMarkFlag = 1;
				}
				else {
					pointX = x;
					pointY = y;
					gameBuf->camera->subMarkFlag = 0;
				}
			}
			else {
				pointX = x;
				pointY = y;
				gameBuf->camera->subMarkFlag = 0;
			}

			gameBuf->camera->subMarkX = pointX;
			gameBuf->camera->subMarkY = pointY;

		}

		if (returnKey[1] == 1) {
			if (gameBuf->board.at(pointX).at(pointY).creature == nullptr && gameBuf->board.at(pointX).at(pointY).state == VACANT && gameBuf->board.at(pointX).at(pointY).visual == 1) {//�I���\������
				//�I���\�ȏꏊ�������̂łP

				gameBuf->kids[gameBuf->mobNum].setCharacter(team, directionX, directionY, pointX, pointY, speed);
				gameBuf->board.at(pointX).at(pointY).creature = &gameBuf->kids[gameBuf->mobNum];
				gameBuf->mobNum++;
				gameBuf->camera->mainMsg = "����";
				casting = false;
				gameBuf->camera->subMarkFlag = 0;
				castStart(0);
				return 1;
			}
		}
		
	}
	return 0;
}

int Emperor::castStart(int startOrFinish) {//�X�^�[�g�̎���1�A
	pointX = x;
	pointY = y;
	for (int i = 1; i < 5; i++) {
		int leftX = x - i;
		int rightX = x + i;
		int upY = y - i;
		int downY = y + i;

		//if (leftX < 0) {//�I���\�\�����A�}�X�̊O���������Ă��܂�Ȃ��悤�ɏ���
		//	leftX = 0;
		//}
		//if (rightX >= gameBuf->sizeX) {
		//	rightX = gameBuf->sizeX;
		//}
		//if (upY < 0) {
		//	upY = 0;
		//}
		//if (downY >= gameBuf->sizeY) {
		//	downY = gameBuf->sizeY;
		//}

		
		if (leftX >= 1) {
			gameBuf->board.at(leftX).at(y).visual = startOrFinish;
			if (upY >= 1) {
				gameBuf->board.at(leftX).at(upY).visual = startOrFinish;
			}
			if (downY < gameBuf->sizeY -1) {
				gameBuf->board.at(leftX).at(downY).visual = startOrFinish;
			}
		}
		if (rightX < gameBuf->sizeX -1) {
			gameBuf->board.at(rightX).at(y).visual = startOrFinish;
			if (upY >= 1) {
				gameBuf->board.at(rightX).at(upY).visual = startOrFinish;
			}
			if (downY < gameBuf->sizeY -1) {
				gameBuf->board.at(rightX).at(downY).visual = startOrFinish;
			}
		}
		if (upY >= 1) {
			gameBuf->board.at(x).at(y - i).visual = startOrFinish;
		}
		if (downY < gameBuf->sizeY -1) {
			gameBuf->board.at(x).at(y + i).visual = startOrFinish;//8�����̎˒��͈̓}�X�̕\�����P�i�I���\�̈�j�ɕύX�B
		}
	}
	return 0;
}

int Emperor::useItem() {
	return 0;
}

int Emperor::castItem() {
	return 0;
}