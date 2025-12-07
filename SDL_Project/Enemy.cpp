#include "Enemy.h"

#include <cmath>

Enemy::Enemy(float hp_, float dmg_, float spd_) {
    maxHp = hp_;
    hp = hp_;
    damage = dmg_;
    speed = spd_;
}

void Enemy::TakeDamage(float amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

void Enemy::MoveTowards(const Vec3& targetPos) {
    Vec3 dir = targetPos - pos;
    float len = sqrt(dir.x * dir.x + dir.y * dir.y);

    if (len != 0) {
        dir.x /= len;
        dir.y /= len;
    }

    vel = dir * speed;
}

void Enemy::Update(float deltaTime) {
    pos += vel * deltaTime;
}

