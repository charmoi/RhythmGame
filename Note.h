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
	// ��Ʈ ����
	void Create(const string& img, ScenePtr& scene, int x, int y);
	// ��Ʈ �ϰ�
	void Drop(ScenePtr& scene, char& speed);
	// y��ǥ�� �̵�
	void ReturnStart(ScenePtr& scene);

	friend VOID CALLBACK frameCallback(PVOID lpParam, BOOLEAN TimerOrWaitFired);
};