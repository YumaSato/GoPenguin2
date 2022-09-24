#include "DxLib.h"
//#include<iostream>
//#include<stdio.h>
//Version15.�e�}�X�ڂɐ����̃|�C���^���������悤�Ǝv�������G���[�B�q���y���M�����C���X�^���X�������ۂ�
//�ϒ��z��ɃC���X�^���X�������āA�������̊֐�����o��ƃC���X�^���X���������Ⴄ���������������A��̃G���[�B
#include <iostream>
#include <string>
#include <vector>
#include "MyClasses.h"
#include "consts.h"
#include "externs.h"

#include <algorithm>
#include <functional>

#include <cstdlib>
#include <ctime>

#pragma warning(disable:4996)//printf�n�̊֐����댯���ƌ��������Ďg�킹�Ă���Ȃ�Visual Studio�̌����ӂ������@�̌��t

using namespace std;

using std::string;
using std::vector;
using std::to_string;


//�v���g�^�C�v�錾
void handlePenguin();
void getKey();
//void exhibitScreen(Grid board[FIELDSIZE][FIELDSIZE]);
//void setCreature(int num, int ix, int iy);

Direction GETdirectionBYxy(int x, int y);
void GETxyBYdirection(int* x, int* y, Direction drctn);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
	SetMainWindowText("�y���M�����{�b�g�w���Q�[��");
	if (ChangeWindowMode(TRUE) != 0) {//������TRUE��n���ƃE�B���h�E���[�h�ɂȂ�B
		return 0;
	}
	// �E�C���h�E�̃T�C�Y���蓮�ł͂ł����A���E�C���h�E�̃T�C�Y�ɍ��킹�Ċg������Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetGraphMode(FIELDSIZE * 48 + 384, FIELDSIZE * 48, 32); // ��ʃT�C�Y�͍ő��1024, 900 �ɂ��Ă���
	SetWindowSize(FIELDSIZE * 48 + 384, FIELDSIZE * 48);// �ŏ��� 1024, 900 �ɂ��Ă���

	


	if (DxLib_Init() == -1) {
		return 0;
	}  // �c�w���C�u��������������


	handlePenguin();//�y���M���̑S�Ẳ摜�f�[�^��ǂݍ��ށB
	

	int game = 1;
	bool debug = FALSE;
	int handleTitle;
	int titleStringColor = 200;
	bool colorUpOrDown = TRUE;
	//handleTitle = LoadGraph("Imgs/title.jpg");


	//int music;

	//int pm;
	//pm = LoadSoundMem("Imsg/SampleBGM.ogg");
	//int counter = 0;
	/*handleMusic = LoadSoundMem("Imgs/SampleYukkuri.wav");*/

	/*PlayMusic("Imgs/ochaBGM.mp3", DX_PLAYTYPE_LOOP);
	SetVolumeMusic(40);*/

	//PlaySoundMem(handleMusic, DX_PLAYTYPE_LOOP, 1);
	//PlaySoundMem(pm, DX_PLAYTYPE_BACK, 1);




	for (int i = 0; i < 10; i++) {//�����L�[�̏�����
		for (int j = 0; j < 3; j++) {
			numKey[i][j] = 0;
		}
	}



	int haight = 22;
	GameManager* battle = NULL;

	while (TRUE) {
		if (ProcessMessage() != 0) { //�E�B���h�E�̕���{�^�����������ƃ��[�v�𔲂���
			break;
		}

		if (game == 1) {
			ClearDrawScreen();
			DrawGraph(0, 0, handleBack[1], TRUE);
			DrawString(960, 320, "���[�h��I�����Ă��������B\n\n\n1:�ȒP���[�h(Easy)\n60�^�[�������c��I\n\n\n2:�ʏ탂�[�h(Normal)\n60�^�[�������c��I\n\n\n3:��փ��[�h(Lunatic)\n100�^�[�������c��I\n\n\nEsc:��߂�\n\n\n\n\n\n\n\n\n\n            VERSION:2", GetColor(titleStringColor, 245, 255));

			if (CheckHitKey(KEY_INPUT_1) == TRUE) {
				pushingKey = 1;
				battle = new GameManager(0, 18, 18);
				game = 2;
			}
			if (CheckHitKey(KEY_INPUT_2) == TRUE) {
				pushingKey = 1;
				battle = new GameManager(1, 22, 24);
				game = 2;
			}
		}




		if (game == 2) {
			getKey();
			battle->BattleMode(battle);//���t���[��������Ă�

		}



		if (CheckHitKey(KEY_INPUT_ESCAPE) == TRUE) {
			return 0;
		}




		//if (colorUpOrDown == TRUE) {
		//	titleStringColor += 7;
		//}
		//if (colorUpOrDown == FALSE) {
		//	titleStringColor -= 7;
		//}
		//if (titleStringColor >= 246) {
		//	colorUpOrDown = FALSE;
		//}
		//if (titleStringColor <= 8) {
		//	colorUpOrDown = TRUE;
		//}






		ScreenFlip(); //����ʂ�\��ʂɔ��f
	}


	DxLib_End();    // �c�w���C�u�����g�p�̏I������

	return 0;    // �\�t�g�̏I�� 
}







