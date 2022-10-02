#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"

//プロトタイプ宣言
//void exhibitScreen(/*Grid board[FIELDSIZE][FIELDSIZE]*/);

PenguinKids::PenguinKids() {//皇帝のコンストラクタ
}

PenguinKids::PenguinKids(GameManager* battle) {//皇帝のコンストラクタ
	gameBuf = battle;
}

PenguinKids::~PenguinKids() {
}

int PenguinKids::setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed) {
	team = ParentTeam;
	if (team == red) {
		name = "赤クローン";
	}
	else if (team == blue) {
		name = "青クローン";
	}
	SETdirection(DirectionX, DirectionY);
	status = NORMAL;
	x = ix;
	y = iy;
	speed = parentSpeed;
	HP_Limit = 50;
	HP = 50;
	defensePower = 30;
	attackPower = 30;
	num = gameBuf->mobNum;
	fishingTurn = 0;
	stamina = 10;
	
	return 0;
}

int PenguinKids::selectAction() {
	gameBuf->camera->markX = x;
	gameBuf->camera->markY = y;
	int actFlag = 0;
	
	if (item == nullptr) {
		actFlag = fishingItem();
	}
	if (actFlag == 0) {
		actFlag = attack();
	}
	if (item != nullptr) {
		if (HP_Limit - HP > item->recoverPower && item->recoverPower >0) {//所持アイテムの回復力が0以上で、蓄積ダメージがアイテムによる回復量を上回っている場合
			HP += item->recoverPower;
			gameBuf->camera->actionMsg += "\n" + item->name + "を食べた。";
			item = nullptr;
		}
	}
	
	
	//deliverItem();

	

	return actFlag;
}

int PenguinKids::attack() {

	int cx = 0;
	int cy = 0;

	int dx = 0;
	int dy = 0;
	int directRandom = 0;
	int diCheck[4] = {0,1,2,3};

	for (int i = 0; i < 4; i++) {
		int reorganize = GetRand(3-i)+i;
		int exchange = diCheck[i];
		diCheck[i] = diCheck[reorganize];
		diCheck[reorganize] = exchange;
	}
	for (int i = 0; i < 4; i++) {
		if (diCheck[i] == 0) {
			dx = 1;
			dy = 0;
		}
		if (diCheck[i] == 1) {
			dx = -1;
			dy = 0;
		}
		if (diCheck[i] == 2) {
			dx = 0;
			dy = 1;
		}
		if (diCheck[i] == 3) {
			dx = 0;
			dy = -1;
		}

		cx = x + dx;
		cy = y + dy;
		if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//マスの中で対象マスに生物が居たら。

			if (gameBuf->board.at(cx).at(cy).creature != nullptr) {
				if (gameBuf->board.at(cx).at(cy).creature->team != team) {//味方でなければ殴打。

					gameBuf->board.at(cx).at(cy).creature->HP -= 4 * attackPower / gameBuf->board.at(cx).at(cy).creature->defensePower;
					/*if (gameBuf->board.at(cx).at(cy).creature->HP <= 0) {
						gameBuf->board.at(cx).at(cy).creature->HP = 0;
					}*/
					//if (HP <= 0) {
					//	gameBuf->board.at(cx).at(cy).creature->num = -1;//numが-1なのは死んだキャラの証。
					//	gameBuf->board.at(cx).at(cy).creature = nullptr;
					//}
					if (gameBuf->board.at(cx).at(cy).creature->HP <= 0) {
						gameBuf->board.at(cx).at(cy).creature->HP = 0;
						gameBuf->board.at(cx).at(cy).creature->num = -1;//numが-1なのは死んだキャラの証。
						gameBuf->board.at(cx).at(cy).creature = nullptr;
					}

					gameBuf->camera->actionMsg = std::to_string(num) +"番の" + name + " X:" + std::to_string(x) + " Y:" + std::to_string(y) + "は攻撃した！";
					SETdirection(dx, dy);
					return 1;
				}
			}
		}	
	}
	return 0;
	
}









