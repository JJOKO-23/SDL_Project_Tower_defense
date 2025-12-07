#include "Scene2.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <MMath.h>
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include<SDL3/SDL_mixer.h>



Scene2::Scene2(SDL_Window* sdlWindow_) :
	window(sdlWindow_)
	, renderer(nullptr)
	, back(nullptr)
	, character(nullptr)
	, enemy1(nullptr)
	
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



	tower = new Tower(300.0f);
	tower->pos = Vec3(15, 2, 0);
	
	waves = new WaveSystem();
	waves->Init(tower);



	#pragma region PlayerIdleAnimation
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_000.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_001.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_002.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_003.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_004.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_005.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_006.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_007.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_008.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_009.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_010.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_011.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_012.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_013.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_014.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_015.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_016.png"));
		player->idleAnim.AddFrame(IMG_LoadTexture(renderer, "textures/IDLE_017.png"));
		// файликик можно менять мяу

	#pragma endregion

	#pragma region PlayerWALKAnimation
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_000.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_001.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_002.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_003.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_004.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_005.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_006.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_007.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_008.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_009.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_010.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_011.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_012.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_013.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_014.png"));
	player->walkAnim.AddFrame(IMG_LoadTexture(renderer, "textures/WALK_015.png"));
	#pragma endregion
	// скорость анимации
	player->animation.SetFPS(17.0f);

	
	//character->SetImage("textures/idle.png", renderer);

	Platform* ground = new Platform(Vec3(5, 1, 0), 15, 2);
	ground->SetImage("textures/grass.jpg", renderer);
	platforms.push_back(ground);

	Platform* ground2 = new Platform(Vec3(24, 1, 0), 15, 2);
	ground2->SetImage("textures/grass.jpg", renderer);
	platforms.push_back(ground2);



	Platform* block = new Platform(Vec3(5, 4, 0), 4, 1);
	platforms.push_back(block);
	Platform* block2 = new Platform(Vec3(25, 5, 0), 4, 1);
	platforms.push_back(block2);

	Platform* block3 = new Platform(Vec3(10, 8, 0), 4, 1);
	platforms.push_back(block3);
	Platform* block4 = new Platform(Vec3(20, 8, 0), 4, 1);
	platforms.push_back(block4);

	entities.push_back(player);



	//**********************UUUUIII*********************

	mainMenuBackground = IMG_LoadTexture(renderer, "textures/MAIN_SCREEN.png");
	SDL_GetWindowSize(window, &w, &h);

	mainMenuRect.x = 0;
	mainMenuRect.y = 0;
	mainMenuRect.w = w;
	mainMenuRect.h = h;

	
	playButtonTexture = IMG_LoadTexture(renderer, "textures/UI_GAME.png");
	
	SDL_GetWindowSize(window, &w, &h);

	playButtonRect.x = 320;
	playButtonRect.y = 340;
	playButtonRect.w = 420;
	playButtonRect.h = 270;

	mainMenuRect.x = (w / 2.0f) - (mainMenuRect.w / 2.0f);
	mainMenuRect.y = (h / 2.0f) - (mainMenuRect.h / 2.0f);
	
	/////////////////

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
		std::cout << "SDL audio init error: " << SDL_GetError() << std::endl;
	}

	if (!MIX_Init()) {
		std::cout << "MIX_Init error: " << SDL_GetError() << std::endl;
	}

	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
	if (!mixer) {
		std::cout << "Failed to create mixer: " << SDL_GetError() << std::endl;
		return false;
	}

	// громкость (1.0f = 100%)
	MIX_SetMasterGain(mixer, 0.2f);


	// ====== LOAD GAME MUSIC ======
	gameMusic = MIX_LoadAudio(mixer, "Audio/GAME_Audio.mp3", true);
	if (!gameMusic) {
		std::cout << "Failed to load GameMusic.wav: " << SDL_GetError() << std::endl;
	}

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
	//if (mixer)
	//{
	//	MIX_DestroyMixer(mixer);
	//	MIX_Quit();
	//}

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

	if (menuMusic) {
		MIX_DestroyAudio(menuMusic);
		menuMusic = nullptr;
	}

	//if (gameMusic) {
	//	MIX_DestroyAudio(gameMusic);
	//	gameMusic = nullptr;
	//}


}

