#include "Ground.h"

Ground::Ground(const Vector2& position) : Actor(L"o", Color::White, position)
{
    // �׸� �� ����� ���� ���� ����.
    SetSortingOrder(0);
}
