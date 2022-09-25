#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"


Grid::Grid(int x, int y) :
	x(x),
	y(y),
	creature(nullptr),
	state(VACANT),
	visual(0)
	//adjacent(0)
{
}

Grid::~Grid() {
}