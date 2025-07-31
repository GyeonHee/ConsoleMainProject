#include <iostream>
#include <Windows.h>
#include "Game/Game.h"

#define MAP_WIDTH 15
#define MAP_HEIGHT 15

void SetConsoleEnvironment()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // ��Ʈ ���� (���簢�� ���� ����)
    CONSOLE_FONT_INFOEX fontInfo = { 0 };
    fontInfo.cbSize = sizeof(fontInfo);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 12 * 2;   // ���� �ʺ�
    fontInfo.dwFontSize.Y = 24 * 2;   // ���� ����
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy_s(fontInfo.FaceName, L"Consolas");

    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

    // ȭ�� ���� ũ��
    COORD bufferSize = { MAP_WIDTH, MAP_HEIGHT };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // â ũ��
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
