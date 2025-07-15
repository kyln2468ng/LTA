#include "Player.h"
#include <assert.h>
#include "Stage.h"
#include "../ImGui/imgui.h"
#include "CsvReader.h"
#include "Knife.h"
#include "global.h"

//static const float Gravity = 0.05f;
//static const float JumpHeight = 64.0f * 2.0f;
//static const float JumpV0 = -sqrtf(2.0f * Gravity * JumpHeight);

//タイトル「シャープワープ」

//namespace
//{
//	bool dir = true;
//	float mcTime = 0.3f;
//	float animTimer = 0.0f;
//	const int LeftLimit_ = 24;
//	int JumpCnt = 0;
//	const int MaxJumpCount = 2;
//	float cTimer = 3.0;
//	int pCount = 0;
//	const int MaxPushuCount = 2;
//	bool knifeTp = false;
//	bool IsFired = true;
//}

Player::Player() : Player(VECTOR2(100,200))
{
}

Player::Player(VECTOR2 pos)
	:Gravity(0),
	JumpHeight(0),
	moveSpeed(0),
	knife_(0),
	nowPushued(false), onGround(true), prevPushed(false)
{
	// パラメーターを読む
	CsvReader* csv = new CsvReader("data/playerParam.csv");
	for (int i = 0; i < csv->GetLines(); i++) {
		std::string tag = csv->GetString(i, 0);
		if (tag == "Gravity") {
			Gravity = csv->GetFloat(i, 1);
		}
		else if (tag == "JumpHeight") {
			JumpHeight = csv->GetFloat(i, 1);
		}
		else if (tag == "MoveSpeed") {
			moveSpeed = csv->GetFloat(i, 1);
		}
	}
	JumpV0 = -sqrtf(2.0f * Gravity * JumpHeight);

	hImage = LoadGraph("data/image/tamadot.png");
	assert(hImage > 0);

	imageSize = VECTOR2(64, 64);
	anim = 0;
	animY = 3;

	position = pos;
	velocityY = 0.0f;
	isAlive = true;
}

Player::~Player()
{
	if (isAlive == false)
	{
		DestroyMe();
	}
}

