#include "Knife.h"
#include <assert.h>

Knife::Knife(VECTOR2 position)
{
	hImage = LoadGraph("data/image/item.png");
	assert(hImage > 0);

	imageSize = VECTOR2(64, 64);
	anim = 1;
	animY = 1;

	isAlive = true;
	speed_ = 200.0f;
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
	position.x += speed_ * dt;
	knifeTimer_ -= dt;
	if (knifeTimer_ <= 0)
	{
		isAlive = false;
	}
}

void Knife::Draw()
{
	if (!isAlive) return;
	Object2D::Draw();


}
