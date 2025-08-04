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

	// 엔진 이벤트 함수
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Render() override;

    static GameLevel& Get();
    void HandleBombExplosion(const Vector2& center);
    std::vector<Actor*> FindActorsAt(const Vector2& pos);
    bool IsInMapBounds(const Vector2& pos);
    void RemoveActor(Actor* actor);

    // 플레이어 인스턴스 가져오기
    //inline Player* GetPlayer() const { return player; } 
private:
	// 맵 파일을 읽어서 게임 객체 생성하는 함수
	void ReadMapFile(const char* fileName);
private:
    Player* player; // 또는 스마트 포인터인 std::unique_ptr<Player>

	int playerWidth = 0;

    // 싱글톤 변수
    static GameLevel* instance;
};