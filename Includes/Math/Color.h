#pragma once
// 색상
// RGB 순서가 아닌 이유
// FOREGROUND_BLUE로 define된 비트값이 1이기 때문 0x0001

enum class Color : int
{
    Black = 0,                         // 0000
    Blue = 1 << 0,                    // 0001
    Green = 1 << 1,                    // 0010
    Cyan = (1 << 0) | (1 << 1),      // 0011
    Red = 1 << 2,                    // 0100
    Magenta = (1 << 0) | (1 << 2),      // 0101
    Yellow = (1 << 1) | (1 << 2),      // 0110
    White = (1 << 0) | (1 << 1) | (1 << 2), // 0111
    Intensity = 1 << 3,                    // 1000

    BrightBlue = Intensity | Blue,          // 1001
    BrightGreen = Intensity | Green,         // 1010
    BrightCyan = Intensity | Cyan,          // 1011
    BrightRed = Intensity | Red,           // 1100
    BrightMagenta = Intensity | Magenta,       // 1101
    BrightYellow = Intensity | Yellow,        // 1110
    BrightWhite = Intensity | White          // 1111
};