#include <bangtal>
#include <fstream>
#include <iostream>
#include "SongInfo.h"
#include "Score.h"
#include "Note.h"
#include "Others.h"

#define D 0
#define F 1
#define SP 2
#define J 3
#define K 4

#define DELAY 5		// 노래 및 노트 시작 딜레이; 싱크 조절용

using namespace std;
using namespace bangtal;

extern SongInfo songs[];
extern int song_index;
ScenePtr ingame_page;
ObjectPtr keylight[5];
unique_ptr<Note[]> noteD;
unique_ptr<Note[]> noteF;
unique_ptr<Note[]> noteSP;
unique_ptr<Note[]> noteJ;
unique_ptr<Note[]> noteK;
ObjectPtr console;
ObjectPtr inst;
Score score;

// 노래의 bpm 기준으로 노트 y좌표 지정
int NoteLocater(int bpm, int bar);
// 노트 맵 생성
void CreateMap();
void InitInGame();
void InGame();

int NoteLocater(int bpm, int bar) {
	return 669 + (bar + ((double)DELAY / (double)60 / (double)bpm / (double)32)) * SPEED;
}

void CreateMap() {
	ifstream map(songs[song_index].mapfile);
	if (map.fail()) {
		cout << "파일 열기 실패" << endl;
		return;
	}
	
	int bpm;
	int bars;
	int noteD_total = 0;		// 키별 노트 개수 total
	int noteF_total = 0;
	int noteSP_total = 0;
	int noteJ_total = 0;
	int noteK_total = 0;

	string buf;
	for (int i = 0; i < 5; i++) {
		map >> buf;
	}
	map >> bpm;
	map >> buf;
	map >> bars;
	map >> buf;
	map >> noteD_total;
	map >> noteF_total;
	map >> noteSP_total;
	map >> noteJ_total;
	map >> noteK_total;

	noteD = make_unique<Note[]>(noteD_total);
	noteF = make_unique<Note[]>(noteF_total);
	noteSP = make_unique<Note[]>(noteSP_total);
	noteJ = make_unique<Note[]>(noteJ_total);
	noteK = make_unique<Note[]>(noteK_total);

	for (int i = 0; i < 7; i++) {
		map >> buf;
	}

	char check_note; // 노트 확인 버퍼
	int iD = 0;		// 노트 배열 인덱스
	int iF = 0;
	int iSP = 0;
	int iJ = 0;
	int iK = 0;

	for (int i = 1; i <= bars * 32; i++) {
		map >> check_note;
		map >> check_note;
		map >> check_note;
		for (int j = 0; j < 5; j++) {
			map >> check_note;
			switch (check_note) {
			case '1':	// i행(박자; bar), j열(key 종류)에 단노트 존재
				switch (j) {
				case D:
					noteD[iD++] = Note::Note("Images/note3.png", ingame_page, 221, NoteLocater(bpm, i));	// bar(인덱스 i) 위치에 노트 D 생성
					break;
				case F:
					/*noteF[iF++].Create("Images/note2.png", ingame_page, 309, NoteLocater(bpm, i));*/
					noteF[iF++] = Note::Note("Images/note2.png", ingame_page, 309, NoteLocater(bpm, i));
					break;
				case SP:
					noteSP[iSP++] = Note::Note("Images/note1.png", ingame_page, 396, NoteLocater(bpm, i));
					break;
				case J:
					noteJ[iJ++] = Note::Note("Images/note2.png", ingame_page, 484, NoteLocater(bpm, i));
					break;
				case K:
					noteK[iK++] = Note::Note("Images/note3.png", ingame_page, 572, NoteLocater(bpm, i));
					break;
				}
				break;
			}
		}
	}

	if (iD != noteD_total || iF != noteF_total || iSP != noteSP_total || iJ != noteJ_total || iK != noteK_total)
		cout << "노트 생성 오류" << endl;
};

void InitInGame() {
	ingame_page = Scene::create("게임 플레이", "Images/ingame_bg.png");
	keylight[D] = Object::create("Images/keylight_blue.png", ingame_page, 206, Y(704));
	keylight[F] = Object::create("Images/keylight_green.png", ingame_page, 294, Y(704));
	keylight[SP] = Object::create("Images/keylight_yellow.png", ingame_page, 382, Y(704));
	keylight[J] = Object::create("Images/keylight_green.png", ingame_page, 469, Y(704));
	keylight[K] = Object::create("Images/keylight_blue.png", ingame_page, 557, Y(704));
	for (int i = 0; i < 5; i++)
		keylight[i]->hide();
	noteD.reset();
	noteF.reset();
	noteSP.reset();
	noteJ.reset();
	noteK.reset();
	//noteD = nullptr;
	//noteF = nullptr;
	//noteSP = nullptr;
	//noteJ = nullptr;
	//noteK = nullptr;
	CreateMap();
	console = Object::create(songs[song_index].cs, ingame_page, 0, 0);
	inst = Object::create("Images/ingame_inst.png", ingame_page, 967, Y(689));
	string temp[10];
	char buf[20];
	for (int i = 0; i < 10; i++) {
		sprintf_s(buf, "Images/%d.png", i);
		temp[i] = buf;
	}
	score.Create(temp, 16, ingame_page, 141, Y(98), 6);

	ingame_page->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		switch (key) {
		case KeyCode::KEY_D:
			if (pressed) {
				keylight[D]->show();
			}
			else {
				keylight[D]->hide();
			}
			break;
		case KeyCode::KEY_F:
			if (pressed) {
				keylight[F]->show();
			}
			else {
				keylight[F]->hide();
			}
			break;
		case KeyCode::KEY_SPACE:
			if (pressed) {
				keylight[SP]->show();
			}
			else {
				keylight[SP]->hide();
			}
			break;
		case KeyCode::KEY_J:
			if (pressed) {
				keylight[J]->show();
			}
			else {
				keylight[J]->hide();
			}
			break;
		case KeyCode::KEY_K:
			if (pressed) {
				keylight[K]->show();
			}
			else {
				keylight[K]->hide();
			}
			break;
		}

		return true;
		});

	InGame();
}

void InGame() {
	ingame_page->enter();
	songs[song_index].Play();

}