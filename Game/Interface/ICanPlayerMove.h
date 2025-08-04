#pragma once

#include "Math/Vector2.h"

class ICanPlayerMove
{
public:
    virtual bool CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition) = 0;

    virtual void TryPlayerMove(const Vector2& playerPosition, const Vector2& newPosition) = 0;
};