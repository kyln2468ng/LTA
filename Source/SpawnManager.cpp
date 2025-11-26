#include "SpawnManager.h"
#include "Stage.h"

SpawnManager::SpawnManager()
{
    timer_ = 0.0f;
    spawnInterval_ = 10.0f;
}

SpawnManager::~SpawnManager()
{
}

void SpawnManager::AddSpawnPoint(const VECTOR2& pos, int tileID)
{
    for (auto& sp : spawnPoints_) {
        if (sp.pos_.x == pos.x && sp.pos_.y == pos.y) {
            return; // Ç‡Ç§ìoò^çœÇ›Ç»ÇÁñ≥éã
        }
    }

    spawnPoints_.push_back({ pos, tileID });
}

void SpawnManager::SetSpawnPoints(const std::vector<VECTOR2>& pts, int tileID)
{
    spawnPoints_.clear();
    for (auto& p : pts)
    {
        spawnPoints_.push_back({ p, tileID });
    }
}

void SpawnManager::Update()
{
    timer_ += Time::DeltaTime();

    if (timer_ >= spawnInterval_)
    {
        timer_ = 0;
        Spawn();
    }
}

void SpawnManager::Spawn()
{
    if (spawnPoints_.empty()) return;
    std::vector<int> ids;

    imageSize = VECTOR2(64, 64);
    for (auto& sp : spawnPoints_)
    {
        //ids.push_back(sp.tileID_);
        int x = sp.pos_.x / imageSize.x;
        int y = sp.pos_.y / imageSize.y;
        Stage* st = FindGameObject<Stage>();
        st->SetTile(x, y, sp.tileID_);
    }
}