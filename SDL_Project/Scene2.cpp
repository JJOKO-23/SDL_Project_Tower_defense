#include "Scene2.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <MMath.h>
#include <iostream>
#include "Entity.h"



Scene2::Scene2(SDL_Window* sdlWindow_) :
	window(sdlWindow_)
	, renderer(nullptr)
	, back(nullptr)
	, character(nullptr)
	, flappyScale(2.0f)
	, xAxis(30.0f)
	, yAxis(15.0f)
{

}

Scene2::~Scene2() {

}

bool Scene2::OnCreate() {
	// Create a project matrix that moves positions from physics/world space 
	// to screen/pixel space
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, -1.0f, 1.0f);
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
	back = new Entity();
	back->pos = Vec3(0.0f, 15.0f, 0.0f);
	back->SetImage("textures/background4b.png", renderer);
/*
	character = new Entity();
	character->pos = Vec3(0.0f, 5.0f, 0.0f);
	character->SetImage("textures/idle.png", renderer);*/


	SDL_Init(SDL_INIT_AUDIO);
	MIX_Init();

	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

	if (!mixer)
	{
		std::cout << "Failed to create mixer: %s\n", SDL_GetError();
		return 0;
	}

	//// Load and play music
	MIX_Audio* Music = MIX_LoadAudio(mixer, "Audio/CrabRave.wav", true);
	MIX_SetMasterGain(mixer, master_volume);
	MIX_PlayAudio(mixer, Music);
	MIX_DestroyAudio(Music);


	return true;
}

void Scene2::OnDestroy() {
	// Clean up the renderer
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	//// Turn off audio
	if (mixer)
	{
		MIX_DestroyMixer(mixer);
		MIX_Quit();
	}

	// Delete the objects created on the heap
	// and set to the null pointer just to be safe
	delete back;
	back = nullptr;

	/*delete character;
	character = nullptr;*/
}

void Scene2::HandleEvents(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_EVENT_KEY_DOWN:
		/*  // Change angle of the ball
		if (event.key.scancode == SDL_SCANCODE_O) {
			character->angleDeg -= 10.0f;
		}
		if (event.key.scancode == SDL_SCANCODE_P) {
			character->angleDeg += 10.0f;
		}
		if (event.key.scancode == SDL_SCANCODE_SPACE) {
			float angleRad = character->angleDeg * (3.14159f / 180.0f);
			character->vel.y -= sin(angleRad) * 30.0f;
			character->vel.x += cos(angleRad) * 30.0f;

			running = 1;
		}*/
		break;

	default:
		break;
	}
}

void Scene2::Update(const float deltaTime) {
	/// Physics goes here	
	/*if (running) {
		Vec3 gravity = Vec3(0.0f, -9.8f, 0.0f); // F = m * a
		Vec3 drag = -0.2f * character->vel; // F = -c * v
		Vec3 wind = Vec3(-15.0f, 0.0f, 0.0f); // F = constant
		Vec3 netForce = gravity + drag + wind;
		character->ApplyForce(netForce); // gravity
		character->Update(deltaTime);
	}*/
}

void Scene2::Render() const {
	SDL_RenderClear(renderer);


	Vec3 screenCoords = projectionMatrix * back->pos;
	
	SDL_FRect square;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	float scale = 1.5f;
	square.w = back->GetSurface()->w * scale;
	square.h = back->GetSurface()->h * scale;

	SDL_RenderTextureRotated(renderer, back->GetTexture(), nullptr, &square, back->angleDeg, nullptr, SDL_FLIP_NONE);

/*
	screenCoords = projectionMatrix * character->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = character->GetSurface()->w * flappyScale;
	square.h = character->GetSurface()->h * flappyScale;
	SDL_RenderTextureRotated(renderer, character->GetTexture(), nullptr, &square, character->angleDeg, nullptr, SDL_FLIP_NONE);
	*/
	//screenCoords = projectionMatrix * back->pos;
	//square.x = screenCoords.x;
	//square.y = screenCoords.y;
	//square.w = back->GetSurface()->w  ;
	//square.h = back->GetSurface()->h ;
	//SDL_RenderTextureRotated(renderer, back->GetTexture(), nullptr, &square, back->angleDeg, nullptr, SDL_FLIP_NONE);



	// Update the screen
	SDL_RenderPresent(renderer);
}