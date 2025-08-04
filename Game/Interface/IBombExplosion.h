#pragma once

#include "Math/Vector2.h"
#include <vector>
class IBombExplosion
{
public:
    // '+' 모양으로 터질 타일들의 좌표값 반환
    virtual void Explode(const Vector2& center) = 0;
};