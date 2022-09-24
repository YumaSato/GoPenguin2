#include "DxLib.h"
//#include<iostream>
//#include<stdio.h>
//Version15.各マス目に生物のポインタを持たせようと思ったがエラー。子供ペンギンをインスタンス化した際に
//可変長配列にインスタンスを代入して、生成時の関数から出るとインスタンスが消えちゃう問題を解決したが、謎のエラー。
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

#pragma warning(disable:4996)//printf系の関数を危険だと言い張って使わせてくれないVisual Studioの口をふさぐ魔法の言葉

using namespace std;

using std::string;
using std::vector;
using std::to_string;


//プロトタイプ宣言
void handlePenguin();
void getKey();
//void exhibitScreen(Grid board[FIELDSIZE][FIELDSIZE]);
//void setCreature(int num, int ix, int iy);

Direction GETdirectionBYxy(int x, int y);
void GETxyBYdirection(int* x, int* y, Direction drctn);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
	SetMainWindowText("ペンギンロボット陣取りゲーム");
	if (ChangeWindowMode(TRUE) != 0) {//引数にTRUEを渡すとウィンドウモードになる。
		return 0;
	}
	// ウインドウのサイズを手動ではできず、且つウインドウのサイズに合わせて拡大もしないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetGraphMode(FIELDSIZE * 48 + 384, FIELDSIZE * 48, 32); // 画面サイズは最大の1024, 900 にしておく
	SetWindowSize(FIELDSIZE * 48 + 384, FIELDSIZE * 48);// 最初は 1024, 900 にしておく

	


	if (DxLib_Init() == -1) {
		return 0;
	}  // ＤＸライブラリ初期化処理


	handlePenguin();//ペンギンの全ての画像データを読み込む。
	

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




	for (int i = 0; i < 10; i++) {//数字キーの初期化
		for (int j = 0; j < 3; j++) {
			numKey[i][j] = 0;
		}
	}



	int haight = 22;
	GameManager* battle = NULL;

	while (TRUE) {
		if (ProcessMessage() != 0) { //ウィンドウの閉じるボタンが押されるとループを抜ける
			break;
		}

		if (game == 1) {
			ClearDrawScreen();
			DrawGraph(0, 0, handleBack[1], TRUE);
			DrawString(960, 320, "モードを選択してください。\n\n\n1:簡単モード(Easy)\n60ターン生き残れ！\n\n\n2:通常モード(Normal)\n60ターン生き残れ！\n\n\n3:難関モード(Lunatic)\n100ターン生き残れ！\n\n\nEsc:やめる\n\n\n\n\n\n\n\n\n\n            VERSION:2", GetColor(titleStringColor, 245, 255));

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
			battle->BattleMode(battle);//毎フレームこれを呼ぶ

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






		ScreenFlip(); //裏画面を表画面に反映
	}


	DxLib_End();    // ＤＸライブラリ使用の終了処理

	return 0;    // ソフトの終了 
}







void getKey() {





	GetHitKeyStateAll(keyBuf);


	if (keyBuf[KEY_INPUT_ESCAPE] == TRUE) {//エスケープキー
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

	if (keyBuf[KEY_INPUT_SPACE] == TRUE) {//SPACEキー
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

	if (keyBuf[KEY_INPUT_RETURN] == TRUE) {//エンターキー
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

	if (keyBuf[KEY_INPUT_LSHIFT] == TRUE || keyBuf[KEY_INPUT_RSHIFT] == TRUE) {//SHIFTキー
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






	if (keyBuf[KEY_INPUT_LEFT] == TRUE) {//LEFTキー
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
	if (keyBuf[KEY_INPUT_RIGHT] == TRUE) {//RIGHTキー
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
	if (keyBuf[KEY_INPUT_UP] == TRUE) {//UPキー
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
	if (keyBuf[KEY_INPUT_DOWN] == TRUE) {//DOWNキー
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




	if (keyBuf[KEY_INPUT_Z] == TRUE) {//Zキー
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


	if (keyBuf[KEY_INPUT_1] == TRUE) {//1キー
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

	if (keyBuf[KEY_INPUT_2] == TRUE) {//2キー
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

	if (keyBuf[KEY_INPUT_3] == TRUE) {//3キー
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

	if (keyBuf[KEY_INPUT_4] == TRUE) {//4キー
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
	

		//if ( keyBuf[KEY_INPUT_LSHIFT] == 1 || keyBuf[KEY_INPUT_LSHIFT] == 1) {//Shiftキー
		//	shiftKey = 1;
		//}
		//else if (keyBuf[KEY_INPUT_LSHIFT] == FALSE || keyBuf[KEY_INPUT_RSHIFT] == FALSE) {
		//	shiftKey = 0;
		//}


		//if (keyBuf[KEY_INPUT_SPACE] == TRUE) {//スペースキー

		//	spaceKey = 1;
		//}
		//else if (keyBuf[KEY_INPUT_SPACE] == FALSE) {
		//	spaceKey = 0;
		//}

		//if (keyBuf[KEY_INPUT_ESCAPE] == TRUE) {//エスケープキー
		//	escapeKey = 1;
		//}
		//else if (keyBuf[KEY_INPUT_ESCAPE] == FALSE) {
		//	escapeKey = 0;
		//}




	//		if (keyBuf[KEY_INPUT_RIGHT] == TRUE) {//右キー
	//		rightKey = 1;
	//	}
	//	else if (keyBuf[KEY_INPUT_RIGHT] == FALSE) {
	//		rightKey = 0;
	//	}
	//
	//	if (keyBuf[KEY_INPUT_LEFT] == TRUE) {//左キー
	//		leftKey = 1;
	//	}
	//	else if (keyBuf[KEY_INPUT_LEFT] == FALSE) {
	//		leftKey = 0;
	//	}
	//
	//	if (keyBuf[KEY_INPUT_UP] == TRUE) {//上きー
	//		upKey = 1;
	//	}
	//	else if (keyBuf[KEY_INPUT_UP] == FALSE) {
	//		upKey = 0;
	//	}
	//
	//	if (keyBuf[KEY_INPUT_DOWN] == TRUE) {//下きー
	//		downKey = 1;
	//	}
	//	else if (keyBuf[KEY_INPUT_DOWN] == FALSE) {
	//		downKey = 0;
	//	}
	//
	//}
	
}
















void handlePenguin() {//ハンドルに画像のポインタを代入

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


	for (int i = 0; i <= 7; i++) {//老いた赤ペンギンも普通のペンギンと同じ絵。
		sprintf(tmp, "Imgs/redOld%d.png", i);
		handle[red][ELDER][i] = LoadGraph(tmp);
	}
	for (int i = 0; i <= 7; i++) {//老いた青ペンギンも普通のペンギンと同じ絵。
		sprintf(tmp, "Imgs/blueOld%d.png", i);
		handle[blue][ELDER][i] = LoadGraph(tmp);
	}
}

//void setCreature(int num, int ix, int iy) {
//    board[ix][iy].creature = handledCharacters[num];
//};




