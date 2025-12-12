#include "WaveSystem.h"

#include <cmath>



void WaveSystem::Init(Tower* t, const std::vector<Platform*>& plats)

{
    tower = t;
    platforms = plats;
    StartWave();
}

void WaveSystem::PushApartEnemies(float dt)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = i + 1; j < enemies.size(); j++)
        {
            Enemy* a = enemies[i];
            Enemy* b = enemies[j];

            float dx = b->pos.x - a->pos.x;
            float dy = b->pos.y - a->pos.y;
            float dist = sqrt(dx * dx + dy * dy);

            float minDist = 1.0f;

            if (dist < minDist && dist > 0.001f)
            {
                float overlap = minDist - dist;

                float nx = dx / dist;
                float ny = dy / dist;


                a->pos.x -= nx * overlap * 0.5f;
                b->pos.x += nx * overlap * 0.5f;

                a->pos.y -= ny * overlap * 0.5f;
                b->pos.y += ny * overlap * 0.5f;
            }
        }
    }
}

void WaveSystem::StartWave() {
    CleanEnemies();
    currentWave++;

    if (currentWave > maxWaves) {
        gameWon = true;
        return;
    }

    int baseCount = 5;
    int enemyCount = baseCount + (currentWave - 1);

    float hpBoost = 1.0f + (currentWave - 1) * 0.5f;
    float dmgBoost = 1.0f + (currentWave - 1) * 0.5f;

    SDL_Renderer* renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));

    for (int i = 0; i < enemyCount; i++) {
        Enemy* e = new Enemy(
            50.0f * hpBoost,
            10.0f * dmgBoost,
            2.0f
        );

        //e->pos = Vec3(2 + i, 12, 0); 

        float spawnLeftX = 2.0f;
        float spawnRightX = 28.0f; 
        float spawnY = 12.0f;

        float offset = 0.8f; 

        if (i % 2 == 0)
        {
            e->pos = Vec3(spawnLeftX + i * offset, spawnY, 0);
        }
        else
        {
            e->pos = Vec3(spawnRightX - i * offset, spawnY, 0);
        }

        

        enemies.push_back(e);
    }

    waveActive = true;
    showWaveComplete = false;
}


void WaveSystem::Update(float dt, const Vec3& playerPos, float& playerHP) {
    if (gameWon || gameLost) return;

  
    for (int i = enemies.size() - 1; i >= 0; i--) {
        Enemy* e = enemies[i];

        float dxP = e->pos.x - playerPos.x;
        float dyP = e->pos.y - playerPos.y;
        float distPlayer = sqrt(dxP * dxP + dyP * dyP);

        float dxT = e->pos.x - tower->pos.x;
        float dyT = e->pos.y - tower->pos.y;
        float distTower = sqrt(dxT * dxT + dyT * dyT);
       //detection raduis for player
        if (distPlayer < 5.0f) {
            e->MoveTowards(playerPos, platforms);

            if (distPlayer < 1.0f) {
                playerHP -= e->GetDamage() * dt;
            }
        }
        else {
			//Detection radius for tower
            e->MoveTowards(tower->pos, platforms);
            if (distTower < 1.2f) {
                e->vel = Vec3(0, 0, 0);  
                tower->TakeDamage(e->GetDamage() * dt);
            }
        }

        e->Update(dt);

        if (e->IsDead()) {
            delete e;
            enemies.erase(enemies.begin() + i);
        }
    }
    PushApartEnemies(dt);
    
    if (tower->IsDestroyed() || playerHP <= 0) {
        gameLost = true;
        return;
    }

    // wawe end
    if (waveActive && enemies.empty()) {
        waveActive = false;
        showWaveComplete = true;
        messageTimer = 2.0f;
        timer = waveDelay;
    }

    // message timer
    if (showWaveComplete) {
        messageTimer -= dt;
        if (messageTimer <= 0) {
            showWaveComplete = false;
        }
    }

	// wawe pause timer
    if (!waveActive && !gameWon && !gameLost) {
        if (timer > 0) {
            timer -= dt;
        }
        else {
            StartWave();
        }
    }
}



void WaveSystem::CleanEnemies() {
    for (auto e : enemies) {
        delete e;
    }
    enemies.clear();
}

