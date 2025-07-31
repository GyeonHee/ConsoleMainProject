#include "Player.h"
#include "Input.h"
#include "Engine.h"
#include "Utils/Utils.h"
#include "Level/Level.h"

Player::Player() : Actor("＠", Color::Green)
{
	// 시작 위치 (화면의 가운데, 가장 아래쪽)
	int xPosition = Engine::Get().Width() / 2 - width / 2;
	int yPosition = Engine::Get().Height() - 1;
	SetPosition(Vector2(xPosition, yPosition));
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

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
		//auto now = std::chrono::steady_clock::now();
		//std::chrono::duration<double> elapsed = now - lastKeyPressTime;

		if (elapsed.count() >= cooldownSec) {
			// 처리
			Vector2 position = Position();
			position.x -= 2;
			SetPosition(position);

			lastKeyPressTime = now;
		}
	}
	if (Input::Get().GetKey(VK_RIGHT))
	{
		//auto now = std::chrono::steady_clock::now();
		//std::chrono::duration<double> elapsed = now - lastKeyPressTime;

		if (elapsed.count() >= cooldownSec) {
			// 처리
			Vector2 position = Position();
			position.x += 2;
			SetPosition(position);

			lastKeyPressTime = now;
		}
	}
	if (Input::Get().GetKey(VK_UP))
	{
		//auto now = std::chrono::steady_clock::now();
		//std::chrono::duration<double> elapsed = now - lastKeyPressTime;

		if (elapsed.count() >= cooldownSec) {
			// 처리
			Vector2 position = Position();
			position.y -= 1;
			SetPosition(position);

			lastKeyPressTime = now;
		}
	}
	if (Input::Get().GetKey(VK_DOWN))
	{
		//auto now = std::chrono::steady_clock::now();
		//std::chrono::duration<double> elapsed = now - lastKeyPressTime;

		if (elapsed.count() >= cooldownSec) {
			// 처리
			Vector2 position = Position();
			position.y += 1;
			SetPosition(position);

			lastKeyPressTime = now;
		}
	}
}
