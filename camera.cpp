#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"
using std::to_string;



Camera::Camera() {//カメラのコンストラクタ
	exhibitX = 0;//表示マス位置の左上の端の基準点
	exhibitY = 0;

	actingX = 0;//行動中のキャラクタの位置に注目色表示を出すための座標。
	actingY = 0;
	damageCount = 0;
	castCount = 0;
	deliverCount = 0;

	string actionMsg = "";
	string mainMsg = "";
	string statusMsg = "";
	string counterMsg = "";
	
}

Camera::~Camera() {//カメラのコンストラクタ
}

int Camera::moveCamera(int markX, int markY, int attentionFlag, GameManager* gameBuf) {

		int moveSpeed = 6;
		if (CheckHitKey(KEY_INPUT_RSHIFT) == TRUE || CheckHitKey(KEY_INPUT_LSHIFT) == TRUE) {
			moveSpeed = 12;
		}

		if (CheckHitKey(KEY_INPUT_W) == TRUE) {//WASDで視点移動
			if (exhibitY > 0) {
				exhibitY -= moveSpeed;
				if (exhibitY < 0) {
					exhibitY = 0;
				}
				//exhibitScreen(markX,markY, TRUE, FALSE, gameBuf->board, handledCharacters);
				//WaitTimer(10);

			}
		}
		if (CheckHitKey(KEY_INPUT_S) == TRUE) {
			if (exhibitY < (gameBuf->sizeY - FIELDSIZE) * SQUARESIZE) {
				exhibitY += moveSpeed;
				if (exhibitY / 48 + FIELDSIZE >= gameBuf->sizeY) {//描画中心が被っているマス＋描画マス数＋１(描画下端マス)が、二次元配列サイズを超えていたら
					exhibitY = (gameBuf->sizeY - FIELDSIZE) * 48;//描画マスの左上を示すexhibitXYが盤面上におけるマイナスや、描画マスの右下が盤面サイズをはみ出る場合、はみ出ない場所に再設定。
				}

				//exhibitScreen(markX,markY, TRUE, FALSE, gameBuf->board, handledCharacters);
				//WaitTimer(10);
			}
		}
		if (CheckHitKey(KEY_INPUT_A) == TRUE) {//WASDで視点移動
			if (exhibitX > 0) {
				exhibitX -= moveSpeed;
				if (exhibitX < 0) {
					exhibitX = 0;
				}
				//exhibitScreen(markX,markY, TRUE, FALSE, gameBuf->board, handledCharacters);
				//WaitTimer(10);

			}
		}
		if (CheckHitKey(KEY_INPUT_D) == TRUE) {
			if (exhibitX < (gameBuf->sizeX - FIELDSIZE) * SQUARESIZE) {
				exhibitX += moveSpeed;
				if (exhibitX / 48 + FIELDSIZE >= gameBuf->sizeX) {
					exhibitX = (gameBuf->sizeX - FIELDSIZE) * 48;
				}
				//exhibitScreen(markX, markY, TRUE, FALSE, gameBuf->board, handledCharacters);
				//WaitTimer(10);
			}
		}
		return 0;
}






void Camera::exhibitStatusMsg(Emperor* handledCharacters) {//動かせるキャラクタのステータス情報を表示する。

	string CharacterStatusMsg;

	//int exhibitY = 600;
	for (int i = 0; i < CHARACTERNUM; i++) {

		DrawBox(830, 300 + i * 100, 1180, 385 + i * 100, GetColor(240, 230, 140), TRUE);

		DrawGraph(832, 305 + i * 100, handle[handledCharacters[i].team][handledCharacters[i].status][5], TRUE);


		string numHP;
		numHP = (to_string(handledCharacters[i].HP));
		string numHP_Limit;
		numHP_Limit = (to_string(handledCharacters[i].HP_Limit));
		string atta;
		atta = (to_string(handledCharacters[i].attackPower));
		string defe;
		defe = (to_string(handledCharacters[i].defensePower));
		string staminaLimit;
		staminaLimit = (to_string(handledCharacters[i].staminaLimit));
		string stamina;
		stamina = (to_string(handledCharacters[i].stamina));

		/*CharacterStatusMsg = handledCharacters[i].name + "      Lv." + numLevel + "\n 状態 HP : " + numHP + " / " + numHP_Limit + "\n 攻撃力：" + atta + "   防御力：" + defe + "\n スタミナ：" + staminaMsg + "/" + neededExp ;*/
		
		CharacterStatusMsg = handledCharacters[i].name + "      HP : " + numHP + " / " + numHP_Limit + "\n 攻撃力：" + atta + "   防御力：" + defe + "\n スタミナ：" + stamina + "/" + staminaLimit;

		DrawString(875, 305 + i * 100, CharacterStatusMsg.c_str(), GetColor(20, 0, 0));

		//exhibitY = exhibitY + 90;
	}

}



void Camera::exhiHP(int exhiX, int exhiY, Creature* cre) {//ダメージ受けてるキャラのHPを表示する。

	DrawGraph(exhiX + 5, exhiY + 29, hHP, TRUE);
	DrawBox(exhiX + 16, exhiY + 31, exhiX + 16 + cre->HP / 2, exhiY + 36, GetColor(45, 205, 50), TRUE);

}





