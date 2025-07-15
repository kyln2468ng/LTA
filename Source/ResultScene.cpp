#include "ResultScene.h"
#include "../Source/GameData.h"

ResultScene::ResultScene()
{
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
	//DrawString(0, 0, "RESULT SCENE", GetColor(255, 255, 255));
	

	//DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	//DrawString(200, 600, "RESULT", GetColor(255, 255, 255));

	SetFontSize(32);
	static float timer =GameData::GetClearTime();
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "クリアタイム : %3.1f", timer);
	DrawString(200, 100, buffer, GetColor(255, 255, 255));
	SetFontSize(16);
	DrawString(200, 500, "Push [T]Key To Title", GetColor(255, 255, 255));
}
