#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#include "Entity.h"

class Platform : public Entity {
public:
    float width;
    float height;

    Platform(Vec3 pos, float w, float h);

    float Left()   const { return pos.x - width * 0.5f; }
    float Right()  const { return pos.x + width * 0.5f; }
    float Top()    const { return pos.y + height * 0.5f; }
    float Bottom() const { return pos.y - height * 0.5f; }
};

#endif