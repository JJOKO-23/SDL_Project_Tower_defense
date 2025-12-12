#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"



class Projectile : public Entity {
public:
    Projectile(const Vec3& startPos, bool direction);
    void Update(float dt) override;


    float speed = 20.0f;
    bool facingRight = true;
};


#endif
