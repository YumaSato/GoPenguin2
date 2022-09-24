#pragma once
#include <string>
#include <vector>
#include "consts.h"
#include "MyClasses.h"

using std::vector;
using std::string;

class PenguinKids;//コンパイラに怒られないためのおまじない。「PenguinKidsっていうクラスがあるんだよ。内容はあとで定義するよ。」という意味。
class Grid;
class Creature;
class Character;
class Camera;
class Emperor;
class GameManager;


extern bool quitGame;
extern int clicking;
extern int pushingKey;


extern int numKey[10][3];
extern int spaceKey[3];
extern int shiftKey[3];
extern int escapeKey[3];
extern int returnKey[3];

extern int upKey[3];
extern int downKey[3];
extern int rightKey[3];
extern int leftKey[3];
extern int wKey[3];
extern int aKey[3];
extern int sKey[3];
extern int dKey[3];
extern int zKey[3];
//extern int numKey;
//extern int spaceKey;
//extern int shiftKey;
//extern int escapeKey;
//
//extern int upKey;
//extern int downKey;
//extern int rightKey;
//extern int leftKey;
//extern int wKey;
//extern int aKey;
//extern int sKey;
//extern int dKey;

extern char keyBuf[256];







extern int HandleBoard;
extern int hHP;
extern int HandleCastle;
extern int handle[3][9][8];
extern int handleField[64];
extern int handleBack[32];

extern int handleMusic[8];



int GetClickPlace(int* xCllick, int* yClick);