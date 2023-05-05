#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineBase\GameEngineTime.h>
#include <GameEngineCore/GameEngineDevice.h>
#include "GameEngineVideo.h"
#include "GameEngineGUI.h"

std::map<std::string, std::shared_ptr<GameEngineLevel>> GameEngineCore::LevelMap;
std::shared_ptr<GameEngineLevel> GameEngineCore::MainLevel = nullptr;
std::shared_ptr<GameEngineLevel> GameEngineCore::NextLevel = nullptr;

GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}

void GameEngineCore::EngineStart(std::function<void()> _ContentsStart)
{
	// 리소스 초기화 이전에 디바이스 초기화를 해준다. 
	GameEngineDevice::Initialize();

	// 게임에서 사용할 리소스 초기화
	CoreResourcesInit();

	// imgui 초기화
	GameEngineGUI::Initialize();

	if (nullptr == _ContentsStart)
	{
		MsgAssert("시작 컨텐츠가 존재하지 않습니다.");
	}
	_ContentsStart();
}

// Loop , 게임이 실행되면 반복동작
void GameEngineCore::EngineUpdate()
{
	// 다음 레벨이 nullptr 이 아니라면
	if (nullptr != NextLevel)
	{
		// 현재 레벨도 nullptr 이 아니라면 
		if (nullptr != MainLevel)
		{
			// 현재 메인레벨의 종료시점의 작업수행
			MainLevel->LevelChangeEnd();
		}

		// 메인레벨은 다음레벨이 된다. 
		MainLevel = NextLevel;

		// 변경된 레벨의 start 
		if (nullptr != MainLevel)
		{
			MainLevel->LevelChangeStart();
		}

		// 변수초기화 
		NextLevel = nullptr;

		// 로딩이 오래걸릴수 있기 때문에 델타타임을 한번 리셋 
		GameEngineTime::GlobalTime.Reset();
	}

	if (nullptr == MainLevel)
	{
		MsgAssert("아무런 레벨도 동작하지 않고 있습니다.");
		return;
	}

	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();

	// 델타타임이 너무 오버됐을 경우를 대비, 좋지는 않다. 
	// 문제??? 
	if (TimeDeltaTime > 1 / 30.0f)
	{
		TimeDeltaTime = 1 / 30.0f;
	}

	GameEngineInput::Update(TimeDeltaTime);
	GameEngineSound::SoundUpdate();

	MainLevel->TimeEvent.Update(TimeDeltaTime);
	MainLevel->Update(TimeDeltaTime);
	MainLevel->ActorUpdate(TimeDeltaTime);


	// 비디오가 재생중이라면 렌더링을 하지 않는다. 
	GameEngineVideo::VideoState State = GameEngineVideo::GetCurState();
	if (State != GameEngineVideo::VideoState::Running)
	{
		// 렌더링을 시작할 때 화면을 지워주고
		GameEngineDevice::RenderStart();
		// 렌더 
		MainLevel->Render(TimeDeltaTime);
		MainLevel->ActorRender(TimeDeltaTime);
		GameEngineDevice::RenderEnd();
	}

	MainLevel->ActorRelease();
}

void GameEngineCore::EngineEnd(std::function<void()> _ContentsEnd)
{
	if (nullptr == _ContentsEnd)
	{
		MsgAssert("끝 컨텐츠가 존재하지 않습니다.");
	}

	_ContentsEnd();

	GameEngineGUI::Release();

	LevelMap.clear();

	// sharedptr 로 인해 메모리가 제거되는 걸 알고 있지만. 
	CoreResourcesEnd();
	GameEngineDevice::Release();
	GameEngineWindow::Release();
}

// 릭체크 함수 호출, 마우스 LR 버튼 생성, 윈도우생성, 루프실행
void GameEngineCore::Start(HINSTANCE _instance, std::function<void()> _Start, std::function<void()> _End, float4 _Pos, float4 _Size)
{
	// 릭체크함수호출
	GameEngineDebug::LeakCheck();

	// 마우스 L , R 버튼 생성
	if (false == GameEngineInput::IsKey("EngineMouseLeft"))
	{
		GameEngineInput::CreateKey("EngineMouseLeft", VK_LBUTTON);
		GameEngineInput::CreateKey("EngineMouseRight", VK_RBUTTON);
	}

	// 윈도우 생성
	GameEngineWindow::WindowCreate(_instance, "MainWindow", _Size, _Pos);
	GameEngineWindow::WindowLoop(std::bind(GameEngineCore::EngineStart, _Start), GameEngineCore::EngineUpdate,
								 std::bind(GameEngineCore::EngineEnd, _End));
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	// 문자열 대문자로 변환
	std::string UpperName = GameEngineString::ToUpper(_Name);

	// 변환된 문자열로 맵에 동일한 이름의 레벨이 없다면
	// 생성하지 않은 레벨, assert 처리
	if (LevelMap.end() == LevelMap.find(UpperName))
	{
		MsgAssert("존재하지 않는 레벨로 체인지 하려고 했습니다.");
		return;
	}

	// assert 처리 되지 않았다면 
	// 다음 레벨은 맵에 저장된 인자로 들어온 레벨로 변경
	// map 의 문법, 배열과 비슷하게 사용하며
	// 존재하지 않을 경우 .. 어.. 여기 다시 복습
	NextLevel = LevelMap[UpperName];
}

// 초기화시에 레벨 Start
void GameEngineCore::LevelInit(std::shared_ptr<GameEngineLevel> _Level)
{
	_Level->Start();
}