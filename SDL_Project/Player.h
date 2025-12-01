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

    Animation idleAnim;
    Animation walkAnim;

    Animation* currentAnim = nullptr;

    Player();
    ~Player() = default;

    void HandleInput(const SDL_Event& event);
    void Update(float deltaTime) override;
    void Attack(std::vector<Entity*>& enemies,
        std::vector<Projectile*>& projectiles);
};

#endif