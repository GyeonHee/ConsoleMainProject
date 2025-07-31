#pragma once

#include "Actor/Actor.h"
#include <chrono>

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)
public:
	Player();

	virtual void Tick(float deltaTime) override;

private:
	std::chrono::steady_clock::time_point lastKeyPressTime = std::chrono::steady_clock::now();
	const double cooldownSec = 0.2f;  // 1ÃÊ ÄðÅ¸ÀÓ
};