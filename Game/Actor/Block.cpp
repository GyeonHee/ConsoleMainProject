#include "Block.h"

Block::Block(const Vector2& position) : Actor(L"��", Color::BrightRed, position)
{
    // �׸� �� ����� ���� ���� ����.
    SetSortingOrder(1);
}
