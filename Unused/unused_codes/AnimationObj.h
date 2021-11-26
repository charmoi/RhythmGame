#pragma once

#include <bangtal>

using namespace bangtal;
using namespace std;

class AnimationObj {
private:
	int x, y;
	ObjectPtr obj;
	ScenePtr scene;
	bool moving;
	bool blinking;
	bool shown;

public:
	AnimationObj(string img, ScenePtr scene, int x, int y);
	// 입력한 x, y 좌표로 speed 픽셀값만큼 0.1초마다 이동
	void MoveTo(int dest_x, int dest_y, int speed);	
	// 깜빡이기
	void Blink(const double interval);
	// 깜빡임 종료
	void BlinkStop();
	// 물체 보이기
	void Show();
	// 물체 숨기기
	void Hide();
	// 움직임 여부 반환
	bool IsMoving();
	// 보이기 여부 반환
	bool IsShown();
};
