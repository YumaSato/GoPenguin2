#pragma once

enum Team {

	red = 1, //赤チーム
	blue = 2, //青チーム
	 //敵キャラども。
};

enum Status {
	NORMAL = 0,     //普通ペンギン
	ELDER = 1,      //強化ペンギン
	EMPEROR = 2,    //皇帝ペンギン

};


enum Direction {
	NW = 0,
	NN = 1,
	NE = 2,
	EE = 3,
	SE = 4,
	SS = 5,
	SW = 6,
	WW = 7
};

enum State {
	VACANT,
	ROCK,  //地面
	WATER,   //水
	POISON,   //毒沼
	CASTLE, //城
	BROKENCASTLE//一度攻撃された城
};

constexpr int BUFFER = 256;

//constexpr int FIELDSIZE = 17;//フィールドのマス目の数

constexpr int SQUARESIZE = 48;

//const int CASTLE_X = 8;
//const int CASTLE_Y = 8;

constexpr int CHARACTERNUM = 2;//操作可能なキャラクタ数

const int WHITE = GetColor(255, 255, 255);

const int mobLimit = 2048;

const int FIELDSIZE = 17;
