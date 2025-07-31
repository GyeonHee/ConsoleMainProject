#include "GameLevel.h"
#include "Actor/Player.h"

GameLevel::GameLevel()
{
	// �÷��̾� �߰�
	AddActor(new Player());
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
}

//void GameLevel::ReadMapFile(const char* fileName)
//{
//	// ���� ���� ��� �ϼ�
//	char filepath[256] = {};
//	sprintf_s(filepath, 256, "../Assets/%s", filename);
//
//	FILE* file = nullptr;
//	fopen_s(&file, filepath, "rt");
//
//	// ����ó��
//	if (file == nullptr)
//	{
//		std::cout << "�� ���� �б� ����: " << filename << "\n";
//		__debugbreak();
//		return;
//	}
//
//	// �Ľ�(Parcing, �ؼ�)
//	fseek(file, 0, SEEK_END);
//	size_t fileSize = ftell(file);
//	rewind(file);
//
//	// Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�
//	char* buffer = new char[fileSize + 1];
//	//buffer[fileSize] = '\0';
//	memset(buffer, 0, fileSize + 1);
//	size_t readSize = fread(buffer, sizeof(char), fileSize, file);
//
//	/*if (fileSize != readSize)
//	{
//		std::cout << "fileSize is not matched with readSize\n";
//	}*/
//
//	// �迭 ��ȸ�� ���� �ε��� ����
//	int index = 0;
//
//	// ���ڿ� ���� ��
//	int size = (int)readSize;
//
//	// x, y ��ǥ
//	Vector2 position;
//
//	// ���� �迭 ��ȸ
//	while (index < size)
//	{
//		// �� ���� Ȯ��
//		char mapCharacter = buffer[index];
//		index++;
//
//		// ���� ���� ó��
//		if (mapCharacter == '\n')
//		{
//			// ���� �ٷ� �ѱ�鼭, x ��ǥ �ʱ�ȭ
//			++position.y;
//			position.x = 0;
//
//			//std::cout << "\n";
//			continue;
//		}
//
//		// �� ���ں��� ó��
//		switch (mapCharacter)
//		{
//		case '#':
//		case '1':
//			AddActor(new Wall(position));
//			break;
//		case '.':
//			AddActor(new Ground(position));
//			break;
//		case 'p':
//			// ���� ���� ����
//			AddActor(new Ground(position));
//
//			// Player Actor ����
//			AddActor(new Player(position));
//			break;
//		case 'b':
//			// ���� ���� ����
//			AddActor(new Ground(position));
//
//			AddActor(new Box(position));
//			break;
//		case 't':
//			//std::cout << 't';
//			AddActor(new Target(position));
//
//			// ��ǥ ���� ���� ó��
//			++targetScore;
//			break;
//		}
//
//		// x ��ǥ ���� ó��
//		++position.x;
//	}
//
//	// ���� ����
//	delete[] buffer;
//
//	// ���� �ݱ�
//	fclose(file);
//}
