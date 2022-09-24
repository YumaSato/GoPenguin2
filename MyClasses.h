#pragma once
#include <string>
#include "externs.h"
#include "consts.h"
#include <vector>

using namespace std;







class GameManager;
class Camera;
class PenguinKids;
class Creature;
class Grid;
class Emperor;
class Item;



class Creature {//���ڂɂ��鐶��
private:
	
	Direction compass;

public:
	string name;
	Team team;//�y���M���s��:0�A�ԃy���M��:1�A�y���M��:2
	Status status;//��:1�A��l:2�A�V�l:3�A�c��:4
	int directionX;//�����Ă�������i����-1�A�E��1�j
	int directionY;//�����Ă�������i���-1�A����1�j
	int x;
	int y;
	int HP;
	int HP_Limit;
	int troopNum;//�w�ԍ�
	int troopMemberNum;//�w���l�ԍ�
	int giveExpPoint;//�|���ꂽ�Ƃ��ɗ^����o���l
	int attackPower;
	int defensePower;
	int speed;
	int staminaRecoverAbility;
	int staminaLimit;
	int stamina;

	int num;//�L�����N�^���ʔԍ�
	bool skip;

	int walking;//�����Ă���r�����}�X�ڂ��𔻕ʂ��邽�ߒl�B

	Creature();
	~Creature();

	int selectAction(GameManager* gameBuf);
	int setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, GameManager* gameBuf);
	int walk(GameManager* gameBuf);
	int changeDirection(GameManager* gameBuf);
	int attack(GameManager* gameBuf);
	int setKids(GameManager* gameBuf);
	int castKids(GameManager* gameBuf);
	int useItem(GameManager* gameBuf);
	int castItem(GameManager* gameBuf);

	int killed(GameManager* gameBuf);

	void SETdirection(int xward, int yward);
	void SETdirection(Direction compass);
	void GETdirectionXY(int* xward, int* yward);
	Direction GETdirection();
};




class PenguinKids : public Creature {//�}�X�ڂɂ���L�����N�^�[
public:

	PenguinKids();
	~PenguinKids();

	int selectAction(GameManager* gameBuf);
	int setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, GameManager* gameBuf);
	/*int changeDirection();
	int attack();
	int useItem();*/

};

class Emperor : public Creature {//�}�X�ڂɂ���L�����N�^�[
public:
	Emperor();
	~Emperor();

	int selectAction(GameManager* gameBuf);
	int setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, GameManager* gameBuf);
	
	int walk(GameManager* gameBuf);
	int changeDirection(GameManager* gameBuf);
	int attack(GameManager* gameBuf);
	int setKids(GameManager* gameBuf);
	int castKids(GameManager* gameBuf);
	int useItem(GameManager* gameBuf);
	int castItem(GameManager* gameBuf);
};








class Grid {//�e�}�X
public:
	int x;
	int y;
	State state = VACANT;//�}�X�ڂ̏�ԁB1:�n�ʁ@2:���@3:�ŏ�
	Creature* creature = nullptr;//�}�X�ڂɂ��郂���X�^�[or�L�����N�^�[�̃|�C���^
	int visual;//�O���t�B�b�N
	int adjacent;//�אڃ}�X���t�B�[���h�O���𔻒�B

	Grid(int x, int y);
	~Grid();
};



class Item {//�}�X�ڂɗ����Ă�A�C�e��

};


class Camera {
public:

	int exhibitX;//�\����_
	int exhibitY;
	string actionMsg;
	string mainMsg;
	string statusMsg;
	string counterMsg;

	/*int HandleBoard;
	int hHP;
	int HandleCastle;
	int handle[3][9][8];
	int handleField[64];
	int handleBack[32];*/
	int actingX;
	int actingY;
	int damageCount;
	int castCount;
	int deliverCount;


	Camera();
	~Camera();

	int moveCamera(int markX, int markY, int attentionFlag, GameManager* gameBuf);
	void exhibitScreen(int markX, int markY, int attentionFlag, GameManager* gameBuf);

	/*void exhibitDamage(int markX, int markY, int attentionFlag, GameManager* gameBuf);
	void exhibitCast(int markX, int markY, int attentionFlag, GameManager* gameBuf);
	void exhibitDeliver(GameManager* gameBuf);*/

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
	int mobNum = 0;//���ݏo���ꂽ���u�̑����B�V���Ƀ��u�𐶐�����Ƃ��ɂ����num�ɂ���B
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

	vector<vector<PenguinKids>> troops;

	Emperor handledCharacters[CHARACTERNUM];//����\�ȃL�����N�^�̃A�h���X���i�[����ϐ��B�z��C���f�b�N�X�́A�L�����ԍ��B

	int sizeX;//�X�e�[�W��
	int sizeY;

	vector<vector<Grid>> board;
	//Grid** board;
	Emperor* Emperor1;
	Emperor* Emperor2;

	
	/*Camera camera;*/


	int GameOver(GameManager* gameBuf);
	int GameClear(GameManager* gameBuf);
	/*int ScreenMove(int markX,int markY);*/

	int GoNext(GameManager* gameBuf);//charaFlag��markX��markY�̈ʒu�̃L�����ɒ���
	int FindTroop(GameManager* gameBuf);//�A���w�𔻒肷��
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