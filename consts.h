#pragma once

enum Team {

	red = 1, //�ԃ`�[��
	blue = 2, //�`�[��
	 //�G�L�����ǂ��B
};

enum Status {
	NORMAL = 0,     //���ʃy���M��
	ELDER = 1,      //�����y���M��
	EMPEROR = 2,    //�c��y���M��

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
	ROCK,  //�n��
	WATER,   //��
	POISON,   //�ŏ�
	CASTLE, //��
	BROKENCASTLE//��x�U�����ꂽ��
};

constexpr int BUFFER = 256;

//constexpr int FIELDSIZE = 17;//�t�B�[���h�̃}�X�ڂ̐�

constexpr int SQUARESIZE = 48;

//const int CASTLE_X = 8;
//const int CASTLE_Y = 8;

constexpr int CHARACTERNUM = 2;//����\�ȃL�����N�^��

const int WHITE = GetColor(255, 255, 255);

const int mobLimit = 2048;

const int FIELDSIZE = 17;