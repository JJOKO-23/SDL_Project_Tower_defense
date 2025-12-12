#include "Entity.h"

Entity::Entity(): // this is an initializer list
	surface(nullptr) 
	, texture(nullptr) 
    , angleDeg(0.0f) 
	, mass(1.0f)
	, radius(1.0f)
{
}

Entity::~Entity() {
	// This is the destructor for Entity (notice the little squiggle ~)
	// Clean up the surface and texture data
	//SDL_DestroySurface(surface);
	//SDL_DestroyTexture(texture);
	surface = nullptr;
	texture = nullptr;
}

void Entity::SetImage(const char* filename, SDL_Renderer* renderer) {
	// We will use the surface to grab the width and height of the image later on
	surface = IMG_Load(filename);
	if (surface == nullptr) {
		std::cerr << "Did you spell the file right?" << std::endl;
	}
	// We will use the texture to render to screen later on
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}

//ИСЛЛАААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААААМ
// вот это анимация  не трогай пжшка // ok 
void Entity::AddAnimationFrame(const char* filename, SDL_Renderer* renderer) {
	SDL_Surface* surf = IMG_Load(filename);
	if (!surf) {
		std::cerr << "Failed to load frame: " << filename << "\n";
		return;
	}
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
	animation.AddFrame(tex);

	if (!surface) surface = surf;
}

void Entity::ApplyForce(Vec3 netForce)
{
	// Code this up like assignment 1
	// But remember, we need x and y motion
	acc = netForce / mass;
}

void Entity::Update(float deltaTime)
{
	// Code this up like assignment 1
	// But remember, we need x and y motion
	vel +=  acc * deltaTime;
	pos += vel * deltaTime + 0.5f * acc * (deltaTime * deltaTime);
}
