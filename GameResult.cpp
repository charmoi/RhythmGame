#include "GameResult.h"
#include "Others.h"

void InitGameResult() {
	result_page = Scene::create("게임 결과", "Images/NAKKA_bs.png");
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
}

void GameResult() {
	// bgm 플레이

}