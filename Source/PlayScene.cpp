#include "PlayScene.h"
#include <DxLib.h>
#include "Stage.h"
#include "Player.h"
#include "GameData.h"

PlayScene::PlayScene()
{
	new Stage();
	bImage = LoadGraph("data/image/backImage.png");
	bgm = LoadSoundMem("data/sound/wonderland.mp3");
	ChangeVolumeSoundMem(128, bgm);
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}

PlayScene::~PlayScene()
{
	DeleteGraph(bImage);
	DeleteSoundMem(bgm);
}

void PlayScene::Update()
{
	Stage* st = FindGameObject<Stage>();
	Player* pl = FindGameObject<Player>();
	GameData* gd = FindGameObject<GameData>();

	if (!st->GetAlive()) {
		GameData::SetClearTime(st->GetTimer());
		StopSoundMem(bgm);
		SceneManager::ChangeScene("RESULT");
		return;
	}
	if (!pl || st->GetTimer() < 0) {
		StopSoundMem(bgm);
		gd->dethCount++;
		SceneManager::ChangeScene("GAMEOVER");
		return;
	}

}

void PlayScene::Draw()
{
	SetFontSize(25);
	DrawExtendGraph(0, 0, 1280, 720, bImage, TRUE);
	Stage* st = FindGameObject<Stage>();
	GameData* gd = FindGameObject<GameData>();
	if (st)
	{
		float timer = st->GetTimer();
		char buffer[32];
		snprintf(buffer, sizeof(buffer), "timer : %3.1f", timer);
		DrawString(20, 0, buffer, GetColor(255, 255, 255));
		int dieCount = gd->GetDethCount();
		char buff[32];
		snprintf(buff, sizeof(buff), "éÄñSâÒêî : %3d", dieCount);
		DrawString(20, 70, buff, GetColor(255, 255, 255));

	}
	//DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	//DrawString(100, 400, "Push [L]Key To Result", GetColor(255, 255, 255));
	
	//printfDx("time: %03d", tiemr);
	SetFontSize(16);
}

