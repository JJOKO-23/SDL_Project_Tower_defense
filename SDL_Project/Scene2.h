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

using namespace MATH;
class Scene2 : public Scene {
private:
	SDL_Window* window;
	float xAxis;
	float yAxis;
	float worldScale = 20.0f;

	
	std::vector<Projectile*> projectiles;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;

	Entity* back;
	Entity* character; 
	Entity* enemy1;
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

	float loadingTime = 1.0f;


	bool playHover = false;
	float playScale = 1.0f;        // текущий масштаб
	float playTargetScale = 1.2f;

	// MUSIC
	MIX_Audio* menuMusic = nullptr;
	MIX_Audio* gameMusic = nullptr;

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
};

#endif
