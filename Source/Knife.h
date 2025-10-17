#pragma once
#include "Object2D.h"

class Knife : public Object2D
{
public:
	Knife();
	Knife(VECTOR2 pos,bool pDir);
	~Knife();
	void Update() override;
	void Draw() override;
	//void SetKnifeTimer(float nTime) { knifeTimer_ = nTime; }
	//void SetDirR(bool dir) { dirRight = dir; }
	//void GetTimer() { return knifeTimer_; }
private:
	float knifeTimer_;
	float speed_;
	bool dir; //ƒiƒCƒt‚ÌŒü‚« true
};