#pragma once
#include <bangtal>

#define MAIN_R 0
#define FAIL_R 1
#define SUCCESS_R 2

using namespace bangtal;
using namespace std;

extern SoundPtr click;

ScenePtr story_mode;
ObjectPtr SceneImage;
SoundPtr bgm[10];
bool bgmPlaying[10];
int bgmIndex;
SoundPtr fx[6];

bool onStoryMode;					// 게임 플레이 함수에서, 자유/스토리 모드 구분
bool readyToPlay;					// 스토리모드 키조작 제어
int storyRoute;						// 0: 메인 스토리, 1: 성공 결말, 2: 실패 결말
int sceneIndex;						// 현재 씬 넘버 저장
int songIndexStory;					// 스토리모드용 노래 인덱스
bool happyEnd;						// 키조작 제어

void InGame(const int& index);		// 게임 시작

void GameMode();					// 게임 모드 선택으로 이동

void InitStoryMode();				// 스토리모드 객체 빌드
void SetKeyStory();					// 스토리모드 키설정
void CheckSceneMain(int& index);	// 장면별 변수 체크 (메인 스토리)
void CheckSceneFail(int& index);	// 장면별 변수 체크 (실패 결말)
void CheckSceneSuccess(int& index);	// 장면별 변수 체크 (성공 결말)
void StoryGameover();				// 게임 오버 장면 표시
void StoryMode(bool restart);		// 스토리 모드 시작
void CloseSounds();					// 배경음, 효과음 중지