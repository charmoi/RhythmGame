#pragma once
#include <bangtal>

#define SPEED 2		// 32분의 1 bar마다 note가 이동하는 픽셀거리

using namespace std;
using namespace bangtal;

class Note {
private:
	ObjectPtr object;
	int x;
	
protected:
	int y;

public:
	Note();
	Note(const string& img, ScenePtr& scene, int x, int y);
	// 노트 생성
	void Create(const string& img, ScenePtr& scene, int x, int y);
	// 노트 하강
	void Drop(ScenePtr& scene);
	// y좌표로 이동
	void Locate(int y, ScenePtr& scene);
};