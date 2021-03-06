#pragma once
#include <bangtal>

#define MISS 0
#define GOOD 1
#define GREAT 2
#define PERFECT 3

#define SCORE_PFT 17
#define SCORE_GRT 13
#define SCORE_GOD 10

using namespace bangtal;
using namespace std;

class Judge {
private:
	ObjectPtr object;
	string img[4];
	int miss;
	int good;
	int great;
	int perfect;
	bool shown;

public:
	Judge();
	Judge(string* img, ScenePtr& scene, const int x, const int y);
	void Create(string* img, ScenePtr& scene, const int x, const int y);
	void MissInc();
	int GoodInc();
	int GreatInc();
	int PerfectInc();
	int GetMiss();
	int GetGood();
	int GetGreat();
	int GetPerfect();
	int GetTotal();
	void Show();
	void Hide();
	void Reset();
};