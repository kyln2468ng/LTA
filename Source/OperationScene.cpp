#include "OperationScene.h"
#include "../Source/GameData.h"

OperationScene::OperationScene()
	:nowP(false),preP(false)
{
	opeImage = LoadGraph("data/image/cnt.png");	
}

OperationScene::~OperationScene()
{
	
}

void OperationScene::Update()
{
	GameData* gd = FindGameObject<GameData>();
	bool scSet = gd->GetScroll();

	nowP = false;
	if (CheckHitKey(KEY_INPUT_O))
	{
		nowP = true;
		if (!preP && nowP)
		{
			gd->SetScroll(!scSet);
		}
	}
	preP = nowP;

	if (CheckHitKey(KEY_INPUT_P))
	{
		SceneManager::ChangeScene("PLAY");
		gd->dethCount = 0;
	}
}

void OperationScene::Draw()
{
	DrawExtendGraph(0, 0, 1280, 720, opeImage, TRUE);
	GameData* gd = FindGameObject<GameData>();
	bool scSet = gd->GetScroll();
	std::string buff;
	if (scSet)
		buff = "ON";
	else
		buff = "OFF";

	std::string message = "強制スクロール　：" + buff;
	SetFontSize(32);
	DrawString(20, 0, message.c_str(), GetColor(255, 255, 255));
	SetFontSize(16);
}
