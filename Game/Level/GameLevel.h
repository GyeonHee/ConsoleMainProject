#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"
#include <set>

class GameLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

    // Interface
    virtual bool CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition) override;
    virtual void TryPlayerMove(const Vector2& playerPosition, const Vector2& newPosition) override;

	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

    static GameLevel& Get();
    void HandleBombExplosion(const Vector2& center);
    void InternalHandleBombExplosion(const Vector2& center, std::set<Vector2>& visited);
    bool HandleExplosionAt(const Vector2& target, std::set<Vector2>& visited);
    std::vector<Actor*> FindActorsAt(const Vector2& pos);
    bool IsInMapBounds(const Vector2& pos);

private:
	// �� ������ �о ���� ��ü �����ϴ� �Լ�
	void ReadMapFile(const char* fileName);
private:
	int playerWidth = 0;

    // �̱��� ����
    static GameLevel* instance;


private:
    void SetExplosionEffect(const std::set<Vector2>& tiles);
    void ClearExplosionEffect();

    std::set<Vector2> explosionTiles;
    float explosionTimer = 0.0f;
    bool isExplosionVisible = false;
};