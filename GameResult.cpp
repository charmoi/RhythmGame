#include "GameResult.h"
#include "Others.h"
#include <iostream>


void InitGameResult() {
	result_page = Scene::create("게임 결과", "Images/NAKKA_bg.png");
	bg = Object::create("Images/NAKKA_result.png", result_page, 0, 0);	// 낙하 이미지로 초기화
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
				timerDeleted = true;
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

	int score = SCORE_GOD * judge.GetGood() + SCORE_GRT * judge.GetGreat() + SCORE_PFT * judge.GetPerfect();
	int max = SCORE_PFT * judge.GetTotal();

	double percentage = (double)score / max * 100;

	if (percentage < 50)
		songs[song_index].grade = "Images/gradeD.png";
	else if (percentage < 70)
		songs[song_index].grade = "Images/gradeC.png";
	else if (percentage < 80)
		songs[song_index].grade = "Images/gradeB.png";
	else if (percentage < 90)
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
		if (playScore) {
			scoreSound->stop();
			scoreResult.Update(score.GetScore());
			gradeResult->show();
			playScore = false;
		}

		if (gradeScale > 1.1) {
			gradeScale -= 0.1;
			gradeResult->setScale(gradeScale);
			return;
		}
		else {
			gradeResult->setScale(1.f);
			endAnimation = true;
			gradeSound->play(false);
			if (isNewRecord) {
				Sleep(100);
				newRecord->show();
				// 효과음 추가
			}
			return;
		}
	}

	if (!playScore) {
		scoreSound->play(true);
		playScore = true;
	}

	if (perfect.GetScore() != judge.GetPerfect())
		perfect.Increase();
	else
		aniDone[0] = true;

	if (great.GetScore() != judge.GetGreat())
		great.Increase();
	else
		aniDone[1] = true;

	if (good.GetScore() != judge.GetGood())
		good.Increase();
	else
		aniDone[2] = true;

	if (miss.GetScore() != judge.GetMiss())
		miss.Increase();
	else
		aniDone[3] = true;

	if (maxcombo.GetScore() != comboMax)
		maxcombo.Increase();
	else
		aniDone[4] = true;

	for (int i = 0; i < 5; i++) {
		if (!aniDone[i])
			return;
	}
	startGrade = true;
}

void ResetGameResult() {
	perfect.Reset();
	great.Reset();
	good.Reset();
	miss.Reset();
	maxcombo.Reset();
	scoreResult.Reset();

	perfect.Show();
	great.Show();
	good.Show();
	miss.Show();
	maxcombo.Show();

	gradeResult->hide();
	newRecord->hide();

	playScore = false;
	startGrade = false;
	endAnimation = false;
	isNewRecord = false;
	gradeScale = 5.f;
	gradeResult->setScale(gradeScale);
	
	for (int i = 0; i < 5; i++)
		aniDone[i] = false;
}

void GameResult() {
	// bgm 플레이
	ResetGameResult();

	GradeCalc();
	HighscoreCalc();

	pFTimer = CreateThreadpoolTimer(timerCallback, NULL, NULL);
	timerDeleted = false;

	if (NULL == pFTimer) {
		cout << endl << "Animation timer failed: False Creation" << endl;
		endGame();
	}

	result_page->enter();

	SetThreadpoolTimer(pFTimer, &ftStartTime, 30, 0);
	cout << endl << "Timer start" << endl;
}