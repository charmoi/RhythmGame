#pragma once
#include <bangtal>
#include <Windows.h>

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
	void Drop(ScenePtr& scene, char& speed);
	// y좌표로 이동
	void ReturnStart(ScenePtr& scene);

	friend VOID CALLBACK frameCallback(PVOID lpParam, BOOLEAN TimerOrWaitFired);
};