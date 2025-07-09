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
private:
	float velocityY;
	bool onGround;
	bool prevPushed;
	bool nowPushued;

	float Gravity;
	float JumpHeight;
	float JumpV0;
	float moveSpeed;

	Knife* knife_;
};