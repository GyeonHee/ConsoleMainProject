#include "Engine.h"
#include "Input.h"
#include "Level/Level.h"
#include "Utils/Utils.h"
#include "Render/ScreenBuffer.h"

#include <iostream>
#include <Windows.h>
#include <cstdlib> // for system()

// 2차원 배열을 컴퓨터가 1차원 배열로 계산하는 과정
//(y * 4) + x
// 4는 [y][x]에서 [][4]일 경우 
// [][5]면 (y * 5) + x
// ex(arr[3][4]일 경우 [1][1]인덱스의 값은 arr[(1 * 4) + 1] 이다. == arr[5];

// 정적 변수 초기화
Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
	case CTRL_CLOSE_EVENT:
		// Engine 메모리 해제
		Engine::Get().CleanUp();
		return false;
	}

	return false;
}

Engine::Engine()
{
	instance = this;

	// 콘솔 커서 끄기
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	// 엔진 설정 로드
	LoadEngineSettings();

	// 랜덤 종자값(seed) 설정
	srand(static_cast<unsigned int>(time(nullptr)));

	// 이미지 버퍼 생성.
	Vector2 screenSize(settings.width, settings.height); // 30, 30
	imageBuffer = new CHAR_INFO[(screenSize.x + 1) * screenSize.y + 1];

	// 버퍼 초기화 (문자 버퍼).
	ClearImageBuffer();

	// 두 개의 버퍼 생성.
	renderTargets[0] = new ScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE), screenSize);
	renderTargets[1] = new ScreenBuffer(screenSize);

	
	// 버퍼 교환.
	Present();

	ConsoleSizeSetting();

	// 콘솔 창 이벤트 등록
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);
}

Engine::~Engine()
{
	CleanUp();
}

void Engine::Run()
{
	// 밀리 세컨드 단위로 현재 시간을 알려줌
	//float currentTime = timeGetTime();

	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;
	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// 하드웨어 시계의 정밀도(주파수) 가져오기.
	// 나중에 초로 변환하기 위해
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// 타겟 프레임
	float targetFrameRate = settings.framerate == 0.0f ? 60.0f : settings.framerate;

	// 타겟 한 프레임 시간
	float oneFrameTime = 1.0f / targetFrameRate;

	// GameLoop.
	while (true)
	{
		// 엔진 종료 여부 확인
		if (isQuit)
		{
			// 루프 종료
			break;
		}

		// 프레임 시간 계산
		// (현재 시간 - 이전 시간) / 주파수 = 초단위
		QueryPerformanceCounter(&currentTime);

		// 프레임 시간
		float deltaTime =
			(currentTime.QuadPart - previousTime.QuadPart)
			/ (float)frequency.QuadPart;

		// 입력은 최대한 빨리
		input.ProcessInput();

		// 고정 프레임
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// 시간 업데이트
			previousTime = currentTime;

			// 현재 프레임의 입력을 기록
			input.SavePreviousKeyStates();

			// 이전 프레임에 추가 및 삭제 요청된 액터 처리
			if (mainLevel)
			{
				mainLevel->ProcessAddAndDestroyActors();
			}
		}
	}

	// 정리(텍스트 색상 원래대로 돌려놓기)
	Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void Engine::WriteToBuffer(const Vector2& position, const char* image, Color color)
{
	// 문자열 길이.
	int length = static_cast<int>(strlen(image));

	// 문자열 기록.
	for (int ix = 0; ix < length; ++ix)
	{
		// 기록할 문자 위치.
		int index = (position.y * (settings.width)) + position.x + ix;

		// 버퍼에 문자/색상 기록.
		imageBuffer[index].Char.AsciiChar = image[ix];
		imageBuffer[index].Attributes = (WORD)color;
	}
}

void Engine::PresentImmediately()
{
	GetRenderer()->Render(imageBuffer);
	Present();
}

