#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"
using std::to_string;



Camera::Camera() {//�J�����̃R���X�g���N�^
	exhibitX = 0;//�\���}�X�ʒu�̍���̒[�̊�_
	exhibitY = 0;

	actingX = 0;//�s�����̃L�����N�^�̈ʒu�ɒ��ڐF�\�����o�����߂̍��W�B
	actingY = 0;
	damageCount = 0;
	castCount = 0;
	deliverCount = 0;

	string actionMsg = "";
	string mainMsg = "";
	string statusMsg = "";
	string counterMsg = "";
	
}

Camera::~Camera() {//�J�����̃R���X�g���N�^
}

int Camera::moveCamera(int markX, int markY, int attentionFlag, GameManager* gameBuf) {

		int moveSpeed = 6;
		if (CheckHitKey(KEY_INPUT_RSHIFT) == TRUE || CheckHitKey(KEY_INPUT_LSHIFT) == TRUE) {
			moveSpeed = 12;
		}

		if (CheckHitKey(KEY_INPUT_W) == TRUE) {//WASD�Ŏ��_�ړ�
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
				if (exhibitY / 48 + FIELDSIZE >= gameBuf->sizeY) {//�`�撆�S������Ă���}�X�{�`��}�X���{�P(�`�扺�[�}�X)���A�񎟌��z��T�C�Y�𒴂��Ă�����
					exhibitY = (gameBuf->sizeY - FIELDSIZE) * 48;//�`��}�X�̍��������exhibitXY���Ֆʏ�ɂ�����}�C�i�X��A�`��}�X�̉E�����ՖʃT�C�Y���͂ݏo��ꍇ�A�͂ݏo�Ȃ��ꏊ�ɍĐݒ�B
				}

				//exhibitScreen(markX,markY, TRUE, FALSE, gameBuf->board, handledCharacters);
				//WaitTimer(10);
			}
		}
		if (CheckHitKey(KEY_INPUT_A) == TRUE) {//WASD�Ŏ��_�ړ�
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






void Camera::exhibitStatusMsg(Emperor* handledCharacters) {//��������L�����N�^�̃X�e�[�^�X����\������B

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

		/*CharacterStatusMsg = handledCharacters[i].name + "      Lv." + numLevel + "\n ��� HP : " + numHP + " / " + numHP_Limit + "\n �U���́F" + atta + "   �h��́F" + defe + "\n �X�^�~�i�F" + staminaMsg + "/" + neededExp ;*/
		
		CharacterStatusMsg = handledCharacters[i].name + "      HP : " + numHP + " / " + numHP_Limit + "\n �U���́F" + atta + "   �h��́F" + defe + "\n �X�^�~�i�F" + stamina + "/" + staminaLimit;

		DrawString(875, 305 + i * 100, CharacterStatusMsg.c_str(), GetColor(20, 0, 0));

		//exhibitY = exhibitY + 90;
	}

}



void Camera::exhiHP(int exhiX, int exhiY, Creature* cre) {//�_���[�W�󂯂Ă�L������HP��\������B

	DrawGraph(exhiX + 5, exhiY + 29, hHP, TRUE);
	DrawBox(exhiX + 16, exhiY + 31, exhiX + 16 + cre->HP / 2, exhiY + 36, GetColor(45, 205, 50), TRUE);

}





void Camera::exhibitScreen(int markX, int markY, int attentionFlag, GameManager* gameBuf) {//�y���M����`��i�X�e�[�^�X�ƌ�������y���M���̓K�؂ȉ摜�̃n���h������肵�i�[���Ă���`��j
	int h;//�n���h���i�[�p
	string turn = "";
	bool HPexhibitOrNot;
	ClearDrawScreen();//��x��ʂ�S����

	int exhibitXsize = exhibitX / 48 + FIELDSIZE + 1;//�`�悷��̈���m�肳����B
	int exhibitYsize = exhibitY / 48 + FIELDSIZE + 1;
	if (exhibitX % 48 == 0) {
		exhibitXsize = exhibitX / 48 + FIELDSIZE;
	}
	if (exhibitY % 48 == 0) {
		exhibitYsize = exhibitY / 48 + FIELDSIZE;
	}





	for (int ix = exhibitX / 48; ix < exhibitXsize; ix++) {//exhibitX��Y�̊�_���珇�Ԃɕ`��
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


			if (attentionFlag == TRUE && markX == ix && markY == iy) {//���ڑΏۃL�����̃}�X�ɒ��ڗp�̉~��\�����邩�ۂ�
				DrawBox(-exhibitX + markX * 48 + 4, -exhibitY + markY * 48 + 4, -exhibitX + markX * 48 + 44, -exhibitY + markY * 48 + 44, GetColor(255, 200, 0), TRUE);
			}



			HPexhibitOrNot = FALSE;//�̗͂����^���łȂ��ꍇ�A���ꂪTRUE�ɂȂ�A���[�^���\�������B

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
			DrawGraph(-exhibitX + ix * SQUARESIZE, -exhibitY + iy * SQUARESIZE, h, TRUE);//��x�N���X�̕ϐ��Ɋi�[����Handle�ŕ`��
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

	turn = "���݂̃^�[��:" + std::to_string(gameBuf->turnNum) + "   ���݂�rutine:" + std::to_string(gameBuf->rutine);
	DrawString(FIELDSIZE * SQUARESIZE + 5, FIELDSIZE * SQUARESIZE - 20, turn.c_str(), GetColor(255, 200, 255));
	//actionMsg = "";

	exhibitStatusMsg(gameBuf->handledCharacters);

	DrawString(FIELDSIZE * SQUARESIZE + 320, FIELDSIZE * SQUARESIZE - 20, std::to_string(exhibitX).c_str(), GetColor(10, 20, 100));
	DrawString(FIELDSIZE * SQUARESIZE + 355, FIELDSIZE * SQUARESIZE - 20, std::to_string(exhibitY).c_str(), GetColor(10, 20, 100));

	DrawBox(FIELDSIZE * SQUARESIZE + 120, 700, FIELDSIZE * SQUARESIZE + 320, 785, GetColor(90, 70, 0), TRUE);
	DrawString(FIELDSIZE * SQUARESIZE + 170, 720, "���֐i��\n(SPACE)", GetColor(20, 0, 40));
}





