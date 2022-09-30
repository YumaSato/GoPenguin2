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



class Creature {//���ڂɂ��鐶��
private:
	
	Direction compass;

public:
	GameManager* gameBuf;

	string name;
	Team team;//�y���M���s��:0�A�ԃy���M��:1�A�y���M��:2
	Status status;//��:1�A��l:2�A�V�l:3�A�c��:4
	shared_ptr<Item> item;
	int directionX;//�����Ă�������i����-1�A�E��1�j
	int directionY;//�����Ă�������i���-1�A����1�j
	int x;
	int y;
	int HP;
	int HP_Limit;
	//int troopNum;//�w�ԍ�
	//int troopMemberNum;//�w���l�ԍ�
	int giveExpPoint;//�|���ꂽ�Ƃ��ɗ^����o���l
	int attackPower;
	int defensePower;
	int speed;
	int staminaRecoverAbility;
	int staminaLimit;
	int stamina;

	int num;//�L�����N�^���ʔԍ��Bnum��-1�Ȃ͎̂��񂾃L�����̏؁B
	bool skip;//���ݕs�g�p

	int walking;//�����Ă���r�����}�X�ڂ��𔻕ʂ��邽�ߒl�B

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
	shared_ptr<Item> requestItem(int type, vector<PenguinKids*> confirmed);//x,y�͈˗���̍��W�B�܂肱�̊֐����Ăԑ��̍��W�B
	int deliverItem();//
	int fishingItem();

	int killed();

	void SETdirection(int xward, int yward);
	void SETdirection(Direction compass);
	void GETdirectionXY(int* xward, int* yward);
	Direction GETdirection();
};




class PenguinKids : public Creature {//�}�X�ڂɂ���L�����N�^�[

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
	
	shared_ptr<Item> requestItem(int type, vector<PenguinKids*> confirmed);//x,y�͈˗���̍��W�B�܂肱�̊֐����Ăԑ��̍��W�B
	int deliverItem();//
	int fishingItem();
	
	/*int changeDirection();
	int attack();
	int useItem();*/

};

class Emperor : public Creature {//�}�X�ڂɂ���L�����N�^�[
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








class Grid {//�e�}�X
public:
	int x;
	int y;
	State state = VACANT;//�}�X�ڂ̏�ԁB1:�n�ʁ@2:���@3:�ŏ�
	Creature* creature = nullptr;//�}�X�ڂɂ��郂���X�^�[or�L�����N�^�[�̃|�C���^
	int visual;//�O���t�B�b�N
	//int adjacent;//�אڃ}�X���t�B�[���h�O���𔻒�B

	Grid(int x, int y);
	~Grid();
};



class Item {//�A�C�e��
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

	int exhibitX;//�\����_
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
	bool markFlag;//���ڃ}�X�\�������邩�ۂ�

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
	int mobNum = 0;//���ݏo���ꂽ���u�̑����B�V���Ƀ��u�𐶐�����Ƃ��ɂ����num�ɂ���B���񂾃��u���c������B
	int score = 0;
	int turnNum = 0;

	int gameMode = 0;
	int rutine = 0;//���ꂪ1�̎��́A�c��z�񂪌Ă΂�A���ꂪ2�̎��̓��u�z��A3�̎��ɐA�������������B
	int moveCount = 0;//�c������Ԃɏ�������Ƃ��̃C���N�������g�B
	int mobCount = 0;//���u�����Ԃɏ�������Ƃ��̃C���N�������g�B

	int goNextFlag = 0;


	//vector<PenguinKids> Kids;//�q�y���M�������郁�C���ƂȂ�z��B
	PenguinKids kids[1024];

	vector<PenguinKids*> mobsSpeedOrder;

	//vector<vector<PenguinKids>> troops;

	Emperor handledCharacters[CHARACTERNUM];//����\�ȃL�����N�^�̃A�h���X���i�[����ϐ��B�z��C���f�b�N�X�́A�L�����ԍ��B

	int sizeX;//�X�e�[�W��
	int sizeY;

	vector<vector<Grid>> board;
	//Grid** board;
	/*Emperor* Emperor1;
	Emperor* Emperor2;*/

	
	/*Camera camera;*/


	int GameOver(GameManager* gameBuf);
	int GameClear(GameManager* gameBuf);
	/*int ScreenMove(int markX,int markY);*/

	int GoNext(GameManager* gameBuf);//charaFlag��markX��markY�̈ʒu�̃L�����ɒ���
	//int FindTroop(GameManager* gameBuf);//�A���w�𔻒肷��
	int ActMobs(GameManager* gameBuf);//���u�𓮂����B
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