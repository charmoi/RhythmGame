#pragma once
#include <bangtal>
#include <fstream>
#include <iostream>
#include "SongInfo.h"
#include "Score.h"
#include "Note.h"
#include "Judge.h"
#include "HP.h"

#define D 0
#define F 1
#define J 2
#define K 3

#define IMG_POOL 7		// 노트 하강 애니메이션용 이미지 풀; 동시 가용 노트 이미지 수
#define HP_DEFAULT 18	// 기본 HP값 **HP 최대값은 26; HP.h 참조

using namespace std;
using namespace bangtal;

//---------------ingame_page의 고정 객체-----------------

extern SongInfo songs[];
extern int song_index;
ScenePtr ingame_page;
ObjectPtr keylight[4];
Note note_img[4][IMG_POOL];
ObjectPtr console;
Score score;
Score combo;
Judge judge;
HP hp;
ObjectPtr gameover;
ObjectPtr gameclear;
ObjectPtr press_enter;

//---------------ingame_page의 유동 변수-----------------

unique_ptr<bool[]> note_map;

int bpm;			// 노래의 bpm
int lines;			// 맵의 행 수
int split;			// 한 박을 몇 개로 쪼갰는가
char speed;			// 프레임 반복마다 노트 이미지가 이동하는 픽셀거리

int comboMax;		
double bonus;		// 콤보 수에 따라 점수에 가산되는 보너스
bool isGameover;		// GameResult에 넘겨줄 게임 오버 여부

//---------------Timer 관련 변수-----------------

PTP_TIMER pFTimer;				// 프레임 타이머 포인터
PTP_TIMER pBTimer;				// 비트 타이머 포인터
FILETIME ftStartTime;			// 타이머 duetime 계산용
UINT uFres = 20;				// 프레임 해상도 20ms
UINT bpmTosec;					// bpm과 split을 토대로 노래 최소 박자를 ms 단위로 변환
bool timerDeleted;
bool safeEnd;					// 모든 노트가 제자리로 돌아감; true면 타이머 delete 가능
bool lastLine;					// 마지막 줄 확인; true면 더이상 맵을 읽지 않음

bool img_shown;					// press_enter 문구 깜빡임용

bool note_move[4][IMG_POOL];	// 5가지 key에 대해, note_img를 움직일지 말지 저장
char img_index[4];				// note_move[][i]의 i 인덱스 값을 저장
int line_index;					// 타이머 콜백에서 note_map 배열의 각 행을 읽기 위한 인덱스
bool songPlaying;				// 노래 최초 재생 이후 재생 중첩 방지용
int frame_count;				// 프레임 카운터; 노래 시작 타이밍 맞추기
int trigger_frame;				// 노래가 시작될 프레임; 노트 출발 지점부터 도착지점까지 필요한 프레임 수
int delay;						// 노트 판정 시간 계산용; 프레임 해상도 * trigger_frame
int note_time[4][IMG_POOL];		// 노트가 출발하는 시점의 ms_count를 복사, delay만큼 더해서 계산
char time_index[4];				// note_time을 순서대로 읽기 위한 인덱스
int pressed_time[4];			// 키 누른 시간 저장용


// 게임 결과 창으로 이동
void GameResult();
// 노트 맵 생성
bool CreateMap(int& index, unique_ptr<bool[]>& note_map);
// 판정 함수; 누른 시각과 노트 시작한 시각을 비교
bool NoteJudge(int press_time, int start_time);
// 콤보 보너스 설정
void SetComboBonus(int combo);
// 키보드 입력시 실행 함수
void KeyAction(char key, bool& pressed, int pressed_t);
// 키보드 입력 콜백 세팅
void SetKeyboard();
// 게임 플레이 페이지 빌드
void InitInGame();
// 렌더링용 타이머 콜백 함수
VOID CALLBACK frameCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer);
// 맵리딩용 타이머 콜백 함수
VOID CALLBACK beatCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer);
// 게임 페이지 리셋
void ResetInGame();
// 게임 플레이 페이지로 이동
void InGame();
// 곡 선택 창으로 이동
void SongSelect();
// 플레이 종료 절차
void ClosePlaying();