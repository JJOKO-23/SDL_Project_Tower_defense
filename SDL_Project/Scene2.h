#pragma once
#ifndef SCENE2_H
#define SCENE2_H
#include <SDL3/SDL.h>
#include <Matrix.h>
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Tower.h"
#include "Platform.h"
#include "CollisionManager.h"
#include "Entity.h"
#include "Projectile.h"
#include <SDL3/SDL_mixer.h>
#include "WaveSystem.h"
#include <unordered_map>


using namespace MATH;
class Scene2 : public Scene {
private:
	SDL_Window* window;
	float xAxis;
	float yAxis;
	float worldScale = 20.0f;
	

	WaveSystem* waves = nullptr;
	Tower* tower = nullptr;
	
	float playerHP = 100.0f;
	float playerMaxHP = 100.0f;
	float playerDamage = 20.0f;
	

	std::vector<Projectile*> projectiles;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;

	Entity* back;
	Entity* character; 
	Enemy* enemy1;
	Player* player;

	std::vector<Entity*> enemies;
	
	std::vector<Entity*> entities;
	std::vector<Platform*> platforms;
	
	
	CollisionManager* collisionManager;
	bool running = 0;

	float flappyScale; // a scale to make the texture smaller or larger

	MIX_Mixer* mixer;
	float master_volume = 0.25f;

	//UUUUIIIII

	bool showMainMenu = true;

	SDL_Texture* mainMenuBackground = nullptr;
	SDL_Texture* playButtonTexture = nullptr;

	SDL_FRect playButtonRect;
	SDL_FRect mainMenuRect;


	struct EnemyAnimState {
		float timer = 0.0f;
		int frame = 0;
	};

	std::vector<SDL_Texture*> enemyAnimFrames;
	float enemyAnimFPS = 10.0f;
	std::unordered_map<Enemy*, EnemyAnimState> enemyAnim;

	SDL_Texture* settingsButtonTexture = nullptr;
	SDL_Texture* settingsBackground = nullptr;
	SDL_Texture* volumeBarTexture = nullptr;
	SDL_Texture* backButtonTexture = nullptr;
	SDL_Texture* towerTexture = nullptr;
	SDL_Texture* winTexture = nullptr;
	SDL_Texture* loseTexture = nullptr;

	SDL_FRect settingsButtonRect;
	bool showSettingsMenu = false;
	SDL_FRect backButtonRect;
	SDL_FRect volumeBarRect;


	float loadingTime = 1.0f;


	bool playHover = false;
	float playScale = 1.0f;        // текущий масштаб
	float playTargetScale = 1.2f;

	// MUSIC
	MIX_Audio* menuMusic = nullptr;
	MIX_Audio* gameMusic = nullptr;
	MIX_Track* musicTrack = nullptr;

	int menuMusicID = -1;
	int gameMusicID = -1;


public:
	
	
	Scene2(SDL_Window* sdlWindow);
	~Scene2();
	bool OnCreate() override;
	void OnDestroy() override;
	void HandleEvents(const SDL_Event& event) override;
	void Update(const float time) override;
	void Render() const override;

	float settingsScale = 1.0f;
	float settingsTargetScale = 1.0f;
	bool settingsHover = false;

	// audio volume
	float volume = 0.2f;
};

#endif
