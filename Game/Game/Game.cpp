#include "Game.h"
#include "Level/GameLevel.h"
#include "Level/MenuLevel.h"

//#include <Windows.h>
Game* Game::instance = nullptr;
Game::Game()
{
    instance = this;

	// ���� �߰�
	AddLevel(new GameLevel());
    //�޴� ���� ����
    //menuLevel = new MenuLevel();
    
}

Game::~Game()
{
    CleanUp();
}

void Game::ToggleMenu()
{
    system("cls");

    showMenu = !showMenu;

    if (showMenu)
    {
        // ���� ������ �ڷ� �б�
        backLevel = mainLevel;

        // ���� ������ ���� ������ ����
        mainLevel = menuLevel;
    }
    else
    {
        // ���� ������ ���� ������ ����
    }
}

void Game::CleanUp()
{
    // �̶��� Engine�� mainLevel�� menuLevel.
    if (showMenu)
    {
        // ���� ���� ����.
        SafeDelete(backLevel);
        mainLevel = nullptr;
    }


    SafeDelete(menuLevel);
    Engine::CleanUp();
}

Game& Game::Get()
{
    return *instance;
}