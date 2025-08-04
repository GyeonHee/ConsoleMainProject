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
	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

    void DestroyActorsAt(const Vector2& position);
    bool IsInMapBounds(const Vector2& pos) const;
    Actor* FindActorAt(const Vector2& pos) const;
private:
	// �� ������ �о ���� ��ü �����ϴ� �Լ�
	void ReadMapFile(const char* fileName);
private:
	int playerWidth = 0;

};