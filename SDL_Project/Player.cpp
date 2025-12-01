
#include "Player.h"
#include <iostream>

Player::Player()
{
    moveSpeed = 8.0f;
    grounded = false;

    pos = Vec3(5.0f, 5.0f, 0.0f);
    vel = Vec3(0.0f, 0.0f, 0.0f);
    acc = Vec3(0.0f, 0.0f, 0.0f);

    mass = 1.0f;
    radius = 0.5f;

    Animation animation;

    currentAnim = &idleAnim;
}

void Player::HandleInput(const SDL_Event& event)
{
    switch (event.type) {

        // KEY DOWN
    case SDL_EVENT_KEY_DOWN:
        switch (event.key.scancode) {
        case SDL_SCANCODE_W:
            vel.y = moveSpeed;
            break;

        case SDL_SCANCODE_S:
            vel.y = -moveSpeed;
            break;

        case SDL_SCANCODE_A:
            vel.x = -moveSpeed;
            facingRight = false;
            break;

        case SDL_SCANCODE_D:
            vel.x = moveSpeed;
            facingRight = true;
            break;

        default:
            break;
        }
        break;

        // KEY UP
    case SDL_EVENT_KEY_UP:
        switch (event.key.scancode) {

        case SDL_SCANCODE_W:
        case SDL_SCANCODE_S:
            vel.y = 0.0f;
            break;

        case SDL_SCANCODE_A:
        case SDL_SCANCODE_D:
            vel.x = 0.0f;
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}

void Player::Update(float deltaTime)
{

    vel.y -= 25.0f * deltaTime;


    if (vel.y < -20.0f)
        vel.y = -20.0f;

    pos += vel * deltaTime;

    bool isMoving = (vel.x != 0 || vel.y > 0.5f);

    if (isMoving)
        currentAnim = &walkAnim;
    else
        currentAnim = &idleAnim;

    currentAnim->Update(deltaTime);
}