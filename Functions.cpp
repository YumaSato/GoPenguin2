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
//	Creature* damaged = board[damageX][damageY].creature;//被ダメージ側を一時保存。
//	board[damageX][damageY].creature = NULL;//一旦その場にキャラがいないことにする。
//
//	Creature substitute = *damaged;//被ダメージ側の身代わりを作る。
//	substitute.HP += damageHP;//身代わりは、体力満タンとして扱う。
//
//	int damaging = 0;//繰り返しにより減り続けるメーターのHP値。
//
//	//int damagedHP = damaged->HP;//被ダメージ側のHPを一時保存。
//
//	for (int i = 0; i < damageHP + 5; i++) {
//		if (i % 5 == 0) {
//			board[damageX][damageY].creature = NULL;//4の倍数ごとにチカチカ切り替え。
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
//	if (markX == statusX && markY == statusY) {//ステータス表示キャラと操作可能キャラが同じだった場合、行動選択の表示を行う。
//
//
//		string Msg1 = "";
//		string Msg2 = "";
//
//		DrawBox(-gameBuf->exhibitX + markX * 48 + 40, -gameBuf->exhibitY + markY * 48 + 2, -gameBuf->exhibitX + markX * 48 + 360, -gameBuf->exhibitY + markY * 48 + 46, GetColor(225, 200, 0), TRUE);//外側のボックス
//		DrawBox(-gameBuf->exhibitX + markX * 48 + 39, -gameBuf->exhibitY + markY * 48 + 1, -gameBuf->exhibitX + markX * 48 + 361, -gameBuf->exhibitY + markY * 48 + 47, GetColor(125, 0, 0), FALSE);//外側のボックスの縁
//
//		for (int iii = 0; iii < 6; iii++) {
//			DrawBox(-gameBuf->exhibitX + markX * 48 + 50 + iii * 51, -gameBuf->exhibitY + markY * 48 + 24, -gameBuf->exhibitX + markX * 48 + 85 + iii * 51, -gameBuf->exhibitY + markY * 48 + 43, GetColor(50 + ((color + iii * 3) / 10), 220 + iii * 5 - (color / 3), 100), TRUE);//選択ボックス
//
//
//		}
//
//		Msg1 = board[markX][markY].creature->name + "のHP:" + std::to_string(board[markX][markY].creature->HP) + "/" + std::to_string(board[markX][markY].creature->HP_Limit) + "   素早さ値:" + std::to_string(board[markX][markY].creature->speed);
//		Msg2 = " 歩く　産卵　孵化　攻撃　押す　パス";
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
//		Msg = board[statusX][statusY].creature->name + "  HP:" + to_string(board[statusX][statusY].creature->HP) + "/" + to_string(board[statusX][statusY].creature->HP_Limit) + "　 Lv." + to_string(board[statusX][statusY].creature->levelUp) + "\n素早さ:" + to_string(board[statusX][statusY].creature->speed) + "  攻撃:" + (to_string(board[statusX][statusY].creature->attackPower)) + "  防御:" + to_string(board[statusX][statusY].creature->defensePower);
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
//	Creature* walking = board[markX][markY].creature;//蹴られた卵のポインタを仮置き場に代入し保持。
//	board[markX][markY].creature = NULL;//一旦盤面からキャラクタを除去。
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
//	Creature* kicked = board[kickX + dx][kickY + dy].creature;//蹴られた卵のポインタを仮置き場に代入し保持。
//	int handleEgg = handle[board[kickX + dx][kickY + dy].creature->team][EGG][NW];
//	board[kickX + dx][kickY + dy].creature = NULL;
//	for (int i = 0; i < distance * SQUARESIZE / 4; i = i++) {
//
//		exhibitScreen(kickX, kickY, TRUE, FALSE, board, handledCharacters);
//		DrawGraph(-gameBuf->exhibitX + (kickX + dx) * SQUARESIZE + (i * 4 * dx), -gameBuf->exhibitY + (kickY + dy) * SQUARESIZE + (i * 4 * dy), handleEgg, TRUE);
//		WaitTimer(2);
//		ScreenFlip(); //裏画面を表画面に反映
//	}
//
//	board[kickX + dx][kickY + dy].creature = kicked;//元の位置にポインタを戻す。
//}
//
//
//
//
//
//void exhibitRule() {
//
//	string rule1 = "ペンギンロボットバトル・ルールブック\n\n 二匹の皇帝ペンギンロボを動かして、城を守れ！\n 敵に城を壊されたらゲームオーバー！\n 赤皇帝と青皇帝が協力し合ってクローンペンギンを増やし、守りを固めろ！\n 卵を産んで孵化させ、クローンを作ろう。\n クローンは向いている方向に１度だけ卵を産んで、自分で孵化させるよ。\n クローンは敵に遭遇すると自動で戦ってくれるから、沢山増殖させよう！\n\n\nターンについて: 盤面上の全てのキャラクタは、素早さ順に行動するぞ！";
//	string rule2 = "行動について: \n  歩く:\n　　皇帝ペンギンは3歩まで歩ける。\n　産卵：\n　　向いている方向にクローンペンギンの卵を産む。";
//	string rule3 = "　孵化：\n　　向いている方向にいる卵を孵化させる。\n　　クローンは自分と同じ色の卵だけ孵化させる。\n　　生まれた子は孵化させたペンギンと同じ方向を向く。";
//	string rule4 = "\n　攻撃：\n　　向いている方向にいるキャラクタにダメージを与える。\n　蹴る：\n　　卵を蹴るとペンギンにぶつかるまで真っすぐ転がる。\n　　クローンペンギンを押すと、押した皇帝と同じ方向を向く。";
//	string rule5 = "クローンペンギンについて:\n  クローンは歩けない。産卵と攻撃と孵化を行う。\n　クローンペンギンには、「卵・若者・老人」の3つの状態がある。\n　　若者：卵を産む前の状態。向いている方向に産卵しようとする。\n　　老人：卵を産むと老人になる。\n　　　　　周囲に敵がいれば攻撃し、卵があれば孵化させる。\n\n\n\nEsc:ルールを閉じる";
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










int GetClickPlace(int* xClick, int* yClick) {//なにも押されていなければ0、左クリックなら1、右クリックなら2を返し、渡したアドレスにクリック時のマウス座標を格納。

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
	if(!(mouse & MOUSE_INPUT_RIGHT) && !(mouse & MOUSE_INPUT_LEFT)) {//右も左もどちらのクリックも押されていなかったら、次のクリックを受け付ける。
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
//void exhiHP(int exhiX, int exhiY, Creature* cre) {//ダメージ受けてるキャラのHPを表示する。
//
//	DrawGraph(exhiX + 5, exhiY + 29, hHP, TRUE);
//	DrawBox(exhiX + 16, exhiY + 31, exhiX + 16 + cre->HP / 2, exhiY + 36, GetColor(45, 205, 50), TRUE);
//
//}



