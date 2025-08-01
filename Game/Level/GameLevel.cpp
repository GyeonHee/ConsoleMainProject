#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"

GameLevel::GameLevel()
{
    ReadMapFile("Map1.txt");

	// �÷��̾� �߰�
	Player* player = new Player();
	playerWidth = player->Width();
	AddActor(player);
}

GameLevel::~GameLevel()
{
}


void GameLevel::BeginPlay()
{
	super::BeginPlay();
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}

void GameLevel::Render()
{
	super::Render();

    /*for (int i = 0; i < 14; ++i)
    {
        snprintf(map[i], sizeof(map[i]), "%c, %c", i + 1, i + 1);
    }*/
}

void GameLevel::ReadMapFile(const char* fileName)
{
	// ���� ���� ��� �ϼ�
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Assets/%s", fileName);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	// ����ó��
	if (file == nullptr)
	{
		//std::cout << "�� ���� �б� ����: " << filename << "\n";
		__debugbreak();
		return;
	}

	// �Ľ�(Parcing, �ؼ�)
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�
	char* buffer = new char[fileSize + 1];
	//buffer[fileSize] = '\0';
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	/*if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize\n";
	}*/

	// �迭 ��ȸ�� ���� �ε��� ����
	int index = 0;

	// ���ڿ� ���� ��
	int size = (int)readSize;

	// x, y ��ǥ
	Vector2 position;

	// ���� �迭 ��ȸ
	while (index < size)
	{
		// �� ���� Ȯ��
		char mapCharacter = buffer[index];
		index++;

		// ���� ���� ó��
		if (mapCharacter == '\n')
		{
			// ���� �ٷ� �ѱ�鼭, x ��ǥ �ʱ�ȭ
			++position.y;
			position.x = 0;

			continue;
		}

		// �� ���ں��� ó��
		switch (mapCharacter)
		{
        case '0':
            AddActor(new Ground(position));
            break;

        case '1':
            AddActor(new Wall(position));
            break;
		}

		// x ��ǥ ���� ó��
		++position.x;
	}

	// ���� ����
	delete[] buffer;

	// ���� �ݱ�
	fclose(file);
}

bool GameLevel::CanPlayerMove(
    const Vector2& playerPosition,
    const Vector2& newPosition)
{
    //// ���� Ŭ���� ���� Ȯ�� �� ���� ó��.
    //if (isGameClear)
    //{
    //    return false;
    //}

    //// �ڽ� ó��.
    //std::vector<Box*> boxActors;
    //for (Actor* const actor : actors)
    //{
    //    Box* box = actor->As<Box>();
    //    if (box)
    //    {
    //        boxActors.emplace_back(box);
    //    }
    //}

    //// �̵��Ϸ��� ��ġ�� �ڽ��� �ִ��� Ȯ��.
    //Box* searchedBox = nullptr;
    //for (Box* const boxActor : boxActors)
    //{
    //    // �÷��̾ �̵��Ϸ��� ��ġ�� �ڽ��� ��ġ�� ������ ��.
    //    if (boxActor->Position() == newPosition)
    //    {
    //        // ���� ��ġ�� �ִ� �ڽ� ���� �� ���� ����.
    //        searchedBox = boxActor;
    //        break;
    //    }
    //}

    //// �̵��Ϸ��� ��ġ�� �ڽ��� �ִ� ��� ó��.
    //if (searchedBox)
    //{
    //    // #1: �ڽ��� �̵���Ű���� ��ġ�� �ٸ� �ڽ��� �� �ִ��� Ȯ��.
    //    Vector2 direction = newPosition - playerPosition;
    //    Vector2 nextPosition = searchedBox->Position() + direction;

    //    for (Box* const otherBox : boxActors)
    //    {
    //        // ���� �ڽ��� �ǳʶٱ�.
    //        if (otherBox == searchedBox)
    //        {
    //            continue;
    //        }

    //        // �ڽ��� �̵���Ű���� ��ġ�� �ٸ� �ڽ��� �ִ��� Ȯ��.
    //        if (otherBox->Position() == nextPosition)
    //        {
    //            // �÷��̾� �̵� ����.
    //            return false;
    //        }
    //    }

    //    for (Actor* const actor : actors)
    //    {
    //        if (actor->Position() == nextPosition)
    //        {
    //            // #2: �ڽ��� ������, ���� ���� ������ Ȯ��.
    //            if (actor->As<Wall>())
    //            {
    //                // �÷��̾� �̵� ����.
    //                return false;
    //            }

    //            // #3: �̵� ������ ���(�׶���, Ÿ��)���� �ڽ� �̵� ó��.
    //            if (actor->As<Ground>() || actor->As<Target>())
    //            {
    //                // �ڽ� �̵� ó��.
    //                searchedBox->SetPosition(nextPosition);

    //                // ���� Ŭ���� ���� Ȯ��.
    //                isGameClear = CheckGameClear();

    //                // �÷��̾� �̵� ����.
    //                return true;
    //            }
    //        }
    //    }
    //}

    // �÷��̾ �̵��Ϸ��� ��ġ�� �ڽ��� ���� ���.
    for (Actor* const actor : actors)
    {
        if (actor->Position() == newPosition)
        {
            // ���̸� �̵� �Ұ�.
            if (actor->As<Wall>())
            {
                return false;
            }

            // �׶��� or Ÿ��.
            return true;
        }
    }
    // ???.
    return false;
}