#include "AnimationObj.h"

AnimationObj::AnimationObj(string img, ScenePtr scene, int x, int y) : scene(scene), x(x), y(y) {
	this->obj = Object::create(img, scene, x, y);
	moving = false;
	blinking = false;
	shown = true;
}

void AnimationObj::MoveTo(const int dest_x, const int dest_y, const int speed) {
	moving = true;

	if (this->x == dest_x && this->y == dest_y) {
		moving = false;
		return;
	}
	else if (this->x < dest_x)
		this->obj->locate(scene, this->x += speed, this->y);
	else if (this->x > dest_x)
		this->obj->locate(scene, this->x -= speed, this->y);
	else if (this->y < dest_y)
		this->obj->locate(scene, this->x, this->y += speed);
	else if (this->y > dest_y)
		this->obj->locate(scene, this->x, this->y -= speed);
}

void AnimationObj::Blink(const double interval) {
	this->blinking = true;
	TimerPtr t1 = Timer::create(interval);
	TimerPtr t2 = Timer::create(interval);
	t1->setOnTimerCallback([&](TimerPtr timer)->bool {
		if (this->blinking) {
			this->obj->show();
			timer->set(interval);
			t2->start();
		}
		else
			return true;

		timer->set(interval);
		timer->start();

		return true;
		});

	t2->setOnTimerCallback([&](TimerPtr timer)->bool {
		const double i = interval;
		if (this->blinking) {
			this->obj->show();
			timer->set(i);
			t1->start();
		}
		else
			return true;

		return true;
		});

	this->obj->hide();
	t1->start();
}

void AnimationObj::BlinkStop() {
	this->blinking = false;
}

void AnimationObj::Show() {
	this->shown = true;
	this->obj->show();
}

void AnimationObj::Hide() {
	this->shown = false;
	this->obj->hide();
}

bool AnimationObj::IsMoving() {
	return this->moving;
}

bool AnimationObj::IsShown() {
	return this->shown;
}