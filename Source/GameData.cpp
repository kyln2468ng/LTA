#include "GameData.h"

bool GameData::setScroll_ = false;
float GameData::clearTime = 0.0f;
int GameData::dethCount = 0;
std::vector<float> GameData::recentClearTimes_ = {};

void GameData::AddClearTime(float time)
{
	// æ“ª‚É‘}“ü‚µ‚ÄÅV‡‚ÉˆÛŽ
	recentClearTimes_.insert(recentClearTimes_.begin(), time);
	if ((int)recentClearTimes_.size() > MaxRecords) {
		recentClearTimes_.resize(MaxRecords);
	}
}

const std::vector<float>& GameData::GetRecentClearTimes()
{
	return recentClearTimes_;
}

void GameData::ClearRecentTimes()
{
	recentClearTimes_.clear();
}