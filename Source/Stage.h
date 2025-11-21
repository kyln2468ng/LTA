#pragma once
#include "Object2D.h"
#include <vector>

class Stage : public Object2D {
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	float ScrollX() { return scrollX; }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="sc">  </param>
	void SetScrollX(int sc) { scrollX = sc; }

	/// <summary>
	/// 指定した点が当たっているか調べる
	/// </summary>
	/// <param name="pos">調べる点</param>
	/// <returns>当たっていれば、左に押し返す量</returns>
	int CheckRight(VECTOR2 pos);

	int CheckLeft(VECTOR2 pos);

	int CheckDown(VECTOR2 pos);

	int CheckUp(VECTOR2 pos);

	float GetTimer() { return countTimer; }

	void SetTile(int x, int y, int tileID)
	{
		map[y][x] = tileID;
	}

private:
	float scrollX; // 横スクロール量

	bool IsWall(VECTOR2 pos);
	bool IsHit;
	float countTimer;
	float timer;
	int flagImage;
	std::vector<std::vector<int>> map;
	bool nIsAlive;
};