void getKey() {





	GetHitKeyStateAll(keyBuf);


	if (keyBuf[KEY_INPUT_ESCAPE] == TRUE) {//�G�X�P�[�v�L�[
		if (escapeKey[0] == 0) {
			escapeKey[1] = 1;
		}
		else {
			escapeKey[1] = 0;
		}
		escapeKey[0] = 1;
		escapeKey[2] = 0;
	}
	else if (keyBuf[KEY_INPUT_ESCAPE] == FALSE) {
		if (escapeKey[0] == 1) {
			escapeKey[2] = 1;
		}
		escapeKey[0] = 0;
		escapeKey[1] = 0;
	}

	if (keyBuf[KEY_INPUT_SPACE] == TRUE) {//SPACE�L�[
		if (spaceKey[0] == 0) {
			spaceKey[1] = 1;
		}
		else {
			spaceKey[1] = 0;
		}
		spaceKey[0] = 1;
		spaceKey[2] = 0;
	}
	else if (keyBuf[KEY_INPUT_SPACE] == FALSE) {
		if (spaceKey[0] == 1) {
			spaceKey[2] = 1;
		}
		spaceKey[0] = 0;
		spaceKey[1] = 0;
	}

	if (keyBuf[KEY_INPUT_RETURN] == TRUE) {//�G���^�[�L�[
		if (returnKey[0] == 0) {
			returnKey[1] = 1;
		}
		else {
			returnKey[1] = 0;
		}
		returnKey[0] = 1;
		returnKey[2] = 0;
	}
	else if (keyBuf[KEY_INPUT_RETURN] == FALSE) {
		if (returnKey[0] == 1) {
			returnKey[2] = 1;
		}
		returnKey[0] = 0;
		returnKey[1] = 0;
	}

	if (keyBuf[KEY_INPUT_LSHIFT] == TRUE || keyBuf[KEY_INPUT_RSHIFT] == TRUE) {//SHIFT�L�[
		if (shiftKey[0] == 0) {
			shiftKey[1] = 1;
		}
		else {
			shiftKey[1] = 0;
		}
		shiftKey[0] = 1;
		shiftKey[2] = 0;
	}
	else if (keyBuf[KEY_INPUT_LSHIFT] == FALSE && keyBuf[KEY_INPUT_RSHIFT] == FALSE) {
		if (shiftKey[0] == 1) {
			shiftKey[2] = 1;
		}
		shiftKey[0] = 0;
		shiftKey[1] = 0;
	}






	if (keyBuf[KEY_INPUT_LEFT] == TRUE) {//LEFT�L�[
		if (leftKey[0] == 0) {
			leftKey[1] = 1;
		}
		else {
			leftKey[1] = 0;
		}
		leftKey[0] = 1;
		leftKey[2] = 0;
	}
	else if (keyBuf[KEY_INPUT_LEFT] == FALSE) {
		if (leftKey[0] == 1) {
			leftKey[2] = 1;
		}
		leftKey[0] = 0;
		leftKey[1] = 0;
	}
	if (keyBuf[KEY_INPUT_RIGHT] == TRUE) {//RIGHT�L�[
		if (rightKey[0] == 0) {
			rightKey[1] = 1;
		}
		else {
			rightKey[1] = 0;
		}
		rightKey[0] = 1;
		rightKey[2] = 0;
	}
	else if (keyBuf[KEY_INPUT_RIGHT] == FALSE) {
		if (rightKey[0] == 1) {
			rightKey[2] = 1;
		}
		rightKey[0] = 0;
		rightKey[1] = 0;
	}
	if (keyBuf[KEY_INPUT_UP] == TRUE) {//UP�L�[
		if (upKey[0] == 0) {
			upKey[1] = 1;
		}
		else {
			upKey[1] = 0;
		}
		upKey[0] = 1;
		upKey[2] = 0;
	}
	else if (keyBuf[KEY_INPUT_UP] == FALSE) {
		if (upKey[0] == 1) {
			upKey[2] = 1;
		}
		upKey[0] = 0;
		upKey[1] = 0;
	}
	if (keyBuf[KEY_INPUT_DOWN] == TRUE) {//DOWN�L�[
		if (downKey[0] == 0) {
			downKey[1] = 1;
		}
		else {
			downKey[1] = 0;
		}
		downKey[0] = 1;
		downKey[2] = 0;
	}
	else if (keyBuf[KEY_INPUT_DOWN] == FALSE) {
		if (downKey[0] == 1) {
			downKey[2] = 1;
		}
		downKey[0] = 0;
		downKey[1] = 0;
	}




	if (keyBuf[KEY_INPUT_Z] == TRUE) {//Z�L�[
		if (zKey[0] == 0) {
			zKey[1] = 1;
		}
		else {
			zKey[1] = 0;
		}
		zKey[0] = 1;
		zKey[2] = 0;
	}
	else if (keyBuf[KEY_INPUT_Z] == FALSE) {
		if (zKey[0] == 1) {
			zKey[2] = 1;
		}
		zKey[0] = 0;
		zKey[1] = 0;
	}


	if (keyBuf[KEY_INPUT_1] == TRUE) {//1�L�[
		if (numKey[1][0] == 0) {
			numKey[1][1] = 1;
		}
		else {
			numKey[1][1] = 0;
		}
		numKey[1][0] = 1;
		numKey[1][2] = 0;
	}
	else if (keyBuf[KEY_INPUT_1] == FALSE) {
		if (numKey[1][0] == 1) {
			numKey[1][2] = 1;
		}
		numKey[1][0] = 0;
		numKey[1][1] = 0;
	}

	if (keyBuf[KEY_INPUT_2] == TRUE) {//2�L�[
		if (numKey[2][0] == 0) {
			numKey[2][1] = 1;
		}
		else {
			numKey[2][1] = 0;
		}
		numKey[2][0] = 1;
		numKey[2][2] = 0;
	}
	else if (keyBuf[KEY_INPUT_2] == FALSE) {
		if (numKey[2][0] == 1) {
			numKey[2][2] = 1;
		}
		numKey[2][0] = 0;
		numKey[2][1] = 0;
	}

	if (keyBuf[KEY_INPUT_3] == TRUE) {//3�L�[
		if (numKey[3][0] == 0) {
			numKey[3][1] = 1;
		}
		else {
			numKey[3][1] = 0;
		}
		numKey[3][0] = 1;
		numKey[3][2] = 0;
	}
	else if (keyBuf[KEY_INPUT_3] == FALSE) {
		if (numKey[3][0] == 1) {
			numKey[3][2] = 1;
		}
		numKey[3][0] = 0;
		numKey[3][1] = 0;
	}

	if (keyBuf[KEY_INPUT_4] == TRUE) {//4�L�[
		if (numKey[4][0] == 0) {
			numKey[4][1] = 1;
		}
		else {
			numKey[4][1] = 0;
		}
		numKey[4][0] = 1;
		numKey[4][2] = 0;
	}
	else if (keyBuf[KEY_INPUT_4] == FALSE) {
		if (numKey[4][0] == 1) {
			numKey[4][2] = 1;
		}
		numKey[4][0] = 0;
		numKey[4][1] = 0;
	}


	//int numKeyBuf = 0;
	//if (keyBuf[KEY_INPUT_1] == TRUE) {
	//	numKeyBuf = 1;
	//}
	//if (keyBuf[KEY_INPUT_2] == TRUE) {
	//	numKeyBuf = 2;
	//}
	//if (keyBuf[KEY_INPUT_3] == TRUE) {
	//	numKeyBuf = 3;
	//}
	//if (keyBuf[KEY_INPUT_4] == TRUE) {
	//	numKeyBuf = 4;
	//}
	//if (keyBuf[KEY_INPUT_5] == TRUE) {
	//	numKeyBuf = 5;
	//}
	//if (keyBuf[KEY_INPUT_6] == TRUE) {
	//	numKeyBuf = 6;
	//}
	//if (keyBuf[KEY_INPUT_7] == TRUE) {
	//	numKeyBuf = 7;
	//}
	//if (keyBuf[KEY_INPUT_8] == TRUE) {
	//	numKeyBuf = 8;
	//}
	//if (keyBuf[KEY_INPUT_9] == TRUE) {
	//	numKeyBuf = 9;
	//}

	//if (numKeyBuf > 0 && numKeyBuf < 10) {
	//	if (numKey[numKeyBuf][0] == 0) {
	//		numKey[numKeyBuf][1] = 1;
	//	}
	//	else {
	//		numKey[numKeyBuf][1] = 0;
	//	}
	//	numKey[numKeyBuf][0] = 1;
	//	numKey[numKeyBuf][2] = 0;
	//	return;
	//}



	//if (keyBuf[KEY_INPUT_1] == FALSE) {
	//	numKeyBuf = -1;
	//}
	//if (keyBuf[KEY_INPUT_2] == FALSE) {
	//	numKeyBuf = -2;
	//}
	//if (keyBuf[KEY_INPUT_3] == FALSE) {
	//	numKeyBuf = -3;
	//}
	//if (keyBuf[KEY_INPUT_4] == FALSE) {
	//	numKeyBuf = -4;
	//}
	//if (keyBuf[KEY_INPUT_5] == FALSE) {
	//	numKeyBuf = -5;
	//}
	//if (keyBuf[KEY_INPUT_6] == FALSE) {
	//	numKeyBuf = -6;
	//}
	//if (keyBuf[KEY_INPUT_7] == FALSE) {
	//	numKeyBuf = -7;
	//}
	//if (keyBuf[KEY_INPUT_8] == FALSE) {
	//	numKeyBuf = -8;
	//}
	//if (keyBuf[KEY_INPUT_9] == FALSE) {
	//	numKeyBuf = -9;
	//}

	//
	//else if (numKeyBuf < 0 && numKeyBuf > -10) {
	//	if (numKey[-numKeyBuf][0] == 1) {
	//		numKey[-numKeyBuf][2] = 1;
	//	}
	//	numKey[-numKeyBuf][0] = 0;
	//	numKey[-numKeyBuf][1] = 0;
	//}
	

		//if ( keyBuf[KEY_INPUT_LSHIFT] == 1 || keyBuf[KEY_INPUT_LSHIFT] == 1) {//Shift�L�[
		//	shiftKey = 1;
		//}
		//else if (keyBuf[KEY_INPUT_LSHIFT] == FALSE || keyBuf[KEY_INPUT_RSHIFT] == FALSE) {
		//	shiftKey = 0;
		//}


		//if (keyBuf[KEY_INPUT_SPACE] == TRUE) {//�X�y�[�X�L�[

		//	spaceKey = 1;
		//}
		//else if (keyBuf[KEY_INPUT_SPACE] == FALSE) {
		//	spaceKey = 0;
		//}

		//if (keyBuf[KEY_INPUT_ESCAPE] == TRUE) {//�G�X�P�[�v�L�[
		//	escapeKey = 1;
		//}
		//else if (keyBuf[KEY_INPUT_ESCAPE] == FALSE) {
		//	escapeKey = 0;
		//}




	//		if (keyBuf[KEY_INPUT_RIGHT] == TRUE) {//�E�L�[
	//		rightKey = 1;
	//	}
	//	else if (keyBuf[KEY_INPUT_RIGHT] == FALSE) {
	//		rightKey = 0;
	//	}
	//
	//	if (keyBuf[KEY_INPUT_LEFT] == TRUE) {//���L�[
	//		leftKey = 1;
	//	}
	//	else if (keyBuf[KEY_INPUT_LEFT] == FALSE) {
	//		leftKey = 0;
	//	}
	//
	//	if (keyBuf[KEY_INPUT_UP] == TRUE) {//�カ�[
	//		upKey = 1;
	//	}
	//	else if (keyBuf[KEY_INPUT_UP] == FALSE) {
	//		upKey = 0;
	//	}
	//
	//	if (keyBuf[KEY_INPUT_DOWN] == TRUE) {//�����[
	//		downKey = 1;
	//	}
	//	else if (keyBuf[KEY_INPUT_DOWN] == FALSE) {
	//		downKey = 0;
	//	}
	//
	//}
	
}
















