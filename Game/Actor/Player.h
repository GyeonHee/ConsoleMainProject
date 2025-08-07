#pragma once

#include "Actor/Actor.h"
#include <chrono>

class Player : public Actor
{
public:
    struct KeyMap
    {
        int moveUp;
        int moveDown;
        int moveLeft;
        int moveRight;
        int putBomb;

        KeyMap(int up, int down, int left, int right, int putBombKey)
            : moveUp(up), moveDown(down), moveLeft(left), moveRight(right), putBomb(putBombKey) {
        }
    };

	RTTI_DECLARATIONS(Player, Actor)
public:
    Player(const Vector2& position, const KeyMap& keys, Color color);

    virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

    void ChangeImage(const wchar_t* newimage);
    void Fire();
    
    void PlayerHitBomb();
    bool ShouldBeRemoved() const;

private:
	std::chrono::steady_clock::time_point lastKeyPressTime = std::chrono::steady_clock::now();
	const double moveCooldownSec = 0.2f;  // ÄðÅ¸ÀÓ
    const double putBombCooldownSec = 0.2f;

    bool isHit = false;
    float timeSinceHit = 0.0f;
    
    class ICanPlayerMove* canPlayerMoveInterface = nullptr;

    KeyMap keyMap;
};