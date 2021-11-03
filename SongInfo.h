#pragma once
#include <bangtal>

using namespace std;
using namespace bangtal;

class SongInfo {
private:
	SoundPtr sound;

protected:
	string bg;
	string img;
	string info;
	string cs;
	string result;
	string mapfile;
	int highscore;
	string grade;

public:
	SongInfo();
	SongInfo(const string& bg, const string& img, const string& info, const string& sound, const string& cs, const string& result, const string& mapfile);
	// 기본 정보 입력
	void Create(const string& bg, const string& img, const string& info, const string& sound, const string& cs, const string& result, const string& mapfile);
	// 노래 재생
	void Play(bool loop = false);
	// 노래 정지
	void Stop();


	friend void InitSelectPage();
	friend void Slide(char dir);
	friend void InitInGame();
	friend void CreateMap();
};