#include "Scene2.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <MMath.h>
#include <iostream>
#include "Entity.h"
#include "Player.h"
#include<SDL3/SDL_mixer.h>
#include<SDL3/SDL_ttf.h>



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

	//TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", 24);
	

	//ACTOR CREATION START

	// Create the objects that will be rendered on the screen
	back = new Entity();
	back->pos = Vec3(0.0f, 15.0f, 0.0f);
	back->SetImage("textures/lala.png", renderer);

	player = new Player();
	player->pos = Vec3(15, 8, 0);
	
	tower = new Tower(500.0f);
	tower->pos = Vec3(15, 2, 0);
	
	waves = new WaveSystem();
	waves->Init(tower, platforms);



	//ACTOR CREATION END


	//ANIMATION START

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

#pragma region PlayerMeleeAnimation
	player->meleeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/slash_000 (1).png"));
	player->meleeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/slash_000 (2).png"));
	player->meleeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/slash_000 (3).png"));
	player->meleeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/slash_000 (4).png"));
	player->meleeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/slash_000 (5).png"));
	player->meleeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/slash_000 (6).png"));
	player->meleeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/slash_000 (7).png"));
	player->meleeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/slash_000 (8).png"));
	player->meleeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/slash_000 (9).png"));
	player->meleeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/slash_000 (10).png"));
	player->meleeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/slash_000 (11).png"));
	player->meleeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/slash_000 (12).png"));
	
#pragma endregion

#pragma region PlayerRangeAnimation
	player->rangeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/RANGE_000 (1).png"));
	player->rangeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/RANGE_000 (2).png"));
	player->rangeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/RANGE_000 (3).png"));
	player->rangeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/RANGE_000 (4).png"));
	player->rangeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/RANGE_000 (5).png"));
	player->rangeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/RANGE_000 (6).png"));
	player->rangeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/RANGE_000 (7).png"));
	player->rangeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/RANGE_000 (8).png"));
	player->rangeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/RANGE_000 (9).png"));
	player->rangeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/RANGE_000 (10).png"));
	player->rangeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/RANGE_000 (11).png"));
	player->rangeAnim.AddFrame(IMG_LoadTexture(renderer, "textures/RANGE_000 (12).png"));
	
