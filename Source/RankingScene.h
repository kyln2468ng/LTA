#pragma once
#include "../Library/SceneBase.h"


class RankingScene : public SceneBase
{
public:
	RankingScene();
	~RankingScene();
	void Update() override;
	void Draw() override;
private:
	int bImage;
};
