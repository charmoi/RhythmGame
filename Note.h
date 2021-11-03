#pragma once
#include <bangtal>

#define SPEED 2		// 32���� 1 bar���� note�� �̵��ϴ� �ȼ��Ÿ�

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
	void Locate(int y, ScenePtr& scene);
};