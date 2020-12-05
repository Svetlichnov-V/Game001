#pragma once
#include "Vector2f.h"

Vector2f operator * (float f, Vector2f v)
{
    return Vector2f(f * v.x, f * v.y);
}

std::ostream& operator << (std::ostream& streamP, const Vector2f vector)
{
    streamP << vector.x << ' ' << vector.y;
    return streamP;
}