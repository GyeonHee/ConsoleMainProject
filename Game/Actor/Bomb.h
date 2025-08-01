#pragma once

#include "Actor/Actor.h"
#include <chrono>

class Bomb : public Actor
{
    RTTI_DECLARATIONS(Bomb, Actor)
public:
    Bomb(const Vector2& position);
    ~Bomb();

    virtual void Tick(float deltaTime) override;

    //void ChangeImage(const char* newimage);
private:
    std::chrono::steady_clock::time_point lastKeyPressTime = std::chrono::steady_clock::now();
    const double bombCooldownSec = 1.5f;  // 2.5�� ��Ÿ��
};