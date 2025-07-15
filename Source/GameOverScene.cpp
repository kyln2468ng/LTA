#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
}

void GameOverScene::Draw()
{
	SetFontSize(32);
	DrawString(300, 250, "game over", GetColor(255, 255, 255));

	SetFontSize(16);
	DrawString(100,600, "Push [T]Key To Title", GetColor(255, 255, 255));
	DrawString(600, 600, "Push [P]Key To PLAY", GetColor(255, 255, 255));
}
