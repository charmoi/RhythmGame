#include <bangtal>
#include <iostream>
#include <Windows.h>

using namespace bangtal;
using namespace std;

extern PTP_TIMER pFTimer;
extern PTP_TIMER pBTimer;
extern bool timerDeleted;
extern FILETIME ftStartTime;

ScenePtr start_page = Scene::create("시작", "Images/startpage.png");

void InitSelectPage();	// 곡 선택 페이지 생성
void SongSelect();		// 곡 선택 페이지 이동
void InitInGame();		// 게임 플레이창 생성
void InitGameResult();	// 게임 결과창 생성

void Opening() {
	ObjectPtr opening_t1 = Object::create("Images/start_t1.png", start_page, 0, 189);
	ObjectPtr opening_t2 = Object::create("Images/start_t2.png", start_page, 0, 45);
	ObjectPtr opening_inst = Object::create("Images/pressEnter.png", start_page, 735, 60);

	TimerPtr t1 = Timer::create(0.5f);
	TimerPtr t2 = Timer::create(0.5f);

	SoundPtr opening_bgm = Sound::create("Sounds/start.mp3");
	opening_bgm->play(true);

	start_page->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		switch (key) {
		case KeyCode::KEY_ENTER:
			t1->stop();
			t2->stop();
			opening_bgm->stop();
			SongSelect();
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

	ULARGE_INTEGER ulStartTime;
	ulStartTime.QuadPart = (LONGLONG)-(10000000);
	ftStartTime.dwHighDateTime = ulStartTime.HighPart;
	ftStartTime.dwLowDateTime = ulStartTime.LowPart;

	InitSelectPage();
	InitInGame();
	InitGameResult();
	Opening();

	if (!timerDeleted) {
		WaitForThreadpoolTimerCallbacks(pFTimer, true);
		CloseThreadpoolTimer(pFTimer);
		WaitForThreadpoolTimerCallbacks(pBTimer, true);
		CloseThreadpoolTimer(pBTimer);
		cout << endl << "Timer deleted" << endl;
	}

	return 0;
}