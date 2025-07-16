#pragma once
#include "Object2D.h"

class Knife;

class Player : public Object2D {
public:
	Player();
	Player(VECTOR2 pos);
	~Player();
	void Update() override;
	void Draw() override;
	void KnifeSrrow();
	void WorkMortion();
private:

	float velocityY;
	bool onGround;
	bool prevPushed; // ナイフ投げる判定一回とるための変数
	bool nowPushued; // ナイフ投げる判定一回とるための変数
	bool prevPushuedS; // ジャンプの判定とるための変数
	bool nowPushuedS; // ジャンプの判定とるための変数

	float Gravity;
	float JumpHeight;
	float JumpV0;
	float MoveSpeed;

	Knife* knife_;
};