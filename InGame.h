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

#define IMG_POOL 7		// ��Ʈ �ϰ� �ִϸ��̼ǿ� �̹��� Ǯ; ���� ���� ��Ʈ �̹��� ��

using namespace std;
using namespace bangtal;

//---------------ingame_page�� ���� ��ü-----------------

extern SongInfo songs[];
extern int song_index;
ScenePtr ingame_page;
ObjectPtr keylight[5];
Note note_img[5][IMG_POOL];
ObjectPtr console;
ObjectPtr inst;
Score score;
//---------------ingame_page�� ���� ����-----------------

unique_ptr<bool[]> note_map;

int bpm;	// �뷡�� bpm
int lines;	// ���� �� ��
int split;	// �� ���� �� ���� �ɰ��°�

//---------------Timer ���� ����-----------------

//HANDLE timerQueue;				//
HANDLE frameTimer;
int timerResult;
bool lastLine;

int bpmTosec;					// bpm�� split�� ���� �뷡 �ּ� ���ڸ� ms ������ ��ȯ
bool note_move[5][IMG_POOL];	// 5���� key�� ����, note_img�� �������� ���� ����
char img_index[5];				// note_move[][i]�� i �ε��� ���� ����
int line_index;					// bpmT���� note_map �迭�� �� ���� �б� ���� �ε���
bool songPlaying;				// �뷡 ���� ��� ���� ��� ��ø ������
int ms_index;					// 1ms Ÿ�̸ӿ� �ε���


// ��Ʈ �� ����
bool CreateMap(int& index, unique_ptr<bool[]>& note_map);
// Ű���� �Է� �ݹ� ����
void SetKeyboard();
// ���� �÷��� ������ ����
void InitInGame();
// �������� Ÿ�̸� �ݹ� �Լ�
VOID CALLBACK frameCallback(PVOID lpParam, BOOLEAN TimerOrWaitFired);
// ���� ������ ����
void ResetInGame();
// ���� �÷��� �������� �̵�
void InGame();