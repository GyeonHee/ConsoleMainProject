# Crazy Arcade Clone (Console Engine)

> 콘솔 환경에서 자체 게임 엔진을 처음부터 구축하고, 그 위에 크레이지 아케이드를 모작한 프로젝트입니다.

![Engine](https://img.shields.io/badge/Engine-Custom%20(Console)-blue) ![Language](https://img.shields.io/badge/Language-C%2B%2B-orange) ![Status](https://img.shields.io/badge/Status-Completed-success)

🎥 **[데모 영상 보기](https://youtu.be/qIgSy6AaXGU)**

<br>

## 📌 프로젝트 개요

| 항목 | 내용 |
|---|---|
| 개발 기간 | 2025.07.31 ~ 2025.08.07 (1주) |
| 참여 인원 | 1인 (전체 개발) |
| 엔진 | 자체 제작 (Console, DLL 분리 구조) |
| 플랫폼 | Windows Console |

상용 엔진 없이 **콘솔 환경에서 동작하는 게임 엔진을 1주일 만에 직접 설계·구현**하고, 그 위에서 크레이지 아케이드의 핵심 메카닉(폭탄, 연쇄폭발, 2인 동시 플레이)을 구현한 프로젝트입니다.

<br>

## 🎯 핵심 구현

### 1. 콘솔 엔진 기반 시스템
- `QueryPerformanceCounter` 기반 고정 프레임레이트 게임 루프
- **더블 버퍼링 렌더링 파이프라인** — 콘솔 스크린 버퍼 2개를 생성해 프레임마다 교환, `CHAR_INFO` 배열에 일괄 기록 후 `WriteConsoleOutputW()` 1회 호출로 출력해 깜빡임 제거
- 입력 시스템 — 매 루프 `GetAsyncKeyState()`로 255개 키 상태를 기록, 이전 프레임과 비교해 `GetKey`/`GetKeyDown`/`GetKeyUp` 구분
- 엔진 설정 파일(`EngineSettings.txt`) 파싱 및 콘솔 초기화

### 2. 게임 오브젝트 시스템
- Actor / Level 컴포넌트 구조 설계, `vector<Actor*>` 기반 BeginPlay/Tick/Render 루프
- **커스텀 RTTI 타입 캐스팅 시스템** — `dynamic_cast` 없이 `Is<T>()` / `As<T>()` 구현
- SortingOrder 기반 렌더링 우선순위 (Ground=0, Bomb=1, Block/Box=2, Player=3)
- 지연 생성/삭제 큐로 Tick/Render 도중 벡터 직접 수정 시 발생하는 iterator 무효화 문제 해결

### 3. 핵심 게임 메카닉
- `ICanPlayerMove` 인터페이스로 Player ↔ GameLevel 간 직접 참조 제거 (의존성 역전)
- **폭탄 타이머 및 재귀 연쇄폭발 알고리즘** — `std::chrono` 기반 타이머, 4방향 × 2칸 선형 스캔으로 폭발 범위 계산, `visited` set으로 중복 처리 방지
- 폭발 범위 시각화 (타이머 기반 색상 플래시)
- 텍스트 파일 맵(`Map1.txt`) 파싱 및 레이어 배치

### 4. 게임 루프 완성
- 2인 동시 플레이 — 독립된 KeyMap 구조체로 1P(WASD+Shift) / 2P(IJKL+Shift) 분리 운용
- 피격 및 사망 처리, 메뉴 레벨 전환(람다 콜백 UI)
- `SafeDelete` 템플릿 + Engine DLL 분리 구조로 메모리 관리

<br>

## 🛠 기술 스택

```
언어        C++
개발 환경    Visual Studio 2022 (v143)
빌드 구조    Engine(DLL) / Game(EXE) 분리
버전 관리    Git / GitHub
```

<br>

## 💡 트러블슈팅

### 1. 댕글링 포인터로 인한 크래시
**문제**: 물풍선으로 블록을 파괴하는 로직에서 `destroy()` 함수가 동일 객체에 여러 번 호출되며 nullptr 참조 크래시 발생

**원인**: 이미 삭제된 객체를 다시 참조 → 댕글링 포인터(Dangling Pointer)

**해결**: 객체 삭제 후 포인터를 `nullptr`로 초기화하고, 이미 삭제된 객체에 `destroy()`가 재호출되지 않도록 상태 체크 로직 추가

### 2. 재귀 탐색 중 스택 오버플로우
**문제**: 물풍선 범위를 재귀적으로 탐색하는 과정에서 종료 조건이 미흡해 동일 위치를 반복 탐색 → 무한 재귀 → 스택 오버플로우

**해결**: 재귀 종료 조건에 (1) 범위 이탈, (2) 이미 방문한 위치, (3) 더 이상 파괴 불가능한 블록을 추가해 무한 재귀를 방지하고 안정적인 탐색 구조를 확보

<br>

## 😅 아쉬운 점

- 게임의 기본 루프와 플레이는 완성했지만, 밸런스 조정·UI 개선·세부 연출까지는 다듬지 못한 채 마무리되었습니다.
- 텍스트 기반 콘솔 렌더링의 한계로 특수 문자 사용 시 글자 바이트 수 차이로 인한 깨짐 현상이 있었고, 배경/전경색을 통일하는 방식으로 우회했습니다.

<br>

## 📂 프로젝트 구조

```
ConsoleMainProject.sln
├── Engine (DLL)              # 재사용 가능한 엔진 레이어
│   ├── Core/                  # 게임루프, 더블버퍼링, 설정 로드, RTTI
│   ├── Actor/                 # 모든 게임 오브젝트의 기반 클래스
│   ├── Level/                 # 액터 관리, BeginPlay/Tick/Render 루프
│   ├── Render/                # 콘솔 스크린 버퍼 이중화 관리
│   └── Math/                  # Vector2, 콘솔 16색 팔레트
└── Game (EXE)                 # 게임 로직 레이어
    ├── Actor/                  # Player, Bomb, Block/Box/Wall/Bush/Ground
    ├── Level/                  # GameLevel(맵/충돌/폭발), MenuLevel(UI)
    ├── Interface/              # ICanPlayerMove
    ├── Assets/Map1.txt          # 텍스트 기반 맵 데이터
    └── Settings/EngineSettings.txt
```
