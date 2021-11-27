#pragma once
#include <bangtal>

#define HP_MAX 27			// 배열 길이는 27, hp 최대값은 26
#define HP_LOSS 6

using namespace bangtal;
using namespace std;

class HP {
private:
	ObjectPtr hpLevel[HP_MAX];
	int hp;					// 0 ~ 26 사이의 숫자

public:
	HP();
	HP(const string& img, ScenePtr& scene, int x, int y);
	void Create(const string& img, ScenePtr& scene, int x, int y);
	// HP 구간별(startIndex부터 endIndex까지) 게이지 색 변경
	void SetColor(const string& img, int startIndex, int endIndex);
	void Show();
	void Hide();
	void Update(int new_hp);
	// 1씩 HP 증가
	void Increase();
	// HP_LOSS만큼 HP 감소, 0이 되면 false 값 리턴
	bool Decrease();
};