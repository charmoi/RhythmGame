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
	char grade_c;
	char speed;

public:
	SongInfo();
	SongInfo(const string& bg, const string& img, const string& info, const string& sound, const string& cs, const string& result, const string& mapfile, const char speed);
	// 기본 정보 입력
	void Create(const string& bg, const string& img, const string& info, const string& sound, const string& cs, const string& result, const string& mapfile, const char speed);
	// 노래 재생
	void Play(bool loop = false);
	// 노래 정지
	void Stop();

	
	friend bool LoadData();
	friend bool SaveData();

	friend void Slide(char dir);
	friend void SongSelect();

	friend bool CreateMap(const int& index, unique_ptr<bool[]>& note_map);
	friend void ResetInGame(const int& index);

	friend void ResetGameResult();
	friend void GradeCalc(const int index);
	friend void HighscoreCalc(const int index);
};