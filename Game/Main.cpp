#include <iostream>
#include <Windows.h>
#include "Game/Game.h"

#define MAP_WIDTH 15
#define MAP_HEIGHT 15

void SetConsoleEnvironment()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 폰트 설정 (정사각형 느낌 비율)
    CONSOLE_FONT_INFOEX fontInfo = { 0 };
    fontInfo.cbSize = sizeof(fontInfo);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 12 * 2;   // 문자 너비
    fontInfo.dwFontSize.Y = 24 * 2;   // 문자 높이
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy_s(fontInfo.FaceName, L"Consolas");

    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

    // 화면 버퍼 크기
    COORD bufferSize = { MAP_WIDTH, MAP_HEIGHT };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // 창 크기
    SMALL_RECT windowSize = { 0, 0, (MAP_WIDTH * 2) - 1, MAP_HEIGHT - 1};
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}


int main()
{
    SetConsoleEnvironment();

    Game game;
    game.Run();

    return 0;
}
