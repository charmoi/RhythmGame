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
Score combo;
ObjectPtr judge_img[4];

//---------------ingame_page�� ���� ����-----------------

unique_ptr<bool[]> note_map;

int bpm;			// �뷡�� bpm
int lines;			// ���� �� ��
int split;			// �� ���� �� ���� �ɰ��°�
char speed = 1;		// ������ �ݺ����� ��Ʈ �̹����� �̵��ϴ� �ȼ��Ÿ�

//---------------Timer ���� ����-----------------

HANDLE frameTimer;
bool safeEnd;					// ��� ��Ʈ�� ���ڸ��� ���ư�; true�� Ÿ�̸� delete ����
bool lastLine;					// ������ �� Ȯ��; true�� ���̻� ���� ���� ����

int bpmTosec;					// bpm�� split�� ���� �뷡 �ּ� ���ڸ� ms ������ ��ȯ
bool note_move[5][IMG_POOL];	// 5���� key�� ����, note_img�� �������� ���� ����
char img_index[5];				// note_move[][i]�� i �ε��� ���� ����
int line_index;					// bpmT���� note_map �迭�� �� ���� �б� ���� �ε���
bool songPlaying;				// �뷡 ���� ��� ���� ��� ��ø ������
int ms_index;					// 1ms Ÿ�̸ӿ� �ε���
int ms_count;					// ��ü �帥 �ð� ������
int delay;						// �뷡 ���� Ÿ�̹� ���߱� & ��Ʈ ���� �ð� ����
int note_time[5][IMG_POOL];		// ��Ʈ�� ����ϴ� ������ ms_count�� ����, delay��ŭ ���ؼ� ���


// ��Ʈ �� ����
bool CreateMap(int& index, unique_ptr<bool[]>& note_map);
// ���� �Լ�; ���� �ð��� ��Ʈ ������ �ð��� ��
void NoteJudge(int press_time, int start_time);
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