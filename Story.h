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

bool onStoryMode;					// ���� �÷��� �Լ�����, ����/���丮 ��� ����
bool readyToPlay;					// ���丮��� Ű���� ����
int storyRoute;						// 0: ���� ���丮, 1: ���� �ḻ, 2: ���� �ḻ
int sceneIndex;						// ���� �� �ѹ� ����
bool bgmPlaying;
int songIndexStory;					// ���丮���� �뷡 �ε���
bool happyEnd;						// Ű���� ����

void InGame(const int& index);		// ���� ����

void GameMode();					// ���� ��� �������� �̵�

void InitStoryMode();				// ���丮��� ��ü ����
void SetKeyStory();					// ���丮��� Ű����
void CheckSceneMain(int& index);	// ��麰 ���� üũ (���� ���丮)
void CheckSceneFail(int& index);	// ��麰 ���� üũ (���� �ḻ)
void CheckSceneSuccess(int& index);	// ��麰 ���� üũ (���� �ḻ)
void StoryGameover();				// ���� ���� ��� ǥ��
void StoryMode(bool restart);		// ���丮 ��� ����