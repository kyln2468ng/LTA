#include "Player.h"
#include <assert.h>
#include "Stage.h"
#include "../ImGui/imgui.h"
#include "CsvReader.h"
#include "Knife.h"
#include "global.h"
#include "Screen.h"

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
	MoveSpeed(0),
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
			MoveSpeed = csv->GetFloat(i, 1);
		}
	}
	JumpV0 = -sqrtf(2.0f * Gravity * JumpHeight);

	hImage = LoadGraph("data/image/player.png");
	assert(hImage > 0);

	jumpSE = LoadSoundMem("data/sound/jump.mp3");
	knifeSE = LoadSoundMem("data/sound/knife.mp3");
	warpSE = LoadSoundMem("data/sound/warp.mp3");
	assert(jumpSE > 0);

	int vol = 128;
	ChangeVolumeSoundMem(vol, jumpSE);
	ChangeVolumeSoundMem(vol, knifeSE);
	ChangeVolumeSoundMem(vol, warpSE);

	imageSize = VECTOR2(64, 64);
	anim = 1;
	animY = 0;

	position = pos;
	velocityY = 0.0f;
	isAlive = true;
	nFiredAir = true;
}

Player::~Player()
{
	DeleteGraph(hImage);
	DeleteSoundMem(jumpSE);
	DeleteSoundMem(knifeSE);
	DeleteSoundMem(warpSE);
}

void Player::Update()
{
	nowPushued = false;
	nowPushuedS = false;
	Stage* st = FindGameObject<Stage>();
	//if(st == nullptr) {
	//	this->DestroyMe();
	//}
	if (CheckHitKey(KEY_INPUT_D)) {
		position.x += MoveSpeed;
		int push = st->CheckRight(position+VECTOR2(24,-31)); // 右上
		position.x -= push;
		push = st->CheckRight(position + VECTOR2(24, 31)); // 右下
		position.x -= push;
		dir = true;
		animY = 0;
		WorkMortion();
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		position.x -= MoveSpeed;
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
		DestroyMe();
	}
	
	int kCount = st->GetKnifeCount();
	if (CheckHitKey(KEY_INPUT_N) && IsFired)
	{
		nowPushued = true;
		//KnifeSrrow();
	}

	// 1回押し判定で呼ぶ（前フレームと比較）
	if (nowPushued && !prevPushed && kCount != 0)
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
			PlaySoundMem(jumpSE, DX_PLAYTYPE_BACK);
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
		// 強制スクロール中
		if (st->ForcedScrollSpeed() > 0.0f) {
			float playerLeft = position.x - imageSize.x / 2;
			float playerRight = position.x + imageSize.x / 2;
			
			float scrollLineLeft = st->ScrollX(); // 背景の左スクロール位置
			float scrollLineRight = st->ScrollX() + Screen::WIDTH;

			bool pushed = false;
			if (playerLeft < scrollLineLeft) {

				// 差分
				float diff = scrollLineLeft - playerLeft;
				position.x += diff;
				pushed = true;
			}

			if (playerRight > scrollLineRight) {
				float diff = playerRight - scrollLineRight;
				position.x -= diff;
			}

			if (pushed) {
				int l1 = st->CheckLeft(position + VECTOR2(24, -31));
				int l2 = st->CheckLeft(position + VECTOR2(24, 31));

				if (l1 > 0 || l2 > 0) {
					DestroyMe();
					return;
				}
			}
			
		}
		else {
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
	}
	//ImGui::Begin("Player");
	//ImGui::Checkbox("onGround", &onGround);
	//ImGui::InputFloat("positionX", &position.x);
	//ImGui::InputFloat("positionY", &position.y);
	//ImGui::End();

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
	//DrawBox(x - 24, position.y - 32, x + 24, position.y + 32,
	//	GetColor(255, 0, 0), FALSE);
}

void Player::KnifeSrrow()
{
	//static VECTOR2 prevPos = position;
	if (nowPushued && !prevPushed && knife_ == nullptr && IsFired)
	{
		PlaySoundMem(knifeSE, DX_PLAYTYPE_BACK);
		knife_ = new Knife(position, dir);
		knifeTp = true;

		if (onGround)
			nFiredAir = false;
		else
			nFiredAir = true;

		return;
	}

	if (knife_ != nullptr && knifeTp == true) 
	{
		PlaySoundMem(warpSE, DX_PLAYTYPE_BACK);
		position = knife_->GetPosition();  // ワープ
		Stage* st = FindGameObject<Stage>();
		st->SadKnife();

		if (nFiredAir)
			velocityY = JumpV0/2;
		
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
		if (anim == 1) {
			anim = 0;
		}
		else {
			anim = 1;
		}
		animTimer = 0.0f;
	}
}