#pragma endregion

	enemyAnimFrames.reserve(6);

	SDL_Texture* ef0 = IMG_LoadTexture(renderer, "textures/enemy_attack (1).png");
	SDL_Texture* ef1 = IMG_LoadTexture(renderer, "textures/enemy_attack (2).png");
	SDL_Texture* ef2 = IMG_LoadTexture(renderer, "textures/enemy_attack (3).png");
	SDL_Texture* ef3 = IMG_LoadTexture(renderer, "textures/enemy_attack (4).png");
	SDL_Texture* ef4 = IMG_LoadTexture(renderer, "textures/enemy_attack (5).png");
	SDL_Texture* ef5 = IMG_LoadTexture(renderer, "textures/enemy_attack (6).png");
	SDL_Texture* ef6 = IMG_LoadTexture(renderer, "textures/enemy_attack (7).png");
	SDL_Texture* ef7 = IMG_LoadTexture(renderer, "textures/enemy_attack (8).png");
	SDL_Texture* ef8 = IMG_LoadTexture(renderer, "textures/enemy_attack (9).png");
	SDL_Texture* ef9 = IMG_LoadTexture(renderer, "textures/enemy_attack (10).png");
	SDL_Texture* ef10 = IMG_LoadTexture(renderer, "textures/enemy_attack (11).png");
	SDL_Texture* ef11 = IMG_LoadTexture(renderer, "textures/enemy_attack (12).png");
	

	// Добавляем только реально загруженные
	if (ef0) enemyAnimFrames.push_back(ef0);
	if (ef1) enemyAnimFrames.push_back(ef1);
	if (ef2) enemyAnimFrames.push_back(ef2);
	if (ef3) enemyAnimFrames.push_back(ef3);
	if (ef4) enemyAnimFrames.push_back(ef4);
	if (ef5) enemyAnimFrames.push_back(ef5);
	if (ef6) enemyAnimFrames.push_back(ef6);
	if (ef7) enemyAnimFrames.push_back(ef7);
	if (ef8) enemyAnimFrames.push_back(ef8);
	if (ef9) enemyAnimFrames.push_back(ef9);
	if (ef10) enemyAnimFrames.push_back(ef10);
	if (ef11) enemyAnimFrames.push_back(ef11);;

	enemyAnimFrames.reserve(12);

	if (enemyAnimFrames.empty()) {
		std::cout << "WARNING: Enemy animation frames not loaded. Will fallback to e->texture.\n";
	}


	// скорость анимации
	player->animation.SetFPS(17.0f);

	
	//ANIMATION END

	//PLATFORMS	START

	Platform* ground = new Platform(Vec3(5, 1, 0), 15, 2);
	ground->SetImage("textures/lalaBrick.png", renderer);
	platforms.push_back(ground);

	Platform* ground2 = new Platform(Vec3(24, 1, 0),20, 2);
	ground2->SetImage("textures/lalaBrick.png", renderer);
	platforms.push_back(ground2);

	Platform* block = new Platform(Vec3(5, 4, 0), 4, 1);
	block->SetImage("textures/lalaBrick.png", renderer);
	platforms.push_back(block);
	Platform* block2 = new Platform(Vec3(25, 5, 0), 4, 1);
	block2->SetImage("textures/lalaBrick.png", renderer);
	platforms.push_back(block2);

	Platform* block3 = new Platform(Vec3(10, 8, 0), 4, 1);
	block3->SetImage("textures/lalaBrick.png", renderer);
	platforms.push_back(block3);
	Platform* block4 = new Platform(Vec3(20, 8, 0), 4, 1);
	block4->SetImage("textures/lalaBrick.png", renderer);
	platforms.push_back(block4);

	entities.push_back(player);

	//PLATFORMS END

	//**********************UUUUIII*********************

	winTexture = IMG_LoadTexture(renderer, "textures/LOSE.png");
	if (!winTexture)
	{
		std::cout << "Failed to load WIN texture: " << SDL_GetError() << std::endl;
	}
	loseTexture = IMG_LoadTexture(renderer, "textures/WIN.png");
	if (!winTexture)
	{
		std::cout << "Failed to load WIN texture: " << SDL_GetError() << std::endl;
	}

	towerTexture = IMG_LoadTexture(renderer, "textures/TOWER.png");
	if (!towerTexture)
	{
		std::cout << "Failed to load tower texture: " << SDL_GetError() << std::endl;
	}

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


	settingsButtonTexture = IMG_LoadTexture(renderer, "textures/SETTINGS_BUTTON2.png");
	settingsButtonRect.x = 320;
	settingsButtonRect.y = 500;
	settingsButtonRect.w = 420;
	settingsButtonRect.h = 270;

	settingsBackground = IMG_LoadTexture(renderer, "textures/MAIN_SCREEN.png");

	volumeBarTexture = IMG_LoadTexture(renderer, "textures/VOLUME_BAR2.png");
	volumeBarRect = { 300, 300, 700, 100 };

	backButtonTexture = IMG_LoadTexture(renderer, "textures/BACK_BUTTON.png");
	backButtonRect = { 20, 20, 200, 120 };
	
	//**********************UUUUIII*********************
	// ===== INIT AUDIO =====

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

	if (gameMusic)
	{
		musicTrack = MIX_CreateTrack(mixer);
		if (!musicTrack)
		{
			std::cout << "Failed to create music track: " << SDL_GetError() << std::endl;
		}
		else
		{
			// bind audio to this track
			MIX_SetTrackAudio(musicTrack, gameMusic);

			// initial volume (you уже можешь ещё и master gain юзать, это опционально)
			MIX_SetTrackGain(musicTrack, volume);
		}
	}
	// ===== INIT AUDIO END =====

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

	if (musicTrack)
	{
		MIX_DestroyTrack(musicTrack);
		musicTrack = nullptr;
	}

	if (gameMusic)
	{
		MIX_DestroyAudio(gameMusic);
		gameMusic = nullptr;
	}

	//if (gameMusic) {
	//	MIX_DestroyAudio(gameMusic);
	//	gameMusic = nullptr;
	//}
	/*for (SDL_Texture* t : enemyAnimFrames) {
		if (t) SDL_DestroyTexture(t);
	}*/
	enemyAnimFrames.clear();
	enemyAnim.clear();

}

