#include "Ground.h"

Ground::Ground(const Vector2& position) : Actor(L"��", Color::BrightWhite, position)
{
    // �׸� �� ����� ���� ���� ����.
    SetSortingOrder(0);
}
