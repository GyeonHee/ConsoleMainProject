#include "Ground.h"

Ground::Ground(const Vector2& position) : Actor(L"��", Color::White, Color::White, position)
{
    // �׸� �� ����� ���� ���� ����.
    SetSortingOrder(0);
}
