#pragma once
#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Tower.h"
#include "Platform.h"
#include "Entity.h"

class CollisionManager {
public:
    CollisionManager(float minX, float maxX, float minY, float maxY);
    void CheckCollisions(std::vector<Entity*>& entities);
    void CheckPlayerPlatform(Player* player, const std::vector<Platform*>& platforms);
    void ClampToWorld(Entity* obj);

    void CheckEnemyPlatform(Enemy* enemy, const std::vector<Platform*>& platforms);


private:
    float worldMinX;
    float worldMaxX;
    float worldMinY;
    float worldMaxY;
    bool Intersects(Entity* a, Entity* b);
    void ResolveCollision(Entity* a, Entity* b);
    void ResolvePush(Entity* a, Entity* b);

    
    
};

#endif