#include "Wall.h"

Wall::Wall(const Vector2& position) : Actor(L"x", Color::Red, position)
{
    // �׸� �� ����� ���� ���� ����.
    SetSortingOrder(0);
}
