#include "Score.h"

Score::Score() {
	score = 0;
	for (int i = 0; i < 10; i++) {
		this->img[i] = "\0";
	}
	p = nullptr;
	length = 0;
	index = nullptr;
	shown = true;
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
	shown = true;
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
	shown = true;
}

void Score::Hide() {
	for (int i = 0; i < length; i++)
		p[i]->hide();
	shown = false;
}

void Score::Show() {
	for (int i = 0; i < length; i++)
		p[i]->show();
	shown = true;
}

void Score::Update(int amount) {
	if (!shown)
		Show();

	this->score = amount;
	for (int i = 0; i < length; i++) {
		index[i] = amount % 10;
		amount /= 10;
		p[i]->setImage(img[index[i]]);
	}
}

void Score::Add(int amount) {
	if (!shown)
		Show();

	this->score += amount;
	int temp = score;
	for (int i = 0; i < length; i++) {
		index[i] = temp % 10;
		temp /= 10;
		p[i]->setImage(img[index[i]]);
	}
}

void Score::Reset() {
	this->score = 0;
	for (int i = 0; i < length; i++) {
		p[i]->setImage(img[0]);
		index[i] = 0;
	}
	Hide();
}

int Score::Increase() {
	if (!shown) {
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
	return score;
}

int Score::GetScore() {
	return this->score;
}