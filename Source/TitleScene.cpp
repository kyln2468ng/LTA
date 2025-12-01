#include "TitleScene.h"
#include <DxLib.h>

TitleScene::TitleScene()
{
	backImage = LoadGraph("data/image/Title.png");
	bgm = LoadSoundMem("data/sound/title.mp3");
	ChangeVolumeSoundMem(128, bgm);
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}

TitleScene::~TitleScene()
{
	DeleteGraph(backImage);
	DeleteSoundMem(bgm);
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		SceneManager::ChangeScene("OPERATION");
	}
	if (CheckHitKey(KEY_INPUT_P))
	{
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DrawExtendGraph(0, 0, 1280, 720, backImage, TRUE);
	//DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	
	SetFontSize(32);
	DrawString(800, 550, "Push [SPACE]Key To Play", GetColor(255, 255, 255));
	SetFontSize(16);
}
