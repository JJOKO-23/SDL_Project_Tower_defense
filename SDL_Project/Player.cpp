
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
    attackCooldown = 0.3f;   // сколько длится анимация атаки
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

    // таймер атаки (управляет длиной анимации удара / выстрела)
    if (attacking)
    {
        attackTimer -= deltaTime;
        if (attackTimer <= 0.0f)
        {
            attackTimer = 0.0f;
            attacking = false;
        }
    }

    // ===== ФИЗИКА / ГРАВИТАЦИЯ =====

    // простая гравитация
    vel.y -= 25.0f * deltaTime;

    // ограничиваем падение, чтобы не разгонялся бесконечно
    if (vel.y < -20.0f)
        vel.y = -20.0f;

    // обновляем позицию
    pos += vel * deltaTime;

    // ===== ВЫБОР АНИМАЦИИ =====

    if (attacking)
    {
        // во время атаки всегда показываем атакующую анимацию
        if (meleeMode)
            currentAnim = &meleeAnim;   // ближняя атака
        else
            currentAnim = &rangeAnim;   // дальняя атака
    }
    else
    {
        // если не атакуем – обычная логика ходьба/статичный
        bool isMoving = (vel.x != 0.0f || vel.y > 0.5f);

        if (isMoving)
            currentAnim = &walkAnim;
        else
            currentAnim = &idleAnim;
    }

    // ===== ОБНОВЛЕНИЕ ТЕКУЩЕЙ АНИМАЦИИ =====

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
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                hitSomething = true;
            }
        }

        // запускаем анимацию ближней атаки даже если не попали
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

            // запускаем анимацию дальней атаки
            attacking = true;
            attackTimer = attackCooldown;
        }
    }
}