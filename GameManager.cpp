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



GameManager::GameManager(int stageLevel, int xSize, int ySize) {//�R���X�g���N�^�B
	turnNum = 0;
	score = 0;
	gameMode = 1;
	goNextFlag = 0;

	this->sizeX = xSize;
	this->sizeY = ySize;

	camera = new Camera(this);



	/*vector<vector<Grid>> board(xSize, vector<Grid>(ySize));*/
	//board.at(xSize).at(ySize);//�v�f���𒴂��Ă��܂�Ȃ��悤�Ɍx�����Ă����B

	for (int ix = 0; ix < xSize; ix++) {
		vector<Grid> xVec;
		for (int iy = 0; iy < ySize; iy++) {
			Grid yVec(ix,iy);
			xVec.push_back(yVec);
		}
		board.push_back(xVec);
	}

	


	


	for (int ix = 0; ix < sizeX; ix++) {//Grid�̏�Ԃ��Z�b�g
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


	shared_ptr <Emperor> Emperor1 = make_shared<Emperor>(Emperor(this));//�C���X�^���X��
	Emperor1->setCharacter(red, 1, 0, 5, 5, 1001);
	handledCharacters[0] = *Emperor1;
	board[Emperor1->x][Emperor1->y].creature = &handledCharacters[0];//�}�X�ڂɎ����̃|�C���^�����B

	shared_ptr <Emperor> Emperor2 = make_shared<Emperor>(Emperor(this));
	//Emperor* Emperor2 = new Emperor();//�C���X�^���X��
	Emperor2->setCharacter(blue, 0, 1, 7, 10, 1000);
	handledCharacters[1] = *Emperor2;
	board[Emperor2->x][Emperor2->y].creature = &handledCharacters[1];

	//gameBuf = this;
}




GameManager::~GameManager() {

	//for (int xi = 0; xi < sizeX; xi++) {//�}�X�ڂ�����
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
				if (moveCount >= 0 && moveCount < moveCharaNumber) {//�G���y���[�̐��������s
					if (handledCharacters[moveCount].HP > 0) {
						camera->actingX = handledCharacters[moveCount].x;
						camera->actingY = handledCharacters[moveCount].y;
						if (handledCharacters[moveCount].selectAction() == 1) {//�s���I���ł���1���A���Ă����玟�L������
							moveCount++;
						};
					}
				}
				else {//�G���y���[�̐��̕������J��Ԃ�����,�������rutine2�̃t�F�[�Y�̊e���u�𓮂����Ă����B
					moveCount = 0;
					rutine = 1;
				}
			}

			if (rutine == 1) {
				for (int i = 0; i < mobNum; i++) {//��������������B
					if (kids[i].num >= 0) {//num���}�C�i�X�A�܂莀��̃L�����������B
						mobsSpeedOrder.push_back(&kids[i]);
					}
				}
				sort(mobsSpeedOrder.begin(), mobsSpeedOrder.end(), speedOrder);//mob�̑f�����z�������������B
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

					//actFlag = ActMobs(gameBuf);//���u�J�E���g�̑����͂��̊֐��̒��ōs���Ă���B
					//if (actFlag = 1) {//�s���������u��������
					//	
					//}
				}
				else {//mob�B�S�����s��������������
					turnNum++;
					mobCount = 0;
					rutine = 3;
					camera->actionMsg = "���̃^�[��(" + std::to_string(turnNum) + ")�֐i�݂܂��B";
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
			//		moveCount = 4;//�A�����������āA������m�F����GoNext��True�ɂȂ��Ă���
			//	}
			//}
		}
	}

	if (gameMode == 2) {//��������ƃG���f�B���O
		return 0;
	}

	camera->exhibitScreen(0, 0, FALSE);

	return 0;
}




// keyBuf[KEY_INPUT_SPACE]

int GameManager::GoNext(GameManager* gameBuf) {

	if (returnKey[1] == 1) {
		goNextFlag = 0;//�t���O���~���B
		return 0;//goNextFlag�ɂ��ꂪ�������āA�i����GoNext���Ă΂ꑱ�����Ԃ����������B
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



//int GameManager::ActMobs(GameManager* gameBuf) {�����s���̗�O���������鈫���̊֐�
//	if (mobCount >= 0 && mobCount < mobNum) {//���u�J�E���g�����u�̐���菬������
//		int mobAct = 0;
//		mobAct = mobsSpeedOrder[mobCount]->selectAction();
//		mobCount++;
//		if (mobAct == 0) {//�s�����������Ȃ������ꍇ
//			return 0;
//			if (mobCount >= 0 && mobCount < mobNum) {
//				return ActMobs(gameBuf);//�ŏI�I�ɍs�����郂�u��������A1���Ԃ��ꑱ���čŌ�1���Ԃ�B
//			}
//		}
//		if (mobAct == 1) {//�s�����������Ă����\����GoNext�őҋ@����K�v������ꍇ
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