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

    // �Է�ó��
    if (Input::Get().GetKeyDown(VK_UP))
    {
        currentIdx = (currentIdx - 1 + length) % length;
    }

    if (Input::Get().GetKeyDown(VK_DOWN))
    {
        currentIdx = (currentIdx + 1) % length;
    }

    // ����Ű �Ǵ� �����̽��� �Է�
    if (Input::Get().GetKeyDown(VK_RETURN))
    {
        // �޴� �������� �����ϰ� �ִ� �Լ� ȣ��
        items[currentIdx]->onSelected();
    }

    if (Input::Get().GetKeyDown(VK_ESCAPE))
    {
        // Game�� ��� �޴� ��� �߰� �� ȣ���ؾ� ��
        Game::Get().ToggleMenu();

        // �޴� �ε��� �ʱ�ȭ
        currentIdx = 0;
    }
}

void MenuLevel::Render()
{   
    Engine::Get().WriteToBuffer(Vector2(2, 3), L"Crazy Arcade", Color::Cyan, Color::Blue);
    // �޴� ������ ������.
    for (int ix = 0; ix < length; ++ix)
    {
        // ������ ���� Ȯ��.
        Color textColor =
            (ix == currentIdx) ? selectedColor : unSelectedColor;

        // ���� ����.
        Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

        // �޴� �ؽ�Ʈ ���.
        Engine::Get().WriteToBuffer(Vector2(2, ix + 5), items[ix]->menuText, Color::Black, textColor);
    }
   
    super::Render();  
}
