#include "OperationScene.h"

OperationScene::OperationScene()
{
	opeImage = LoadGraph("data/image/cnt.png");
}

OperationScene::~OperationScene()
{
	
}

void OperationScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P))
	{
		SceneManager::ChangeScene("PLAY");
	}
}

void OperationScene::Draw()
{
	DrawExtendGraph(0, 0, 1280, 720, opeImage, TRUE);
}
