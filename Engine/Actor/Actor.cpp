#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Level/Level.h"

#include <Windows.h>
#include <iostream>

// �ƽ�Ű�ڵ�

//Actor::Actor(const char* image, Color color, const Vector2& position)
//	: color(color), position(position)
//{
//	// ���ڿ� ����
//	width = (int)strlen(image);
//
//	// �޸� �Ҵ�
//	this->image = new char[width + 1];
//
//	// ���ڿ� ����
//	strcpy_s(this->image, width + 1, image);
//    
//} 

// �����ڵ�(����)

//Actor::Actor(const wchar_t* image, Color color, const Vector2& position)
//    : color(color), position(position)
//{
//    //// ���ڿ� ����
//    width = (int)wcslen(image);
//
//    //// �޸� �Ҵ�
//    this->image = new wchar_t[width + 1];
//
//    //// ���ڿ� ����
//    wcscpy_s(this->image, width + 1, image);
//
//}

// ��� ���� ����(�����ڵ�)
Actor::Actor(const wchar_t* image, Color bgColor, Color fgColor, const Vector2& position)
    : bgColor(bgColor), fgColor(fgColor), position(position)
{
    // ���ڿ� ����
    width = (int)wcslen(image);

    // �޸� �Ҵ�
    this->image = new wchar_t[width + 1];

    //���ڿ� ����
    wcscpy_s(this->image, width + 1, image);
}

Actor::~Actor()
{
	// �޸� ����
	SafeDeleteArray(image);
}

// �̺�Ʈ �Լ�

// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����)
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// ������ ���� ȣ�� (�ݺ��� �۾� / ���Ӽ��� �ʿ��� �۾�)
void Actor::Tick(float deltaTime)
{

}

// �׸��� �Լ�
void Actor::Render()
{
	Engine::Get().WriteToBuffer(position, image, bgColor, fgColor);
}

void Actor::SetPosition(const Vector2& newPosition)
{
	// �ܼ� ����� �����ϴ� �ڵ� ������
	//static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// ����ó�� (ȭ�� ������� Ȯ��)

	// ���� �����ڸ��� ȭ�� ������ �������
	if (newPosition.x < 0)
	{
		return;
	}

	// ������ �����ڸ��� ȭ�� �������� �������
	if (newPosition.x + width > Engine::Get().Width())
	{
		return;
	}

	// ���� �����ڸ��� ȭ���� ���� �������
	if (newPosition.y < 0)
	{
		return;
	}

	// ȭ�� �Ʒ��� �������
	if (newPosition.y + 1 > Engine::Get().Height())
	{
		return;
	}

	// ������ ������Ʈ ����
	if (position == newPosition)
	{
		return;
	}

	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}


int Actor::Width() const
{
	return width;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
	this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

bool Actor::TestIntersect(const Actor* const other)
{
	// AABB(Axis Aligned Bounding Box).
	// Note: ���� ���� ���� �� ���δ� ũ�Ⱑ ����(ũ�Ⱑ 1).
	//       ���� ������ �ּ�/�ִ� ��ġ�� �� ����ϸ� ��.

	// �� ������ x ��ǥ ����.
	int xMin = position.x;
	int xMax = position.x + width - 1;

	// �浹 ���� �ٸ� ������ x ��ǥ ����.
	int otherXMin = other->position.x;
	int otherXMax = other->position.x + other->width - 1;

	// �Ȱ�ġ�� ���� Ȯ��.

	// �ٸ� ������ ���� ��ǥ�� �� ������ ��ǥ���� �� �����ʿ� ������ �Ȱ�ħ.
	if (otherXMin > xMax)
	{
		return false;
	}

	// �ٸ� ������ ������ ��ǥ�� �� ���� ��ǥ���� �� ���ʿ� ������ �Ȱ�ħ.
	if (otherXMax < xMin)
	{
		return false;
	}

	// y ��ǥ�� ������ ���� Ȯ��.
	return position.y == other->position.y;
}

void Actor::Destroy()
{
	// ���� ��û �Ǿ��ٰ� ����
	isExpired = true;

	owner->DestroyActor(this);
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}

void Actor::SetColor(Color newBgColor)
{
    bgColor = newBgColor;
}
