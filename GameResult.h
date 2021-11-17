#pragma once
#include <bangtal>
#include "Score.h"
#include "SongInfo.h"
#include "Judge.h"
#include <Windows.h>

using namespace bangtal;
using namespace std;

//---------------SongSelect���� �Ѱ� �޴� ����-------------
extern SongInfo songs[];
extern int song_index;
extern bool img_shown;
extern int frame_count;

//---------------InGame���� �Ѱ� �޴� ����-----------------
extern Judge judge;
extern int comboMax;
extern Score score;
extern PTP_TIMER pFTimer;
extern FILETIME ftStartTime;
extern bool timerDeleted;
extern bool isGameover;

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
ObjectPtr pressEnterResult;
SoundPtr scoreSound;
SoundPtr gradeSound;

bool playScore;
bool startGrade;
bool endAnimation;
bool isNewRecord;
float gradeScale;
bool aniDone[5];


// �� ����â���� �̵�
void SongSelect();
// ���� ���â ����
void InitGameResult();
// Grade ��� �Լ�
void GradeCalc();
// Highscore �޼� ���� �˻�
void HighscoreCalc();
// ���� �ö󰡴� �ִϸ��̼�
VOID CALLBACK timerCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer);
// ���� ��� â ����
void ResetGameResult();
void GameResult();