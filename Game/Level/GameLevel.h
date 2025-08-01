#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class GameLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

    virtual bool CanPlayerMove(
        const Vector2& playerPosition,
        const Vector2& newPosition) override;

	// 엔진 이벤트 함수
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;
private:
	// 맵 파일을 읽어서 게임 객체 생성하는 함수
	void ReadMapFile(const char* fileName);
private:
	int playerWidth = 0;
};