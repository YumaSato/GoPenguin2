#include "DxLib.h"
#include <string>
#include <iostream>
#include "DxLib.h"
#include "consts.h"
#include "externs.h"
#include "MyClasses.h"
#include <vector>

using std::to_string;


//void exhiHP(int exhiX, int exhiY, Creature* cre);













//
//
//
//
//
//
//void exhibitDamage(int markX, int markY, int damageX, int damageY, bool attention, int damageHP, Grid** board, Emperor* handledCharacters) {
//	
//	/*PlayMusic("Imgs/Sound/Hit.wav", DX_PLAYTYPE_BACK);
//	SetVolumeMusic(250);*/
//
//	Creature* damaged = board[damageX][damageY].creature;//��_���[�W�����ꎞ�ۑ��B
//	board[damageX][damageY].creature = NULL;//��U���̏�ɃL���������Ȃ����Ƃɂ���B
//
//	Creature substitute = *damaged;//��_���[�W���̐g��������B
//	substitute.HP += damageHP;//�g����́A�̗͖��^���Ƃ��Ĉ����B
//
//	int damaging = 0;//�J��Ԃ��ɂ�茸�葱���郁�[�^�[��HP�l�B
//
//	//int damagedHP = damaged->HP;//��_���[�W����HP���ꎞ�ۑ��B
//
//	for (int i = 0; i < damageHP + 5; i++) {
//		if (i % 5 == 0) {
//			board[damageX][damageY].creature = NULL;//4�̔{�����ƂɃ`�J�`�J�؂�ւ��B
//		}
//		if (i % 5 == 3) {
//			board[damageX][damageY].creature = &substitute;
//		}
//
//
//		if (damaging < damageHP) {
//			damaging += 1;
//		}
//		exhibitScreen(markX, markY, TRUE, FALSE, board, handledCharacters);
//		DrawGraph(-gameBuf->exhibitX + damageX * SQUARESIZE + 5, -gameBuf->exhibitY + damageY * SQUARESIZE + 29, hHP, TRUE);
//		DrawBox(-gameBuf->exhibitX + damageX * SQUARESIZE + 16, -gameBuf->exhibitY + damageY * SQUARESIZE + 31, -gameBuf->exhibitX + damageX * SQUARESIZE + 16 + (substitute.HP - damaging) / 2, -gameBuf->exhibitY + damageY * SQUARESIZE + 36, GetColor(45, 205, 50), TRUE);
//
//		WaitTimer(30);
//
//		if (substitute.HP - damaging < 0) {
//			break;
//		}
//	}
//	board[damageX][damageY].creature = damaged;
//}
//
//
//
//
//
//
//
//
//
//
//
//void exhibitStatus(int markX, int markY, int statusX, int statusY, bool attention, int color, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {
//	//exhibitScreen(markX, markY, attention,FALSE, board, handledCharacters);
//	string Msg = "";
//	string Bulls = "";
//
//	//if (statusX < gameBuf->exhibitX && statusY < gameBuf->exhibitY) {
//
//
//
//	if (markX == statusX && markY == statusY) {//�X�e�[�^�X�\���L�����Ƒ���\�L�����������������ꍇ�A�s���I���̕\�����s���B
//
//
//		string Msg1 = "";
//		string Msg2 = "";
//
//		DrawBox(-gameBuf->exhibitX + markX * 48 + 40, -gameBuf->exhibitY + markY * 48 + 2, -gameBuf->exhibitX + markX * 48 + 360, -gameBuf->exhibitY + markY * 48 + 46, GetColor(225, 200, 0), TRUE);//�O���̃{�b�N�X
//		DrawBox(-gameBuf->exhibitX + markX * 48 + 39, -gameBuf->exhibitY + markY * 48 + 1, -gameBuf->exhibitX + markX * 48 + 361, -gameBuf->exhibitY + markY * 48 + 47, GetColor(125, 0, 0), FALSE);//�O���̃{�b�N�X�̉�
//
//		for (int iii = 0; iii < 6; iii++) {
//			DrawBox(-gameBuf->exhibitX + markX * 48 + 50 + iii * 51, -gameBuf->exhibitY + markY * 48 + 24, -gameBuf->exhibitX + markX * 48 + 85 + iii * 51, -gameBuf->exhibitY + markY * 48 + 43, GetColor(50 + ((color + iii * 3) / 10), 220 + iii * 5 - (color / 3), 100), TRUE);//�I���{�b�N�X
//
//
//		}
//
//		Msg1 = board[markX][markY].creature->name + "��HP:" + std::to_string(board[markX][markY].creature->HP) + "/" + std::to_string(board[markX][markY].creature->HP_Limit) + "   �f�����l:" + std::to_string(board[markX][markY].creature->speed);
//		Msg2 = " �����@�Y���@�z���@�U���@�����@�p�X";
//
//		DrawString(-gameBuf->exhibitX + markX * 48 + 42, -gameBuf->exhibitY + markY * 48 + 5, Msg1.c_str(), GetColor(0, 10, 55));
//		DrawString(-gameBuf->exhibitX + markX * 48 + 42, -gameBuf->exhibitY + markY * 48 + 26, Msg2.c_str(), GetColor(0, 10, 55));
//
//		//WaitTimer(10);
//
//	}
//	else {
//
//		DrawBox(-gameBuf->exhibitX + statusX * 48 + 40, -gameBuf->exhibitY + statusY * 48 + 5, -gameBuf->exhibitX + statusX * 48 + 300, -gameBuf->exhibitY + statusY * 48 + 43, GetColor(225, 200, 0), TRUE);
//		DrawBox(-gameBuf->exhibitX + statusX * 48 + 40, -gameBuf->exhibitY + statusY * 48 + 5, -gameBuf->exhibitX + statusX * 48 + 300, -gameBuf->exhibitY + statusY * 48 + 43, GetColor(125, 000, 0), FALSE);
//
//		Msg = board[statusX][statusY].creature->name + "  HP:" + to_string(board[statusX][statusY].creature->HP) + "/" + to_string(board[statusX][statusY].creature->HP_Limit) + "�@ Lv." + to_string(board[statusX][statusY].creature->levelUp) + "\n�f����:" + to_string(board[statusX][statusY].creature->speed) + "  �U��:" + (to_string(board[statusX][statusY].creature->attackPower)) + "  �h��:" + to_string(board[statusX][statusY].creature->defensePower);
//
//		DrawString(-gameBuf->exhibitX + statusX * 48 + 42, -gameBuf->exhibitY + statusY * 48 + 7, Msg.c_str(), GetColor(0, 10, 55));
//
//
//	}
//
//	//}
//}
//
//
//void exhibitWalking(int markX, int markY, int dx, int dy, int color, PenguinKids* mobs_PenguinKids, Bull* mobs_Bull, Grid** board, Emperor* handledCharacters) {
//
//	Creature* walking = board[markX][markY].creature;//�R��ꂽ���̃|�C���^�����u����ɑ�����ێ��B
//	board[markX][markY].creature = NULL;//��U�Ֆʂ���L�����N�^�������B
//
//	Direction directionNum;
//	directionNum = walking->GETdirection();
//	int handleWalking = handle[walking->team][walking->status][directionNum];
//
//	for (int i = 0; i <= SQUARESIZE; i+=8) {
//		exhibitScreen(markX, markY, FALSE, FALSE, board, handledCharacters);
//		DrawGraph(-gameBuf->exhibitX + markX*SQUARESIZE + dx * i, -gameBuf->exhibitY + markY * SQUARESIZE + dy * i, handleWalking, TRUE);
//		if (walking->HP < walking->HP_Limit) {
//			exhiHP(-gameBuf->exhibitX + markX * SQUARESIZE + dx * i, -gameBuf->exhibitY+ markY * SQUARESIZE + dy * i, walking);
//		}
//		gameBuf->ScreenMove(markX, markY);
//		ScreenFlip();
//	}
//
//	board[markX][markY].creature = walking;
//}
//
//
//
//
//
//
//
//void exhibitRolling(int kickX, int kickY, int dx, int dy, int distance, Grid** board, Emperor* handledCharacters) {
//
//
//	//actionMsg = std::to_string(distance).c_str();
//	//exhibitScreen(kickX, kickY, TRUE, board, handledCharacters);
//	//WaitKey();
//
//	Creature* kicked = board[kickX + dx][kickY + dy].creature;//�R��ꂽ���̃|�C���^�����u����ɑ�����ێ��B
//	int handleEgg = handle[board[kickX + dx][kickY + dy].creature->team][EGG][NW];
//	board[kickX + dx][kickY + dy].creature = NULL;
//	for (int i = 0; i < distance * SQUARESIZE / 4; i = i++) {
//
//		exhibitScreen(kickX, kickY, TRUE, FALSE, board, handledCharacters);
//		DrawGraph(-gameBuf->exhibitX + (kickX + dx) * SQUARESIZE + (i * 4 * dx), -gameBuf->exhibitY + (kickY + dy) * SQUARESIZE + (i * 4 * dy), handleEgg, TRUE);
//		WaitTimer(2);
//		ScreenFlip(); //����ʂ�\��ʂɔ��f
//	}
//
//	board[kickX + dx][kickY + dy].creature = kicked;//���̈ʒu�Ƀ|�C���^��߂��B
//}
//
//
//
//
//
//void exhibitRule() {
//
//	string rule1 = "�y���M�����{�b�g�o�g���E���[���u�b�N\n\n ��C�̍c��y���M�����{�𓮂����āA������I\n �G�ɏ���󂳂ꂽ��Q�[���I�[�o�[�I\n �ԍc��Ɛc�邪���͂������ăN���[���y���M���𑝂₵�A�����ł߂�I\n �����Y��śz�������A�N���[������낤�B\n �N���[���͌����Ă�������ɂP�x���������Y��ŁA�����śz���������B\n �N���[���͓G�ɑ�������Ǝ����Ő���Ă���邩��A��R���B�����悤�I\n\n\n�^�[���ɂ���: �Ֆʏ�̑S�ẴL�����N�^�́A�f�������ɍs�����邼�I";
//	string rule2 = "�s���ɂ���: \n  ����:\n�@�@�c��y���M����3���܂ŕ�����B\n�@�Y���F\n�@�@�����Ă�������ɃN���[���y���M���̗����Y�ށB";
//	string rule3 = "�@�z���F\n�@�@�����Ă�������ɂ��闑��z��������B\n�@�@�N���[���͎����Ɠ����F�̗������z��������B\n�@�@���܂ꂽ�q�͛z���������y���M���Ɠ��������������B";
//	string rule4 = "\n�@�U���F\n�@�@�����Ă�������ɂ���L�����N�^�Ƀ_���[�W��^����B\n�@�R��F\n�@�@�����R��ƃy���M���ɂԂ���܂Ő^�������]����B\n�@�@�N���[���y���M���������ƁA�������c��Ɠ��������������B";
//	string rule5 = "�N���[���y���M���ɂ���:\n  �N���[���͕����Ȃ��B�Y���ƍU���ƛz�����s���B\n�@�N���[���y���M���ɂ́A�u���E��ҁE�V�l�v��3�̏�Ԃ�����B\n�@�@��ҁF�����Y�ޑO�̏�ԁB�����Ă�������ɎY�����悤�Ƃ���B\n�@�@�V�l�F�����Y�ނƘV�l�ɂȂ�B\n�@�@�@�@�@���͂ɓG������΍U�����A��������Λz��������B\n\n\n\nEsc:���[�������";
//
//
//	DrawBox(550, 30, 1150, 1150, GetColor(236, 232, 248), TRUE);
//	DrawBox(550, 30, 1150, 1150, GetColor(130, 0, 0), FALSE);
//	DrawString(560, 50, rule1.c_str(), GetColor(0, 40, 55));
//	DrawString(560, 250, rule2.c_str(), GetColor(0, 40, 55));
//	DrawString(560, 340, rule3.c_str(), GetColor(0, 40, 55));
//	DrawString(560, 400, rule4.c_str(), GetColor(0, 40, 55));
//	DrawString(560, 550, rule5.c_str(), GetColor(0, 40, 55));
//}






















