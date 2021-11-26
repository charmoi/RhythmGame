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
	// �Է��� x, y ��ǥ�� speed �ȼ�����ŭ 0.1�ʸ��� �̵�
	void MoveTo(int dest_x, int dest_y, int speed);	
	// �����̱�
	void Blink(const double interval);
	// ������ ����
	void BlinkStop();
	// ��ü ���̱�
	void Show();
	// ��ü �����
	void Hide();
	// ������ ���� ��ȯ
	bool IsMoving();
	// ���̱� ���� ��ȯ
	bool IsShown();
};
