#include "Bomb.h"

Bomb::Bomb(const Vector2& position) : Actor(L"o", Color::Red, position)
{
}

Bomb::~Bomb()
{

}

void Bomb::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = now - lastKeyPressTime;

    if (elapsed.count() >= bombCooldownSec)
    {
        Destroy();
    }
}