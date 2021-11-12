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
	for (int i = 0; i < 7; i++) {
		map >> buf;
	}

	note_map = make_unique<bool[]>(lines * 4); // lines: ��� * 4: key ����

	int check_note; // ��Ʈ Ȯ�� ����
	int count1 = 0;
	int count0 = 0;
	for (int i = 0; i < lines; i++) {
		map >> buf;
		map >> buf;
		map >> buf;
		for (int j = 0; j < 4; j++) {
			map >> check_note;
			if (check_note == 0) {
				count0++;
				note_map[i * 4 + j] = false;
			}
			else if (check_note == 1) {
				count1++;
				note_map[i * 4 + j] = true;
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

bool NoteJudge(int press_time, int start_time) {
	int diff_abs = abs(press_time - (start_time + delay));	// delay: ��Ʈ�� ��� ����(0)���� judgeline(680)���� �����ϴ� �� �ҿ�Ǵ� �ð�(ms)
	if (diff_abs < 25) {
		score.Add(judge.PerfectInc()); // ***�޺� ���ʽ� �߰��ϱ�!!!
		return true;
	}
	else if (diff_abs < 35) {
		score.Add(judge.GreatInc());
		return true;
	}
	else if (diff_abs < 60) {
		score.Add(judge.GoodInc());
		return true;
	}
	
	return false;	// miss ������ timer �ݹ鿡 ����
}

void KeyAction(char key, bool& pressed, int pressed_t) {
	if (pressed) {
		if (NoteJudge(pressed_t, note_time[key][time_index[key]])) {
			note_move[key][time_index[key]] = false;
			note_img[key][time_index[key]].ReturnStart(ingame_page);
			if (++time_index[key] == IMG_POOL) {						// IMG_POOL��ŭ�� �ε����� ����Ŭ�� ���ư��� ���������� ����
				time_index[key] = 0;
			}
			combo.Increase();
		}
		keylight[key]->show();
	}
	else {
		keylight[key]->hide();
	}
}

void SetKeyboard() {
	ingame_page->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		switch (key) {
		case KeyCode::KEY_D:
			pressed_time[D] = ms_count;
			KeyAction(D, pressed, pressed_time[D]);
			break;
		case KeyCode::KEY_F:
			pressed_time[F] = ms_count;
			KeyAction(F, pressed, pressed_time[F]);
			break;
		case KeyCode::KEY_J:
			pressed_time[J] = ms_count;
			KeyAction(J, pressed, pressed_time[J]);
			break;
		case KeyCode::KEY_K:
			pressed_time[K] = ms_count;
			KeyAction(K, pressed, pressed_time[K]);
			break;
		case KeyCode::KEY_BACKSPACE:
			if (!pressed) {
				songs[song_index].Stop();
				if (DeleteTimerQueueTimer(NULL, frameTimer, INVALID_HANDLE_VALUE)) {
					cout << "\nTimer deleted" << endl;
				}
				else {
					cout << "\nTimer deletion failed" << endl;
				}
				SongSelect();
			}
			break;
		case KeyCode::KEY_ENTER:
			if (pressed) {
				if (safeEnd) {
					if (DeleteTimerQueueTimer(NULL, frameTimer, INVALID_HANDLE_VALUE)) {
						cout << "\nTimer deleted" << endl;
					}
					else {
						cout << "\nTimer deletion failed" << endl;
					}
				}
			}
			break;
		}

		return true;
		});
}

void InitInGame() {
	ingame_page = Scene::create("���� �÷���", "Images/ingame_bg.png");
	keylight[D] = Object::create("Images/note1_light.png", ingame_page, 294, Y(704));
	keylight[F] = Object::create("Images/note2_light.png", ingame_page, 382, Y(704));
	keylight[J] = Object::create("Images/note3_light.png", ingame_page, 469, Y(704));
	keylight[K] = Object::create("Images/note4_light.png", ingame_page, 557, Y(704));
	for (int i = 0; i < 4; i++)
		keylight[i]->hide();
	for (int i = 0; i < IMG_POOL; i++) {
		note_img[D][i].Create("Images/note1.png", ingame_page, 309, 720);
		note_img[F][i].Create("Images/note2.png", ingame_page, 396, 720);
		note_img[J][i].Create("Images/note3.png", ingame_page, 484, 720);
		note_img[K][i].Create("Images/note4.png", ingame_page, 572, 720);
	}

	console = Object::create(songs[0].cs, ingame_page, 0, 0);	// 0�� �� �̹����� �ӽ� ����

	string temp[10];
	char buf[20];
	for (int i = 0; i < 10; i++) {
		sprintf_s(buf, "Images/%d.png", i);
		temp[i] = buf;
	}
	score.Create(temp, 16, ingame_page, 227, Y(98), 6);

	for (int i = 0; i < 10; i++) {
		sprintf_s(buf, "Images/combo_%d.png", i);
		temp[i] = buf;
	}
	combo.Create(temp, 34, ingame_page, 212, Y(204), 3);
	combo.Hide();

	string img[4] = { "Images/miss.png", "Images/good.png", "Images/great.png", "Images/perfect.png" };
	judge.Create(img, ingame_page, 113, Y(220));

	SetKeyboard();

	//timerQueue = CreateTimerQueue();
}

VOID CALLBACK frameCallback(PVOID lpParam, BOOLEAN TimerOrWaitFired) {
	if (!songPlaying && ms_count == delay) {
		ingame_page->enter();
		songs[song_index].Play(false);			// Ÿ�̸� ȣ�� ������ �뷡 ������ ���߱� ����, �뷡 ���� ������ �ݹ� �Լ� ������ ����
		songPlaying = true;						// ���� ��� ����, ��� �ݺ� ����
	}

	if (!lastLine && ms_index == 0) {					// bpmTosec ������ map �迭 �˻�
		for (int i = 0; i < 4; i++) {					// 1ȸ �˻翡 5���� �б�; 5Ű
			if (note_map[line_index * 4 + i]) {
				note_move[i][img_index[i]] = true;
				note_time[i][img_index[i]] = ms_count;	// note ���� �ð� ���
				if (++img_index[i] == IMG_POOL) {		// �� Ű���� IMG_POOL��ŭ�� �̹����� ����Ŭ�� ���ư��� ���
					img_index[i] = 0;
				}
			}
		}
		line_index++;									// ���� �˻� ��, note_map�� ���� �� �б�
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < IMG_POOL; j++) {
			if (note_move[i][j]) {
				note_img[i][j].Drop(ingame_page, speed);
				if (note_img[i][j].y < -33) {
					if (++time_index[i] == IMG_POOL) {	// ��Ʈ ���� �ð� �ε��� ����; ���� �������� ��Ʈ�� �ð� �б�
						time_index[i] = 0;
					}
					combo.Reset();
					judge.MissInc();
					note_move[i][j] = false;
					note_img[i][j].ReturnStart(ingame_page);
				}
			}
		}
	}

	if (line_index == lines) {							// �� ���� ���� �����ϸ� ������ ���� ���μ��� ����
		lastLine = true;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < IMG_POOL; j++) {
				if (note_img[i][j].y == 0) {			// ��� ��Ʈ �̹����� ����ġ�� ���ư� ������ ��ٸ�
					safeEnd = true;					// ���� Ű (Ÿ�̸� �Ҹ� �Լ�) �۵� ����
				}
			}
		}
		return;
	}

	if (++ms_index == bpmTosec) {
		ms_index = 0;
	}

	ms_count++;
}

