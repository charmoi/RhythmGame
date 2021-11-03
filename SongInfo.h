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
	// �⺻ ���� �Է�
	void Create(const string& bg, const string& img, const string& info, const string& sound, const string& cs, const string& result, const string& mapfile);
	// �뷡 ���
	void Play(bool loop = false);
	// �뷡 ����
	void Stop();


	friend void InitSelectPage();
	friend void Slide(char dir);
	friend void InitInGame();
	friend void CreateMap();
};