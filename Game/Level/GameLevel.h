#pragma once

#include "Level/Level.h"

class GameLevel : public Level
{
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

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