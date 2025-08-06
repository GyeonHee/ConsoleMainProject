#include "Game.h"
#include "Level/GameLevel.h"
#include "Level/MenuLevel.h"

//Game* Game::instance = nullptr;

Game::Game()
{
    menuLevel = new MenuLevel();
    backLevel = new GameLevel();
    AddLevel(menuLevel); 
}

Game::~Game()
{
    CleanUp();
}

void Game::ToggleMenu()
{
    // ȭ�� ����.
    // clear screen ��ɾ� ����.
    system("cls");

    // ��� ó��.
    showMenu = !showMenu;

    if (showMenu)
    {
        // ���� ������ �ڷ� �б�.
        backLevel = mainLevel;

        // �޴� ������ ���� ������ ����.
        mainLevel = menuLevel;
    }
    else
    {
        // ���� ������ ���� ������ ����.
        mainLevel = backLevel;
    }
}

void Game::CleanUp()
{
    // �̶��� Engine�� mainLevel�� menuLevel.
    if (showMenu)
    {
        // ���� ���� ����.
        SafeDelete(backLevel);
        SafeDelete(mainLevel);
        mainLevel = nullptr;
    }
    //// mainLevel�� ���� ���� -> �̶��� Engine���� �ϴ����� �����ϸ� ��.
    else
    {
        mainLevel = nullptr;
        SafeDelete(backLevel);
        SafeDelete(menuLevel);
        menuLevel = nullptr;
    }

    //SafeDelete(menuLevel);
    Engine::CleanUp();
}

//Game& Game::Get()
//{
//    return *instance;
//}