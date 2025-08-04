#include "Bush.h"

Bush::Bush(const Vector2& position) : Actor(L"бс", Color::BrightGreen, position)
{
    SetSortingOrder(4);
}
