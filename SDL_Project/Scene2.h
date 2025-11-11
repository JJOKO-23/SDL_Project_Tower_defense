#pragma once
#ifndef SCENE2_H
#define SCENE2_H
#include <SDL3/SDL.h>
#include <Matrix.h>
#include "Scene.h"
#include "Entity.h"

#include <SDL3/SDL_mixer.h>

using namespace MATH;
class Scene2 : public Scene {
private:
	SDL_Window* window;
	float xAxis;
	float yAxis;

	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;

	Entity* back;
	Entity* character;
	

	bool running = 0;

	float flappyScale; // a scale to make the texture smaller or larger

	MIX_Mixer* mixer;
	float master_volume = 0.25f;
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
