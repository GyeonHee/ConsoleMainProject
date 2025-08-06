#include "Bush.h"

Bush::Bush(const Vector2& position) : Actor(L"♒", Color::BrightGreen, Color::Green, position)
{
    SetSortingOrder(4);
}
