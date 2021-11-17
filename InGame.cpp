#include "InGame.h"
#include "Others.h"
#include <Windows.h>

#pragma comment(lib, "winmm.lib")

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
	if (diff_abs < 33) {
		score.Add(judge.PerfectInc() * bonus); // ***콤보 보너스 추가하기!!!
		return true;
	}
	else if (diff_abs < 50) {
		score.Add(judge.GreatInc() * bonus);
		return true;
	}
	else if (diff_abs < 120) {
		score.Add(judge.GoodInc() * bonus);
		return true;
	}
	
	return false;	// miss 판정은 timer 콜백에 있음
}

void SetComboBonus(int combo) {
	if (combo < 20)
		bonus = 1;
	else if (combo < 50)
		bonus = 1.1;
	else if (combo < 100)
		bonus = 1.15;
	else if (combo < 200)
		bonus = 1.2;
	else if (combo < 300)
		bonus = 1.3;
	else if (combo < 400)
		bonus = 1.4;
	else if (combo < 500)
		bonus = 1.5;
	else
		bonus = 1.6;
}

void KeyAction(char key, bool& pressed, int pressed_t) {
	if (pressed) {
		if (NoteJudge(pressed_t, note_time[key][time_index[key]])) {
			note_move[key][time_index[key]] = false;
			note_img[key][time_index[key]].ReturnStart(ingame_page);
			if (++time_index[key] == IMG_POOL) {						// IMG_POOL만큼의 인덱스를 사이클로 돌아가며 순차적으로 읽음
				time_index[key] = 0;
			}
			SetComboBonus(combo.Increase());
			hp.Increase();
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
			pressed_time[D] = timeGetTime();
			KeyAction(D, pressed, pressed_time[D]);
			break;
		case KeyCode::KEY_F:
			pressed_time[F] = timeGetTime();
			KeyAction(F, pressed, pressed_time[F]);
			break;
		case KeyCode::KEY_J:
			pressed_time[J] = timeGetTime();
			KeyAction(J, pressed, pressed_time[J]);
			break;
		case KeyCode::KEY_K:
			pressed_time[K] = timeGetTime();
			KeyAction(K, pressed, pressed_time[K]);
			break;
		case KeyCode::KEY_BACKSPACE:
			if (!pressed) {
				songs[song_index].Stop();
				ClosePlaying();
				SongSelect();
			}
			break;
		case KeyCode::KEY_ENTER:
			if (!pressed) {
				if (safeEnd) {
					ClosePlaying();
					if (combo.GetScore() > comboMax) {	// All combo 달성시, 여기서 max combo 저장
						comboMax = combo.GetScore();
					}
					GameResult();
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

	hp.Create("Images/life1.png", ingame_page, 130, Y(667));
	hp.SetColor("Images/life2.png", 4, 13);
	hp.SetColor("Images/life3.png", 14, 21);
	hp.SetColor("Images/life4.png", 22, 26);

	gameclear = Object::create("Images/songclear.png", ingame_page, 278, Y(701));
	gameclear->hide();
	gameover = Object::create("Images/gameover.png", ingame_page, 278, Y(701));
	gameover->hide();
	press_enter = Object::create("Images/pressEnterIngame.png", ingame_page, 314, Y(496));
	press_enter->hide();

	clearSound = Sound::create("Sounds/gameclear.mp3");
	overSound = Sound::create("Sounds/gameover.mp3");

	SetKeyboard();
}

VOID CALLBACK frameCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer) {
	if (safeEnd) {						// 게임 종료 플래그
		if (frame_count % 30 == 0) {	// 30프레임(30 * 20ms = 0.6초)마다 깜빡임 효과
			if (!img_shown) {
				press_enter->show();
				img_shown = true;
			}
			else {
				press_enter->hide();
				img_shown = false;
			}
		}
		frame_count++;
		return;
	}

	if (!songPlaying) {
		if (frame_count++ >= trigger_frame) {
			songs[song_index].Play(false);			// 타이머 호출 시점과 노래 시작을 맞추기 위해, 노래 시작 지점을 콜백 함수 안으로 넣음
			songPlaying = true;						// 최초 재생 이후, 재생 반복 방지
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < IMG_POOL; j++) {
			if (note_move[i][j]) {
				note_img[i][j].Drop(ingame_page, speed);
				if (note_img[i][j].y < -50) {
					if (++time_index[i] == IMG_POOL) {	// 노트 시작 시간 인덱스 증가; 다음 떨어지는 노트의 시간 읽기
						time_index[i] = 0;
					}
					note_move[i][j] = false;
					note_img[i][j].ReturnStart(ingame_page);
					if (combo.GetScore() > comboMax) {	// 최대 콤보 수 저장
						comboMax = combo.GetScore();
					}
					combo.Reset();
					judge.MissInc();
					if (!hp.Decrease()) {
						if (!safeEnd) {					// 중복 호출 방지
							safeEnd = true;
							isGameover = true;			// 게임 오버 알림
							gameover->show();
							songs[song_index].Stop();
							overSound->play(false);
						}
					}
				}
			}
		}
	}
	if (lastLine) {
		if (frame_count++ > trigger_frame * 2 + 50) {		// 처음 시작할 때 frame count 한 거 + 마지막 노트 출발부터 판정선 도달까지 count + 50프레임 (20ms*50 = 1초)
			if (!safeEnd) {									// 중복 호출 방지
				safeEnd = true;								// 종료 키 (타이머 소멸 함수) 작동 가능
				gameclear->show();
				clearSound->play(false);
			}
		}
	}

}

VOID CALLBACK beatCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer) {
	if (!lastLine) {									// bpmTosec 단위로 map 배열 검사
		for (int i = 0; i < 4; i++) {					// 1회 검사에 5개씩 읽기; 5키
			if (note_map[line_index * 4 + i]) {
				note_move[i][img_index[i]] = true;
				note_time[i][img_index[i]] = timeGetTime();	// note 시작 시간 기록
				if (++img_index[i] == IMG_POOL) {		// 각 키별로 IMG_POOL만큼의 이미지를 사이클로 돌아가며 사용
					img_index[i] = 0;
				}
			}
		}
		if (++line_index == lines) {						// 다음 검사 시, note_map의 다음 행 읽기
			lastLine = true;								// 마지막 라인에 도달하면, 콜백 내부 건너뛰기
		}
	}
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
	lastLine = false;
	safeEnd = false;
	frame_count = 1;								// frame_count는 1부터 시작
	speed = songs[song_index].speed;				// trigger_frame 값이 정수로 나누어떨어지도록 680의 약수로 설정
	trigger_frame = 680 / speed;					
	delay = uFres * trigger_frame;					// 노트 출발부터 도착까지 걸리는 시간 (ms단위)
	judge.Reset();
	hp.Update(HP_DEFAULT);
	gameover->hide();
	gameclear->hide();
	press_enter->hide();
	comboMax = 0;
	isGameover = false;
}

void InGame() {
	if (CreateMap(song_index, note_map)) {
		ResetInGame();
	}
	else {
		cout << "\nMap Building Failure." << endl;
		endGame();
	}
	
	pFTimer = CreateThreadpoolTimer(frameCallback, NULL, NULL);
	pBTimer = CreateThreadpoolTimer(beatCallback, NULL, NULL);
	timerDeleted = false;
	beatTDeleted = false;

	ingame_page->enter();
	
	SetThreadpoolTimer(pFTimer, &ftStartTime, uFres, 0);
	SetThreadpoolTimer(pBTimer, &ftStartTime, bpmTosec, 0);
	cout << endl << "Timer Start" << endl;
}

void ClosePlaying() {
	if (!timerDeleted) {
		WaitForThreadpoolTimerCallbacks(pFTimer, TRUE);
		WaitForThreadpoolTimerCallbacks(pBTimer, TRUE);
		CloseThreadpoolTimer(pFTimer);
		CloseThreadpoolTimer(pBTimer);
		cout << endl << "Timer deleted" << endl;
		timerDeleted = true;
		beatTDeleted = true;
	}
}