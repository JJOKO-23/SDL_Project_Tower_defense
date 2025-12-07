#pragma once
#ifndef WAVESYSTEM_H
#define WAVESYSTEM_H

#include <vector>
#include "Enemy.h"
#include "Tower.h"

class WaveSystem {
public:
    int currentWave = 0;
    int maxWaves = 3;

    bool waveActive = false;
    float waveDelay = 5.0f;
    float timer = 0.0f;

    bool showWaveComplete = false;
    float messageTimer = 0.0f;

    bool gameWon = false;
    bool gameLost = false;

    std::vector<Enemy*> enemies;
    Tower* tower = nullptr;

    void Init(Tower* t);
    void StartWave();
    void Update(float dt, const Vec3& playerPos, float& playerHP);
    void CleanEnemies();
};

#endif