void Scene2::HandleEvents(const SDL_Event& event)
{
	player->HandleInput(event);

	if (showMainMenu)
	{
		if (event.type == SDL_EVENT_MOUSE_MOTION)
		{
			float mx = event.motion.x;
			float my = event.motion.y;

			bool inside =
				mx >= playButtonRect.x && mx <= playButtonRect.x + playButtonRect.w &&
				my >= playButtonRect.y && my <= playButtonRect.y + playButtonRect.h;

			if (inside)
			{
				playHover = true;
				playTargetScale = 1.15f;   // кнопка увеличивается
			}
			else
			{
				playHover = false;
				playTargetScale = 1.0f;    // возвращается к нормальному размеру
			}
		}

		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
		{
			float mx = event.button.x;
			float my = event.button.y;

			if (mx >= playButtonRect.x && mx <= playButtonRect.x + playButtonRect.w &&
				my >= playButtonRect.y && my <= playButtonRect.y + playButtonRect.h)
			{
				showMainMenu = false;
				
				if (gameMusic) {
					MIX_PlayAudio(mixer, gameMusic);
				}
				
			}
		}

		return;
	}

	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
		event.button.button == SDL_BUTTON_LEFT)
	{
		
		player->Attack((std::vector<Entity*>&)waves->enemies, projectiles);

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

	if (showMainMenu)
	{
		// плавная интерполяция
		float speed = 10.0f; // скорость анимации
		playScale += (playTargetScale - playScale) * speed * deltaTime;

		return;
	}

	player->Update(deltaTime);
	waves->Update(deltaTime, player->pos, playerHP);
	//character->pos += character->vel * deltaTime;
	collisionManager->CheckPlayerPlatform(player, platforms);
	collisionManager->CheckCollisions(entities);
	
	
	//collisionManager->CheckCollisions(entities);
	collisionManager->ClampToWorld(player);
	player->animation.Update(deltaTime);




	//projectiles update START

	for (int i = projectiles.size() - 1; i >= 0; i--)
	{
		projectiles[i]->Update(deltaTime);

		bool destroyed = false;

		
		for (int e = (int)waves->enemies.size() - 1; e >= 0; e--)
		{
			float dx = fabs(projectiles[i]->pos.x - waves->enemies[e]->pos.x);
			float dy = fabs(projectiles[i]->pos.y - waves->enemies[e]->pos.y);

			if (dx < 1.0f && dy < 1.0f)
			{
				
				waves->enemies[e]->TakeDamage(playerDamage);

				
				if (waves->enemies[e]->IsDead())
				{
					delete waves->enemies[e];
					waves->enemies.erase(waves->enemies.begin() + e);
				}

				delete projectiles[i];
				projectiles.erase(projectiles.begin() + i);

				destroyed = true;
				break;
			}
		}

		if (destroyed)
			continue;

		
		if (projectiles[i]->pos.x < 0 || projectiles[i]->pos.x > xAxis)
		{
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
		}
	}
	//projectiles update END
}

	