void Engine::AddLevel(Level* newLevel)
{
	// 기존에 있던 레벨은 제거
	if (mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

void Engine::CleanUp()
{
	// 레벨 삭제
	SafeDelete(mainLevel);

	// 문자 버퍼 삭제.
	SafeDeleteArray(imageBuffer);

	// 렌더 타겟 삭제.
	SafeDelete(renderTargets[0]);
	SafeDelete(renderTargets[1]);
}

void Engine::Quit()
{
	// 종료 플래그 설정
	isQuit = true;
}

Engine& Engine::Get()
{
	return *instance;
}

int Engine::Width() const
{
	return settings.width;
}

int Engine::Height() const
{
	return settings.height;
}

void Engine::OnInitialized()
{
}

void Engine::BeginPlay()
{
	if (mainLevel)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float deltaTime)
{
	// 레벨 업데이트
	if (mainLevel)
	{
		mainLevel->Tick(deltaTime);
	}
}

void Engine::Clear()
{
	ClearImageBuffer();
	GetRenderer()->Clear();
}

void Engine::Render()
{
	//Utils::SetConsoleTextColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	// 화면 지우기.
	Clear();

	// 레벨 그리기
	if (mainLevel)
	{
		mainLevel->Render();
	}

	// 백버퍼에 데이터 쓰기.
	GetRenderer()->Render(imageBuffer);

	// 버퍼 교환.
	Present();
}

// 콘솔 버퍼 교환 후 출력
void Engine::Present()
{
	// 버퍼 교환.
	SetConsoleActiveScreenBuffer(GetRenderer()->buffer);

	// 인덱스 뒤집기 공식
	// 1 - x
	// 인덱스 뒤집기. 1->0, 0->1.
	currentRenderTargetIndex = 1 - currentRenderTargetIndex;
}

// Settings 폴더에서 EngineSetting.txt에 저장된 데이터 읽어오기
void Engine::LoadEngineSettings()
{
	// 엔진 설정 파일 열기
	FILE* file = nullptr;
	fopen_s(&file, "../Settings/EngineSettings.txt", "rt");

	if (file == nullptr)
	{
		std::cout << "Failed to load engine settings.\n";
		__debugbreak();
		return;
	}

	// 로드
	// FP(File Position) 포인터를 가장 뒤로 옮기기
	fseek(file, 0, SEEK_END);

	// 이 위치 구하기
	size_t fileSize = ftell(file);

	// 다시 첫 위치로 되돌리기
	rewind(file);

	// 파일 내용을 저장할 버퍼 할당
	char* buffer = new char[fileSize + 1];
	memset(buffer, 0, fileSize + 1);

	// 내용 읽기
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);

	char* context = nullptr;
	char* token = nullptr;

	// 파싱(Parcing, 구문 해석 -> 필요한 정보를 얻는 과정)
	token = strtok_s(buffer, "\n", &context);

	// 구문 분석
	while (token != nullptr)
	{
		// 키/값 분리
		char header[10] = {};

		// 아래 구문이 제대로 동작하려면 키와 값 사이의 빈칸이 있어야 함
		sscanf_s(token, "%s", header, 10);

		// 헤더 문자열 비교
		if (strcmp(header, "framerate") == 0)
		{
			sscanf_s(token, "framerate = %f", &settings.framerate);
		}
		else if (strcmp(header, "width") == 0)
		{
			sscanf_s(token, "width = %d", &settings.width);
		}
		else if (strcmp(header, "height") == 0)
		{
			sscanf_s(token, "height = %d", &settings.height);
		}

		// 그 다음 줄 분리
		token = strtok_s(nullptr, "\n", &context);
	}

	// 버퍼 해제
	SafeDeleteArray(buffer);

	fclose(file);
}

ScreenBuffer* Engine::GetRenderer() const
{
	return renderTargets[currentRenderTargetIndex];
}

void Engine::ClearImageBuffer()
{
	// 글자 버퍼 덮어쓰기.
	for (int y = 0; y < settings.height; ++y)
	{
		for (int x = 0; x < settings.width; ++x)
		{
			CHAR_INFO& buffer = imageBuffer[(y * (settings.width)) + x];
			buffer.Char.AsciiChar = ' ';
			buffer.Attributes = 0;
		}

		// 각 줄 끝에 개행 문자 추가.
		CHAR_INFO& buffer = imageBuffer[(y * (settings.width)) + settings.width];
		buffer.Char.AsciiChar = '\n';
		buffer.Attributes = 0;
	}

	// 마지막에 널 문자 추가.
	CHAR_INFO& buffer = imageBuffer[(settings.width) * settings.height + 1];
	buffer.Char.AsciiChar = '\0';
	buffer.Attributes = 0;
}

void Engine::ConsoleSizeSetting()
{
	for (int i = 0; i < 2; ++i) {
		HANDLE hOut = renderTargets[i]->GetHandle();

        // 무조건 "창 크기 ≤ 버퍼 크기" 그래서 임시로 줄여놓음
        SMALL_RECT tempWindow = { 0, 0, 1, 1 };
        SetConsoleWindowInfo(hOut, TRUE, &tempWindow);

		// 1. 버퍼 크기 설정
		COORD bufferSize = { static_cast<SHORT>(settings.width), static_cast<SHORT>(settings.height) };
		if (!SetConsoleScreenBufferSize(hOut, bufferSize))
		{
			std::cerr << "SetConsoleScreenBufferSize 실패 buffer" << i << "\n";
			continue;
		}

		// 2. 콘솔 창 크기 설정
		SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(settings.width - 1), static_cast<SHORT>(settings.height - 1) };
		if (!SetConsoleWindowInfo(hOut, TRUE, &windowSize))
		{
			std::cerr << "SetConsoleWindowInfo 실패\n";
			return;
		}

        // 3. 폰트 크기 설정(단위: 픽셀)
        ConsoleFontSizeSetting(hOut, 15 * 2, 20 * 2);
	}
}

void Engine::ConsoleFontSizeSetting(HANDLE hConsole, int width, int height)
{
    CONSOLE_FONT_INFOEX fontInfo = { 0 };
    fontInfo.cbSize = sizeof(fontInfo);
    fontInfo.dwFontSize.X = width;   // 글자 너비
    fontInfo.dwFontSize.Y = height;  // 글자 높이
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy_s(fontInfo.FaceName, L"Consolas"); // 또는 L"Lucida Console"

    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) {
        std::cerr << "폰트 설정 실패\n";
    }
}
