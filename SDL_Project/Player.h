#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Animation.h"
#include <SDL3/SDL.h>
#include <vector>

class Projectile;
class Entity;

class Player : public Entity {
private:
    float moveSpeed;
    bool attacking;
    float attackCooldown;
    float attackTimer;


public:
    bool grounded;
    bool onPlatform;
    float width = 1.0f;
    float height = 1.8f;
    bool facingRight = true;
    float meleeDamage = 20.0f;
    float meleeRadius = 2.0f;
    bool meleeMode = true;     
    float meleeRange = 1.5f;  
    float projectileCooldown = 0.25f;
    float projectileTimer = 0.0f;

    Animation idleAnim;
    Animation walkAnim;
    Animation meleeAnim;
    Animation rangeAnim;

    Animation* currentAnim = nullptr;

    Player();
    ~Player() = default;

    void HandleInput(const SDL_Event& event);
    void Update(float deltaTime) override;
    void Attack(std::vector<Entity*>& enemies,
        std::vector<Projectile*>& projectiles);
};

#endif