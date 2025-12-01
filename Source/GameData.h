#pragma once
#include <vector>

class GameData
{
public:
	GameData() = delete;
	~GameData() = delete;

	static bool setScroll_;
	static float clearTime;
	static int dethCount;

	// クリアタイム保存（従来互換）
	static void SetClearTime(float time) { clearTime = time; }
	static float GetClearTime() { return clearTime; }

	// 直近のクリアタイム（最大 MaxRecords 件）を管理
	static void AddClearTime(float time);
	static const std::vector<float>& GetRecentClearTimes();
	static void ClearRecentTimes();

	static void SetScroll(bool s) { setScroll_ = s; }
	static bool GetScroll() { return setScroll_; }
	int GetDethCount() { return dethCount; }

private:
	static std::vector<float> recentClearTimes_;
	static const int MaxRecords = 5;
};