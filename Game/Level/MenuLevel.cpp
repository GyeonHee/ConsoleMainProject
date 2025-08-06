#include "MenuLevel.h"
#include "Game/Game.h"
#include "Utils/Utils.h"
#include "Input.h"

MenuLevel::MenuLevel()
{
    // �޴� ������ �߰�.
    items.emplace_back(new MenuItem(
        L"Resume Game",
        []() { static_cast<Game&>(Engine::Get()).ToggleMenu(); }
    ));

    items.emplace_back(new MenuItem(
        L"Quit Game",
        []() { Engine::Get().Quit(); }
    ));

    // ������ �� �̸� ����.
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

    // �Է� ó��.
    if (Input::Get().GetKeyDown(VK_UP))
    {
        currentIndex = (currentIndex - 1 + length) % length;
    }

    if (Input::Get().GetKeyDown(VK_DOWN))
    {
        currentIndex = (currentIndex + 1) % length;
    }

    // Enter Ű �Է�.
    if (Input::Get().GetKeyDown(VK_RETURN))
    {
        // �޴� �������� �����ϰ� �ִ� �Լ� ȣ��.
        items[currentIndex]->onSelected();
    }

    if (Input::Get().GetKeyDown(VK_ESCAPE))
    {
        // Game�� ��� �޴� ��� �߰��� ȣ���ؾ� ��.
        Engine::Get().Quit();

        // �޴� �ε��� �ʱ�ȭ.
        currentIndex = 0;
    }
}

void MenuLevel::Render()
{
    super::Render();

    Engine::Get().WriteToBuffer(Vector2(2, 3), L"Crazy Arcade", Color::Cyan, Color::Blue);
    // �޴� ������ ������.
    for (int ix = 0; ix < length; ++ix)
    {
        // ������ ���� Ȯ��.
        Color textColor =
            (ix == currentIndex) ? selectedColor : unSelectedColor;

        // ���� ����.
        Utils::SetConsoleTextColor(static_cast<WORD>(textColor));

        // �޴� �ؽ�Ʈ ���.
        Engine::Get().WriteToBuffer(Vector2(2, ix + 5), items[ix]->menuText, Color::Black, textColor);
    }
}