void ResetInGame() {
	console->setImage(songs[song_index].cs);
	score.Reset();
	score.Show();
	combo.Reset();

	for (int i = 0; i < 4; i++) {
		img_index[i] = 0;
		time_index[i] = 0;
		for (int j = 0; j < IMG_POOL; j++) {
			note_move[i][j] = false;
			note_img[i][j].ReturnStart(ingame_page);
			note_time[i][j] = 10000;				// ���� ���� �� �� ������ �� ���� �νĵǴ� �� ����
		}
	}
	// ���� �������� ���� �־����!!
	bpmTosec = 60 * 1000 / bpm / split;	// bpmTosec�� = 60�� * 1000(ms��ȯ) / bpm / split(�� ���� ��� �ɰ��°�)
	songPlaying = false;
	line_index = 0;
	ms_index = 0;									// ms_index�� 0���� ����
	lastLine = false;
	safeEnd = false;
	ms_count = 1;									// ms_count�� 1ms���� ����
	speed = songs[song_index].speed;				// delay ���� ������ ������������� 680�� ����� ����
	delay = 680 / speed;							// 680: ��Ʈ ����������� ������������ �̵��Ÿ�
	judge.Reset();
}

void InGame() {
	if (CreateMap(song_index, note_map)) {
		ResetInGame();
	}
	else {
		cout << "\nMap Building Failure." << endl;
		endGame();
	}
	
	CreateTimerQueueTimer(&frameTimer, NULL, frameCallback, NULL, 100, 1, WT_EXECUTEDEFAULT);
}