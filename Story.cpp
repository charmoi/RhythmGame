#include "Story.h"

void InitStoryMode() {
	story_mode = Scene::create("스토리모드", "Images/Story/story1.png");
	SceneImage = Object::create("Images/Story/story54.png", story_mode, 0, 0);
	sceneIndex = 54;		// scene 넘버는 1부터 시작

	onStoryMode = false;
	readyToPlay = false;
	bgmPlaying = false;
	happyEnd = false;
	storyRoute = MAIN_R;

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
	
	switch (index) {										// 스테이지 확인 및 효과음 재생
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
	
	if (!bgmPlaying) {										// 배경음 재생
		if (index < 26) {
			// 배경음 1 플레이
			bgmPlaying = true;
		}
		else if (index < 29) {
			// 배경음 2 플레이
			bgmPlaying = true;
		}
		else if (index < 45) {
			// 배경음 3 플레이
			bgmPlaying = true;
		}
		else if (index < 55) {
			// 배경음 4 플레이
			bgmPlaying = true;
		}
	}

}

void CheckSceneFail(int& index) {
	char buf[30];											// 장면 전환
	sprintf_s(buf, "Images/Story/fail%d.png", index);
	SceneImage->setImage(buf);

	switch (index) {										// 스테이지 확인 및 효과음 재생
	//case 25:
	//	songIndexStory = 0;
	//	readyToPlay = true;
	//	break;
	//case 28:
	//	songIndexStory = 2;
	//	readyToPlay = true;
	//	break;
	//case 44:
	//	songIndexStory = 3;
	//	readyToPlay = true;
	//	break;
	case 12:
		songIndexStory = 4;
		readyToPlay = true;
		break;
	default:
		readyToPlay = false;
		break;
	}

	if (!bgmPlaying) {										// 배경음 재생
		// 배경음 재생
		bgmPlaying = true;
	}

}

void CheckSceneSuccess(int& index) {
	char buf[30];											// 장면 전환
	sprintf_s(buf, "Images/Story/success%d.png", index);
	SceneImage->setImage(buf);

	switch (index) {										// 스테이지 확인 및 효과음 재생
	//case 25:
	//	songIndexStory = 0;
	//	readyToPlay = true;
	//	break;
	//case 28:
	//	songIndexStory = 2;
	//	readyToPlay = true;
	//	break;
	//case 44:
	//	songIndexStory = 3;
	//	readyToPlay = true;
	//	break;
	case 7:
		happyEnd = true;
		break;
	default:
		readyToPlay = false;
		break;
	}

	if (!bgmPlaying) {										// 배경음 재생
		// 배경음 재생
		bgmPlaying = true;
	}

}

void StoryMode(bool restart = false) {
	onStoryMode = true;
	
	if (restart) {
		storyRoute = MAIN_R;
		sceneIndex = 1;
	}
	//if (happyEnd) {
	//	happyEnd = false;
	//	storyRoute = MAIN_R;
	//	sceneIndex = 1;
	//}

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