//
//shared_ptr<Item> PenguinKids::requestItem(int type, vector<PenguinKids*> confirmed) {
//
//	int cx = 0;
//	int cy = 0;
//	int dx = 0;
//	int dy = 0;
//	int directRandom = 0;
//	int diCheck[4] = { 0,1,2,3 };
//	bool throughFlag = false;
//
//	for (int i = 0; i < 4; i++) {
//		int reorganize = GetRand(3 - i) + i;
//		int exchange = diCheck[i];
//		diCheck[i] = diCheck[reorganize];
//		diCheck[reorganize] = exchange;
//	}
//	for (int j = 0; j < 2; j++) {
//		for (int i = 0; i < 4; i++) {
//			throughFlag = false;
//			if (diCheck[i] == 0) {
//				dx = 1;
//				dy = 0;
//			}
//			if (diCheck[i] == 1) {
//				dx = -1;
//				dy = 0;
//			}
//			if (diCheck[i] == 2) {
//				dx = 0;
//				dy = 1;
//			}
//			if (diCheck[i] == 3) {
//				dx = 0;
//				dy = -1;
//			}
//
//			cx = x + dx;
//			cy = y + dy;
//			for (int cNum = 0; cNum < confirmed.size(); cNum++) {
//				if (cx == confirmed.at(cNum)->x && cy == confirmed.at(cNum)->y) {//依頼主の方向は無視する。
//					throughFlag = true;
//					continue;
//				}
//			}
//			if (throughFlag == true) {
//				continue;
//			}
//			
//			if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//マスの中で対象マスに生物がいれば
//				if (gameBuf->board.at(cx).at(cy).creature != nullptr) {
//					
//					if (gameBuf->board.at(cx).at(cy).creature->team == team && status == NORMAL) {
//						if (j == 0) {
//							if (gameBuf->board.at(cx).at(cy).creature->item != nullptr) {
//								if (gameBuf->board.at(cx).at(cy).creature->item->itemType == type) {//リクエストされたアイテムが発見されたら
//									shared_ptr<Item> buf = gameBuf->board.at(cx).at(cy).creature->item;
//									gameBuf->board.at(cx).at(cy).creature->item = nullptr;
//									return buf;
//								}
//								//アイテムが見つかったのでreturn
//							}
//
//						}
//						if (j == 1) {
//							
//							shared_ptr<Item> itemBuf = nullptr;
//							PenguinKids* kidsBuf = static_cast<PenguinKids*>(gameBuf->board.at(cx).at(cy).creature);
//							confirmed.push_back(kidsBuf);//もうすでに調べたからループさせないために調査対象除外リスト配列に、次のリクエスト主体をぶち込む。
//							itemBuf = kidsBuf->requestItem(type, confirmed);
//							if (itemBuf != nullptr) {//何かしらのアイテムが返ってきてたらreturnする
//								return itemBuf;
//							}
//						}
//					}
//					
//				}
//			}
//		}
//		
//	}
//
//	//for (int i = 0; i < 4; i++) {//全方位調べた結果、アイテムを持っているやつはいなかったので、連携捜索を開始。
//	//	if (diCheck[i] == 0) {
//	//		dx = 1;
//	//		dy = 0;
//	//	}
//	//	if (diCheck[i] == 1) {
//	//		dx = -1;
//	//		dy = 0;
//	//	}
//	//	if (diCheck[i] == 2) {
//	//		dx = 0;
//	//		dy = 1;
//	//	}
//	//	if (diCheck[i] == 3) {
//	//		dx = 0;
//	//		dy = -1;
//	//	}
//	//	cx = x + dx;
//	//	cy = y + dy;
//	//	if (cx == clientX && cy == clientY) {//依頼主の方向は無視する。
//	//		continue;
//	//	}
//	//	if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//マスの中で対象マスに生物がいれば
//
//	//		//if (gameBuf->board.at(cx).at(cy).creature != nullptr) {
//	//		if (gameBuf->board.at(cx).at(cy).creature != nullptr) {
//	//			if (gameBuf->board.at(cx).at(cy).creature->team == team && status == NORMAL) {
//	//				
//
//	//				//アイテムが見つかったのでreturn
//
//
//	//			}
//	//		}
//	//	}
//	//	
//	//}
//
//	return nullptr;//アイテムどころか隣に味方すらいなかった場合
//};

int PenguinKids::deliverItem() {
	return 0;
};

int PenguinKids::fishingItem() {
	int cx = 0;
	int cy = 0;
	int dx = 0;
	int dy = 0;
	int directRandom = 0;
	int diCheck[4] = { 0,1,2,3 };

	for (int i = 0; i < 4; i++) {
		int reorganize = GetRand(3 - i) + i;
		int exchange = diCheck[i];
		diCheck[i] = diCheck[reorganize];
		diCheck[reorganize] = exchange;
	}
	for (int i = 0; i < 4; i++) {
		if (diCheck[i] == 0) {
			dx = 1;
			dy = 0;
		}
		if (diCheck[i] == 1) {
			dx = -1;
			dy = 0;
		}
		if (diCheck[i] == 2) {
			dx = 0;
			dy = 1;
		}
		if (diCheck[i] == 3) {
			dx = 0;
			dy = -1;
		}

		cx = x + dx;
		cy = y + dy;
		if (cx < gameBuf->sizeX && cx >= 0 && cy < gameBuf->sizeY && cy >= 0) {//マスの中で対象マスに生物がいなければ
			if (gameBuf->board.at(cx).at(cy).creature == nullptr && gameBuf->board.at(cx).at(cy).state == VACANT) {

				SETdirection(dx, dy);

				//fishingTurn += GetRand(2) + 1;
				//if (fishingTurn >= 3) {

					if (GetRand(5) % 5 == 0) {//レアな魚
						item = make_shared<Fish1>(Fish1());
						gameBuf->camera->actionMsg = item->name + "が釣れた！";
					}
					else {
						item = make_shared<Fish1>(Fish1());
						gameBuf->camera->actionMsg = item->name + "が釣れた！";
					}

					fishingTurn = 0;
					
				//}
				/*else {
					gameBuf->camera->actionMsg = name + "は、釣りをしている。";
				}*/
				return 1;
			}
		}
	}//全ての方向がふさがっていたら
	if (HP < HP_Limit / 2) {
		shared_ptr<Item> itemBuf;
		vector<Creature*> confirmed;//調査済みペンギンを入れていく。これにより多重確認ループ地獄を起こさせない
		confirmed.push_back(this);

		itemBuf = requestItem(0, confirmed);//回復アイテムを周囲に要求
		if (itemBuf != nullptr) {
			item = itemBuf;
			gameBuf->camera->actionMsg = "仲間から" + item->name + "を受け取った。";
			return 1;
		}
	}



	return 0;
};