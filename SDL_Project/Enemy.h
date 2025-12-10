#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
private:
    float hp;
    float maxHp;
    float damage;
    float speed;
    

 
    bool grounded = false;
    float jumpForce = 12.0f;
    float gravity = 9.8f;


public:
    float width = 2.0f;   // world units
    float height = 3.0f;  // world units
    SDL_Texture* texture = nullptr;
    
    float drawSize = 40.0f;
    void SetTexture(SDL_Texture* tex) { texture = tex; }

    Enemy(float hp_ = 50.0f, float dmg_ = 10.0f, float spd_ = 2.0f);

    void Update(float deltaTime) override;
    void MoveTowards(const Vec3& targetPos);

    void TakeDamage(float amount);
    bool IsDead() const { return hp <= 0.0f; }

    float GetHP() const { return hp; }
    float GetMaxHP() const { return maxHp; }
    float GetDamage() const { return damage; }
};

#endif
