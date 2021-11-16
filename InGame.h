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

#define IMG_POOL 7		// ��Ʈ �ϰ� �ִϸ��̼ǿ� �̹��� Ǯ; ���� ���� ��Ʈ �̹��� ��
#define HP_DEFAULT 18	// �⺻ HP�� **HP �ִ밪�� 26; HP.h ����

using namespace std;
using namespace bangtal;

//---------------ingame_page�� ���� ��ü-----------------

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

//---------------ingame_page�� ���� ����-----------------

unique_ptr<bool[]> note_map;

int bpm;			// �뷡�� bpm
int lines;			// ���� �� ��
int split;			// �� ���� �� ���� �ɰ��°�
char speed;			// ������ �ݺ����� ��Ʈ �̹����� �̵��ϴ� �ȼ��Ÿ�

int comboMax;		
double bonus;		// �޺� ���� ���� ������ ����Ǵ� ���ʽ�
bool isGameover;		// GameResult�� �Ѱ��� ���� ���� ����

//---------------Timer ���� ����-----------------

PTP_TIMER pFTimer;				// ������ Ÿ�̸� ������
PTP_TIMER pBTimer;				// ��Ʈ Ÿ�̸� ������
FILETIME ftStartTime;			// Ÿ�̸� duetime ����
UINT uFres = 20;				// ������ �ػ� 20ms
UINT bpmTosec;					// bpm�� split�� ���� �뷡 �ּ� ���ڸ� ms ������ ��ȯ
bool timerDeleted;
bool safeEnd;					// ��� ��Ʈ�� ���ڸ��� ���ư�; true�� Ÿ�̸� delete ����
bool lastLine;					// ������ �� Ȯ��; true�� ���̻� ���� ���� ����

bool img_shown;					// press_enter ���� �����ӿ�

bool note_move[4][IMG_POOL];	// 5���� key�� ����, note_img�� �������� ���� ����
char img_index[4];				// note_move[][i]�� i �ε��� ���� ����
int line_index;					// Ÿ�̸� �ݹ鿡�� note_map �迭�� �� ���� �б� ���� �ε���
bool songPlaying;				// �뷡 ���� ��� ���� ��� ��ø ������
int frame_count;				// ������ ī����; �뷡 ���� Ÿ�̹� ���߱�
int trigger_frame;				// �뷡�� ���۵� ������; ��Ʈ ��� �������� ������������ �ʿ��� ������ ��
int delay;						// ��Ʈ ���� �ð� ����; ������ �ػ� * trigger_frame
int note_time[4][IMG_POOL];		// ��Ʈ�� ����ϴ� ������ ms_count�� ����, delay��ŭ ���ؼ� ���
char time_index[4];				// note_time�� ������� �б� ���� �ε���
int pressed_time[4];			// Ű ���� �ð� �����


// ���� ��� â���� �̵�
void GameResult();
// ��Ʈ �� ����
bool CreateMap(int& index, unique_ptr<bool[]>& note_map);
// ���� �Լ�; ���� �ð��� ��Ʈ ������ �ð��� ��
bool NoteJudge(int press_time, int start_time);
// �޺� ���ʽ� ����
void SetComboBonus(int combo);
// Ű���� �Է½� ���� �Լ�
void KeyAction(char key, bool& pressed, int pressed_t);
// Ű���� �Է� �ݹ� ����
void SetKeyboard();
// ���� �÷��� ������ ����
void InitInGame();
// �������� Ÿ�̸� �ݹ� �Լ�
VOID CALLBACK frameCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer);
// �ʸ����� Ÿ�̸� �ݹ� �Լ�
VOID CALLBACK beatCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer);
// ���� ������ ����
void ResetInGame();
// ���� �÷��� �������� �̵�
void InGame();
// �� ���� â���� �̵�
void SongSelect();
// �÷��� ���� ����
void ClosePlaying();