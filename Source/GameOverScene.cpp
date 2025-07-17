#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
	bImage = LoadGraph("data/image/backImage.png");
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
	DrawExtendGraph(0, 0, 1280, 720, bImage, TRUE);
	SetFontSize(128);
	DrawString(1280/4, 250, "GAME OVER", GetColor(180, 30, 30));

	SetFontSize(16);
	DrawString(100,600, "Push [T]Key To Title", GetColor(255, 255, 255));
	DrawString(600, 600, "Push [P]Key To PLAY", GetColor(255, 255, 255));
}
