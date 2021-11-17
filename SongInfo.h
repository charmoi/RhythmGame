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
	char speed;

public:
	SongInfo();
	SongInfo(const string& bg, const string& img, const string& info, const string& sound, const string& cs, const string& result, const string& mapfile, const char speed);
	// �⺻ ���� �Է�
	void Create(const string& bg, const string& img, const string& info, const string& sound, const string& cs, const string& result, const string& mapfile, const char speed);
	// �뷡 ���
	void Play(bool loop = false);
	// �뷡 ����
	void Stop();


	//friend void InitSelectPage();
	friend void Slide(char dir);
	friend void SongSelect();

	friend bool CreateMap(int& index, unique_ptr<bool[]>& note_map);
	friend void ResetInGame();

	friend void ResetGameResult();
	friend void GradeCalc();
	friend void HighscoreCalc();
};