#include "MenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"
#include "Actor/Player.h"

MenuLevel::MenuLevel()
{
    // 메뉴 아이템 추가.
    items.emplace_back(new MenuItem(
        L"⏯️Resume Game",
        []() { static_cast<Game&>(Engine::Get()).ToggleMenu(); }
    ));

    items.emplace_back(new MenuItem(
        L"❎ Quit Game",
        []() { Engine::Get().Quit(); }
    ));

    // 아이템 수 미리 저장.
    length = static_cast<int>(items.size());
}

MenuLevel::~MenuLevel()
{
    for (MenuItem* item : items)
    {
        SafeDelete(item);
    }

    items.clear();
}

void MenuLevel::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    // 입력 처리.
    if (Input::Get().GetKeyDown(VK_UP))
    {
        currentIndex = (currentIndex - 1 + length) % length;
    }

    if (Input::Get().GetKeyDown(VK_DOWN))
    {
        currentIndex = (currentIndex + 1) % length;
    }

    // Enter 키 입력.
    if (Input::Get().GetKeyDown(VK_RETURN))
    {
        // 메뉴 아이템이 저장하고 있는 함수 호출.
        items[currentIndex]->onSelected();
    }

    if (Input::Get().GetKeyDown(VK_ESCAPE))
    {
        // Game에 토글 메뉴 기능 추가후 호출해야 함.
        Engine::Get().Quit();

        // 메뉴 인덱스 초기화.
        currentIndex = 0;
    }
}

void MenuLevel::Render()
{
    super::Render();
    // 제목 출력
    Engine::Get().WriteToBuffer(Vector2(1, 2), L"✨ 🎊    🎉✨", Color::Black, Color::Yellow);
    Engine::Get().WriteToBuffer(Vector2(1, 3), L"Crazy", Color::Black, Color::Red);
    Engine::Get().WriteToBuffer(Vector2(6, 3), L"Arcade", Color::Black, Color::Blue);
    Engine::Get().WriteToBuffer(Vector2(1, 4), L"💣", Color::Black, Color::Blue);
    Engine::Get().WriteToBuffer(Vector2(3, 4), L"🛼", Color::Black, Color::Red);
    Engine::Get().WriteToBuffer(Vector2(5, 4), L"🥽", Color::Black, Color::BrightCyan);
    Engine::Get().WriteToBuffer(Vector2(7, 4), L"💥", Color::Black, Color::BrightRed);
    Engine::Get().WriteToBuffer(Vector2(9, 4), L"💦", Color::Black, Color::Cyan);
    Engine::Get().WriteToBuffer(Vector2(11, 4), L"🕶️", Color::Black, Color::White);

    // 메뉴 아이템 렌더링.
    for (int ix = 0; ix < length; ++ix)
    {
        // 아이템 색상 확인.
        Color textColor =
            (ix == currentIndex) ? selectedColor : unSelectedColor;

        // 색상 설정.
        Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

        // 메뉴 텍스트 출력.
        Engine::Get().WriteToBuffer(Vector2(1, ix + 8), items[ix]->menuText, Color::Black, textColor);
    }
}