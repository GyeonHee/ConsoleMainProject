#include "Bush.h"

Bush::Bush(const Vector2& position) : Actor(L"��", Color::Green, Color::BrightGreen, position)
{
    SetSortingOrder(4);
}
