#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Bomb.h"
#include "Actor/Block.h"
#include "Actor/Box.h"
#include "Actor/Bush.h"

GameLevel* GameLevel::instance = nullptr;

GameLevel::GameLevel()
{
    instance = this;
    // 0 : Ground, 1 : Wall, 2 : Block, 3 : Box, 4 : Bush 
    ReadMapFile("Map1.txt");
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

    // 플레이어가 물풍선에 맞았을 때, 5초 후에 삭제
    std::vector<Actor*> toRemove;

    for (Actor* actor : actors)
    {
        actor->Tick(deltaTime);

        if (Player* player = actor->As<Player>())
        {
            if (player->ShouldBeRemoved())
            {
                toRemove.push_back(player);
            }
        }
    }

    for (Actor* actor : toRemove)
    {
        RemoveActor(actor);       
    }
}

void GameLevel::Render()
{
	super::Render();
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
         // 0 : Ground, 1 : Wall, 2 : Block, 3 : Box, 4 : Bush 
		switch (mapCharacter)
		{
        case 's':
            AddActor(new Player(position));
            AddActor(new Ground(position));
            break;
        case '0':
            AddActor(new Ground(position));
            break;
        case '1':
            AddActor(new Wall(position));
            break;
        case '2':
            AddActor(new Block(position));
            AddActor(new Ground(position));
            break;
        case '3':
            AddActor(new Box(position));
            AddActor(new Ground(position));
            break;
        case '4':
            AddActor(new Bush(position));
            AddActor(new Ground(position));
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

// 기존에 썼던 CanPlayerMove함수

//bool GameLevel::CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition)
//{
//    // 박스 처리
//    std::vector<Box*> boxActors;
//    for (Actor* const actor : actors)
//    {
//        Box* box = actor->As<Box>();
//        if (box)
//        {
//            boxActors.emplace_back(box);
//        }
//    }
//
//    // 이동하려는 위치에 박스가 있는지 확인
//    Box* searchedBox = nullptr;
//    for (Box* const boxActor : boxActors)
//    {
//        // 플레이어가 이동하려는 위치와 박스의 위치가 같은지 비교
//        if (boxActor->Position() == newPosition)
//        {
//            // 같은 위치에 있는 박스 저장 후 루프 종료
//            searchedBox = boxActor;
//            break;
//        }
//    }
//
//    bool isBlocked = false;
//    bool hasGround = false;
//    // 이동하려는 위치에 박스가 있는 경우 처리
//    if (searchedBox)
//    {
//        // #1: 박스를 이동시키려는 위치에 다른 박스가 또 있는지 확인
//        Vector2 direction = newPosition - playerPosition;
//        Vector2 nextPosition = searchedBox->Position() + direction;
//        
//
//        for (Box* const otherBox : boxActors)
//        {
//            if (otherBox == searchedBox)
//            {
//                continue;
//            }
//
//            // 박스를 이동시키려는 위치에 다른 박스가 있는지 확인
//            if (otherBox->Position() == nextPosition)
//            {
//                // 플레이어 이동 못함
//                return false;
//            }
//        }
//
//        // #2: 박스를 이동시키려는 위치에 박스제외 다른 액터가 있는지 확인
//        for (Actor* const actor : actors)
//        {
//            if (actor == searchedBox) continue;
//
//            if (actor->Position() == nextPosition)
//            {
//                 // 벽, 블럭, 폭탄이 있는지 확인
//                 if (actor->As<Wall>() || actor->As<Block>() || actor->As<Bomb>())
//                 {
//                     // 있으면 true하고 탈출
//                     isBlocked = true;
//                     break;
//                 }
//
//                 if (actor->As<Ground>())
//                 {
//                     // 땅이면 hasGround true
//                     hasGround = true;
//                 }
//            }
//        }
//
//        // 다른 블럭들 아니고 오로지 땅이면 박스 이동
//        if (!isBlocked && hasGround)
//        {
//            searchedBox->SetPosition(nextPosition);
//            return true;
//        }
//
//        // 전부 다 해당이 안될 때(버그임)
//        return false;
//    } // if (searchedBox)
//
//    // #3: 플레이어가 이동하려는 위치에 박스가 없는 경우
//    for (Actor* const actor : actors)
//    {
//        if (actor->Position() == newPosition)
//        {
//            /*if (actor->As<Wall>() ||
//                actor->As<Block>() ||
//                actor->As<Bomb>())
//            {
//                return false;
//            }*/
//
//            if (actor->As<Wall>() ||
//                actor->As<Bomb>())
//            {
//                return false;
//            }
//        }
//    }
//
//    return true;
//}

// 플레이어가 움직일 수 있는지 판단
bool GameLevel::CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition)
{
    Actor* searchedBox = nullptr;

    for (Actor* const actor : actors)
    {
        // 이동할 위치에 액터가 있을때
        if (actor->Position() == newPosition)
        {
            // 그 액터가 박스이면
            if (actor->As<Box>())
                // 액터에 박스 저장
                searchedBox = actor;

            // 그 액터가 벽이거나, 블럭이거나, 물풍선이면
            if (actor->As<Wall>() || actor->As<Block>() || actor->As<Bomb>())
            //if (actor->As<Wall>() || actor->As<Bomb>()) // 디버깅용
                return false;
        }
    }

    // 아까 저장해둔 박스
    if (searchedBox != nullptr)
    {
        Vector2 direction = newPosition - playerPosition;
        Vector2 nextPosition = searchedBox->Position() + direction;

        // 맵 범위 벗어나면 못움직임
        if (nextPosition.x < 0 || nextPosition.x >= 15 ||
            nextPosition.y < 0 || nextPosition.y >= 13)
        {
            return false;
        }

        for (Actor* const actor : actors)
        {
            // 다음 이동할 곳이 어떤 액터의 좌표값과 같다면
            if (actor->Position() == nextPosition)
            {
                // 그게 벽이거나 블럭,폭탄, 박스라면
                if (actor->As<Wall>() || actor->As<Block>() || actor->As<Bomb>() || actor->As<Box>())
                //if (actor->As<Wall>() || actor->As<Bomb>() || actor->As<Box>()) // 디버깅용
                    // 못움직임
                    return false;
            }
        }
    }

    return true;
}

// 움직일 수 있으면 움직이게 좌표값 정해줌
void GameLevel::TryPlayerMove(const Vector2& playerPosition, const Vector2& newPosition)
{
    Vector2 direction = newPosition - playerPosition;

    for (Actor* const actor : actors)
    {
        if (actor->Position() == newPosition && actor->As<Box>())
        {
            Vector2 boxNextPosition = newPosition + direction;
            actor->SetPosition(boxNextPosition);
            break;
        }
    }
}

GameLevel& GameLevel::Get()
{
    return *instance;
}

void GameLevel::HandleBombExplosion(const Vector2& center)
{
    const Vector2 directions[] = {
       {0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    std::vector<Actor*> toDestroy; // 삭제할 액터 저장
    
    for (const Vector2& dir : directions)
    {
        Vector2 target = center + dir;
        if (!IsInMapBounds(target)) continue;

        std::vector<Actor*> actorsAt = FindActorsAt(target);

        for (Actor* actor : actorsAt)
        {
            if (actor->As <Wall>()) continue;

            if (actor->As<Block>() || actor->As<Box>() || actor->As<Bomb>() || actor->As<Bush>())
            {
                toDestroy.push_back(actor); // 먼저 저장
                
            }

            if (actor->As<Player>())
            {
                actor->As<Player>()->PlayerHitBomb();
            }
        }
    }

    for (Actor* actor : toDestroy)
    {
        RemoveActor(actor); // 나중에 제거
    }
}

std::vector<Actor*> GameLevel::FindActorsAt(const Vector2& pos)
{
    std::vector<Actor*> result;

    for (Actor* actor : actors)
    {
        if (actor->Position() == pos)
            result.push_back(actor);
    }

    return result;
}

bool GameLevel::IsInMapBounds(const Vector2& pos)
{
    return (pos.x >= 0 && pos.x < 15 &&
        pos.y >= 0 && pos.y < 13);
}

void GameLevel::RemoveActor(Actor* actor)
{
    auto it = std::find(actors.begin(), actors.end(), actor);
    
    if (it != actors.end())
    {
        delete* it;           // 메모리 해제
        actors.erase(it);     // 벡터에서 제거
    }
}
