#pragma once
#include "../Library/SceneBase.h"

class Player;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	int bImage;
	int bgm;
};
