#include "Judge.h"

Judge::Judge() {
	object = nullptr;
	for (int i = 0; i < 4; i++) {
		this->img[i] = "\0";
	}
	miss = 0;
	good = 0;
	great = 0;
	perfect = 0;
	shown = false;
}

Judge::Judge(string* img, ScenePtr& scene, const int x, const int y) {
	for (int i = 0; i < 4; i++) {
		this->img[i] = img[i];
	}
	object = Object::create(img[MISS], scene, x, y);
	miss = 0;
	good = 0;
	great = 0;
	perfect = 0;
	object->hide();
	shown = false;
}

void Judge::Create(string* img, ScenePtr& scene, const int x, const int y) {
	for (int i = 0; i < 4; i++) {
		this->img[i] = img[i];
	}
	object = Object::create(img[MISS], scene, x, y);
	miss = 0;
	good = 0;
	great = 0;
	perfect = 0;
	object->hide();
	shown = false;
}

void Judge::MissInc() {
	miss++;
	object->setImage(img[MISS]);
	if (!shown)
		Show();
}

int Judge::GoodInc() {
	good++;
	object->setImage(img[GOOD]);
	if (!shown)
		Show();
	return SCORE_GOD;
}

int Judge::GreatInc() {
	great++;
	object->setImage(img[GREAT]);
	if (!shown)
		Show();
	return SCORE_GRT;
}

int Judge::PerfectInc() {
	perfect++;
	object->setImage(img[PERFECT]);
	if (!shown)
		Show();
	return SCORE_PFT;
}

int Judge::GetMiss() {
	return miss;
}

int Judge::GetGood() {
	return good;
}

int Judge::GetGreat() {
	return great;
}

int Judge::GetPerfect() {
	return perfect;
}

int Judge::GetTotal() {
	return miss + good + great + perfect;
}

void Judge::Show() {
	object->show();
	shown = true;
}

void Judge::Hide() {
	object->hide();
	shown = false;
}

void Judge::Reset() {
	object->setImage(img[MISS]);
	object->hide();
	shown = false;
	miss = 0;
	good = 0;
	great = 0;
	perfect = 0;
}