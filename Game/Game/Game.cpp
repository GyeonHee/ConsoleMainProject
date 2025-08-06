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
    // 화면 정리.
    // clear screen 명령어 실행.
    system("cls");

    // 토글 처리.
    showMenu = !showMenu;

    if (showMenu)
    {
        // 게임 레벨을 뒤로 밀기.
        backLevel = mainLevel;

        // 메뉴 레벨을 메인 레벨로 설정.
        mainLevel = menuLevel;
    }
    else
    {
        // 게임 레벨을 메인 레벨로 설정.
        mainLevel = backLevel;
    }
}

void Game::CleanUp()
{
    // 이때는 Engine의 mainLevel이 menuLevel.
    if (showMenu)
    {
        // 게임 레벨 제거.
        SafeDelete(backLevel);
        SafeDelete(mainLevel);
        mainLevel = nullptr;
    }
    //// mainLevel이 게임 레벨 -> 이때는 Engine에서 하던데로 정리하면 됨.
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