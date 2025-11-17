#pragma once
#include "../Library/GameObject.h"

struct VECTOR2 {
	float x, y;
	VECTOR2() { x = 0; y = 0; }
	VECTOR2(float _x, float _y) { x = _x; y = _y; }
};

enum class Direction {
	Left,
	Right
};

inline VECTOR2 operator -(VECTOR2 a, VECTOR2 b) {
	VECTOR2 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	return r;
}

inline VECTOR2 operator +(VECTOR2 a, VECTOR2 b) {
	VECTOR2 r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return r;
}

inline VECTOR2 operator /(VECTOR2 a, int b) {
	return VECTOR2(a.x / (float)b, a.y / (float)b);
}

inline float VSize(VECTOR2 v) {
	return sqrtf(v.x * v.x + v.y * v.y);
}

class Object2D : public GameObject {
public:
	Object2D();
	virtual ~Object2D();
	virtual void Update() override;
	virtual void Draw() override;
	VECTOR2 GetPosition() { return position; }
	void SetPosition(const VECTOR2& pos) { position = pos; }
	void SetAlive(bool alive) { isAlive = alive; }
	bool GetAlive() const { return isAlive; }

protected:
	int hImage; // ‰æ‘œ‚ğ“Ç‚Ş‚½‚ß
	int anim; // ŠG‚ÌêŠ
	int animY; // ŠG‚ÌêŠ
	bool isAlive; // ¶‚«‚Ä‚é‚©€‚ñ‚Å‚é‚©
	//bool dirRight; // ¶‰E‚Ç‚Á‚¿Œü‚¢‚Ä‚é‚©
	VECTOR2 position; // À•W
	VECTOR2 imageSize; // ‚P‚Â‚ÌŠG‚Ì‘å‚«‚³
};