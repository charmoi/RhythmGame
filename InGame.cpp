#include "InGame.h"
#include "Others.h"
#include <Windows.h>
#include <threadpoollegacyapiset.h>

bool CreateMap(int& index, unique_ptr<bool[]>& note_map) {
	note_map.reset();
	
	ifstream map(songs[index].mapfile);
	if (map.fail()) {
		cout << "���� ���� ����" << endl;
		return false;
	}

	string buf;
	for (int i = 0; i < 5; i++) {
		map >> buf;
	}
	map >> bpm;
	map >> buf;
	map >> lines;
	map >> buf;
	map >> split;
	for (int i = 0; i < 8; i++) {
		map >> buf;
	}

	note_map = make_unique<bool[]>(lines * 5); // lines: ��� * 5: key ����

	int check_note; // ��Ʈ Ȯ�� ����
	int count1 = 0;
	int count0 = 0;
	for (int i = 0; i < lines; i++) {
		map >> buf;
		map >> buf;
		map >> buf;
		for (int j = 0; j < 5; j++) {
			map >> check_note;
			if (check_note == 0) {
				count0++;
				note_map[i * 5 + j] = false;
			}
			else if (check_note == 1) {
				count1++;
				note_map[i * 5 + j] = true;
			}
			else {
				cout << "\nInvalid Note Value: Check the note map file at line: " << i << ", col: " << j << endl;
				return false;
			}
		}
	}

	map.close();
	cout << "\nMap Copy Complete! Notes: " << count1 << " Empties: " << count0 << endl;
	return true;
};

void SetKeyboard() {
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
				if (lastLine) {
					if (DeleteTimerQueueTimer(NULL, frameTimer, INVALID_HANDLE_VALUE)) {
						cout << "\nTimer deleted" << endl;
					}
					else {
						cout << "\nTimer deletion failed" << endl;
					}
				}
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
		case KeyCode::KEY_ESCAPE:
			if (pressed) {

			}
			break;
		}

		return true;
		});


}

void InitInGame() {
	ingame_page = Scene::create("���� �÷���", "Images/ingame_bg.png");
	keylight[D] = Object::create("Images/keylight_blue.png", ingame_page, 206, Y(704));
	keylight[F] = Object::create("Images/keylight_green.png", ingame_page, 294, Y(704));
	keylight[SP] = Object::create("Images/keylight_yellow.png", ingame_page, 382, Y(704));
	keylight[J] = Object::create("Images/keylight_green.png", ingame_page, 469, Y(704));
	keylight[K] = Object::create("Images/keylight_blue.png", ingame_page, 557, Y(704));
	for (int i = 0; i < 5; i++)
		keylight[i]->hide();
	for (int i = 0; i < IMG_POOL; i++) {
		note_img[D][i].Create("Images/note3.png", ingame_page, 221, 720);
		note_img[F][i].Create("Images/note2.png", ingame_page, 309, 720);
		note_img[SP][i].Create("Images/note1.png", ingame_page, 396, 720);
		note_img[J][i].Create("Images/note2.png", ingame_page, 484, 720);
		note_img[K][i].Create("Images/note3.png", ingame_page, 572, 720);
	}

	console = Object::create(songs[0].cs, ingame_page, 0, 0);	// tutorial �̹����� �ӽ� ����
	inst = Object::create("Images/ingame_inst.png", ingame_page, 967, Y(689));
	string temp[10];
	char buf[20];
	for (int i = 0; i < 10; i++) {
		sprintf_s(buf, "Images/%d.png", i);
		temp[i] = buf;
	}
	score.Create(temp, 16, ingame_page, 141, Y(98), 6);

	SetKeyboard();
}

VOID CALLBACK frameCallback(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
	if (!songPlaying) {
		songs[song_index].Play(false);			// Ÿ�̸� ȣ�� ������ �뷡 ������ ���߱� ����, �뷡 ���� ������ �ݹ� �Լ� ������ ����
		songPlaying = true;						// ���� ��� ����, ��� �ݺ� ����
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < IMG_POOL; j++) {
			if (note_move[i][j]) {
				note_img[i][j].Drop(ingame_page);
			}
			if (note_img[i][j].y < 0) {
				note_move[i][j] = false;
				note_img[i][j].ReturnStart(ingame_page);
			}

		}
	}
	if (line_index == lines) {					// ���� �˻� ��, note_map�� ���� �� �б�
		lastLine = true;							// �� ���� ���� �����ϸ� Ÿ�̸� �Ҹ�, ������ ����
		return;
	}
	if (ms_index == 0) {								// bpmTosec ������ map �迭 �˻�
		for (int i = 0; i < 5; i++) {					// 1ȸ �˻翡 5���� �б�; 5Ű
			if (note_map[line_index * 5 + i]) {
				note_move[i][img_index[i]] = true;
				if (++img_index[i] == IMG_POOL) {		// �� Ű���� IMG_POOL��ŭ�� �̹����� ����Ŭ�� ���ư��� ���
					img_index[i] = 0;
				}
			}
		}
		line_index++;
	}

	if (++ms_index == bpmTosec) {
		ms_index = 0;
	}
	if (lastLine) {
		cout << "\nWrong process" << endl;
	}
}

void ResetInGame() {
	console->setImage(songs[song_index].cs);
	score.Reset();

	for (int i = 0; i < 5; i++) {
		img_index[i] = 0;
		for (int j = 0; j < IMG_POOL; j++) {
			note_move[i][j] = false;
		}
	}
	bpmTosec = (double) 60 / bpm / split * 1000;	// bpmTosec�� = 60�� / bpm / split(�� ���� ��� �ɰ��°�)
	songPlaying = false;
	line_index = 0;
	ms_index = 0;
	lastLine = false;
}

void InGame() {
	if (CreateMap(song_index, note_map)) {
		ResetInGame();
	}
	else {
		cout << "\nMap Building Failure." << endl;
		endGame();
	}

	ingame_page->enter();
	CreateTimerQueueTimer(&frameTimer, NULL, frameCallback, NULL, 100, 1, WT_EXECUTEDEFAULT);
}