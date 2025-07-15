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
	DrawString(0, 0, "RESULT SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	DrawString(200, 600, "RESULT", GetColor(255, 255, 255));

	static float timer =GameData::GetClearTime();
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "timer : %3.1f", timer);
	DrawString(10, 10, buffer, GetColor(255, 255, 255));
}
