#include "Story.h"

void InitStoryMode() {
	story_mode = Scene::create("스토리모드", "Images/Story/story1.png");
	SceneImage = Object::create("Images/Story/story1.png", story_mode, 0, 0);
	sceneIndex = 1;		// scene 넘버는 1부터 시작

	onStoryMode = false;
	readyToPlay = false;
	happyEnd = false;
	storyRoute = MAIN_R;

	bgmIndex = 0;
	bgm[0] = Sound::create("Sounds/Story/intro.mp3");
	bgm[1] = Sound::create("Sounds/Story/applauselong.mp3");
	fx[0] = Sound::create("Sounds/Story/stadium.mp3");
	fx[1] = Sound::create("Sounds/Story/guitarsolo.mp3");
	bgm[2] = Sound::create("Sounds/Story/backstage.mp3");
	fx[2] = Sound::create("Sounds/Story/swish.mp3");
	fx[3] = Sound::create("Sounds/Story/reveal.mp3");
	bgm[3] = Sound::create("Sounds/Story/intro2.mp3");
	bgm[4] = Sound::create("Sounds/Story/stage1.mp3");
	bgm[5] = Sound::create("Sounds/Story/stage2.mp3");
	fx[4] = Sound::create("Sounds/Story/cheerclose.mp3");
	fx[5] = Sound::create("Sounds/Story/crisis.mp3");
	bgm[6] = Sound::create("Sounds/Story/stage3.mp3");
	bgm[7] = Sound::create("Sounds/Story/stage4.mp3");
	bgm[8] = Sound::create("Sounds/Story/ending1.mp3");
	bgm[9] = Sound::create("Sounds/Story/ending2.mp3");

	for (int i = 0; i < 10; i++) {
		bgmPlaying[i] = false;
	}

	SetKeyStory();
}

void SetKeyStory() {
	story_mode->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		switch (key) {
		case KeyCode::KEY_SPACE:
			if (!pressed) {
				click->play();
				if (!readyToPlay) {
					switch (storyRoute) {
					case MAIN_R:
						if (sceneIndex < 54)
							sceneIndex++;
						CheckSceneMain(sceneIndex);
						break;
					case FAIL_R:
						if (sceneIndex < 12)
							sceneIndex++;
						CheckSceneFail(sceneIndex);
						break;
					case SUCCESS_R:
						if (sceneIndex < 7)
							sceneIndex++;
						CheckSceneSuccess(sceneIndex);
						break;
					}
				}
			}
			else
				click->stop();
			break;
		case KeyCode::KEY_ENTER:
			if (!pressed) {
				CloseSounds();
				if (readyToPlay) {
					InGame(songIndexStory);
				}
				if (happyEnd) {
					happyEnd = false;
					storyRoute = FAIL_R;
					sceneIndex = 1;
					CheckSceneFail(sceneIndex);
				}
			}
			break;
		case KeyCode::KEY_BACKSPACE:
			if (!pressed) {
				CloseSounds();
				GameMode();
			}
		}

		return true;
		});
}

