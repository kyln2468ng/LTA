#pragma once
#include "../Library/SceneBase.h"

class OperationScene : public SceneBase
{
public:
	OperationScene();
	~OperationScene();
	void Update() override;
	void Draw() override;
private:
	int opeImage;
};
