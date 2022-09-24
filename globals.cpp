#include <string>
#include <vector>
#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"

using std::string;
using std::vector;



bool quitGame = FALSE;
int clicking = 0;
int pushingKey = 0;

//int arrowKey[4][3];
//int wasdKey[4][3];

int spaceKey[3] = { 0,0,0 };
int shiftKey[3] = { 0,0,0 };
int escapeKey[3] = { 0,0,0 };
int returnKey[3] = { 0,0,0 };

int upKey[3] = { 0,0,0 };
int downKey[3] = { 0,0,0 };
int rightKey[3] = { 0,0,0 };
int leftKey[3] = { 0,0,0 };

int wKey[3] = { 0,0,0 };
int aKey[3] = { 0,0,0 };
int sKey[3] = { 0,0,0 };
int dKey[3] = { 0,0,0 };

int zKey[3] = { 0,0,0 };


int numKey[10][3];
//int spaceKey=0;
//int shiftKey=0;
//int escapeKey=0;
//
//int upKey=0;
//int rightKey=0;
//int leftKey=0;
//int downKey = 0;
//
//int wKey = 0;
//int aKey = 0;
//int sKey = 0;
//int dKey = 0;

char keyBuf[256];




int HandleBoard;//ゲーム盤の画像ハンドル
int hHP;
int HandleCastle;
int handle[3][9][8];//[team][status][direction]でペンギンの画像のハンドルを格納する3次元配列。
int handleMusic[8];
int handleField[64];
int handleBack[32];