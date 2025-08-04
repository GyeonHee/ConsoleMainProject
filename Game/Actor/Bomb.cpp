#include "Bomb.h"
#include "Interface/IBombExplosion.h"
Bomb::Bomb(const Vector2& position) : Actor(L"ɵ", Color::BrightCyan, position)
{
    // ɵÖöÓó
    SetSortingOrder(1);
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
        Explode();
        Destroy();
    }
}

void Bomb::Explode()
{
    if (bombExplosionInterface)
        bombExplosionInterface->Explode(Position());
}

void Bomb::SetBombExplosionInterface(IBombExplosion* explosionInterface)
{
    bombExplosionInterface = explosionInterface;
}