void DrawAABB(SDL_Renderer* renderer, float x, float y, float w, float h, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_FRect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_RenderRect(renderer, &rect);
}
void Scene2::Render() const {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	//UI RENDERING
	if (showMainMenu)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// рисуем фон меню
		if (mainMenuBackground)
		{
			SDL_RenderTexture(renderer, mainMenuBackground, nullptr, &mainMenuRect);
		}

		// ----------- HOVER SCALE -----------
		// центр кнопки
		float cx = playButtonRect.x + playButtonRect.w / 2.0f;
		float cy = playButtonRect.y + playButtonRect.h / 2.0f;

		// прямоугольник с учётом текущего масштаба (playScale)
		SDL_FRect scaledRect;
		scaledRect.w = playButtonRect.w * playScale;
		scaledRect.h = playButtonRect.h * playScale;
		scaledRect.x = cx - scaledRect.w / 2.0f;
		scaledRect.y = cy - scaledRect.h / 2.0f;

		// рисуем увеличенную / уменьшенную кнопку
		SDL_RenderTexture(renderer, playButtonTexture, nullptr, &scaledRect);

		SDL_RenderPresent(renderer);
		return;
	}
	//UI RENDERING END

	// Render the player here
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
	
	SDL_Texture* pFrame = player->currentAnim->GetCurrentFrame();
	screenCoords = projectionMatrix * player->pos;
	SDL_FRect pr;
	pr.w = 150;     // размер спрайта на экране
	pr.h = 150;
	pr.x = screenCoords.x - pr.w * 0.5f;
	pr.y = screenCoords.y - pr.h * 0.5f;

	SDL_FlipMode flip = player->facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	SDL_RenderTextureRotated(renderer, pFrame, nullptr, &pr, 0, nullptr, flip);;
	// draw AABB as green rectangle
	DrawAABB(renderer, pr.x, pr.y, pr.w, pr.h, SDL_Color{ 0, 255, 0, 255 });
	//Player HP bar render
	Vec3 psc = projectionMatrix * player->pos;

	float hpRatio = playerHP / playerMaxHP;

	SDL_FRect hpBg = { psc.x - 30, psc.y - 90, 60, 6 };
	SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
	SDL_RenderFillRect(renderer, &hpBg);

	SDL_FRect hpFill = { psc.x - 30, psc.y - 90, 60 * hpRatio, 6 };
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &hpFill);
	
	

	
	float pixelsPerUnitX = 1280 / xAxis;
	float pixelsPerUnitY = 720 / yAxis;
	// platforms render
	for (auto p : platforms)
	{
		Vec3 sc = projectionMatrix * p->pos;

		SDL_FRect r;
		r.w = p->width * pixelsPerUnitX;
		r.h = p->height * pixelsPerUnitY;

		r.x = sc.x - r.w * 0.5f;
		r.y = sc.y - r.h * 0.5f;

		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderFillRect(renderer, &r);

		// draw texture
		SDL_RenderTexture(renderer, p->texture, nullptr, &r);

		// draw AABB as red rectangle
		DrawAABB(renderer, r.x, r.y, r.w, r.h, SDL_Color{ 255, 0, 0, 255 });
	}
	// projectiles render			
	for (auto p : projectiles)
	{
		Vec3 sc = projectionMatrix * p->pos;

		SDL_FRect r;
		r.x = sc.x;
		r.y = sc.y;
		r.w = 20; 
		r.h = 4;  

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &r);
	}

	//wawes render enemies
	for (auto e : waves->enemies) {
		Vec3 sc = projectionMatrix * e->pos;

		SDL_FRect r;
		r.x = sc.x - 10;
		r.y = sc.y - 10;
		r.w = 20;
		r.h = 20;

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &r);

		// HP BAR
		float hpRatio = e->GetHP() / e->GetMaxHP();
		SDL_FRect hpBar;
		hpBar.x = r.x;
		hpBar.y = r.y - 8;
		hpBar.w = 20 * hpRatio;
		hpBar.h = 4;

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer, &hpBar);
	}
	// tower render
	Vec3 tpos = projectionMatrix * tower->pos;

	SDL_FRect towerRect = { tpos.x - 15, tpos.y - 15, 30, 30 };
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &towerRect);

	// money bar
	float mRatio = tower->GetMoney() / tower->GetMaxMoney();
	SDL_FRect moneyBar = { towerRect.x, towerRect.y - 6, 30 * mRatio, 4 };

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderFillRect(renderer, &moneyBar);




	// Update the screen
	SDL_RenderPresent(renderer);
}