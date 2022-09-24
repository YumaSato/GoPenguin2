#include <string>
#include "DxLib.h"
#include "MyClasses.h"

using std::string;

Direction GETdirectionBYxy(int x, int y);
void GETxyBYdirection(int* x, int* y, Direction drctn);

Creature::Creature() {//�R���X�g���N�^�B�`�[���ƈʒu���󂯎��B
	memset(&this->team, NULL, sizeof(this->team));//team��status��int�ł͂Ȃ�enum�^�ł��邩��NULL�����ł��Ȃ��B
	memset(&this->status, NULL, sizeof(this->status));//������memset��team�̃T�C�Y���̎w��o�C�g����NULL�Ŗ��߂Ă�B
	memset(&this->directionX, NULL, sizeof(this->directionX));
	memset(&this->directionY, NULL, sizeof(this->directionY));
	memset(&this->x, NULL, sizeof(this->x));
	memset(&this->y, NULL, sizeof(this->y));
	memset(&this->HP, NULL, sizeof(this->HP));
	memset(&this->HP_Limit, NULL, sizeof(this->HP_Limit));
	memset(&this->troopNum, NULL, sizeof(this->troopNum));
	memset(&this->troopMemberNum, NULL, sizeof(this->troopMemberNum));
	memset(&this->attackPower, NULL, sizeof(this->attackPower));
	memset(&this->defensePower, NULL, sizeof(this->defensePower));
	memset(&this->speed, NULL, sizeof(this->speed));
	memset(&this->staminaRecoverAbility, NULL, sizeof(this->staminaRecoverAbility));
	memset(&this->num, NULL, sizeof(this->num));



	name = "Somebody";
	giveExpPoint = 0;
	walking = 0;
	skip = FALSE;

	//this->team = NULL;
	//this->status = NULL;
	//this->directionX = NULL;
	//this->directionY = NULL;
	//this->x = NULL;
	//this->y = NULL;
	//this->HP = NULL;
	//this->HP_Limit = NULL;
	//this->stamina = NULL;
	//this->staminaLimit = NULL;
	//this->attackPower = NULL;
	//this->defensePower = NULL;
	//this->speed = NULL;
	//this->staminaRecoverAbility = NULL;
	//this->num = NULL;
}

Creature::~Creature() {
}


int Creature::setCharacter(Team ParentTeam, int DirectionX, int DirectionY, int ix, int iy, int parentSpeed, GameManager* gameBuf) {
	return 0;
}

int Creature::selectAction(GameManager* gameBuf) {
	return TRUE;
}

int Creature::walk(GameManager* gameBuf) {
	return FALSE;
}


int Creature::changeDirection(GameManager* gameBuf) {
	return 0;
}

int Creature::attack(GameManager* gameBuf) {
	return FALSE;
}

int Creature::setKids(GameManager* gameBuf) {
	/*DrawString(800, 300, "Creature.specialMovement1���\�b�h���s", WHITE);
	WaitKey();*/
	return FALSE;
}

int Creature::castKids(GameManager* gameBuf) {
	return FALSE;
}

int Creature::useItem(GameManager* gameBuf) {
	return 0;
};

int Creature::castItem(GameManager* gameBuf) {
	return 0;
};

int Creature::killed(GameManager* gameBuf) {//�w��n�_�ɐ���������O��B�U���̓��e�����s�B
	
	return 0;
}




void Creature::SETdirection(int xward, int yward) {
	this->directionX = xward;
	this->directionY = yward;
	this->compass = GETdirectionBYxy(xward, yward);
}

void Creature::SETdirection(Direction compass) {
	int tmp_x, tmp_y;
	GETxyBYdirection(&tmp_x, &tmp_y, compass);

	this->directionX = tmp_x;
	this->directionY = tmp_y;
	this->compass = compass;
}

void Creature::GETdirectionXY(int* xward, int* yward) {//�����̒l��������ϐ��̃A�h���X���󂯎��
	*xward = directionX;
	*yward = directionY;//���̃A�h���X�̒��g�ɕ��������B�^���I�ɒl��Ԃ���B
}

Direction Creature::GETdirection() {
	return compass;
}




//void Creature::DeleteCreature() {
//	memset(&this->team, NULL, sizeof(this->team));
//	memset(&this->status, NULL, sizeof(this->status));
//	memset(&this->directionX, NULL, sizeof(this->directionX));
//	memset(&this->directionY, NULL, sizeof(this->directionY));
//	memset(&this->x, NULL, sizeof(this->x));
//	memset(&this->y, NULL, sizeof(this->y));
//	memset(&this->HP, NULL, sizeof(this->HP));
//	memset(&this->HP_Limit, NULL, sizeof(this->HP_Limit));
//	memset(&this->levelUp, NULL, sizeof(this->levelUp));
//	memset(&this->expPoint, NULL, sizeof(this->expPoint));
//	memset(&this->attackPower, NULL, sizeof(this->attackPower));
//	memset(&this->defensePower, NULL, sizeof(this->defensePower));
//	memset(&this->speed, NULL, sizeof(this->speed));
//	memset(&this->staminaRecoverAbility, NULL, sizeof(this->staminaRecoverAbility));
//	memset(&this->num, NULL, sizeof(this->num));
//
//}




