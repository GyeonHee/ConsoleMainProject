#include "Game.h"
#include "Level/GameLevel.h"
#include "Level/MenuLevel.h"

//#include <Windows.h>
Game* Game::instance = nullptr;
Game::Game()
{
    instance = this;

	// 레벨 추가
	AddLevel(new GameLevel());
    //메뉴 레벨 생성
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
        // 게임 레벨을 뒤로 밀기
        backLevel = mainLevel;

        // 게임 레벨을 메인 레벨로 설정
        mainLevel = menuLevel;
    }
    else
    {
        // 게임 레벨을 메인 레벨로 설정
    }
}

void Game::CleanUp()
{
    // 이때는 Engine의 mainLevel이 menuLevel.
    if (showMenu)
    {
        // 게임 레벨 제거.
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