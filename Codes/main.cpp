#include <bangtal>
#include <iostream>
#include <Windows.h>
#include "Others.h"

using namespace bangtal;
using namespace std;

extern PTP_TIMER pFTimer;
extern PTP_TIMER pBTimer;
extern bool timerDeleted;
extern bool beatTDeleted;
extern FILETIME ftStartTime;

extern bool onStoryMode;

ScenePtr game_mode;
ObjectPtr opt[3];
ObjectPtr putear;
SoundPtr opening_bgm;
SoundPtr click;
char opt_index;
bool bgmPlayed;


void InitStoryMode();			// ���丮 ��� ����
void InitSelectPage();			// �� ���� ������ ����
void InitInGame();				// ���� �÷���â ����
void InitGameResult();			// ���� ���â ����
void SongSelect();				// �� ���� ������ �̵�
void StoryMode(bool restart);	// ���丮 ��� ����

void GameMode();				// ���� ��� ����
void SetKeyGameMode();			// ���� ��� Ű����
void Opening();					// ���� ������ ����

void GameMode() {
	onStoryMode = false;
	if (!bgmPlayed) {
		opening_bgm->play(true);
	}
	game_mode->enter();
	
}

void SetKeyGameMode() {
	game_mode->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		switch (key) {
		case KeyCode::KEY_F:
			if (pressed) {
				click->play();
				if (opt_index > 0) {
					opt[opt_index]->hide();
					opt[--opt_index]->show();
				}
			}
			else {
				click->stop();
			}
			break;
		case KeyCode::KEY_J:
			if (pressed) {
				click->play();
				if (opt_index < 2) {
					opt[opt_index]->hide();
					opt[++opt_index]->show();
				}
			}
			else {
				click->stop();
			}
			break;
		case KeyCode::KEY_SPACE:
			if (!pressed) {
				switch (opt_index) {
				case 0:
					opening_bgm->stop();
					bgmPlayed = false;
					StoryMode(true);
					break;
				case 1:
					opening_bgm->stop();
					bgmPlayed = false;
					StoryMode(false);
					break;
				case 2:
					opening_bgm->stop();
					bgmPlayed = false;
					SongSelect();
					break;
				}
			}
			break;
		case KeyCode::KEY_ESCAPE:
			if (!pressed) {
				endGame();
			}
			break;
		}

		return true;
		});
}

void Opening() {
	ScenePtr start_page = Scene::create("����", "Images/startpage.png");

	ObjectPtr opening_t1 = Object::create("Images/start_t1.png", start_page, 0, 189);
	ObjectPtr opening_t2 = Object::create("Images/start_t2.png", start_page, 0, 45);
	ObjectPtr opening_inst = Object::create("Images/pressEnter.png", start_page, 735, 60);

	TimerPtr t1 = Timer::create(0.5f);
	TimerPtr t2 = Timer::create(0.5f);

	opening_bgm = Sound::create("Sounds/start.mp3");
	opening_bgm->play(true);
	bgmPlayed = true;

	start_page->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		switch (key) {
		case KeyCode::KEY_ENTER:
			t1->stop();
			t2->stop();
			GameMode();
			break;
		}

		return true;
		});

	t1->setOnTimerCallback([&](TimerPtr timer)->bool {
		opening_inst->hide();
		timer->set(0.5f);
		t2->start();

		return true;
		});

	t2->setOnTimerCallback([&](TimerPtr timer)->bool {
		opening_inst->show();
		timer->set(0.5f);
		t1->start();

		return true;
		});

	t1->start();

	startGame(start_page);
}


int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	timerDeleted = true;
	beatTDeleted = true;

	ULARGE_INTEGER ulStartTime;
	ulStartTime.QuadPart = (LONGLONG)-(10000000);
	ftStartTime.dwHighDateTime = ulStartTime.HighPart;
	ftStartTime.dwLowDateTime = ulStartTime.LowPart;

	game_mode = Scene::create("��弱��", "Images/startoption.png");
	putear = Object::create("Images/putear.png", game_mode, 106, Y(673));
	opt[0] = Object::create("Images/opt1.png", game_mode, 238, Y(539));
	opt[1] = Object::create("Images/opt2.png", game_mode, 538, Y(539));
	opt[2] = Object::create("Images/opt3.png", game_mode, 836, Y(539));
	opt[1]->hide();
	opt[2]->hide();
	opt_index = 0;
	click = Sound::create("Sounds/click.mp3");

	SetKeyGameMode();

	InitStoryMode();
	InitSelectPage();
	InitInGame();
	InitGameResult();
	Opening();		// ���� ���� ����


	//-------------------���α׷� ���� �� ����-------------------------

	if (!timerDeleted) {
		WaitForThreadpoolTimerCallbacks(pFTimer, true);
		CloseThreadpoolTimer(pFTimer);
		cout << endl << "Timer1 deleted" << endl;
	}
	if (!beatTDeleted) {
		WaitForThreadpoolTimerCallbacks(pBTimer, true);
		CloseThreadpoolTimer(pBTimer);
		cout << endl << "Timer2 deleted" << endl;
	}

	return 0;
}