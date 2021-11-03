#pragma once
#include <bangtal>
#include <fstream>
#include <iostream>
#include "SongInfo.h"
#include "Score.h"
#include "Note.h"

#define D 0
#define F 1
#define SP 2
#define J 3
#define K 4

#define IMG_POOL 5		// 노트 하강 애니메이션용 이미지 풀; 동시 가용 노트 이미지 수

//#define DELAY 5		// 노래 및 노트 시작 딜레이; 싱크 조절용

using namespace std;
using namespace bangtal;

//---------------ingame_page의 고정 객체-----------------

extern SongInfo songs[];
extern int song_index;
ScenePtr ingame_page;
ObjectPtr keylight[5];
Note note_img[5][IMG_POOL];
ObjectPtr console;
ObjectPtr inst;
Score score;
//---------------ingame_page의 유동 변수-----------------

unique_ptr<bool[]> note_map;

int bpm;	// 노래의 bpm
int lines;	// 맵의 행 수
int split;	// 한 박을 몇 개로 쪼갰는가

//---------------Timer 관련 변수-----------------

float bpmTosec;
bool note_move[5][IMG_POOL];	// 5가지 key에 대해, note_img를 움직일지 말지 저장
char img_index[5];				// note_move[][i]의 i 인덱스 값을 저장
int beat_index;					// bpmT에서 note_map 배열의 각 행을 읽기 위한 인덱스
TimerPtr bpmT;
TimerPtr frameT;
bool songPlaying;				// 노래 최초 재생 이후 재생 중첩 방지용

// 노래의 bpm 기준으로 노트 y좌표 지정
//int NoteLocater(int bpm, int bar);

// 노트 맵 생성
bool CreateMap(int& index, unique_ptr<bool[]>& note_map);
// 키보드 입력 콜백 세팅
void SetKeyboard();
// 게임 플레이 페이지 빌드
void InitInGame();
// 비트에 맞춰 돌아가는 타이머 설정
// InitInGame 함수에 포함
// beat 설정값은 ResetInGame 함수에서 현재 곡 map file 리딩 결과에 따라 입력됨
void BeatTimer();
// 게임 화면 렌더링 함수 설정
// InitInGame 함수에 포함
void Render();
// 게임 페이지 리셋
void ResetInGame();
// 게임 플레이 페이지로 이동
void InGame();