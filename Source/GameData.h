#pragma once
class GameData
{
private:

	//ここ直す
public:

	static bool setScroll_;
	static float clearTime;
	static int dethCount;
	// クリアタイム保存
	static void SetClearTime(float time) { clearTime = time; }

	// クリアタイム取得
	static float GetClearTime() { return clearTime; }

	void SetScroll(bool s) { setScroll_ = s; }

	bool GetScroll() { return setScroll_; }

	int GetDethCount() { return dethCount; }
};