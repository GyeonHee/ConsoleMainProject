#pragma once

#include "Math/Vector2.h"
#include <vector>
class IBombExplosion
{
public:
    // '+' ������� ���� Ÿ�ϵ��� ��ǥ�� ��ȯ
    virtual void Explode(const Vector2& center) = 0;
};