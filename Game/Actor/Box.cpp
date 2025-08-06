#include "Box.h"

Box::Box(const Vector2& position) : Actor(L"⏹", Color::BrightYellow, Color::Yellow, position)
{
    SetSortingOrder(2);
}
