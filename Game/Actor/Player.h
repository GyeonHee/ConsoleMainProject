#pragma once

#include "Actor/Actor.h"
#include <chrono>

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)
public:
    Player(const Vector2& position);

    virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

    void ChangeImage(const wchar_t* newimage);
    void Fire();
private:
	std::chrono::steady_clock::time_point lastKeyPressTime = std::chrono::steady_clock::now();
	const double moveCooldownSec = 0.2f;  // ÄðÅ¸ÀÓ
    const double putBombCooldownSec = 0.2f;

    class ICanPlayerMove* canPlayerMoveInterface = nullptr;

};