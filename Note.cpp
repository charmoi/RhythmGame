#include "Note.h"

Note::Note() : x(0), y(0) {
	object = nullptr;
}

Note::Note(const string& img, ScenePtr& scene, int x, int y) : x(x), y(y) {
	object = Object::create(img, scene, x, y);
}

void Note::Create(const string& img, ScenePtr& scene, int x, int y) {
	this->x = x;
	this->y = y;
	object = Object::create(img, scene, x, y);
}

void Note::Drop(ScenePtr& scene, char& speed) {
	y -= speed;
	object->locate(scene, x, y);
}

void Note::ReturnStart(ScenePtr& scene) {
	this->y = 720;
	object->locate(scene, this->x, 720);
}