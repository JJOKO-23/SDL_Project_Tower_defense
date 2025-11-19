#include "Animation.h"

Animation::Animation() :
    fps(10.0f),
    currentTime(0.0f),
    currentFrame(0)
{
}

Animation::~Animation() {}

void Animation::AddFrame(SDL_Texture* texture) {
    frames.push_back(texture);
}

void Animation::SetFPS(float fps_) {
    fps = fps_;
}

void Animation::Update(float deltaTime) {
    if (frames.empty()) return;

    currentTime += deltaTime;

    float frameDuration = 1.0f / fps;

    while (currentTime >= frameDuration) {
        currentTime -= frameDuration;
        currentFrame = (currentFrame + 1) % frames.size();
    }
}

SDL_Texture* Animation::GetCurrentFrame() const {
    if (frames.empty()) return nullptr;
    return frames[currentFrame];
}
