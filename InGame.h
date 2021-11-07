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

#define IMG_POOL 5		// ��Ʈ �ϰ� �ִϸ��̼ǿ� �̹��� Ǯ; ���� ���� ��Ʈ �̹��� ��

//#define DELAY 5		// �뷡 �� ��Ʈ ���� ������; ��ũ ������

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

float bpmTosec;
bool note_move[5][IMG_POOL];	// 5���� key�� ����, note_img�� �������� ���� ����
char img_index[5];				// note_move[][i]�� i �ε��� ���� ����
int beat_index;					// bpmT���� note_map �迭�� �� ���� �б� ���� �ε���
TimerPtr bpmT;
TimerPtr frameT;
bool songPlaying;				// �뷡 ���� ��� ���� ��� ��ø ������

// �뷡�� bpm �������� ��Ʈ y��ǥ ����
//int NoteLocater(int bpm, int bar);

// ��Ʈ �� ����
bool CreateMap(int& index, unique_ptr<bool[]>& note_map);
// Ű���� �Է� �ݹ� ����
void SetKeyboard();
// ���� �÷��� ������ ����
void InitInGame();
// ��Ʈ�� ���� ���ư��� Ÿ�̸� ����
// InitInGame �Լ��� ����
// beat �������� ResetInGame �Լ����� ���� �� map file ���� ����� ���� �Էµ�
void BeatTimer();
// ���� ȭ�� ������ �Լ� ����
// InitInGame �Լ��� ����
void Render();
// ���� ������ ����
void ResetInGame();
// ���� �÷��� �������� �̵�
void InGame();