void Player::Update()
{
	nowPushued = false;
	nowPushuedS = false;
	Stage* st = FindGameObject<Stage>();
	if (CheckHitKey(KEY_INPUT_D)) {
		position.x += moveSpeed;
		int push = st->CheckRight(position+VECTOR2(24,-31)); // 右上
		position.x -= push;
		push = st->CheckRight(position + VECTOR2(24, 31)); // 右下
		position.x -= push;
		dir = true;
		animY = 3;
		WorkMortion();
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		position.x -= moveSpeed;
		int push = st->CheckLeft(position + VECTOR2(-24, -31)); // 左上
		position.x += push;
		push = st->CheckLeft(position + VECTOR2(-24, 31)); // 左下
		position.x += push;
		if (position.x - LeftLimit_< 0)
		{
			position.x = LeftLimit_;
		}
		dir = false;
		animY = 1;
		WorkMortion();
	}

	if (position.y - 32 < 0)
	{
		position.y = 32;
	}

	if (position.y + 31 > 1280)
	{
		isAlive = false;
	}
	
	if (CheckHitKey(KEY_INPUT_N) && IsFired)
	{
		nowPushued = true;
		//KnifeSrrow();
	}

	//if (prevPushed == false && nowPushued)
	//{
	//	if (pCount < MaxPushuCount && knife_ == nullptr)
	//	{
	//		KnifeSrrow();
	//		pCount++; // pCount足されるタイムんぐ調整必要
	//	}
	//}

	// 1回押し判定で呼ぶ（前フレームと比較）
	if (nowPushued && !prevPushed)
	{
		KnifeSrrow();
	}

	if (onGround)
	{
		JumpCnt = 0;
		IsFired = true;
	}

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		nowPushuedS = true;
	}

	if (prevPushuedS == false && nowPushuedS)
	{
		if (JumpCnt < MaxJumpCount)
		{
			velocityY = JumpV0;
			JumpCnt++;
		}
	}

	prevPushed = nowPushued;
	prevPushuedS = nowPushuedS;

	/*if (onGround) {
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			if (prevPushed == false) {
				velocityY = JumpV0;
			}
			prevPushed = true;
		}
		else {
			prevPushed = false;
		}
	}*/


	{
		position.y += velocityY;
		velocityY += Gravity;
		onGround = false;
		if (velocityY < 0.0f) {
			int push = st->CheckUp(position + VECTOR2(-24, -31)); // 左下
			if (push > 0) {
				velocityY = 0.0f;
				position.y += push;
			}
			push = st->CheckUp(position + VECTOR2(24, -31)); // 右下
			if (push > 0) {
				velocityY = 0.0f;
				position.y += push;
			}
		}
		else {
			int push = st->CheckDown(position + VECTOR2(-24, 31+1)); // 左下
			if (push > 0) {
				velocityY = 0.0f;
				onGround = true;
				position.y -= push-1;
			}
			push = st->CheckDown(position + VECTOR2(24, 31+1)); // 右下
			if (push > 0) {
				velocityY = 0.0f;
				onGround = true;
				position.y -= push-1;
			}
		}
	}

	// プレイヤーの表示位置が、600よりも右だったら、右にスクロールする
	// プレイヤーの表示位置が、400よりも左だったら、左にスクロール
	if (st != nullptr) {
		float drawX = position.x - st->ScrollX(); // これが表示座標
		static const int RightLimit = 600;
		static const int LeftLimit = 400;
		if (drawX > RightLimit) {
			st->SetScrollX(position.x - RightLimit);
			position.x = RightLimit + st->ScrollX();
		}
		else if (drawX < LeftLimit) {
			st->SetScrollX(position.x - LeftLimit);
			position.x = LeftLimit + st->ScrollX();
		}
		if (position.x < LeftLimit)
		{
			st->SetScrollX(0);
		}
	}
	ImGui::Begin("Player");
	ImGui::Checkbox("onGround", &onGround);
	ImGui::InputFloat("positionX", &position.x);
	ImGui::InputFloat("positionY", &position.y);
	ImGui::End();

	if (knife_ != nullptr && !knife_->GetAlive())
	{
		knife_->DestroyMe();
		knife_ = nullptr;
	}
}

void Player::Draw()
{
	Object2D::Draw();
	Stage* st = FindGameObject<Stage>();
	float x = position.x - st->ScrollX();
	DrawBox(x - 24, position.y - 32, x + 24, position.y + 32,
		GetColor(255, 0, 0), FALSE);
}

void Player::KnifeSrrow()
{
	//static VECTOR2 prevPos = position;
	if (nowPushued && prevPushed == false && knife_ == nullptr)
	{
		knife_ = new Knife(position, dir);
		knife_->SetPos(position);
		knife_->SetKnifeTimer(3.0f);
		knifeTp = true;
		//cTimer = 3.0f;
		
		if (dir)
		{
			knife_->SetDirR(true);
		}
		else
			knife_->SetDirR(false);		
		return;
	}

	//if (knife_ != nullptr)
	//{
	//	cTimer -= Time::DeltaTime();
	//}
	//else
	//	cTimer = 0;

	//if (knife_ != nullptr && !knife_->GetAlive())
	//{
	//	knife_->DestroyMe();
	//	knife_ = nullptr;
	//}
	
	if (knife_ != nullptr && knifeTp == true && IsFired) //&& cTimer > 0.0f)
	{
		position = knife_->GetPosition();  // ワープ
		knife_->SetKnifeTimer(0);          // タイマー切る（無効化）
		knife_->DestroyMe();
		knife_ = nullptr;
		knifeTp = false;
		IsFired = false;
		return;
	}

}

void Player::WorkMortion()
{
	animTimer += Time::DeltaTime();
	if (animTimer >= mcTime)
	{
		if (anim == 5) {
			anim = 6;
		}
		else {
			anim = 5;
		}
		animTimer = 0.0f;
	}
}
