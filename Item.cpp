#include "DxLib.h"
#include "MyClasses.h"
#include "externs.h"
#include "consts.h"
#include "string"


Item::Item() {
}
Item::~Item() {
}

Fish1::Fish1() {
	itemType = 0;
	name = "いわし";
	recoverPower = 25;
	hurtPower = 1;
}
Fish1::~Fish1() {
}


Fish2::Fish2() {
	itemType = 0;
	name = "あじ";
	recoverPower = 35;
	hurtPower = 1;
}
Fish2::~Fish2() {
}