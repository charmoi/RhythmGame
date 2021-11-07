#pragma once
#include <bangtal>
#include <Windows.h>

#define SPEED 1		// ������ �ݺ����� ��Ʈ �̹����� �̵��ϴ� �ȼ��Ÿ�

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
	// ��Ʈ ����
	void Create(const string& img, ScenePtr& scene, int x, int y);
	// ��Ʈ �ϰ�
	void Drop(ScenePtr& scene);
	// y��ǥ�� �̵�
	void ReturnStart(ScenePtr& scene);

	//friend void Render();
	friend VOID CALLBACK timerCallback(PVOID lpParam, BOOLEAN TimerOrWaitFired);
};