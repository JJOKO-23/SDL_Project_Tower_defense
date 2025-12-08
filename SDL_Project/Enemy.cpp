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

void Enemy::MoveTowards(const Vec3& targetPos)
{
    float dx = targetPos.x - pos.x;

    vel.x = (dx > 0 ? 1.0f : -1.0f) * speed;

    // прыжок если цель выше
    if (targetPos.y > pos.y + 1.0f && grounded)
    {
        vel.y = jumpForce;
        grounded = false;
    }
}


void Enemy::Update(float deltaTime)
{
    // гравитация
    vel.y -= gravity * deltaTime;
    if (vel.y < -20.0f) vel.y = -20.0f;

    // обновляем позицию
    pos += vel * deltaTime;
}


