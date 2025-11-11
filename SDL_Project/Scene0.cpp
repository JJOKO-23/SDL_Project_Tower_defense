#include "Scene0.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <MMath.h>
#include <iostream>
#include "Entity.h"



Scene0::Scene0(SDL_Window* sdlWindow_) :
	window(sdlWindow_)
	, renderer(nullptr)
	, cliff(nullptr)
	, flappy(nullptr)
	, flappyScale(2.0f)
	, xAxis(30.0f)
	, yAxis(15.0f)
{

}

Scene0::~Scene0(){

}

bool Scene0::OnCreate() {
	// Create a project matrix that moves positions from physics/world space 
	// to screen/pixel space
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
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
	cliff = new Entity();
	cliff->pos = Vec3(0.0f, 5.0f, 0.0f);
	cliff->SetImage("textures/cliff.png", renderer);

	flappy = new Entity();
	flappy->pos = Vec3(0.0f, 5.0f, 0.0f);
	flappy->SetImage("textures/flappyBird.png", renderer);




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

void Scene0::OnDestroy() {
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
	delete cliff;
	cliff = nullptr;

	delete flappy;
	flappy = nullptr;
}

void Scene0::HandleEvents(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_EVENT_KEY_DOWN:
		// Change angle of the ball
		if (event.key.scancode == SDL_SCANCODE_O) {
			flappy->angleDeg -= 10.0f;
		}
		if (event.key.scancode == SDL_SCANCODE_P) {
			flappy->angleDeg += 10.0f;
		}
		if (event.key.scancode == SDL_SCANCODE_SPACE) {
			float angleRad = flappy->angleDeg * (3.14159f / 180.0f);
			flappy->vel.y -= sin(angleRad) * 30.0f;
			flappy->vel.x += cos(angleRad) * 30.0f;
		
			running = 1;
		}
		break;

	default:
		break;
	}
}

void Scene0::Update(const float deltaTime) {
	/// Physics goes here	
	if (running) {
		Vec3 gravity = Vec3(0.0f, -9.8f, 0.0f); // F = m * a
		Vec3 drag = -0.2f * flappy->vel; // F = -c * v
		Vec3 wind = Vec3(-15.0f, 0.0f, 0.0f); // F = constant
		Vec3 netForce = gravity + drag + wind;
		flappy->ApplyForce(netForce); // gravity
		flappy->Update(deltaTime);
	}
}

void Scene0::Render() const {
	SDL_RenderClear(renderer);

	// Convert from world coordinates to pixel coordinates using Scott's magical matrix
	Vec3 screenCoords = projectionMatrix * cliff->pos;
	// Set up sprite's position and size
	SDL_FRect square;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = cliff->GetSurface()->w;
	square.h = cliff->GetSurface()->h;
	// Display object on the screen
	SDL_RenderTextureRotated(renderer, cliff->GetTexture(), nullptr, &square, cliff->angleDeg, nullptr, SDL_FLIP_NONE);

	// Rinse and repeat for flappy
	screenCoords = projectionMatrix * flappy->pos;
	square.x = screenCoords.x;
	square.y = screenCoords.y;
	square.w = flappy->GetSurface()->w * flappyScale; // we will scale the bird 
	square.h = flappy->GetSurface()->h * flappyScale;
	SDL_RenderTextureRotated(renderer, flappy->GetTexture(), nullptr, &square, flappy->angleDeg, nullptr, SDL_FLIP_NONE);

	// Update the screen
	SDL_RenderPresent(renderer);
}