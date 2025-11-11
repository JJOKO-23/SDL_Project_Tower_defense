#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() const = 0;
	virtual void HandleEvents(const SDL_Event &event) = 0;
};

#endif
