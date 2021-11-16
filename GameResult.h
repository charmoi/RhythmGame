#pragma once
#include <bangtal>
#include "Score.h"
#include "SongInfo.h"
#include "Judge.h"

using namespace bangtal;
using namespace std;

//---------------SongSelect에서 넘겨 받는 변수-------------
extern SongInfo songs[];
extern int song_index;

//---------------InGame에서 넘겨 받는 변수-----------------
extern Judge judge;
extern int comboMax;
extern Score score;

//---------------GameResult에서 사용하는 객체--------------
ScenePtr result_page;
ObjectPtr bg;
Score perfect;
Score great;
Score good;
Score miss;
Score maxcombo;
Score scoreResult;
ObjectPtr gradeResult;
ObjectPtr newRecord;
SoundPtr scoreSound;


// 게임 결과창 생성
void InitGameResult();
void GameResult();