#include "InGame.h"
#include "Others.h"
#include <Windows.h>
#include <threadpoollegacyapiset.h>

bool CreateMap(int& index, unique_ptr<bool[]>& note_map) {
	note_map.reset();
	
	ifstream map(songs[index].mapfile);
	if (map.fail()) {
		cout << "파일 열기 실패" << endl;
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

	note_map = make_unique<bool[]>(lines * 4); // lines: 행수 * 4: key 개수

	int check_note; // 노트 확인 버퍼
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
	int diff_abs = abs(press_time - (start_time + delay));	// delay: 노트가 출발 지점(0)부터 judgeline(680)까지 도달하는 데 소요되는 시간(ms)
	if (diff_abs < 25) {
		score.Add(judge.PerfectInc()); // ***콤보 보너스 추가하기!!!
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
	
	return false;	// miss 판정은 timer 콜백에 있음
}

void KeyAction(char key, bool& pressed, int pressed_t) {
	if (pressed) {
		if (NoteJudge(pressed_t, note_time[key][time_index[key]])) {
			note_move[key][time_index[key]] = false;
			note_img[key][time_index[key]].ReturnStart(ingame_page);
			if (++time_index[key] == IMG_POOL) {						// IMG_POOL만큼의 인덱스를 사이클로 돌아가며 순차적으로 읽음
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
	ingame_page = Scene::create("게임 플레이", "Images/ingame_bg.png");
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

	console = Object::create(songs[0].cs, ingame_page, 0, 0);	// 0번 곡 이미지로 임시 설정

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
		songs[song_index].Play(false);			// 타이머 호출 시점과 노래 시작을 맞추기 위해, 노래 시작 지점을 콜백 함수 안으로 넣음
		songPlaying = true;						// 최초 재생 이후, 재생 반복 방지
	}

	if (!lastLine && ms_index == 0) {					// bpmTosec 단위로 map 배열 검사
		for (int i = 0; i < 4; i++) {					// 1회 검사에 5개씩 읽기; 5키
			if (note_map[line_index * 4 + i]) {
				note_move[i][img_index[i]] = true;
				note_time[i][img_index[i]] = ms_count;	// note 시작 시간 기록
				if (++img_index[i] == IMG_POOL) {		// 각 키별로 IMG_POOL만큼의 이미지를 사이클로 돌아가며 사용
					img_index[i] = 0;
				}
			}
		}
		line_index++;									// 다음 검사 시, note_map의 다음 행 읽기
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < IMG_POOL; j++) {
			if (note_move[i][j]) {
				note_img[i][j].Drop(ingame_page, speed);
				if (note_img[i][j].y < -33) {
					if (++time_index[i] == IMG_POOL) {	// 노트 시작 시간 인덱스 증가; 다음 떨어지는 노트의 시간 읽기
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

	if (line_index == lines) {							// 총 라인 수에 도달하면 렌더링 종료 프로세스 시작
		lastLine = true;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < IMG_POOL; j++) {
				if (note_img[i][j].y == 0) {			// 모든 노트 이미지가 정위치에 돌아갈 때까지 기다림
					safeEnd = true;					// 종료 키 (타이머 소멸 함수) 작동 가능
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
			note_time[i][j] = 10000;				// 게임 시작 시 막 눌렀을 때 판정 인식되는 거 방지
		}
	}
	// 나눠 떨어지는 수로 넣어야함!!
	bpmTosec = 60 * 1000 / bpm / split;	// bpmTosec식 = 60초 * 1000(ms변환) / bpm / split(한 박을 몇개로 쪼갰는가)
	songPlaying = false;
	line_index = 0;
	ms_index = 0;									// ms_index는 0부터 시작
	lastLine = false;
	safeEnd = false;
	ms_count = 1;									// ms_count는 1ms부터 시작
	speed = songs[song_index].speed;				// delay 값이 정수로 나누어떨어지도록 680의 약수로 설정
	delay = 680 / speed;							// 680: 노트 출발지점부터 판정선까지의 이동거리
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