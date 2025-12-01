
#include "Projectile.h"

Projectile::Projectile(const Vec3& startPos, bool direction)
{
    pos = startPos;
    facingRight = direction;

    speed = 20.0f;
    vel = Vec3(0, 0, 0);     // важно НЕ ТРОГАТЬ

    // летит в нужную сторону
    vel.x = facingRight ? speed : -speed;
}

void Projectile::Update(float dt)
{
    pos += vel * dt;
}