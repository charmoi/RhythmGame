#pragma once
#include <bangtal>
#include "Score.h"
#include "SongInfo.h"
#include "Judge.h"
#include <Windows.h>

using namespace bangtal;
using namespace std;

//---------------SongSelect에서 넘겨 받는 변수-------------
extern SongInfo songs[];
extern int song_index;
extern bool img_shown;
extern int frame_count;

//---------------InGame에서 넘겨 받는 변수-----------------
extern Judge judge;
extern int comboMax;
extern Score score;
extern PTP_TIMER pFTimer;
extern FILETIME ftStartTime;
extern bool timerDeleted;
extern bool isGameover;

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
ObjectPtr pressEnterResult;
SoundPtr scoreSound;
SoundPtr gradeSound;

bool playScore;
bool startGrade;
bool endAnimation;
bool isNewRecord;
float gradeScale;
bool aniDone[5];


// 곡 선택창으로 이동
void SongSelect();
// 게임 결과창 생성
void InitGameResult();
// Grade 계산 함수
void GradeCalc();
// Highscore 달성 여부 검사
void HighscoreCalc();
// 점수 올라가는 애니메이션
VOID CALLBACK timerCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer);
// 게임 결과 창 리셋
void ResetGameResult();
void GameResult();