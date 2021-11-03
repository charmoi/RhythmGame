#include "SongSelect.h"
#include "Others.h"

void InitSelectPage(){
	// 곡 정보 입력
	select_page = Scene::create("곡선택", "Images/tutorial_bg.png");
	songs[0].Create("Images/tutorial_bg.png", "Images/tutorial_cover.png", "Images/tutorial_info.png", "Sounds/NAKKA_100.mp3", "Images/tutorial_cs.png", "Images/tutorial_result.png", "NoteMaps/NAKKA_AKMU.txt");
	songs[1].Create("Images/parachute_bg.png", "Images/parachute_cover.png", "Images/parachute_info.png", "Sounds/parachute.mp3", "Images/parachute_cs.png", "Images/parachute_result.png", "NoteMaps/NAKKA_AKMU.txt");
	songs[2].Create("Images/STAY_bg.png", "Images/STAY_cover.png", "Images/STAY_info.png", "Sounds/STAY.mp3", "Images/STAY_cs.png", "Images/STAY_result.png", "NoteMaps/NAKKA_AKMU.txt");
	songs[3].Create("Images/AfterSchool_bg.png", "Images/AfterSchool_cover.png", "Images/AfterSchool_info.png", "Sounds/AfterSchool.mp3", "Images/AfterSchool_cs.png", "Images/AfterSchool_result.png", "NoteMaps/NAKKA_AKMU.txt");

	// 화면 내 오브젝트 생성; tutorial 이미지 기준으로 최초 설정
	background = Object::create(songs[0].bg, select_page, 0, 0);
	selected_bg = Object::create("Images/selected_bg.png", select_page, 369, 0);
	song_selected = Object::create(songs[0].img, select_page, 400, 208);
	song_left = Object::create(songs[SONG_MAX - 1].img, select_page, -112, Y(512));
	song_left->setScale(MINI_ALBUM);
	song_right = Object::create(songs[1].img, select_page, 1008, Y(512));
	song_right->setScale(MINI_ALBUM);
	song_info = Object::create(songs[0].info, select_page, 412, Y(604));
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
	grade = Object::create("Images/F.png", select_page, 787, Y(700));
	grade->setScale(MINI_GRADE);
	grade->hide();
	instruction = Object::create("Images/select_inst.png", select_page, 1016, Y(696));
	shade = Object::create("Images/album_shade.png", select_page, -112, Y(512));
	slide = Sound::create("Sounds/slide.mp3");

	song_index = 0;

	select_page->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		if (key == KeyCode::KEY_F) {
			if (pressed)
				Slide(LEFT);
		}
		if (key == KeyCode::KEY_J) {
			if (pressed)
				Slide(RIGHT);
		}
		if (key == KeyCode::KEY_SPACE) {
			if (pressed) {
				songs[song_index].Stop();
				InGame();
			}
		}
		if (key == KeyCode::KEY_BACKSPACE) {
			endGame();
		}


		return true;
		});
}

void Slide(char dir) {
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
	select_page->enter();
}