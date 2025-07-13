#pragma once
#include "Object2D.h"

class Knife : public Object2D
{
public:
	Knife(VECTOR2 position,bool dirRight);
	~Knife();
	void Update() override;
	void Draw() override;
	void SetKnifeTimer(float nTime) { knifeTimer_ = nTime; }
	void SetPos(VECTOR2 pos) { position = pos; }
	void SetDirR(bool dir) { dirRight = dir; }
	//void GetTimer() { return knifeTimer_; }
private:
	float knifeTimer_;
	float speed_;
	bool isFired_;
	bool dirRight;
};