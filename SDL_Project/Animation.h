#pragma once
#pragma once
#include <SDL3/SDL.h>
#include <vector>

class Animation {
public:
    Animation();
    ~Animation();

    void AddFrame(SDL_Texture* texture);
    void SetFPS(float fps);
    void Update(float deltaTime);
    SDL_Texture* GetCurrentFrame() const;

private:
    std::vector<SDL_Texture*> frames;
    float fps;
    float currentTime;
    int currentFrame;
};