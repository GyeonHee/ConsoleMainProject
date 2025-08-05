#include "MenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"

#include <iostream>


MenuLevel::MenuLevel()
{
    items.emplace_back(new MenuItem(L"1P Play", []() {Game::Get().ToggleMenu(); }));
    items.emplace_back(new MenuItem(L"2P Play", []() {Game::Get().ToggleMenu(); }));
    items.emplace_back(new MenuItem(L"Select Map", []() {Game::Get().ToggleMenu(); }));
                                    
    items.emplace_back(new MenuItem(L"Quit Game", []() {Game::Get().Quit(); }));

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

    // 입력처리
    if (Input::Get().GetKeyDown(VK_UP))
    {
        currentIdx = (currentIdx - 1 + length) % length;
    }

    if (Input::Get().GetKeyDown(VK_DOWN))
    {
        currentIdx = (currentIdx + 1) % length;
    }

    // 엔터키 또는 스페이스바 입력
    if (Input::Get().GetKeyDown(VK_RETURN))
    {
        // 메뉴 아이템이 저장하고 있는 함수 호출
        items[currentIdx]->onSelected();
    }

    if (Input::Get().GetKeyDown(VK_ESCAPE))
    {
        // Game에 토글 메뉴 기능 추가 후 호출해야 함
        Game::Get().ToggleMenu();

        // 메뉴 인덱스 초기화
        currentIdx = 0;
    }
}

void MenuLevel::Render()
{   
    Engine::Get().WriteToBuffer(Vector2(2, 3), L"Crazy Arcade", Color::Cyan, Color::Blue);
    // 메뉴 아이템 렌더링.
    for (int ix = 0; ix < length; ++ix)
    {
        // 아이템 색상 확인.
        Color textColor =
            (ix == currentIdx) ? selectedColor : unSelectedColor;

        // 색상 설정.
        Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

        // 메뉴 텍스트 출력.
        Engine::Get().WriteToBuffer(Vector2(2, ix + 5), items[ix]->menuText, Color::Black, textColor);
    }
   
    super::Render();  
}
