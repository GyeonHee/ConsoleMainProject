#pragma once

#include "Actor/Actor.h"

class Block : public Actor
{
    RTTI_DECLARATIONS(Block, Actor)
public:
    Block(const Vector2& position);
};