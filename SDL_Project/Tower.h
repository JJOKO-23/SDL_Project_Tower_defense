#pragma once
#ifndef TOWER_H
#define TOWER_H

#include "Entity.h"

class Tower : public Entity {
private:
    float health;
    float maxHealth;

public:
    Tower(float hp = 200.0f);
    ~Tower() = default;

    void TakeDamage(float amount);
    bool IsDestroyed() const { return health <= 0.0f; }
    void Update(float deltaTime) override {}
};

#endif