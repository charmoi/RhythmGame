#include "Score.h"

Score::Score() {
	score = 0;
	for (int i = 0; i < 10; i++) {
		this->img[i] = "\0";
	}
	p = nullptr;
	length = 0;
	index = nullptr;
}

Score::Score(string* img, const int img_spacing, ScenePtr& scene, const int x, const int y, const int length) : length(length) {
	for (int i = 0; i < 10; i++) {
		this->img[i] = img[i];
	}
	p = make_unique<ObjectPtr[]>(length);
	index = make_unique<char[]>(length);
	for (int i = 0; i < this->length; i++) {
		p[i] = Object::create(this->img[0], scene, x - img_spacing * i, y);
		index[i] = 0;
	}
	score = 0;
}

void Score::Create(string* img, const int img_spacing, ScenePtr& scene, const int x, const int y, const int length){
	this->length = length;
	for (int i = 0; i < 10; i++) {
		this->img[i] = img[i];
	}
	p = make_unique<ObjectPtr[]>(length);
	index = make_unique<char[]>(length);
	for (int i = 0; i < length; i++) {
		p[i] = Object::create(this->img[0], scene, x - img_spacing * i, y);
		index[i] = 0;
	}
	score = 0;
}

void Score::Hide() {
	for (int i = 0; i < length; i++)
		p[i]->hide();
}

void Score::Show() {
	for (int i = 0; i < length; i++)
		p[i]->show();
}

void Score::Update(int score) {
	if (!this->score) {
		Show();
	}
	this->score = score;
	for (int i = 0; i < length; i++) {
		index[i] = score % 10;
		score /= 10;
		p[i]->setImage(img[index[i]]);
	}
}

void Score::Reset() {
	this->score = 0;
	for (int i = 0; i < length; i++) {
		p[i]->setImage(img[0]);
	}
	Hide();
}

void Score::Increase() {
	if (!this->score) {
		Show();
	}
	this->score++;
	for (int i = 0; i < length; i++) {
		if (++index[i] < 10) {
			p[i]->setImage(img[index[i]]);
			break;
		}
		else {
			index[i] = 0;
			p[i]->setImage(img[0]);
		}
	}
}