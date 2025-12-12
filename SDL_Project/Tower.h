#pragma once
#ifndef TOWER_H
#define TOWER_H

#include "Entity.h"


class Tower : public Entity {
private:
    float money;
    float maxMoney;

public:
    Tower(float cash = 200.0f);

    void TakeDamage(float amount);

    float GetMoney() const { return money; }
    float GetMaxMoney() const { return maxMoney; }

    bool IsDestroyed() const { return money <= 0.0f; }

    void Update(float deltaTime) override {}
};

#endif