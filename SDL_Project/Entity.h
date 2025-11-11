#ifndef ENTITY_H
#define ENTITY_H

#include <Vector.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
using namespace MATH;

class Entity {
private:
	// Keep these private as we should only build them in the setImage method
	// I do listen to Scott sometimes...
	SDL_Surface* surface; // Used to get the width and height of the image
	SDL_Texture* texture; // Used to render the image

public:
	float angleDeg;
	Vec3 pos;
	Vec3 vel;
	Vec3 acc;
	float mass;
	// Let's pretend all entities are circles
	float radius;

	Entity();
	~Entity();
	void SetImage(const char* filename, SDL_Renderer* renderer);

	// Just like assignment 1!
	void ApplyForce(Vec3 netForce);
	virtual void Update(float deltaTime);

	// Need getters for private member variables. 
	SDL_Surface* GetSurface() const { return surface; }
	SDL_Texture* GetTexture() const { return texture; }
};

#endif