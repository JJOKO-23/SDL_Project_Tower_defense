#ifndef Scene1_H
#define Scene1_H
#include <SDL3/SDL.h>
#include <Matrix.h>
#include "Scene.h"
#include "Entity.h"

using namespace MATH;
class Scene1 : public Scene {
private:
	SDL_Window* window;
	float xAxis;
	float yAxis;

	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;

	Entity* star1;
	Entity* star2;
	Entity* rocket;


	bool running = 0;

	float rocketScale; // a scale to make the texture smaller or larger

public:
	Scene1(SDL_Window* sdlWindow);
	~Scene1();
	bool OnCreate() override;
	void OnDestroy() override;
	void HandleEvents(const SDL_Event& event) override;
	void Update(const float time) override;
	void Render() const override;
};

#endif

