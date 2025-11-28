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
	//, enemy1(nullptr)
	
	, player(nullptr)
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

	player = new Player();
	player->pos = Vec3(15, 8, 0);
	//player->radius = 1.0f;
	//player->radius = 0.5f;

	// файликик можно менять мяу
	player->AddAnimationFrame("textures/IDLE_000.png", renderer);
	player->AddAnimationFrame("textures/IDLE_001.png", renderer);
	player->AddAnimationFrame("textures/IDLE_002.png", renderer);
	player->AddAnimationFrame("textures/IDLE_003.png", renderer);
	player->AddAnimationFrame("textures/IDLE_004.png", renderer);
	player->AddAnimationFrame("textures/IDLE_005.png", renderer);
	player->AddAnimationFrame("textures/IDLE_006.png", renderer);
	player->AddAnimationFrame("textures/IDLE_007.png", renderer);
	player->AddAnimationFrame("textures/IDLE_008.png", renderer);
	player->AddAnimationFrame("textures/IDLE_009.png", renderer);
	player->AddAnimationFrame("textures/IDLE_010.png", renderer);
	player->AddAnimationFrame("textures/IDLE_011.png", renderer);
	player->AddAnimationFrame("textures/IDLE_012.png", renderer);
	player->AddAnimationFrame("textures/IDLE_013.png", renderer);
	player->AddAnimationFrame("textures/IDLE_014.png", renderer);
	player->AddAnimationFrame("textures/IDLE_015.png", renderer);
	player->AddAnimationFrame("textures/IDLE_016.png", renderer);
	player->AddAnimationFrame("textures/IDLE_017.png", renderer);


	// скорость анимации
	player->animation.SetFPS(12.0f);

	//enemy1 = new Entity();
	//enemy1->pos = Vec3(10.0f, 7.5f, 0.0f);
	//enemy1->radius = 0.5f;
	//character->SetImage("textures/idle.png", renderer);
	Platform* ground = new Platform(Vec3(15, 3, 0), 6, 1);
	ground->SetImage("textures/Stontex.png", renderer);
	platforms.push_back(ground);

	Platform* block = new Platform(Vec3(10, 8, 0), 4, 1);
	platforms.push_back(block);


	entities.push_back(player);
	entities.push_back(enemy1);

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

	collisionManager = new CollisionManager(0.0f, xAxis, 0.0f, yAxis);
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

	if (collisionManager) {
		delete collisionManager;
		collisionManager = nullptr;
	}
	// Delete the objects created on the heap
	// and set to the null pointer just to be safe
	delete back;
	back = nullptr;

	delete character;
	character = nullptr;

	//delete enemy1;
	//enemy1 = nullptr;

	delete player;
	player = nullptr;

}

void Scene2::HandleEvents(const SDL_Event& event)
{
	player->HandleInput(event);
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

	player->Update(deltaTime);
	//character->pos += character->vel * deltaTime;
	collisionManager->CheckPlayerPlatform(player, platforms);
	//collisionManager->CheckCollisions(entities);
	collisionManager->ClampToWorld(player);
	player->animation.Update(deltaTime);

	//if (running) {
	//	Vec3 gravity = Vec3(0.0f, -9.8f, 0.0f);
	//	Vec3 drag = -0.2f * character->vel;
	//	Vec3 wind = Vec3(-15.0f, 0.0f, 0.0f);
	//	Vec3 netForce = gravity + drag + wind;
	//	//character->ApplyForce(netForce);
	//	//character->Update(deltaTime);
	//}

}

void Scene2::Render() const {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);




	Vec3 screenCoords = projectionMatrix * back->pos;
	SDL_FRect rect;
	rect.x = screenCoords.x;
	rect.y = screenCoords.y;
	rect.w = back->GetSurface()->w * 1.5f;
	rect.h = back->GetSurface()->h * 1.5f;
	SDL_RenderTextureRotated(renderer, back->GetTexture(), nullptr, &rect, back->angleDeg, nullptr, SDL_FLIP_NONE);

	screenCoords = projectionMatrix * player->pos;
	float size = player->radius * 2.0f * worldScale;
	//SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

	//это АНИМАЦИЯ НЕ ТРОГАТЬ 
	
	SDL_Texture* pFrame = player->animation.GetCurrentFrame();
	screenCoords = projectionMatrix * player->pos;
	SDL_FRect pr;
	pr.w = 100;     // размер спрайта на экране
	pr.h = 100;
	pr.x = screenCoords.x - pr.w * 0.5f;
	pr.y = screenCoords.y - pr.h * 0.5f;


	SDL_RenderTextureRotated(renderer, pFrame, nullptr, &pr, 0, nullptr, SDL_FLIP_NONE);

	for (auto p : platforms) {
		Vec3 sc = projectionMatrix * p->pos;
		SDL_FRect r;
		
		r.w = p->width * worldScale;
		r.h = p->height * worldScale;
		r.x = sc.x - r.w * 0.5f;
		r.y = sc.y - r.h * 0.5f;
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderFillRect(renderer, &r);
	}
	
	/*screenCoords = projectionMatrix * enemy1->pos;
	rect.x = screenCoords.x - 10;
	rect.y = screenCoords.y - 10;
	rect.w = 20;
	rect.h = 20;
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);*/


	// Update the screen
	SDL_RenderPresent(renderer);
}