Direction GETdirectionBYxy(int x, int y) {
	if (x == -1) {
		if (y == -1)return NW;
		if (y == 0)return WW;
		if (y == 1)return SW;
	}
	if (x == 0) {
		if (y == -1)return NN;
		if (y == 1)return SS;
	}
	if (x == 1) {
		if (y == -1)return NE;
		if (y == 0)return EE;
		if (y == 1)return SE;
	}
}

void GETxyBYdirection(int* x, int* y, Direction drctn) {
	switch (drctn) {
	case NW:
		*x = -1;
		*y = -1;
		break;
	case NN:
		*x = 0;
		*y = -1;
		break;
	case NE:
		*x = 1;
		*y = -1;
		break;
	case EE:
		*x = 1;
		*y = 0;
		break;
	case SE:
		*x = 1;
		*y = 1;
		break;
	case SS:
		*x = 0;
		*y = 1;
		break;
	case SW:
		*x = -1;
		*y = 1;
		break;
	case WW:
		*x = -1;
		*y = 0;
		break;
	}
}










int GetClickPlace(int* xClick, int* yClick) {//�Ȃɂ�������Ă��Ȃ����0�A���N���b�N�Ȃ�1�A�E�N���b�N�Ȃ�2��Ԃ��A�n�����A�h���X�ɃN���b�N���̃}�E�X���W���i�[�B

	int mouse = NULL;
	int xc = NULL;
	int yc = NULL;
	mouse = GetMouseInput();
	if (mouse & MOUSE_INPUT_LEFT) {
		if (clicking == 0) {
			clicking = 1;
			GetMousePoint(&xc, &yc);
			*xClick = xc;
			*yClick = yc;
			return 1;
		}
	}
	if (mouse & MOUSE_INPUT_RIGHT) {
		if (clicking == 0) {
			clicking = 1;
			GetMousePoint(&xc, &yc);
			*xClick = xc;
			*yClick = yc;
			return 2;
		}
	}
	if(!(mouse & MOUSE_INPUT_RIGHT) && !(mouse & MOUSE_INPUT_LEFT)) {//�E�������ǂ���̃N���b�N��������Ă��Ȃ�������A���̃N���b�N���󂯕t����B
		clicking = 0;
		return 0;
	}


	//if (clicking == 0) {
	//	clicking = 1;
	//	GetMousePoint(&xc, &yc);
	//	*xClick = xc;
	//	*yClick = yc;
	//	return 1;
	//}

}










//
//void exhiHP(int exhiX, int exhiY, Creature* cre) {//�_���[�W�󂯂Ă�L������HP��\������B
//
//	DrawGraph(exhiX + 5, exhiY + 29, hHP, TRUE);
//	DrawBox(exhiX + 16, exhiY + 31, exhiX + 16 + cre->HP / 2, exhiY + 36, GetColor(45, 205, 50), TRUE);
//
//}



