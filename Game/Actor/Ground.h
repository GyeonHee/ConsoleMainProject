#pragma once

#include "Actor/Actor.h"
#include "Engine.h"

class Ground : public Actor
{
    RTTI_DECLARATIONS(Ground, Actor)
public:
    Ground(const Vector2& position);
    ~Ground() override = default;

    void SetExploding(bool val) { isExploding = val; }

    virtual void Render() override
    {
        Color fg = Color::White;
        Color bg = Color::White;

        if (isExploding)
        {
            bg = Color::Blue;  // 폭발 시 배경을 빨간색으로 변경
            fg = Color::Blue;  
        }

        Engine::Get().WriteToBuffer(Position(), L"■", bg, fg);
    }

private:
    bool isExploding = false;
};