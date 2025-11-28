#include "CollisionManager.h"
CollisionManager::CollisionManager(float minX, float maxX, float minY, float maxY) :
    worldMinX(minX), worldMaxX(maxX), worldMinY(minY), worldMaxY(maxY)
{
}

void CollisionManager::ClampToWorld(Entity* obj) {
    if (obj->pos.x - obj->radius < worldMinX) {
        obj->pos.x = worldMinX + obj->radius;
        obj->vel.x = 0;
    }
    if (obj->pos.x + obj->radius > worldMaxX) {
        obj->pos.x = worldMaxX - obj->radius;
        obj->vel.x = 0;
    }
    if (obj->pos.y - obj->radius < worldMinY) {
        obj->pos.y = worldMinY + obj->radius;
        obj->vel.y = 0;
    }
    if (obj->pos.y + obj->radius > worldMaxY) {
        obj->pos.y = worldMaxY - obj->radius;
        obj->vel.y = 0;
    }
}

bool CollisionManager::Intersects(Entity* a, Entity* b) {
    
    float dx = a->pos.x - b->pos.x;
    float dy = a->pos.y - b->pos.y;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = a->radius + b->radius;
    return distanceSquared < radiusSum * radiusSum;
}

void CollisionManager::ResolveCollision(Entity* a, Entity* b) {

    std::swap(a->vel, b->vel);
}

void CollisionManager::CheckCollisions(std::vector<Entity*>& entities) {
    for (size_t i = 0; i < entities.size(); ++i) {
        
        ClampToWorld(entities[i]);

        for (size_t j = i + 1; j < entities.size(); ++j) {
            if (Intersects(entities[i], entities[j])) {
                ResolveCollision(entities[i], entities[j]);
            }
        }
    }
}
void CollisionManager::CheckPlayerPlatform(Player* player, const std::vector<Platform*>& platforms)
{
    player->grounded = false;

    for (auto plat : platforms)
    {
        // Размеры платформы
        float halfW = plat->width * 0.5f;
        float halfH = plat->height * 0.5f;

        // AABB платформы
        float left = plat->pos.x - halfW;
        float right = plat->pos.x + halfW;
        float bottom = plat->pos.y - halfH;
        float top = plat->pos.y + halfH;

        // AABB игрока (квадрат вокруг игрока)
        float pxLeft = player->pos.x - player->radius;
        float pxRight = player->pos.x + player->radius;
        float pxBottom = player->pos.y - player->radius;
        float pxTop = player->pos.y + player->radius;

        // Проверка пересечения AABB <-> AABB
        bool intersects =
            pxRight > left &&
            pxLeft < right &&
            pxTop > bottom &&
            pxBottom < top;

        if (!intersects)
            continue;

        // --- Разрешение коллизии по глубине ---
        float overlapLeft = pxRight - left;
        float overlapRight = right - pxLeft;
        float overlapTop = top - pxBottom;
        float overlapBottom = pxTop - bottom;

        float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

        // Сдвигаем игрока в сторону минимального проникновения
        if (minOverlap == overlapTop)
        {
            // Стоит сверху платформы
            player->pos.y = top + player->radius;
            player->vel.y = 0;
            player->grounded = true;
        }
        else if (minOverlap == overlapBottom)
        {
            // Удар снизу
            player->pos.y = bottom - player->radius;
            player->vel.y = 0;
        }
        else if (minOverlap == overlapLeft)
        {
            player->pos.x = left - player->radius;
            player->vel.x = 0;
        }
        else if (minOverlap == overlapRight)
        {
            player->pos.x = right + player->radius;
            player->vel.x = 0;
        }
    }
}