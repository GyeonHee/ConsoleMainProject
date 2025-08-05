#include "Bomb.h"
#include "Level/GameLevel.h"

Bomb::Bomb(const Vector2& position) : Actor(L"O", Color::White, Color::Blue, position)
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
    }
}

void Bomb::Explode()
{
    // GameLevel이 싱글턴이라면 예: GameLevel::Instance()->HandleBombExplosion(...)
    GameLevel* level = &GameLevel::Get();  // 정적 접근자 또는 외부 주입 방식
    if (level != nullptr)
    {
        level->HandleBombExplosion(Position());
        //owner->DestroyActor(this); //HandleBombExplosion(Position())여기서 삭제함 여기서 하면 역참조 에러남
    }
}
