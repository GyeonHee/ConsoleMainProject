#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"

GameLevel::GameLevel()
{
    ReadMapFile("Map1.txt");

	// 플레이어 추가
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
	// 최종 에셋 경로 완성
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Assets/%s", fileName);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

	// 예외처리
	if (file == nullptr)
	{
		//std::cout << "맵 파일 읽기 실패: " << filename << "\n";
		__debugbreak();
		return;
	}

	// 파싱(Parcing, 해석)
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// 확인한 파일 크기를 활용해 버퍼 할당
	char* buffer = new char[fileSize + 1];
	//buffer[fileSize] = '\0';
	memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	/*if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize\n";
	}*/

	// 배열 순회를 위한 인덱스 변수
	int index = 0;

	// 문자열 길이 값
	int size = (int)readSize;

	// x, y 좌표
	Vector2 position;

	// 문자 배열 순회
	while (index < size)
	{
		// 맵 문자 확인
		char mapCharacter = buffer[index];
		index++;

		// 개행 문자 처리
		if (mapCharacter == '\n')
		{
			// 다음 줄로 넘기면서, x 좌표 초기화
			++position.y;
			position.x = 0;

			continue;
		}

		// 각 문자별로 처리
		switch (mapCharacter)
		{
        case '0':
            AddActor(new Ground(position));
            break;

        case '1':
            AddActor(new Wall(position));
            break;
		}

		// x 좌표 증가 처리
		++position.x;
	}

	// 버퍼 해제
	delete[] buffer;

	// 파일 닫기
	fclose(file);
}

bool GameLevel::CanPlayerMove(
    const Vector2& playerPosition,
    const Vector2& newPosition)
{
    //// 게임 클리어 여부 확인 및 종료 처리.
    //if (isGameClear)
    //{
    //    return false;
    //}

    //// 박스 처리.
    //std::vector<Box*> boxActors;
    //for (Actor* const actor : actors)
    //{
    //    Box* box = actor->As<Box>();
    //    if (box)
    //    {
    //        boxActors.emplace_back(box);
    //    }
    //}

    //// 이동하려는 위치에 박스가 있는지 확인.
    //Box* searchedBox = nullptr;
    //for (Box* const boxActor : boxActors)
    //{
    //    // 플레이어가 이동하려는 위치와 박스의 위치가 같은지 비교.
    //    if (boxActor->Position() == newPosition)
    //    {
    //        // 같은 위치에 있는 박스 저장 후 루프 종료.
    //        searchedBox = boxActor;
    //        break;
    //    }
    //}

    //// 이동하려는 위치에 박스가 있는 경우 처리.
    //if (searchedBox)
    //{
    //    // #1: 박스를 이동시키려는 위치에 다른 박스가 또 있는지 확인.
    //    Vector2 direction = newPosition - playerPosition;
    //    Vector2 nextPosition = searchedBox->Position() + direction;

    //    for (Box* const otherBox : boxActors)
    //    {
    //        // 같은 박스는 건너뛰기.
    //        if (otherBox == searchedBox)
    //        {
    //            continue;
    //        }

    //        // 박스를 이동시키려는 위치에 다른 박스가 있는지 확인.
    //        if (otherBox->Position() == nextPosition)
    //        {
    //            // 플레이어 이동 못함.
    //            return false;
    //        }
    //    }

    //    for (Actor* const actor : actors)
    //    {
    //        if (actor->Position() == nextPosition)
    //        {
    //            // #2: 박스는 없지만, 벽이 있지 않은지 확인.
    //            if (actor->As<Wall>())
    //            {
    //                // 플레이어 이동 못함.
    //                return false;
    //            }

    //            // #3: 이동 가능한 경우(그라우드, 타겟)에는 박스 이동 처리.
    //            if (actor->As<Ground>() || actor->As<Target>())
    //            {
    //                // 박스 이동 처리.
    //                searchedBox->SetPosition(nextPosition);

    //                // 게임 클리어 여부 확인.
    //                isGameClear = CheckGameClear();

    //                // 플레이어 이동 가능.
    //                return true;
    //            }
    //        }
    //    }
    //}

    // 플레이어가 이동하려는 위치에 박스가 없는 경우.
    for (Actor* const actor : actors)
    {
        if (actor->Position() == newPosition)
        {
            // 벽이면 이동 불가.
            if (actor->As<Wall>())
            {
                return false;
            }

            // 그라운드 or 타겟.
            return true;
        }
    }
    // ???.
    return false;
}