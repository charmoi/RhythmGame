#include "HP.h"

HP::HP() : hp(0) {
	for (int i = 0; i < HP_MAX; i++) {
		hpLevel[i] = nullptr;
	}
}

HP::HP(const string& img, ScenePtr& scene, int x, int y) : hp(0) {
	for (int i = 0; i < HP_MAX; i++) {
		hpLevel[i] = Object::create(img, scene, x, y + (14 * i));
	}
}

void HP::Create(const string& img, ScenePtr& scene, int x, int y) {
	for (int i = 0; i < HP_MAX; i++) {
		hpLevel[i] = Object::create(img, scene, x, y + (14 * i));
	}
	hp = 0;
}
void HP::SetColor(const string& img, int startIndex, int endIndex) {
	for (int i = startIndex; i <= endIndex; i++) {
		hpLevel[i]->setImage(img);
	}
}
void HP::Show() {
	for (int i = 0; i < HP_MAX; i++) {
		hpLevel[i]->show();
	}
}
void HP::Hide() {
	for (int i = 0; i < HP_MAX; i++) {
		hpLevel[i]->hide();
	}
}
void HP::Update(int new_hp) {
	if (new_hp > 26 || new_hp < 0) {
		return;
	}
	hp = new_hp;
	HP::Show();
	for (int i = new_hp + 1; i < HP_MAX; i++) {
		hpLevel[i]->hide();
	}
}
void HP::Increase() {
	if (hp == 26) {
		return;
	}
	else {
		hpLevel[++hp]->show();
	}
}
bool HP::Decrease() {
	int pre_hp = hp;
	hp -= HP_LOSS;
	if (hp <= 0) {
		hp = 0;
		HP::Hide();
		return false;			// 게임 종료 시그널; 주어진 HP 모두 소진
	}
	else {
		for (int i = hp + 1; i <= pre_hp; i++) {
			hpLevel[i]->hide();
		}
	}
	return true;
}