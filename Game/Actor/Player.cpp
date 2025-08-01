#include "Player.h"
#include "Input.h"
#include "Engine.h"
#include "Utils/Utils.h"
#include "Level/Level.h"
#include "Bomb.h"

Player::Player() : Actor("▼", Color::Green)
{
	// 시작 위치 (화면의 가운데, 가장 아래쪽)
	int xPosition = 0; // Engine::Get().Width() / 2 - width / 2;
    int yPosition = 0; // Engine::Get().Height() - 1;
	SetPosition(Vector2(xPosition, yPosition));
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	char buffer[20] = {};
	sprintf_s(buffer, 20, "pos: (%d, %d)", position.x, position.y);
	SetConsoleTitleA(buffer);

	// 입력 처리
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// 게임 종료
		QuitGame();
		return;
	}

	// 방향키 입력
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed = now - lastKeyPressTime;
	if (Input::Get().GetKey(VK_LEFT))
	{
        ChangeImage("◀");
		if (elapsed.count() >= moveCooldownSec) 
        {
			// 처리
			Vector2 position = Position();
			position.x -= 2;
			SetPosition(position);

			lastKeyPressTime = now;
		}
	}
	if (Input::Get().GetKey(VK_RIGHT))
	{
        ChangeImage("▶");
		if (elapsed.count() >= moveCooldownSec)
        {
			// 처리
			Vector2 position = Position();
			position.x += 2;
			SetPosition(position);

			lastKeyPressTime = now;
		}
	}
	if (Input::Get().GetKey(VK_UP))
	{
        ChangeImage("▲");
		if (elapsed.count() >= moveCooldownSec) 
        {
			// 처리
			Vector2 position = Position();
			position.y -= 1;
			SetPosition(position);

			lastKeyPressTime = now;
		}
	}
	if (Input::Get().GetKey(VK_DOWN))
	{
        ChangeImage("▼");
		if (elapsed.count() >= moveCooldownSec) 
        {
			// 처리
			Vector2 position = Position();
			position.y += 1;
			SetPosition(position);

			lastKeyPressTime = now;
		}
	}

    if (Input::Get().GetKey(VK_SPACE))
    {
        if (elapsed.count() >= putBombCooldownSec) 
        {
            Fire();

            lastKeyPressTime = now;
        }
    }
}

void Player::ChangeImage(const char* newImage)
{
    // 기존 메모리 해제
    delete[] image;

    // 새 이미지 복사
    width = (int)strlen(newImage);
    image = new char[width + 1];
    strcpy_s(image, width + 1, newImage);
}

void Player::Fire()
{
    // 플레이어 탄약 객체 생성.
    // x: 플레이어의 가운데.
    // y: 플레이어에 가운데
    Vector2 bombPos(position.x, position.y);
    owner->AddActor(new Bomb(bombPos));
}
