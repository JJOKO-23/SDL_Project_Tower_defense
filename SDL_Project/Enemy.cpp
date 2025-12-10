#include "Enemy.h"

#include <cmath>

Enemy::Enemy(float hp_, float dmg_, float spd_) {
    maxHp = hp_;
    hp = hp_;
    damage = dmg_;
    speed = spd_;
    texture = nullptr;
    width = 2.0f;
    height = 3.0f;
    radius = 1.0f;  


}

void Enemy::TakeDamage(float amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}

void Enemy::MoveTowards(const Vec3& targetPos, const std::vector<Platform*>& platforms)
{
    float dx = targetPos.x - pos.x;
    vel.x = (dx > 0 ? 1.0f : -1.0f) * speed;

    bool onEdge = false;

    for (auto plat : platforms)
    {
        float halfW = plat->width * 0.5f;
        float left = plat->pos.x - halfW;
        float right = plat->pos.x + halfW;
        float top = plat->pos.y + plat->height * 0.5f;

        if (fabs(pos.y - top) < 0.2f) 
        {
            if (vel.x > 0 && pos.x > right - 0.3f)
                onEdge = true;

            if (vel.x < 0 && pos.x < left + 0.3f)
                onEdge = true;
        }
    }

    if (onEdge && grounded)
    {
        vel.x = 0; 
    }
}




void Enemy::Update(float deltaTime)
{
    
    vel.y -= gravity * deltaTime;
    if (vel.y < -20.0f) vel.y = -20.0f;

    
    pos += vel * deltaTime;
}


