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
    for (auto plat : platforms)
    {
		// borders of the platform
        float left = plat->pos.x - plat->width / 2;
        float right = plat->pos.x + plat->width / 2;
        float bottom = plat->pos.y;
        float top = plat->pos.y + plat->height;

        
        bool xOverlap = (player->pos.x > left && player->pos.x < right);

		// fall on the platform
        bool yHit = (player->pos.y - player->radius <= top &&
            player->pos.y - player->radius >= top - 0.3f &&
            player->vel.y < 0);

        if (xOverlap && yHit)
        {
			/// player on platform
            player->pos.y = top + player->radius;
            player->vel.y = 0;
            player->grounded = true;
        }
    }

    
    if (!player->onPlatform)
        player->grounded = false;
}