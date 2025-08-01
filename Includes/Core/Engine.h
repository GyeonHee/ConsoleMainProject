#pragma once
#include "Core.h"
#include "Input.h"

#include "Math/Color.h"
#include "Math/Vector2.h"

#include <Windows.h>

// ���� ���� ����ü
struct EngineSettings
{
	// �ܼ� ȭ�� ���� ũ��
	int width = 0;

	// �ܼ� ȭ�� ���� ũ��
	int height = 0;

	// Ÿ�� ������ �ӵ�
	float framerate = 0.0f;
};

class Level;
class ScreenBuffer;
class Engine_API Engine
{
public:
	Engine();
	virtual ~Engine();

	// ���� ���� �Լ�
	void Run();

	// ���ڿ� �׸��� ��û �Լ�.
	void WriteToBuffer(const Vector2& position, const char* image, Color color = Color::White);

	// ���۸� ��ٷ� ��ȯ ��û�� �� ����ϴ� �Լ�
	void PresentImmediately();

	// ���� �߰� �Լ�
	void AddLevel(Level* newLevel);

	// �޸� ���� �Լ�
	virtual void CleanUp();

	// ���� �Լ�
	void Quit();

	// �̱��� ���� �Լ�
	static Engine& Get();

	// ȭ�� ����/���� ũ�� ��ȯ �Լ�
	int Width() const;
	int Height() const;

protected:

	// ����/���� �ʱ�ȭ �� ��� (���� �߰� ��).
	virtual void OnInitialized();

	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();

	// ȭ�� ����� �Լ� (��ü�� �� ���ڿ��� ����).
	void Clear();

	// ���� ��ȯ �Լ� (����Ʈ ���� <-> �����)
	void Present();

	// ���� ���� �ε� �Լ�
	void LoadEngineSettings();

	// ����� ���� Ÿ�� ��ȯ �Լ�.
	ScreenBuffer* GetRenderer() const;

	// ���� ���� ����� �Լ�.
	void ClearImageBuffer();

	// �ܼ�â ũ�� ����
	void ConsoleSizeSetting();

    // �ܼ�â�� �׸� ��Ʈ ũ�� ����
    void ConsoleFontSizeSetting(HANDLE hConsole, int width, int height);

protected:
	// ���� ���� �÷���
	bool isQuit = false;

	// ���� ����
	Level* mainLevel = nullptr;

	// �Է� ������
	Input input;

	// ���� ����
	EngineSettings settings;

	// �����(������).
	CHAR_INFO* imageBuffer = nullptr;

	// ���� ����.
	ScreenBuffer* renderTargets[2] = { };

	// ����۷� ����ϴ� ���� Ÿ���� �ε���.
	int currentRenderTargetIndex = 0;

	// �̱��� ����
	static Engine* instance;
};