void Scene2::HandleEvents(const SDL_Event& event)
{
	// ===== GLOBAL: return to main menu from in-game with ESC =====
	if (!showMainMenu && !showSettingsMenu)
	{
		if (event.type == SDL_EVENT_KEY_DOWN &&
			event.key.key == SDLK_ESCAPE)
		{
			showMainMenu = true;
			showSettingsMenu = false;

			if (musicTrack)
			{
				// stop immediately, no fade (0 frames)
				MIX_StopTrack(musicTrack, 0);
			}

			return;
		}
	}

	// Player input (movement, jump, attacks bound to keys, etc.)
	player->HandleInput(event);

	// ===== MAIN MENU =====
	if (showMainMenu)
	{
		// Play button hover
		if (event.type == SDL_EVENT_MOUSE_MOTION)
		{
			float mx = event.motion.x;
			float my = event.motion.y;

			bool overPlay =
				mx >= playButtonRect.x &&
				mx <= playButtonRect.x + playButtonRect.w &&
				my >= playButtonRect.y &&
				my <= playButtonRect.y + playButtonRect.h;

			if (overPlay)
			{
				playHover = true;
				playTargetScale = 1.15f;
			}
			else
			{
				playHover = false;
				playTargetScale = 1.0f;
			}

			bool overSettings =
				mx >= settingsButtonRect.x &&
				mx <= settingsButtonRect.x + settingsButtonRect.w &&
				my >= settingsButtonRect.y &&
				my <= settingsButtonRect.y + settingsButtonRect.h;

			settingsTargetScale = overSettings ? 1.15f : 1.0f;
		}

		// Play / Settings clicks
		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
			event.button.button == SDL_BUTTON_LEFT)
		{
			float mx = event.button.x;
			float my = event.button.y;

			bool overPlay =
				mx >= playButtonRect.x &&
				mx <= playButtonRect.x + playButtonRect.w &&
				my >= playButtonRect.y &&
				my <= playButtonRect.y + playButtonRect.h;

			if (overPlay)
			{
				showMainMenu = false;

				if (musicTrack)
				{
					// start or restart this single track (no duplication)
					MIX_PlayTrack(musicTrack, 0);   // options = 0 for now
				}
				return;
			}

			bool overSettings =
				mx >= settingsButtonRect.x &&
				mx <= settingsButtonRect.x + settingsButtonRect.w &&
				my >= settingsButtonRect.y &&
				my <= settingsButtonRect.y + settingsButtonRect.h;

			if (overSettings)
			{
				showSettingsMenu = true;
				return;
			}
		}

		return; // do not process game events while in main menu
	}

	// ===== SETTINGS MENU =====
	if (showSettingsMenu)
	{
		// Back button
		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
			event.button.button == SDL_BUTTON_LEFT)
		{
			float mx = event.button.x;
			float my = event.button.y;

			bool overBack =
				mx >= backButtonRect.x &&
				mx <= backButtonRect.x + backButtonRect.w &&
				my >= backButtonRect.y &&
				my <= backButtonRect.y + backButtonRect.h;

			if (overBack)
			{
				showSettingsMenu = false;
				return;
			}
		}

		// Volume dragging
		if (event.type == SDL_EVENT_MOUSE_MOTION &&
			(event.motion.state & SDL_BUTTON_LMASK))
		{
			float mx = event.motion.x;

			float barStart = volumeBarRect.x;
			float barEnd = volumeBarRect.x + volumeBarRect.w;

			// clamp mouse X to bar range
			if (mx < barStart) mx = barStart;
			if (mx > barEnd)   mx = barEnd;

			volume = (mx - barStart) / volumeBarRect.w; // 0.0f .. 1.0f

			if (mixer)
			{
				// simple variant: master gain
				MIX_SetMasterGain(mixer, volume);
			}
		}

		return; // do not process game events while in settings
	}

	// ===== IN-GAME EVENTS =====
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
		settingsScale += (settingsTargetScale - settingsScale) * 10.0f * deltaTime;
		return;
	}

	player->Update(deltaTime);
	waves->Update(deltaTime, player->pos, playerHP);

	if (!enemyAnimFrames.empty())
	{
		// create / update anim state for each alive enemy
		for (Enemy* e : waves->enemies)
		{
			if (!e) continue;

			EnemyAnimState& st = enemyAnim[e]; // creates if missing
			st.timer += deltaTime;

			float frameTime = 1.0f / enemyAnimFPS;
			while (st.timer >= frameTime)
			{
				st.timer -= frameTime;
				st.frame = (st.frame + 1) % (int)enemyAnimFrames.size();
			}
		}

		// cleanup states for enemies that no longer exist
		for (auto it = enemyAnim.begin(); it != enemyAnim.end(); )
		{
			Enemy* key = it->first;

			bool stillAlive = false;
			for (Enemy* e : waves->enemies)
			{
				if (e == key) { stillAlive = true; break; }
			}

			if (!stillAlive) it = enemyAnim.erase(it);
			else ++it;
		}
	}



	for (Enemy* e : waves->enemies)
	{
		collisionManager->CheckEnemyPlatform(e, platforms);
	}




	collisionManager->CheckCollisions(entities);


	entities.clear();
	entities.push_back(player);

	//character->pos += character->vel * deltaTime;
	collisionManager->CheckPlayerPlatform(player, platforms);



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
					Enemy* dead = waves->enemies[e];

					// убрать анимационное состояние
					auto it = enemyAnim.find(dead);
					if (it != enemyAnim.end()) enemyAnim.erase(it);

					delete dead;
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
}
	//projectiles update END


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

	/// 1) СНАЧАЛА — SETTINGS MENU (если открыто)
	if (showSettingsMenu)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// фоновая картинка настроек
		if (settingsBackground)
		{
			SDL_RenderTexture(renderer, settingsBackground, nullptr, nullptr);
		}

		// Кнопка "Назад"
		if (backButtonTexture)
		{
			SDL_RenderTexture(renderer, backButtonTexture, nullptr, &backButtonRect);
		}

		// Полоса громкости
		if (volumeBarTexture)
		{
			SDL_RenderTexture(renderer, volumeBarTexture, nullptr, &volumeBarRect);
		}

		// Ползунок громкости
		SDL_FRect knob;
		knob.w = 40.0f;
		knob.h = 80.0f;
		knob.x = volumeBarRect.x + volume * volumeBarRect.w - knob.w * 0.5f;
		knob.y = volumeBarRect.y;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &knob);

		SDL_RenderPresent(renderer);
		return;
	}

	/// 2) ДАЛЬШЕ — ГЛАВНОЕ МЕНЮ



	
	if (showMainMenu)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// фон главного меню
		if (mainMenuBackground)
		{
			SDL_RenderTexture(renderer, mainMenuBackground, nullptr, &mainMenuRect);
		}

		// --- КНОПКА PLAY (с масштабом) ---
		float cx = playButtonRect.x + playButtonRect.w * 0.5f;
		float cy = playButtonRect.y + playButtonRect.h * 0.5f;

		SDL_FRect scaledPlay;
		scaledPlay.w = playButtonRect.w * playScale;
		scaledPlay.h = playButtonRect.h * playScale;
		scaledPlay.x = cx - scaledPlay.w * 0.5f;
		scaledPlay.y = cy - scaledPlay.h * 0.5f;

		if (playButtonTexture)
		{
			SDL_RenderTexture(renderer, playButtonTexture, nullptr, &scaledPlay);
		}

		// --- КНОПКА SETTINGS (с масштабом) ---
		float csx = settingsButtonRect.x + settingsButtonRect.w * 0.5f;
		float csy = settingsButtonRect.y + settingsButtonRect.h * 0.5f;

		SDL_FRect scaledSettings;
		scaledSettings.w = settingsButtonRect.w * settingsScale;
		scaledSettings.h = settingsButtonRect.h * settingsScale;
		scaledSettings.x = csx - scaledSettings.w * 0.5f;
		scaledSettings.y = csy - scaledSettings.h * 0.5f;

		if (settingsButtonTexture)
		{
			SDL_RenderTexture(renderer, settingsButtonTexture, nullptr, &scaledSettings);
		}

		SDL_RenderPresent(renderer);
		return;
	}
	//UI RENDERING END

	
	Vec3 screenCoords = projectionMatrix * back->pos;
	SDL_FRect rect;
	rect.x = screenCoords.x;
	rect.y = screenCoords.y;
	rect.w = back->GetSurface()->w * 1.5f;
	rect.h = back->GetSurface()->h * 1.5f;

	SDL_RenderTextureRotated(renderer, back->GetTexture(), nullptr, &rect, back->angleDeg, nullptr, SDL_FLIP_NONE);

	
	// platforms render
	
	float pixelsPerUnitX = 1280 / xAxis;
	float pixelsPerUnitY = 720 / yAxis;
	
	for (auto p : platforms)
	{
		Vec3 sc = projectionMatrix * p->pos;

		SDL_FRect r;
		r.w = p->width * pixelsPerUnitX;
		r.h = p->height * pixelsPerUnitY;
		r.x = sc.x - r.w * 0.5f;
		r.y = sc.y - r.h * 0.5f;
		// draw AABB as red rectangle
		//DrawAABB(renderer, r.x, r.y, r.w, r.h, SDL_Color{ 255, 0, 0, 255 });
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		SDL_RenderFillRect(renderer, &r);
		SDL_RenderTexture(renderer, p->texture, nullptr, &r);
		//DrawAABB(renderer, r.x, r.y, r.w, r.h, SDL_Color{ 255, 0, 0, 255 });
	}
	

	// tower render
	Vec3 tpos = projectionMatrix * tower->pos;

	SDL_FRect towerRect;
	towerRect.w = 280;   // подгони под картинку
	towerRect.h = 360;
	towerRect.x = tpos.x - towerRect.w * 0.5f;
	towerRect.y = tpos.y - towerRect.h + 60;

	SDL_RenderTexture(renderer, towerTexture, nullptr, &towerRect);

	// money bar
	float mRatio = tower->GetMoney() / tower->GetMaxMoney();
	SDL_FRect moneyBar = { towerRect.x, towerRect.y - 6, 150 * mRatio, 6 };

	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderFillRect(renderer, &moneyBar);

	// Render the player here
	screenCoords = projectionMatrix * player->pos;
	SDL_Texture* pFrame = player->currentAnim->GetCurrentFrame();
	SDL_FRect pr;
	pr.w = 150;
	pr.h = 150;
	pr.x = screenCoords.x - pr.w * 0.5f;
	pr.y = screenCoords.y - pr.h * 0.5f;

	SDL_FlipMode flip = player->facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	SDL_RenderTextureRotated(renderer, pFrame, nullptr, &pr, 0, nullptr, flip);;
	// draw AABB as green rectangle
	//DrawAABB(renderer, pr.x, pr.y, pr.w, pr.h, SDL_Color{ 0, 255, 0, 255 });

	//Player HP bar render
	Vec3 psc = projectionMatrix * player->pos;

	float hpRatio = playerHP / playerMaxHP;

	SDL_FRect hpBg = { psc.x - 30, psc.y - 90, 60, 6 };
	SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
	SDL_RenderFillRect(renderer, &hpBg);

	SDL_FRect hpFill = { psc.x - 30, psc.y - 90, 60 * hpRatio, 6 };
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &hpFill);

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
		r.w = 50;
		r.h = 70;
		float enemyW = 2.0f;
		float enemyH = 2.5f;

		//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		//SDL_RenderFillRect(renderer, &r);

		

		

		SDL_FRect er;
		er.w = e->width * pixelsPerUnitX;
		er.h = e->height * pixelsPerUnitY;

		er.x = sc.x - er.w * 0.5f;
		er.y = sc.y - er.h * 0.5f;

		//SDL_RenderTexture(renderer, e->texture, nullptr, &er);

		SDL_Texture* enemyFrame = e->texture; // fallback

		if (!enemyAnimFrames.empty())
		{
			auto it = enemyAnim.find(e);
			if (it != enemyAnim.end())
			{
				int idx = it->second.frame;
				if (idx >= 0 && idx < (int)enemyAnimFrames.size())
					enemyFrame = enemyAnimFrames[idx];
			}
		}

		SDL_RenderTexture(renderer, enemyFrame, nullptr, &er);

		Vec3 aabbMin(e->pos.x - enemyW / 2, e->pos.y - enemyH / 2, 0);
		Vec3 aabbMax(e->pos.x + enemyW / 2, e->pos.y + enemyH / 2, 0);

		
		Vec3 scMin = projectionMatrix * aabbMin;
		Vec3 scMax = projectionMatrix * aabbMax;

		SDL_FRect box;
		box.x = scMin.x;
		box.y = scMin.y;
		box.w = scMax.x - scMin.x;
		box.h = scMax.y - scMin.y;

		//SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // жёлтый хитбокс
		//DL_RenderRect(renderer, &box);

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

	
	

	//WAVE TEXT BOX 
	SDL_FRect waveBarBg = { 500, 50, 300, 12 };
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 200);
	SDL_RenderFillRect(renderer, &waveBarBg);

	
	float ratio = (waves->waveDelay - waves->timer) / waves->waveDelay;
	if (ratio < 0) ratio = 0;
	if (ratio > 1) ratio = 1;

	SDL_FRect waveBar = { 500, 50, 300 * ratio, 12 };
	SDL_SetRenderDrawColor(renderer, 100, 200, 255, 255);
	SDL_RenderFillRect(renderer, &waveBar);


	//GAME WON SCREEN
	if (waves->gameWon && winTexture)
	{
		int w, h;
		SDL_GetWindowSize(window, &w, &h);

		SDL_FRect winRect;
		winRect.w = 500;   // размер картинки WIN
		winRect.h = 220;
		winRect.x = (w - winRect.w) * 0.5f;
		winRect.y = (h - winRect.h) * 0.35f;

		SDL_RenderTexture(renderer, winTexture, nullptr, &winRect);
	}

	//GAME LOST SCREEN
	if (waves->gameLost)
	{
		int w, h;
		SDL_GetWindowSize(window, &w, &h);

		SDL_FRect winRect;
		winRect.w = 500;   // размер картинки WIN
		winRect.h = 220;
		winRect.x = (w - winRect.w) * 0.5f;
		winRect.y = (h - winRect.h) * 0.35f;

		SDL_RenderTexture(renderer, winTexture, nullptr, &winRect);
	}



	SDL_RenderPresent(renderer);
}
