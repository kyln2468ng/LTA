#include "GameOverScene.h"
#include <assert.h>

GameOverScene::GameOverScene()
{
	bImage = LoadGraph("data/image/backImage.png");
	se = LoadSoundMem("data/sound/gameover.mp3");
	assert(se > 0);
	ChangeVolumeSoundMem(128, se);
	PlaySoundMem(se, DX_PLAYTYPE_BACK);
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
