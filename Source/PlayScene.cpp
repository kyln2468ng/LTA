#include "PlayScene.h"
#include <DxLib.h>
#include "Stage.h"
#include "Player.h"

PlayScene::PlayScene()
{
	new Stage();
	bImage = LoadGraph("data/image/backImage.png");
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	Stage* st = FindGameObject<Stage>();
	if (st->GetAlive() == false || CheckHitKey(KEY_INPUT_R)){
		SceneManager::ChangeScene("RESULT");
	}
	Player* pl = FindGameObject<Player>();
	if (pl->GetAlive() == false) {
		SceneManager::ChangeScene("GAMEOVER");
	}
}

void PlayScene::Draw()
{
	SetFontSize(32);
	DrawExtendGraph(0, 0, 1280, 720, bImage, TRUE);
	Stage* st = FindGameObject<Stage>();
	float timer = st->GetTimer();
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "timer : %3.1f", timer);

	//DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	//DrawString(100, 400, "Push [L]Key To Result", GetColor(255, 255, 255));
	DrawString(20, 0, buffer, GetColor(255, 255, 255));
	//printfDx("time: %03d", tiemr);
	SetFontSize(16);
}

