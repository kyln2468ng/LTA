#pragma once
#include "../Library/GameObject.h"
#include "Object2D.h"

class SpawnManager : public GameObject
{
public:
	SpawnManager() = default;
	virtual ~SpawnManager() = default;
	virtual void Update() override = 0;
	virtual void Draw() override = 0;

	// 各種登録・リスポーン管理に共通で使う関数
	virtual void RegisterRespawn(VECTOR2 pos, int handle) = 0;
private:
};