#include "ResultScene.h"
#include "../Source/GameData.h"

ResultScene::ResultScene()
{
	stareImage = LoadGraph("data/image/stare.png");
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void ResultScene::Draw()
{
	SetFontSize(32);
	float timer =GameData::GetClearTime();
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "クリアタイム : %3.1f", timer);
	DrawString(200, 100, buffer, GetColor(255, 255, 255));

	int w = 1280 / 5;
	int h = 720 / 4;

	SetFontSize(64);
	int result; //GOOD → GREAT → EXCELLENT
	if (timer <= 60.0f)
	{
		result = 3;
		DrawString(1280 / 2, 80, "EXCELLENT!!", GetColor(192, 64, 255));
	}
	else if (timer <= 70.0f)
	{
		result = 2;
		DrawString(1280 / 2, 80, "GREAT!", GetColor(255, 215, 100));
	}
	else
	{
		result = 1;
		DrawString(1280 / 2, 80, "GOOD", GetColor(64, 255, 160));
	}
	
	for (int i = 1; i <= result; i++)
	{
		DrawExtendGraph(w * i, h, w * (i + 1), h + w, stareImage, TRUE);
	}

	SetFontSize(16);
	DrawString(200, 500, "Push [T]Key To Title", GetColor(255, 255, 255));
}
