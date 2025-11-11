#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <SDL3/SDL.h>

class Player : public Entity {
private:
    float moveSpeed;
    bool attacking;
    float attackCooldown;
    float attackTimer;

public:
    Player();
    ~Player() = default;

    void HandleInput(const SDL_Event& event);
    void Update(float deltaTime) override;
    void Attack();
};

#endif