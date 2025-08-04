#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"
#include "Interface/IBombExplosion.h"

class GameLevel : public Level, public ICanPlayerMove, public IBombExplosion
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

    // Interface
    virtual bool CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition) override;
    virtual void TryPlayerMove(const Vector2& playerPosition, const Vector2& newPosition) override;

    virtual void Explode(const Vector2& center) override;
	// 엔진 이벤트 함수
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

    void DestroyActorsAt(const Vector2& position);
    bool IsInMapBounds(const Vector2& pos) const;
    Actor* FindActorAt(const Vector2& pos) const;
private:
	// 맵 파일을 읽어서 게임 객체 생성하는 함수
	void ReadMapFile(const char* fileName);
private:
	int playerWidth = 0;

};