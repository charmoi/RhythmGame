#pragma once
#include <bangtal>
#include "SongInfo.h"
#include "Score.h"

#define MINI_ALBUM 0.8f
#define MINI_GRADE 0.25f
#define SONG_MAX 4
#define LEFT 0
#define RIGHT 1

ScenePtr select_page;
int song_index;	// 현재 선택한 곡 index
SongInfo songs[SONG_MAX];
ObjectPtr background;
ObjectPtr selected_bg;
ObjectPtr song_selected, song_left, song_right;
ObjectPtr song_info;
ObjectPtr highscore_t;
Score highscore;
ObjectPtr grade;
ObjectPtr instruction;
ObjectPtr shade;
SoundPtr slide;
bool key_block;

// 곡 선택 페이지 빌드
void InitSelectPage();
// 곡 선택 좌우 이동
void Slide(char dir);
void SongSelect();
// 게임 플레이 페이지 이동
void InGame();