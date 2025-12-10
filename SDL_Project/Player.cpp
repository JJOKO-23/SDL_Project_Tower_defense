
#include "Player.h"
#include "Projectile.h"
#include <iostream>

Player::Player()
{
    moveSpeed = 8.0f;
    grounded = false;
    onPlatform = false;

    pos = Vec3(5.0f, 5.0f, 0.0f);
    vel = Vec3(0.0f, 0.0f, 0.0f);
    acc = Vec3(0.0f, 0.0f, 0.0f);

    mass = 1.0f;
    radius = 1.0f;

    facingRight = true;

    meleeMode = true;
    meleeRange = 1.5f;

    projectileCooldown = 0.25f;
    projectileTimer = 0.0f;

    attacking = false;
    attackCooldown = 0.3f;   
    attackTimer = 0.0f;

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
            facingRight = true;
            break;

        case SDL_SCANCODE_Q:
            meleeMode = !meleeMode; 
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
    projectileTimer -= deltaTime;
    if (projectileTimer < 0.0f)
        projectileTimer = 0.0f;

    
    if (attacking)
    {
        attackTimer -= deltaTime;
        if (attackTimer <= 0.0f)
        {
            attackTimer = 0.0f;
            attacking = false;
        }
    }

    

    
    vel.y -= 25.0f * deltaTime;

    
    if (vel.y < -20.0f)
        vel.y = -20.0f;

    
    pos += vel * deltaTime;

    

    if (attacking)
    {
        
        if (meleeMode)
            currentAnim = &meleeAnim;  
        else
            currentAnim = &rangeAnim; 
    }
    else
    {
        
        bool isMoving = (vel.x != 0.0f || vel.y > 0.5f);

        if (isMoving)
            currentAnim = &walkAnim;
        else
            currentAnim = &idleAnim;
    }

   

    if (currentAnim)
    {
        currentAnim->Update(deltaTime);
    }
}

void Player::Attack(std::vector<Entity*>& enemies,
 /*   std::vector<Projectile*>& projectiles)
{
   

    if (meleeMode)
    {
        
        float dir = facingRight ? 1.0f : -1.0f;
        float attackX = pos.x + dir * meleeRange;

        for (int i = enemies.size() - 1; i >= 0; i--)
        {
            float dx = fabs(enemies[i]->pos.x - attackX);
            float dy = fabs(enemies[i]->pos.y - pos.y);

            if (dx < 1.0f && dy < 1.0f) {
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
            }
        }
    }
    else
    {
      
        if (projectileTimer <= 0.0f)
        {
            Projectile* p = new Projectile(pos, facingRight);
            projectiles.push_back(p);

            projectileTimer = projectileCooldown;
        }
    }*/

    std::vector<Projectile*>& projectiles)
{
    if (meleeMode)
    {
        float dir = facingRight ? 1.0f : -1.0f;
        float attackX = pos.x + dir * meleeRange;

        bool hitSomething = false;

        for (int i = (int)enemies.size() - 1; i >= 0; i--)
        {
            float dx = fabs(enemies[i]->pos.x - attackX);
            float dy = fabs(enemies[i]->pos.y - pos.y);

            if (dx < 1.0f && dy < 1.0f)
            {
                Enemy* enemy = dynamic_cast<Enemy*>(enemies[i]);
                if (enemy)
                {
                    enemy->TakeDamage(meleeDamage);

                    if (enemy->IsDead())
                    {
                        delete enemy;
                        enemies.erase(enemies.begin() + i);
                    }
                }
                hitSomething = true;

            }
        }

        
        attacking = true;
        attackTimer = attackCooldown;
    }
    else
    {
        if (projectileTimer <= 0.0f)
        {
            Projectile* p = new Projectile(pos, facingRight);
            projectiles.push_back(p);

            projectileTimer = projectileCooldown;

           
            attacking = true;
            attackTimer = attackCooldown;
        }
    }
}