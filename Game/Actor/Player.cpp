#include "Player.h"
#include "Input.h"
#include "Engine.h"
#include "Utils/Utils.h"
#include "Level/Level.h"
#include "Bomb.h"

#include "Interface/ICanPlayerMove.h"

Player::Player(const Vector2& position) : Actor(L"↓", Color::Green, position)
{
    SetSortingOrder(3);
}

void Player::BeginPlay()
{
    super::BeginPlay();


    // 인터페이스 얻어오기
    if (GetOwner())
    {
        canPlayerMoveInterface = dynamic_cast<ICanPlayerMove*>(GetOwner());

        if (!canPlayerMoveInterface)
        {
            __debugbreak();
        }
    }
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

    // playerhitbomb
    if (isHit)
    {
        timeSinceHit += deltaTime;
        return;
    }

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
        // 이동 전에 이동 가능한지 확인
        if (canPlayerMoveInterface->CanPlayerMove(Position(), Vector2(Position().x - 1, Position().y)))
        {
            ChangeImage(L"←");
            //ChangeImage(L"o");
            if (elapsed.count() >= moveCooldownSec)
            {
                // 처리
                Vector2 position = Position();
                position.x -= 1;
                canPlayerMoveInterface->TryPlayerMove(Position(), position);
                SetPosition(position);

                lastKeyPressTime = now;
            }
        }
	}
	if (Input::Get().GetKey(VK_RIGHT))
	{
        if (canPlayerMoveInterface->CanPlayerMove(Position(), Vector2(Position().x + 1, Position().y)))
        {
            ChangeImage(L"→");
            //ChangeImage(L"o");
            if (elapsed.count() >= moveCooldownSec)
            {
                // 처리
                Vector2 position = Position();
                position.x += 1;
                canPlayerMoveInterface->TryPlayerMove(Position(),position);
                SetPosition(position);

                lastKeyPressTime = now;
            }
        }
	}
	if (Input::Get().GetKey(VK_UP))
	{
        if (canPlayerMoveInterface->CanPlayerMove(Position(), Vector2(Position().x, Position().y - 1)))
        {
            ChangeImage(L"↑");
            //ChangeImage(L"o");
            if (elapsed.count() >= moveCooldownSec)
            {
                // 처리
                Vector2 position = Position();
                position.y -= 1;
                canPlayerMoveInterface->TryPlayerMove(Position(), position);
                SetPosition(position);

                lastKeyPressTime = now;
            }
        }
	}
	if (Input::Get().GetKey(VK_DOWN))
	{
        if (canPlayerMoveInterface->CanPlayerMove(Position(), Vector2(Position().x, Position().y + 1)))
        {
            ChangeImage(L"↓");
            //ChangeImage(L"o");
            if (elapsed.count() >= moveCooldownSec)
            {
                // 처리
                Vector2 position = Position();
                position.y += 1;
                canPlayerMoveInterface->TryPlayerMove(Position(), position);
                SetPosition(position);

                lastKeyPressTime = now;
            }
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

bool Player::ShouldBeRemoved() const
{
    return isHit && timeSinceHit >= 5.0f;
}

void Player::ChangeImage(const wchar_t* newImage)
{
    // 기존 메모리 해제
    delete[] image;

    // 새 이미지 복사
    /*width = (int)strlen(newImage);
    image = new char[width + 1];
    strcpy_s(image, width + 1, newImage);*/

    width = (int)wcslen(newImage);
    image = new wchar_t[width + 1];
    wcscpy_s(image, width + 1, newImage);
}

void Player::Fire()
{
    // 플레이어 탄약 객체 생성.
    // x: 플레이어의 가운데.
    // y: 플레이어에 가운데
     Vector2 bombPos(position.x, position.y);
    owner->AddActor(new Bomb(bombPos)); 
}

void Player::PlayerHitBomb()
{
    if (isHit) return;

    isHit = true;
    timeSinceHit = 0.0f;
    Actor::SetColor(Color::Blue); // 피격 시 색상
}