#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
private:
    float damage;
    float speed;

public:
    Enemy(float dmg = 10.0f, float spd = 40.0f);
    ~Enemy() = default;

    void Update(float deltaTime) override;
    void MoveTowards(const Vec3& targetPos);
};

#endif