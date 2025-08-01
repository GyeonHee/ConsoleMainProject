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

	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;
private:
	// �� ������ �о ���� ��ü �����ϴ� �Լ�
	void ReadMapFile(const char* fileName);
private:
	int playerWidth = 0;
};