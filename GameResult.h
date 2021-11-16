#pragma once
#include <bangtal>
#include "Score.h"
#include "SongInfo.h"
#include "Judge.h"

using namespace bangtal;
using namespace std;

//---------------SongSelect���� �Ѱ� �޴� ����-------------
extern SongInfo songs[];
extern int song_index;

//---------------InGame���� �Ѱ� �޴� ����-----------------
extern Judge judge;
extern int comboMax;
extern Score score;

//---------------GameResult���� ����ϴ� ��ü--------------
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


// ���� ���â ����
void InitGameResult();
void GameResult();