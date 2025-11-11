#include "Scene1.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <MMath.h>
#include <iostream>
#include "Entity.h"

Scene1::Scene1(SDL_Window* sdlWindow_) :
	window(sdlWindow_)
	, renderer(nullptr)
	, star1(nullptr)
	, star2(nullptr)
	, rocket(nullptr)
	, rocketScale(0.15f)
	, xAxis(80.0f)
	, yAxis(40.0f)
{

}

Scene1::~Scene1() {

}

bool Scene1::OnCreate() {
	// Create a project matrix that moves positions from physics/world space 
	// to screen/pixel space
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(-1.0f, xAxis, -15.0f, yAxis, -1.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	//Create screen renderer
	renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	//Initialize renderer color (black)
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Create the objects that will be rendered on the screen
	star1 = new Entity();
	star1->pos = Vec3(5.0f, 10.0f, 0.0f);
	star1->SetImage("textures/stars.png", renderer);
	star1->mass = 100.0f;

	star2 = new Entity();
	star2->pos = Vec3(15.0f, 25.0f, 0.0f);
	star2->SetImage("textures/stars.png", renderer);
	star2->mass = 150.0f;

	rocket = new Entity();
	rocket->pos = Vec3(10.0f, 20.0f, 0.0f);
	rocket->SetImage("textures/rocket.png", renderer);
	rocket->mass = 2.0f;

	return true;
}

void Scene1::OnDestroy() {
	// Clean up the renderer
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	// Delete the objects created on the heap
	// and set to the null pointer just to be safe
	delete star1;
	star1 = nullptr;

	delete star2;
	star2 = nullptr;

	delete rocket;
	rocket = nullptr;
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_EVENT_KEY_DOWN:
		if (event.key.scancode == SDL_SCANCODE_SPACE) {
			rocket->vel = Vec3(4.6f, -2.0f, 0.0f);

			running = 1;
		}
		break;

	default:
		break;
	}
}

void Scene1::Update(const float deltaTime) {
	/// Physics goes here	
	if (running) {
		float G = 1.0f;
		float rS1 = VMath::mag(star1->pos - rocket->pos);
		float pullRocketToStar1 = (G * rocket->mass * star1->mass) / pow(rS1,2);
		Vec3 forceDirection = VMath::normalize(star1->pos - rocket->pos);
		Vec3 forceOnRocketFromStar1 = forceDirection * pullRocketToStar1;
		
		float rS2 = VMath::mag(star2->pos - rocket->pos);
		float pullRocketToStar2 = (G * rocket->mass * star2->mass) / pow(rS2, 2);
		Vec3 forceDirection2 = VMath::normalize(star2->pos - rocket->pos);
		Vec3 forceOnRocketFromStar2 = forceDirection2 * pullRocketToStar2;
		Vec3 netForceOnRocket = forceOnRocketFromStar1 + forceOnRocketFromStar2;

		Vec3 normalizedVelocity = VMath::normalize(rocket->vel);
		rocket->angleDeg = (atan2(normalizedVelocity.y, normalizedVelocity.x) * RADIANS_TO_DEGREES) ;

		rocket->ApplyForce(netForceOnRocket);
		rocket->Update(deltaTime);

	}
}

void Scene1::Render() const {
	SDL_RenderClear(renderer);

	// Convert from world coordinates to pixel coordinates using Scott's magical matrix
	Vec3 screenCoords = projectionMatrix * star1->pos;
	// Set up sprite's position and size
	SDL_FRect square;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = star1->GetSurface()->w;
	square.h = star1->GetSurface()->h;
	// Display object on the screen
	SDL_RenderTextureRotated(renderer, star1->GetTexture(), nullptr, &square, star1->angleDeg, nullptr, SDL_FLIP_NONE);

	// Rinse and repeat for star2
	screenCoords = projectionMatrix * star2->pos;
	square.x = screenCoords.x ;
	square.y = screenCoords.y ;
	square.w = star2->GetSurface()->w ; 
	square.h = star2->GetSurface()->h ;
	SDL_RenderTextureRotated(renderer, star2->GetTexture(), nullptr, &square, star2->angleDeg, nullptr, SDL_FLIP_NONE);

	// Rinse and repeat for rocket
	screenCoords = projectionMatrix * rocket->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = rocket->GetSurface()->w * rocketScale;
	square.h = rocket->GetSurface()->h * rocketScale;
	SDL_RenderTextureRotated(renderer, rocket->GetTexture(), nullptr, &square, rocket->angleDeg, nullptr, SDL_FLIP_NONE);


	// Update the screen
	SDL_RenderPresent(renderer);
}