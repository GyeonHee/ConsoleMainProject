#include "Wall.h"

Wall::Wall(const Vector2& position) : Actor(L"x", Color::Red, position)
{
    // 그릴 때 사용할 정렬 순서 설정.
    SetSortingOrder(0);
}
