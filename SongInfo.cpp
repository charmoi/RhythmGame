#include "SongInfo.h"

SongInfo::SongInfo() {
	bg = "\0";
	img = "\0";
	info = "\0";
	cs = "\0";
	result = "\0";
	mapfile = "\0";
	highscore = 0;
	grade = "\0";
	grade_c = '\0';
	speed = 0;
}

SongInfo::SongInfo(const string& bg, const string& img, const string& info, const string& sound, const string& cs, const string& result, const string& mapfile, const char speed)
	: bg(bg), img(img), info(info), cs(cs), result(result), mapfile(mapfile), speed(speed) {
	this->sound = Sound::create(sound);
	highscore = 0;
	grade = "\0";
	grade_c = '\0';
}

void SongInfo::Create(const string& bg, const string& img, const string& info, const string& sound, const string& cs, const string& result, const string& mapfile, const char speed){
	this->bg = bg;
	this->img = img;
	this->info = info;
	this->cs = cs;
	this->result = result;
	this->mapfile = mapfile;
	this->sound = Sound::create(sound);
	this->speed = speed;
}

void SongInfo::Play(bool loop) {
	this->sound->play(loop);
}

void SongInfo::Stop() {
	this->sound->stop();
}