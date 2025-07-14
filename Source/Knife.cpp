#include "Knife.h"
#include <assert.h>
#include "Stage.h"

namespace
{
	bool isMove = true;
	int push = 0;
}

Knife::Knife(VECTOR2 position,bool dirRight)
{
	hImage = LoadGraph("data/image/item.png");
	assert(hImage > 0);

	imageSize = VECTOR2(64, 64);
	anim = 1;
	animY = 1;

	isAlive = true;
	speed_ = 400.0f;
	knifeTimer_ = 3.0f;
	isFired_ = false;
}

Knife::~Knife()
{
	if (isAlive == false)
	{
		DestroyMe();
		//new Effect;
	}
}

void Knife::Update()
{
	float dt = Time::DeltaTime();
	Stage* st = FindGameObject<Stage>();

	if (dirRight)
	{
		push = st->CheckRight(position + VECTOR2(32, -31));
		position.x -= push;
		push = st->CheckRight(position + VECTOR2(32, 31));
		position.x -= push;

		position.x += speed_ * dt;
	}
	else
	{
		push = st->CheckLeft(position + VECTOR2(-32, -31));
		position.x += push;
		push = st->CheckLeft(position + VECTOR2(-32, 31));
		position.x += push;

		position.x -= speed_ * dt;
	}

	knifeTimer_ -= dt;
	if (knifeTimer_ <= 0)
	{
		isAlive = false;
		
	}

	//if (position.y < 0.0f) {
	//	int push = st->CheckUp(position + VECTOR2(-24, -31)); // ¶‰º
	//	if (push > 0) {
	//		//position.y = 0.0f;
	//		position.y += push;
	//	}
	//	push = st->CheckUp(position + VECTOR2(24, -31)); // ‰E‰º
	//	if (push > 0) {
	//		//position.y = 0.0f;
	//		position.y += push;
	//	}
	//}
	//else {
	//	int push = st->CheckDown(position + VECTOR2(-24, 31 + 1)); // ¶‰º
	//	if (push > 0) {
	//		//position.y = 0.0f;
	//		position.y -= push - 1;
	//	}
	//	push = st->CheckDown(position + VECTOR2(24, 31 + 1)); // ‰E‰º
	//	if (push > 0) {
	//		//position.y = 0.0f;
	//		position.y -= push - 1;
	//	}
	//}


}

void Knife::Draw()
{
	if (!isAlive) return;
	Object2D::Draw();
	DrawBox(position.x - 24, position.y - 32, position.x + 24, position.y + 32,
		GetColor(255, 0, 0), FALSE);

}
