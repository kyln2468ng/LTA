#pragma once
class GameData
{
public:
	static float clearTime;

	// クリアタイム保存
	static void SetClearTime(float time) { clearTime = time; }

	// クリアタイム取得
	static float GetClearTime() { return clearTime; }
};