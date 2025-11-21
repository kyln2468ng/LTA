#pragma once
#include<vector>
#include "Object2D.h"

class Stage;

struct SpawnPoint {
    VECTOR2 pos_;
    int tileID_;
    bool obIsAlive_;
};

class SpawnManager :public Object2D {
public:
    SpawnManager();
    ~SpawnManager();
    void Update() override;
    void AddSpawnPoint(const VECTOR2& pos, int tileID, bool objectAlive);
    void SetSpawnPoints(const std::vector<VECTOR2>& pts, int tileID, bool objectAlive);
    
    void Spawn();

private:
    float timer_;
    float spawnInterval_;
    std::vector<SpawnPoint> spawnPoints_;
};