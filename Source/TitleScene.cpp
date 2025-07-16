#include "TitleScene.h"
#include <DxLib.h>

TitleScene::TitleScene()
{
	backImage = LoadGraph("data/image/Title.png");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		SceneManager::ChangeScene("OPERATION");
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
