#include "SongSelect.h"
#include "Others.h"

void InitSelectPage(){
	// 곡 정보 입력
	select_page = Scene::create("곡선택", "Images/NAKKA_bg.png");
	// speed 변수에는 680의 약수만 넣기 ex) 8, 10, 17, 20, 40
	songs[0].Create("Images/parachute_bg.png", "Images/parachute_cover.png", "Images/parachute_info.png", "Sounds/parachute_cut.mp3", "Images/parachute_cs.png", "Images/parachute_result.png", "NoteMaps/parachute_JohnK.txt", 8);
	songs[1].Create("Images/WeGo_bg.png", "Images/WeGo_cover.png", "Images/WeGo_info.png", "Sounds/WeGo_125.mp3", "Images/WeGo_cs.png", "Images/WeGo_result.png", "NoteMaps/WeGo_Fromis9.txt", 10);
	songs[2].Create("Images/NAKKA_bg.png", "Images/NAKKA_cover.png", "Images/NAKKA_info.png", "Sounds/NAKKA_100.mp3", "Images/NAKKA_cs.png", "Images/NAKKA_result.png", "NoteMaps/NAKKA_AKMU.txt", 10);
	songs[3].Create("Images/PTD_bg.png", "Images/PTD_cover.png", "Images/PTD_info.png", "Sounds/PTD.mp3", "Images/PTD_cs.png", "Images/PTD_result.png", "NoteMaps/NAKKA_AKMU.txt", 10);

	// 화면 내 오브젝트 생성; 0번 song 이미지 기준으로 최초 설정
	background = Object::create("Images/parachute_bg.png", select_page, 0, 0);
	selected_bg = Object::create("Images/selected_bg.png", select_page, 369, 0);
	song_selected = Object::create("Images/parachute_cover.png", select_page, 400, 208);
	song_left = Object::create("Images/PTD_cover.png", select_page, -112, Y(512));
	song_left->setScale(MINI_ALBUM);
	song_right = Object::create("Images/WeGo_cover.png", select_page, 1008, Y(512));
	song_right->setScale(MINI_ALBUM);
	song_info = Object::create("Images/parachute_info.png", select_page, 412, Y(604));
	highscore_t = Object::create("Images/highscore.png", select_page, 802, Y(576));
	highscore_t->hide();
	string temp[10];
	char buf[20];
	for (int i = 0; i < 10; i++) {
		sprintf_s(buf, "Images/hs%d.png", i);
		temp[i] = buf;
	}
	highscore.Create(temp, 13, select_page, 855, Y(605), 6);
	highscore.Hide();
	grade = Object::create("Images/gradeF.png", select_page, 779, Y(695));
	grade->setScale(MINI_GRADE);
	grade->hide();
	instruction = Object::create("Images/select_inst.png", select_page, 1016, Y(696));
	shade = Object::create("Images/album_shade.png", select_page, -112, Y(512));
	slide = Sound::create("Sounds/slide_low.mp3");

	song_index = 0;
	key_block = false;

	select_page->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		if (key == KeyCode::KEY_F) {
			if (!key_block && pressed)
				Slide(LEFT);
		}
		if (key == KeyCode::KEY_J) {
			if (!key_block && pressed)
				Slide(RIGHT);
		}
		if (key == KeyCode::KEY_SPACE) {
			if (!key_block && pressed) {
				key_block = true;
				songs[song_index].Stop();
				InGame();
			}
		}
		if (!key_block && key == KeyCode::KEY_BACKSPACE) {
			endGame();
		}


		return true;
		});
}

void Slide(char dir) {
	slide->stop();
	songs[song_index].Stop();
	slide->play();
	char right, left;

	switch (dir) {
	case LEFT:
		song_index--;
		if (song_index < 0)
			song_index = SONG_MAX - 1;
		right = song_index + 1;
		if (right >= SONG_MAX)
			right = 0;
		left = song_index - 1;
		if (left < 0)
			left = SONG_MAX - 1;

		break;

	case RIGHT:
		song_index++;
		if (song_index >= SONG_MAX)
			song_index = 0;
		right = song_index + 1;
		if (right >= SONG_MAX)
			right = 0;
		left = song_index - 1;
		if (left < 0)
			left = SONG_MAX - 1;

		break;
	}

	song_selected->setImage(songs[song_index].img);
	songs[song_index].Play(true);
	background->setImage(songs[song_index].bg);
	song_right->setImage(songs[right].img);
	song_left->setImage(songs[left].img);
	song_info->setImage(songs[song_index].info);
	if (songs[song_index].highscore) {
		highscore_t->show();
		highscore.Update(songs[song_index].highscore);
		highscore.Show();
	}
	else {
		highscore_t->hide();
		highscore.Hide();
	}
	if (songs[song_index].grade != "\0") {
		grade->setImage(songs[song_index].grade);
		grade->show();
	}
	else {
		grade->hide();
	}
}

void SongSelect() {
	songs[song_index].Play(true);
	if (songs[song_index].highscore) {
		highscore_t->show();
		highscore.Update(songs[song_index].highscore);
		highscore.Show();
	}
	else {
		highscore_t->hide();
		highscore.Hide();
	}
	if (songs[song_index].grade != "\0") {
		grade->setImage(songs[song_index].grade);
		grade->show();
	}
	else {
		grade->hide();
	}
	select_page->enter();
	key_block = false;
}