void CheckSceneMain(int& index) {
	char buf[30];											// 장면 전환
	sprintf_s(buf, "Images/Story/story%d.png", index);
	SceneImage->setImage(buf);
	
	switch (index) {										// 스테이지 확인
	case 25:
		songIndexStory = 0;
		readyToPlay = true;
		break;
	case 28:
		songIndexStory = 2;
		readyToPlay = true;
		break;
	case 44:
		songIndexStory = 3;
		readyToPlay = true;
		break;
	case 54:
		songIndexStory = 4;
		readyToPlay = true;
		break;
	default:
		readyToPlay = false;
		break;
	}
	
	// 효과음 재생

	switch (index) {
	case 5:
		fx[0]->play();
		break;
	case 7:
		fx[0]->stop();
		break;
	case 8:
		fx[1]->play();
		break;
	case 10:
		fx[1]->stop();
		break;
	case 15:
		fx[2]->play();
		break;
	case 17:
		fx[2]->stop();
		fx[3]->play();
		break;
	case 19:
		fx[3]->stop();
		break;
	case 29:
		fx[4]->play();
		break;
	case 31:
		fx[4]->stop();
		fx[5]->play();
		break;
	case 33:
		fx[5]->stop();
		break;
	}

	// 배경음 재생

	if (index < 4) {
		bgmIndex = 0;
	}
	else if (index == 4) {
		if (bgmIndex != -1) {
			bgm[bgmIndex]->stop();
			bgmPlaying[bgmIndex] = false;
			bgmIndex = -1;
		}
	}
	else if (index < 8)
		bgmIndex = 1;
	else if (index < 10) {
		if (bgmIndex != -1) {
			bgm[bgmIndex]->stop();
			bgmPlaying[bgmIndex] = false;
			bgmIndex = -1;
		}
	}
	else if (index < 13)
		bgmIndex = 1;
	else if (index < 15)
		bgmIndex = 2;
	else if (index < 19) {
		if (bgmIndex != -1) {
			bgm[bgmIndex]->stop();
			bgmPlaying[bgmIndex] = false;
			bgmIndex = -1;
		}
	}
	else if (index < 22)
		bgmIndex = 3;
	else if (index == 22) {
		if (bgmIndex != -1) {
			bgm[bgmIndex]->stop();
			bgmPlaying[bgmIndex] = false;
			bgmIndex = -1;
		}
	}
	else if (index < 26)
		bgmIndex = 4;
	else if (index < 29)
		bgmIndex = 5;
	else if (index < 32) {
		if (bgmIndex != -1) {
			bgm[bgmIndex]->stop();
			bgmPlaying[bgmIndex] = false;
			bgmIndex = -1;
		}
	}
	else if (index < 45)
		bgmIndex = 6;
	else if (index < 55)
		bgmIndex = 7;

	if (bgmIndex != -1) {
		if (bgmIndex > 0) {
			bgm[bgmIndex - 1]->stop();
			bgmPlaying[bgmIndex - 1] = false;
		}
		if (!bgmPlaying[bgmIndex]) {
			bgm[bgmIndex]->play();
			bgmPlaying[bgmIndex] = true;
		}

	}
}

void CheckSceneFail(int& index) {
	char buf[30];											// 장면 전환
	sprintf_s(buf, "Images/Story/fail%d.png", index);
	SceneImage->setImage(buf);

	switch (index) {										// 스테이지 확인 및 효과음 재생
	case 12:
		songIndexStory = 4;
		readyToPlay = true;
		break;
	default:
		readyToPlay = false;
		break;
	}

	bgmIndex = 8;
	if (!bgmPlaying[bgmIndex]) {
		bgm[bgmIndex]->play();
		bgmPlaying[bgmIndex] = true;
	}

}

void CheckSceneSuccess(int& index) {
	char buf[30];											// 장면 전환
	sprintf_s(buf, "Images/Story/success%d.png", index);
	SceneImage->setImage(buf);

	switch (index) {										// 스테이지 확인 및 효과음 재생
	case 7:
		happyEnd = true;
		break;
	default:
		readyToPlay = false;
		break;
	}

	fx[0]->play();
	bgmIndex = 9;
	if (!bgmPlaying[bgmIndex]) {
		bgm[bgmIndex]->play();
		bgmPlaying[bgmIndex] = true;
	}
}

void StoryMode(bool restart = false) {
	onStoryMode = true;

	if (restart) {
		storyRoute = MAIN_R;
		sceneIndex = 1;
	}

	switch (storyRoute) {
	case MAIN_R:
		CheckSceneMain(sceneIndex);
		break;
	case FAIL_R:
		CheckSceneFail(sceneIndex);
		break;
	case SUCCESS_R:
		CheckSceneSuccess(sceneIndex);
		break;
	}
	story_mode->enter();
}

void CloseSounds() {
	if (bgmIndex != -1) {
		bgm[bgmIndex]->stop();
		bgmPlaying[bgmIndex] = false;
	}
	for (int i = 0; i < 6; i++) {
		fx[i]->stop();
	}
}