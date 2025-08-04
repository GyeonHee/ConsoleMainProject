#include "Box.h"

Box::Box(const Vector2& position) : Actor(L"■", Color::BrightYellow, position)
{
    SetSortingOrder(2);
}
