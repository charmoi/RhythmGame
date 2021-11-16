#include "GameResult.h"
#include "Others.h"
#include <iostream>


void InitGameResult() {
	result_page = Scene::create("���� ���", "Images/NAKKA_bg.png");
	bg = Object::create("Images/NAKKA_result.png", result_page, 0, 0);	// ���� �̹����� �ʱ�ȭ
	string temp[10];
	char buf[20];
	for (int i = 0; i < 10; i++) {
		sprintf_s(buf, "Images/%d.png", i);
		temp[i] = buf;
	}
	perfect.Create(temp, 18, result_page, 759, Y(154), 3);
	great.Create(temp, 18, result_page, 759, Y(234), 3);
	good.Create(temp, 18, result_page, 759, Y(314), 3);
	miss.Create(temp, 18, result_page, 759, Y(394), 3);
	maxcombo.Create(temp, 18, result_page, 759, Y(500), 3);
	scoreResult.Create(temp, 18, result_page, 1044, Y(527), 6);

	gradeResult = Object::create("Images/gradeF.png", result_page, 807, Y(433));
	gradeResult->hide();
	newRecord = Object::create("Images/newRecord.png", result_page, 826, Y(176));
	newRecord->hide();

	scoreSound = Sound::create("Sounds/score.mp3");
	gradeSound = Sound::create("Sounds/grade.mp3");

	result_page->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		if (key == KeyCode::KEY_ENTER && !pressed) {
			if (endAnimation) {
				WaitForThreadpoolTimerCallbacks(pFTimer, TRUE);
				CloseThreadpoolTimer(pFTimer);
				cout << endl << "Timer deleted" << endl;
				SongSelect();
			}
		}

		return true;
		});

}

void GradeCalc() {
	if (isGameover) {
		songs[song_index].grade = "Images/gradeF.png";
		gradeResult->setImage(songs[song_index].grade);
		return;
	}
	if (judge.GetPerfect() == judge.GetTotal()) {
		songs[song_index].grade = "Images/gradePFT.png";
		gradeResult->setImage(songs[song_index].grade);
		return;
	}

	float percentage = (SCORE_GOD * judge.GetGood() + SCORE_GRT * judge.GetGreat() + SCORE_PFT * judge.GetPerfect()) / (SCORE_PFT * judge.GetTotal()) * 100;

	if (percentage < 70)
		songs[song_index].grade = "Images/gradeD.png";
	else if (percentage < 80)
		songs[song_index].grade = "Images/gradeC.png";
	else if (percentage < 90)
		songs[song_index].grade = "Images/gradeB.png";
	else if (percentage < 95)
		songs[song_index].grade = "Images/gradeA.png";
	else
		songs[song_index].grade = "Images/gradeS.png";

	gradeResult->setImage(songs[song_index].grade);
}

void HighscoreCalc() {
	if (songs[song_index].highscore < score.GetScore()) {
		songs[song_index].highscore = score.GetScore();
		isNewRecord = true;
	}
}

VOID CALLBACK timerCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer) {
	if (endAnimation) {
		return;
	}
	if (startGrade) {
		if (gradeScale > 1.f) {
			gradeScale -= 0.1f;
			gradeResult->setScale(gradeScale);
			return;
		}
		else if (gradeScale <= 1.f) {
			gradeSound->play(false);
			if (isNewRecord) {
				Sleep(1000);
				newRecord->show();
				// ȿ���� �߰�
			}
			endAnimation = true;
		}
	}
	if (playScore) {
		scoreSound->play(true);
		playScore = false;
	}

	if (perfect.GetScore() != judge.GetPerfect()) {
		perfect.Increase();
		return;
	}
	if (great.GetScore() != judge.GetGreat()) {
		great.Increase();
		return;
	}
	if (good.GetScore() != judge.GetGood()) {
		good.Increase();
		return;
	}
	if (miss.GetScore() != judge.GetMiss()) {
		miss.Increase();
		return;
	}
	if (maxcombo.GetScore() != comboMax) {
		maxcombo.Increase();
		return;
	}
	scoreSound->stop();
	scoreResult.Update(score.GetScore());

	startGrade = true;
	gradeResult->show();
}

void ResetGameResult() {

}

void GameResult() {
	// bgm �÷���

	GradeCalc();
	HighscoreCalc();

	pFTimer = CreateThreadpoolTimer(timerCallback, NULL, NULL);
	timerDeleted = false;

	if (NULL == pFTimer) {
		cout << endl << "Animation timer failed: False Creation" << endl;
		endGame();
	}

	cout << endl << "perfect: " << judge.GetPerfect() << endl;
	cout << endl << "great: " << judge.GetGreat() << endl;
	cout << endl << "good: " << judge.GetGood() << endl;
	cout << endl << "miss: " << judge.GetMiss() << endl;

	playScore = true;
	startGrade = false;
	endAnimation = false;
	isNewRecord = false;
	gradeScale = 5.f;
	gradeResult->setScale(gradeScale);

	result_page->enter();

	SetThreadpoolTimer(pFTimer, &ftStartTime, 25, 0);
	cout << endl << "Timer start" << endl;
}