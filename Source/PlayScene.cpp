#include "PlayScene.h"
#include <DxLib.h>
#include "Stage.h"

PlayScene::PlayScene()
{
	new Stage();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	Stage* st = FindGameObject<Stage>();
	if (st->GetAlive() == false){
		SceneManager::ChangeScene("RESULT");
	}
}

void PlayScene::Draw()
{
	Stage* st = FindGameObject<Stage>();
	int timer = st->GetTimer();
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "timer : %03d", timer);

	//DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	//DrawString(100, 400, "Push [L]Key To Result", GetColor(255, 255, 255));
	DrawString(20, 0, buffer, GetColor(255, 255, 255));
	//printfDx("time: %03d", tiemr);
}

