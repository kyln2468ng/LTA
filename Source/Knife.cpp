#include "Knife.h"
#include <assert.h>
#include "Stage.h"

namespace
{
	bool isMove = true;
	int push = 0;
}

Knife::Knife(VECTOR2 position,bool dirRight)
	:dirRight(true)
{
	hImage = LoadGraph("data/image/knife.png");
	assert(hImage > 0);

	imageSize = VECTOR2(64, 32);
	anim = 0;
	animY = 0;

	isAlive = true;
	speed_ = 400.0f;
	knifeTimer_ = 3.0f;
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
		push = st->CheckRight(position + VECTOR2(32, -16));
		position.x -= push;
		push = st->CheckRight(position + VECTOR2(32, 16));
		position.x -= push;

			speed_ = 400.0f;

		position.x += speed_ * dt;
	}
	else
	{
		push = st->CheckLeft(position + VECTOR2(-32, -16));
		position.x += push;
		push = st->CheckLeft(position + VECTOR2(-32, 16));
		position.x += push;

		position.x -= speed_ * dt;
		if (position.x - 32 < 0)
		{
			position.x = 32;
		}
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
	int x = position.x - imageSize.x / 2.0f;
	int y = position.y - imageSize.y / 2.0f;
	Object2D::Draw();
	//DrawRectExtendGraph(x, y, x + imageSize.x, y + imageSize.y, imageSize.x * anim, imageSize.x * animY, imageSize.x * anim, imageSize.x*anim, hImage, TRUE);
	//DrawRectGraph(x, y, anim * imageSize.x, animY * imageSize.y, imageSize.x, imageSize.y, hImage, TRUE);
	
	//DrawBox(position.x - 24, position.y - 16, position.x + 24, position.y + 16,	GetColor(255, 0, 0), FALSE);

}
