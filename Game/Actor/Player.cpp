#include "Player.h"
#include "Input.h"
#include "Engine.h"
#include "Utils/Utils.h"
#include "Level/Level.h"
#include "Bomb.h"
#include "Game/Game.h"

#include "Interface/ICanPlayerMove.h"


Player::Player(const Vector2& position, const KeyMap& keys, Color color) : Actor(L"↓", Color::White, color,  position) ,keyMap(keys)
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
  

    // 피격시 isHit True가 되며 deltaTime이 흘러감
    if (isHit)
    {
        timeSinceHit += deltaTime;

        if (ShouldBeRemoved())
        {
            //Destroy();
            // 여기서 게임 종료 이벤트 처리
            //static_cast<Game&>(Engine::Get()).ReStart();
            Engine::Get().Quit();
        }

        //isHit = false;
        return;
    }

	char buffer[20] = {};
	sprintf_s(buffer, 20, "pos: (%d, %d)", position.x, position.y);
	SetConsoleTitleA(buffer);

	// 방향키 입력
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed = now - lastKeyPressTime;
	//if (Input::Get().GetKey(VK_LEFT))
    if(GetAsyncKeyState(keyMap.moveLeft) & 0x8000)
	{
        // 이동 전에 이동 가능한지 확인
        if (canPlayerMoveInterface->CanPlayerMove(Position(), Vector2(Position().x - 1, Position().y)))
        {
            ChangeImage(L"←");
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
	//if (Input::Get().GetKey(VK_RIGHT))
    if(GetAsyncKeyState(keyMap.moveRight) & 0x8000)
	{
        if (canPlayerMoveInterface->CanPlayerMove(Position(), Vector2(Position().x + 1, Position().y)))
        {
            ChangeImage(L"→");
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
	//if (Input::Get().GetKey(VK_UP))
    if(GetAsyncKeyState(keyMap.moveUp) & 0x8000)
	{
        if (canPlayerMoveInterface->CanPlayerMove(Position(), Vector2(Position().x, Position().y - 1)))
        {
            ChangeImage(L"↑");
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
	//if (Input::Get().GetKey(VK_DOWN))
    if(GetAsyncKeyState(keyMap.moveDown) & 0x8000)
	{
        if (canPlayerMoveInterface->CanPlayerMove(Position(), Vector2(Position().x, Position().y + 1)))
        {
            ChangeImage(L"↓");
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

    if (GetAsyncKeyState(keyMap.putBomb) & 0x8000)
    {
        if (elapsed.count() >= putBombCooldownSec)
        {
            Fire();

            lastKeyPressTime = now;
        }
    }
}

// 폭탄에 피격 했을시 5초가 지나면 Destroy
bool Player::ShouldBeRemoved() const
{
    return isHit && timeSinceHit >= 2.0f;
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