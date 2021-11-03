#pragma once
#include <bangtal>

using namespace bangtal;
using namespace std;

// 점수 Object 클래스
class Score {
private:
	int score;
	string img[10];
	unique_ptr<ObjectPtr[]> p;
	int length;		// 점수 자릿수; object 개수

public:
	Score();
	// img: 이미지 파일 주소 배열, img_spacing: 이미지 간격, length: 점수 자릿수
	Score(string* img, const int img_spacing, ScenePtr& scene, const int x, const int y, const int length);
	// img: 이미지 파일 주소 배열, img_spacing: 이미지 간격, length: 점수 자릿수
	void Create(string* img, const int img_spacing, ScenePtr& scene, const int x, const int y, const int length);
	virtual void Hide();
	virtual void Show();
	// 점수 업데이트
	virtual void Update(int score);
};