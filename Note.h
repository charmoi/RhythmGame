#pragma once
#include <bangtal>
#include <Windows.h>

#define SPEED 1		// 프레임 반복마다 노트 이미지가 이동하는 픽셀거리

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
	void ReturnStart(ScenePtr& scene);

	//friend void Render();
	friend VOID CALLBACK timerCallback(PVOID lpParam, BOOLEAN TimerOrWaitFired);
};