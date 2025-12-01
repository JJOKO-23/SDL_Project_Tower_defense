#include "Enemy.h"

Enemy::Enemy(float dmg, float spd)
{
    damage = dmg;
    speed = spd;
}

void Enemy::Update(float dt) {}
void Enemy::MoveTowards(const Vec3& target) {}