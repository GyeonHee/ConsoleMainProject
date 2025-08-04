#pragma once

#include "Level/Level.h"
#include "Interface/ICanPlayerMove.h"

class Player;
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
    std::vector<Actor*> FindActorsAt(const Vector2& pos);
    bool IsInMapBounds(const Vector2& pos);
    void RemoveActor(Actor* actor);

    // �÷��̾� �ν��Ͻ� ��������
    //inline Player* GetPlayer() const { return player; } 
private:
	// �� ������ �о ���� ��ü �����ϴ� �Լ�
	void ReadMapFile(const char* fileName);
private:
    Player* player; // �Ǵ� ����Ʈ �������� std::unique_ptr<Player>

	int playerWidth = 0;

    // �̱��� ����
    static GameLevel* instance;
};