#pragma once
#include <bangtal>

#define HP_MAX 27			// �迭 ���̴� 27, hp �ִ밪�� 26
#define HP_LOSS 6

using namespace bangtal;
using namespace std;

class HP {
private:
	ObjectPtr hpLevel[HP_MAX];
	int hp;					// 0 ~ 26 ������ ����

public:
	HP();
	HP(const string& img, ScenePtr& scene, int x, int y);
	void Create(const string& img, ScenePtr& scene, int x, int y);
	// HP ������(startIndex���� endIndex����) ������ �� ����
	void SetColor(const string& img, int startIndex, int endIndex);
	void Show();
	void Hide();
	void Update(int new_hp);
	// 1�� HP ����
	void Increase();
	// HP_LOSS��ŭ HP ����, 0�� �Ǹ� false �� ����
	bool Decrease();
};