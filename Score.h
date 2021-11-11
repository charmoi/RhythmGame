#pragma once
#include <bangtal>

using namespace bangtal;
using namespace std;

// ���� Object Ŭ����
class Score {
private:
	int score;
	string img[10];
	unique_ptr<ObjectPtr[]> p;
	int length;					// ���� �ڸ���; object ����
	unique_ptr<char[]> index;	// �� �ڸ��� �̹��� �ε���(�� �ڸ��� ����)

public:
	Score();
	// img: �̹��� ���� �ּ� �迭, img_spacing: �̹��� ����, length: ���� �ڸ���
	Score(string* img, const int img_spacing, ScenePtr& scene, const int x, const int y, const int length);
	// img: �̹��� ���� �ּ� �迭, img_spacing: �̹��� ����, length: ���� �ڸ���
	void Create(string* img, const int img_spacing, ScenePtr& scene, const int x, const int y, const int length);
	void Hide();
	void Show();
	// ���� ������Ʈ
	void Update(int score);
	// ���� 0���� ����
	void Reset();
	// ���� 1����
	void Increase();
};