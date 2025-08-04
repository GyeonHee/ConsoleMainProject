#include "Block.h"

Block::Block(const Vector2& position) : Actor(L"■", Color::BrightRed, position)
{
    // 그릴 때 사용할 정렬 순서 설정.
    SetSortingOrder(1);
}