void Camera::exhibitScreen(int markX, int markY, int attentionFlag, GameManager* gameBuf) {//ペンギンを描画（ステータスと向きからペンギンの適切な画像のハンドルを入手し格納してから描画）
	int h;//ハンドル格納用
	string turn = "";
	bool HPexhibitOrNot;
	ClearDrawScreen();//一度画面を全消し

	int exhibitXsize = exhibitX / 48 + FIELDSIZE + 1;//描画する領域を確定させる。
	int exhibitYsize = exhibitY / 48 + FIELDSIZE + 1;
	if (exhibitX % 48 == 0) {
		exhibitXsize = exhibitX / 48 + FIELDSIZE;
	}
	if (exhibitY % 48 == 0) {
		exhibitYsize = exhibitY / 48 + FIELDSIZE;
	}





	for (int ix = exhibitX / 48; ix < exhibitXsize; ix++) {//exhibitXとYの基準点から順番に描画
		for (int iy = exhibitY / 48; iy < exhibitYsize; iy++) {

			
			
			DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 20, turn.c_str(), GetColor(255, 200, 255));

			if (gameBuf->board[ix][iy].state == VACANT) {
				int stripe = 0;
				if (ix % 2 == 0) {
					if (iy % 2 == 1) {
						stripe = 1;
					}
				}
				else {
					if (iy % 2 == 0) {
						stripe = 1;
					}
				}
				DrawGraph(-exhibitX + ix * SQUARESIZE, -exhibitY + iy * SQUARESIZE, handleField[stripe], TRUE);
			}
			if (gameBuf->board[ix][iy].state == ROCK) {
				DrawBox(-exhibitX + ix * SQUARESIZE, -exhibitY + iy * SQUARESIZE, -exhibitX + ix * SQUARESIZE + 47, -exhibitY + iy * SQUARESIZE + 47, GetColor(205, 133, 63), TRUE);
			}


			if (attentionFlag == TRUE && markX == ix && markY == iy) {//注目対象キャラのマスに注目用の円を表示するか否か
				DrawBox(-exhibitX + markX * 48 + 4, -exhibitY + markY * 48 + 4, -exhibitX + markX * 48 + 44, -exhibitY + markY * 48 + 44, GetColor(255, 200, 0), TRUE);
			}



			HPexhibitOrNot = FALSE;//体力が満タンでない場合、これがTRUEになり、メータが表示される。

			if (gameBuf->board[ix][iy].creature == nullptr) {
				continue;
			}
			else if(gameBuf->board[ix][iy].creature != nullptr) {

				/*turn = "ix = " + std::to_string(ix);
				WaitKey();*/

				Direction directionNum;
				directionNum = gameBuf->board[ix][iy].creature->GETdirection();

				h = handle[gameBuf->board[ix][iy].creature->team][gameBuf->board[ix][iy].creature->status][directionNum];


				if (gameBuf->board[ix][iy].creature->HP < gameBuf->board[ix][iy].creature->HP_Limit) {
					HPexhibitOrNot = TRUE;
				}
			}

			//LoadGraphScreen(0, 0, "back.png", TRUE);
			DrawGraph(-exhibitX + ix * SQUARESIZE, -exhibitY + iy * SQUARESIZE, h, TRUE);//一度クラスの変数に格納したHandleで描画
			//DrawString(450, 20, msg.c_str(), WHITE);

			if (HPexhibitOrNot == TRUE) {
				exhiHP(-exhibitX + ix * SQUARESIZE, -exhibitY + iy * SQUARESIZE, gameBuf->board[ix][iy].creature);

				/*DrawGraph(-exhibitX + ix * SQUARESIZE + 5, -exhibitY + iy * SQUARESIZE + 29, hHP, TRUE);
				DrawBox(-exhibitX + ix * SQUARESIZE + 16, -exhibitY + iy * SQUARESIZE + 31, -exhibitX + ix * SQUARESIZE + 16 + gameBuf->board[ix][iy].creature->HP / 2, -exhibitY + iy * SQUARESIZE + 36, GetColor(45, 205, 50), TRUE);
			*/
			}

		}
	}
	DrawBox(FIELDSIZE * SQUARESIZE, 0, FIELDSIZE * SQUARESIZE + 380, FIELDSIZE * SQUARESIZE, GetColor(256, 256, 256), TRUE);
	DrawGraph(FIELDSIZE * SQUARESIZE, 0, handleBack[0], TRUE);


	DrawString(FIELDSIZE * SQUARESIZE + 5, 20, mainMsg.c_str(), WHITE);
	DrawString(FIELDSIZE * SQUARESIZE + 5, 170, actionMsg.c_str(), GetColor(255, 200, 255));

	turn = "現在のターン:" + std::to_string(gameBuf->turnNum) + "   現在のrutine:" + std::to_string(gameBuf->rutine);
	DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 20, turn.c_str(), GetColor(255, 200, 255));
	//actionMsg = "";

	exhibitStatusMsg(gameBuf->handledCharacters);

	DrawString(FIELDSIZE * SQUARESIZE + 320, FIELDSIZE * SQUARESIZE - 20, std::to_string(exhibitX).c_str(), GetColor(10, 20, 100));
	DrawString(FIELDSIZE * SQUARESIZE + 355, FIELDSIZE * SQUARESIZE - 20, std::to_string(exhibitY).c_str(), GetColor(10, 20, 100));

	DrawBox(FIELDSIZE * SQUARESIZE + 120, 700, FIELDSIZE * SQUARESIZE + 320, 785, GetColor(90, 70, 0), TRUE);
	DrawString(FIELDSIZE * SQUARESIZE + 170, 720, "次へ進む\n(SPACE)", GetColor(20, 0, 40));
}





