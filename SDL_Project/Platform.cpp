#include "Platform.h"

Platform::Platform(Vec3 p, float w, float h)
{
    pos = p;
    width = w;
    height = h;

    
    vel = Vec3(0, 0, 0);
    acc = Vec3(0, 0, 0);
    mass = 0.0f;

    
    radius = std::max(w, h) * 0.5f;
}
