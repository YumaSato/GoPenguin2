#pragma once
#include <string>
#include "externs.h"
#include "consts.h"
#include <vector>
#include <memory>

using namespace std;







class GameManager;
class Camera;
class PenguinKids;
class Creature;
class Grid;
class Emperor;

class Item;
class Fish1;
class Fish2;
class Timber;
class Spear;



class Creature {//升目にいる生物
private:
	
	Direction compass;

public:
	GameManager* gameBuf;

	string name;
	Team team;//ペンギン不在:0、赤ペンギン:1、青ペンギン:2
	Status status;//卵:1、大人:2、老人:3、皇帝:4
	shared_ptr<Item> item;
	int directionX;//向いている方向（左は-1、右は1）
	int directionY;//向いている方向（上は-1、下は1）
	int x;
	int y;
	int HP;
	int HP_Limit;
	//int troopNum;//陣番号
	//int troopMemberNum;//陣内個人番号
	int giveExpPoint;//倒されたときに与える経験値
	int attackPower;
	int defensePower;
	int speed;
	int staminaRecoverAbility;
	int staminaLimit;
	int stamina;

	int num;//キャラクタ識別番号。numが-1なのは死んだキャラの証。
	bool skip;//現在不使用

	int walking;//歩いている途中何マス目かを判別するため値。

	Creature();
	~Creature();

	int selectAction();
	int setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed);
	int walk();
	int changeDirection();
	int attack();
	int setKids();
	int castKids();
	int useItem();
	int castItem();
	shared_ptr<Item> requestItem(int type, vector<PenguinKids*> confirmed);//x,yは依頼主の座標。つまりこの関数を呼ぶ側の座標。
	int deliverItem();//
	int fishingItem();

	int killed();

	void SETdirection(int xward, int yward);
	void SETdirection(Direction compass);
	void GETdirectionXY(int* xward, int* yward);
	Direction GETdirection();
};




class PenguinKids : public Creature {//マス目にいるキャラクター

private:
	int fishingTurn = 0;

public:

	//PenguinKids* adjacent[4];
	PenguinKids();
	PenguinKids(GameManager* battle);
	~PenguinKids();

	int selectAction();
	int setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed);
	int attack();
	
	shared_ptr<Item> requestItem(int type, vector<PenguinKids*> confirmed);//x,yは依頼主の座標。つまりこの関数を呼ぶ側の座標。
	int deliverItem();//
	int fishingItem();
	
	/*int changeDirection();
	int attack();
	int useItem();*/

};

class Emperor : public Creature {//マス目にいるキャラクター
public:
	Emperor();
	Emperor(GameManager* battle);
	~Emperor();

	int selectAction();
	int setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed);
	
	int walk();
	int changeDirection();
	int attack();
	int setKids();
	int castKids();
	int useItem();
	int castItem();


};








class Grid {//各マス
public:
	int x;
	int y;
	State state = VACANT;//マス目の状態。1:地面　2:水　3:毒沼
	Creature* creature = nullptr;//マス目にいるモンスターorキャラクターのポインタ
	int visual;//グラフィック
	//int adjacent;//隣接マスがフィールド外かを判定。

	Grid(int x, int y);
	~Grid();
};



class Item {//アイテム
public:
	int itemType;
	string name;
	int recoverPower;
	int hurtPower;

	Item();
	~Item();
};

class Fish1 : public Item {
public:
	Fish1();
	~Fish1();
};
class Fish2 : public Item {
public:
	Fish2();
	~Fish2();
};




class Camera {
public:

	GameManager* gameBuf;

	int exhibitX;//表示基準点
	int exhibitY;
	string actionMsg;
	string mainMsg;
	string statusMsg;
	string counterMsg;

	int handleItem[8];

	/*int HandleBoard;
	int hHP;
	int HandleCastle;
	int handle[3][9][8];
	int handleField[64];
	int handleBack[32];*/

	int markX;
	int markY;
	bool markFlag;//注目マス表示をするか否か

	int damageCount;
	int castCount;
	int deliverCount;


	Camera(GameManager* battle);
	~Camera();

	int moveCamera(int markX, int markY, int attentionFlag);
	void exhibitScreen();

	/*void exhibitDamage(int markX, int markY, int attentionFlag);
	void exhibitCast(int markX, int markY, int attentionFlag);
	void exhibitDeliver();*/

	void exhiHP(int exhiX, int exhiY, Creature* cre);
	void exhibitStatusMsg(Emperor* handledCharacters);
};







class GameManager {
public:
	GameManager(int stageLevel, int xSize, int ySize);
	~GameManager();
	int BattleMode(GameManager* gameBuf);

	//GameManager* gameBuf = NULL;

	Camera* camera;
	

	int moveCharaNumber = 2;
	/*int num_redKids = 0;
	int num_blueKids = 0;*/
	int mobNum = 0;//生み出されたモブの総数。新たにモブを生成するときにこれをnumにする。死んだモブも残存する。
	int score = 0;
	int turnNum = 0;

	int gameMode = 0;
	int rutine = 0;//これが1の時は、皇帝配列が呼ばれ、これが2の時はモブ配列、3の時に植物が処理される。
	int moveCount = 0;//皇帝を順番に処理するときのインクリメント。
	int mobCount = 0;//モブを順番に処理するときのインクリメント。

	int goNextFlag = 0;


	//vector<PenguinKids> Kids;//子ペンギンを入れるメインとなる配列。
	PenguinKids kids[1024];

	vector<PenguinKids*> mobsSpeedOrder;

	//vector<vector<PenguinKids>> troops;

	Emperor handledCharacters[CHARACTERNUM];//操作可能なキャラクタのアドレスを格納する変数。配列インデックスは、キャラ番号。

	int sizeX;//ステージ幅
	int sizeY;

	vector<vector<Grid>> board;
	//Grid** board;
	/*Emperor* Emperor1;
	Emperor* Emperor2;*/

	
	/*Camera camera;*/


	int GameOver(GameManager* gameBuf);
	int GameClear(GameManager* gameBuf);
	/*int ScreenMove(int markX,int markY);*/

	int GoNext(GameManager* gameBuf);//charaFlagはmarkXとmarkYの位置のキャラに注目
	//int FindTroop(GameManager* gameBuf);//連結陣を判定する
	int ActMobs(GameManager* gameBuf);//モブを動かす。
	int FinishGame(GameManager* gameBuf);

	

};




//class RoadMode_GameManager {
//public:
//	RoadMode_GameManager(int xSize, int ySize);
//
//	int RoadMode(int stageLevel);
//
//	PenguinKids mobs_PenguinKids[mobLimit];
//	Bull mobs_Bull[mobLimit];
//
//	Emperor handledCharacters[CHARACTERNUM];
//
//	Grid **board;
//
//};