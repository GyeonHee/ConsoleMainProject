#pragma once

#include "Actor/Actor.h"

class Bush : public Actor
{
    RTTI_DECLARATIONS(Bush, Actor)
public:
    Bush(const Vector2& position);
};