#include "RankingScene.h"
#include <DxLib.h>
#include "GameData.h"
#include <cstdio>
#include <algorithm>
#include <vector>

RankingScene::RankingScene()
{
	bImage = LoadGraph("data/image/backImage.png");
}

RankingScene::~RankingScene()
{
}

void RankingScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void RankingScene::Draw()
{
	DrawExtendGraph(0, 0, 1280, 720, bImage, TRUE);
	DrawString(800, 600, "Push [T]Key To Title", GetColor(255, 255, 255));

	// 直近記録を取得して昇順（速い順）にソートして表示
	const auto& records = GameData::GetRecentClearTimes();

	SetFontSize(36);
	int startX = 60; // 表示位置（必要に応じて調整）
	int startY = 50;
	int lineHeight = 52;
	char buf[64];

	if (records.empty()) {
		DrawString(startX, startY, "記録がありません", GetColor(255, 255, 255));
		return;
	}

	// コピーして昇順にソート（小さい値が速い）
	std::vector<float> sorted(records.begin(), records.end());
	std::sort(sorted.begin(), sorted.end());

	// 最大 5 件表示
	size_t showCount = std::min<size_t>(5, sorted.size());
	for (size_t i = 0; i < showCount; ++i) {
		float clearTime = 300.0f - sorted[i]; // クリアにかかった時間に変換
		std::snprintf(buf, sizeof(buf), "%zu. %.2f 秒", i + 1, clearTime);
		DrawString(startX, startY + static_cast<int>(i) * lineHeight, buf, GetColor(255, 255, 255));
	}
}