void handlePenguin() {//�n���h���ɉ摜�̃|�C���^����

	handleField[0] = LoadGraph("Imgs/Field/grassGreen.png");
	handleField[1] = LoadGraph("Imgs/Field/grassLight.png");
	handleField[2] = LoadGraph("Imgs/Field/cliff0.png");
	handleField[3] = LoadGraph("Imgs/Field/cliff1.png");
	handleField[4] = LoadGraph("Imgs/Field/cliff2.png");
	handleField[5] = LoadGraph("Imgs/Field/cliff3.png");
	handleField[6] = LoadGraph("Imgs/Field/cliff4.png");
	handleField[7] = LoadGraph("Imgs/Field/cliff5.png");
	handleField[8] = LoadGraph("Imgs/Field/cliff6.png");
	handleField[9] = LoadGraph("Imgs/Field/cliff7.png");
	handleField[10] = LoadGraph("Imgs/BrokenCastle.png");
	handleField[11] = LoadGraph("Imgs/Castle.png");

	handleBack[0] = LoadGraph("Imgs/Back/Nishikita.jpg");
	handleBack[1] = LoadGraph("Imgs/Back/title.jpg");

	HandleBoard = LoadGraph("Imgs/back.png");
	hHP = LoadGraph("Imgs/HPmeter43,9.png");
	HandleCastle = LoadGraph("Imgs/Castle.png");



	char tmp[50];
	for (int i = 0; i <= 7; i++) {
		sprintf(tmp, "Imgs/redPenguin%d.png", i);
		handle[red][NORMAL][i] = LoadGraph(tmp);
	}

	for (int i = 0; i <= 7; i++) {
		sprintf(tmp, "Imgs/redEmperor%d.png", i);
		handle[red][EMPEROR][i] = LoadGraph(tmp);
	}

	for (int i = 0; i <= 7; i++) {
		sprintf(tmp, "Imgs/bluePenguin%d.png", i);
		handle[blue][NORMAL][i] = LoadGraph(tmp);
	}

	for (int i = 0; i <= 7; i++) {
		sprintf(tmp, "Imgs/blueEmperor%d.png", i);
		handle[blue][EMPEROR][i] = LoadGraph(tmp);
	}


	for (int i = 0; i <= 7; i++) {//�V�����ԃy���M�������ʂ̃y���M���Ɠ����G�B
		sprintf(tmp, "Imgs/redOld%d.png", i);
		handle[red][ELDER][i] = LoadGraph(tmp);
	}
	for (int i = 0; i <= 7; i++) {//�V�����y���M�������ʂ̃y���M���Ɠ����G�B
		sprintf(tmp, "Imgs/blueOld%d.png", i);
		handle[blue][ELDER][i] = LoadGraph(tmp);
	}
}

//void setCreature(int num, int ix, int iy) {
//    board[ix][iy].creature = handledCharacters[num];
//};




