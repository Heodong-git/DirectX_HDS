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
	// ���ҽ� �ʱ�ȭ ������ ����̽� �ʱ�ȭ�� ���ش�. 
	GameEngineDevice::Initialize();

	// ���ӿ��� ����� ���ҽ� �ʱ�ȭ
	CoreResourcesInit();

	// imgui �ʱ�ȭ
	GameEngineGUI::Initialize();

	if (nullptr == _ContentsStart)
	{
		MsgAssert("���� �������� �������� �ʽ��ϴ�.");
	}
	_ContentsStart();
}

// Loop , ������ ����Ǹ� �ݺ�����
void GameEngineCore::EngineUpdate()
{
	// ���� ������ nullptr �� �ƴ϶��
	if (nullptr != NextLevel)
	{
		// ���� ������ nullptr �� �ƴ϶�� 
		if (nullptr != MainLevel)
		{
			// ���� ���η����� ��������� �۾�����
			MainLevel->LevelChangeEnd();
		}

		// ���η����� ���������� �ȴ�. 
		MainLevel = NextLevel;

		// ����� ������ start 
		if (nullptr != MainLevel)
		{
			MainLevel->LevelChangeStart();
		}

		// �����ʱ�ȭ 
		NextLevel = nullptr;

		// �ε��� �����ɸ��� �ֱ� ������ ��ŸŸ���� �ѹ� ���� 
		GameEngineTime::GlobalTime.Reset();
	}

	if (nullptr == MainLevel)
	{
		MsgAssert("�ƹ��� ������ �������� �ʰ� �ֽ��ϴ�.");
		return;
	}

	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();

	// ��ŸŸ���� �ʹ� �������� ��츦 ���, ������ �ʴ�. 
	// ����??? 
	if (TimeDeltaTime > 1 / 30.0f)
	{
		TimeDeltaTime = 1 / 30.0f;
	}

	GameEngineInput::Update(TimeDeltaTime);
	GameEngineSound::SoundUpdate();

	MainLevel->TimeEvent.Update(TimeDeltaTime);
	MainLevel->Update(TimeDeltaTime);
	MainLevel->ActorUpdate(TimeDeltaTime);


	// ������ ������̶�� �������� ���� �ʴ´�. 
	GameEngineVideo::VideoState State = GameEngineVideo::GetCurState();
	if (State != GameEngineVideo::VideoState::Running)
	{
		// �������� ������ �� ȭ���� �����ְ�
		GameEngineDevice::RenderStart();
		// ���� 
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
		MsgAssert("�� �������� �������� �ʽ��ϴ�.");
	}

	_ContentsEnd();

	GameEngineGUI::Release();

	LevelMap.clear();

	// sharedptr �� ���� �޸𸮰� ���ŵǴ� �� �˰� ������. 
	CoreResourcesEnd();
	GameEngineDevice::Release();
	GameEngineWindow::Release();
}

// ��üũ �Լ� ȣ��, ���콺 LR ��ư ����, ���������, ��������
void GameEngineCore::Start(HINSTANCE _instance, std::function<void()> _Start, std::function<void()> _End, float4 _Pos, float4 _Size)
{
	// ��üũ�Լ�ȣ��
	GameEngineDebug::LeakCheck();

	// ���콺 L , R ��ư ����
	if (false == GameEngineInput::IsKey("EngineMouseLeft"))
	{
		GameEngineInput::CreateKey("EngineMouseLeft", VK_LBUTTON);
		GameEngineInput::CreateKey("EngineMouseRight", VK_RBUTTON);
	}

	// ������ ����
	GameEngineWindow::WindowCreate(_instance, "MainWindow", _Size, _Pos);
	GameEngineWindow::WindowLoop(std::bind(GameEngineCore::EngineStart, _Start), GameEngineCore::EngineUpdate,
								 std::bind(GameEngineCore::EngineEnd, _End));
}

void GameEngineCore::ChangeLevel(const std::string_view& _Name)
{
	// ���ڿ� �빮�ڷ� ��ȯ
	std::string UpperName = GameEngineString::ToUpper(_Name);

	// ��ȯ�� ���ڿ��� �ʿ� ������ �̸��� ������ ���ٸ�
	// �������� ���� ����, assert ó��
	if (LevelMap.end() == LevelMap.find(UpperName))
	{
		MsgAssert("�������� �ʴ� ������ ü���� �Ϸ��� �߽��ϴ�.");
		return;
	}

	// assert ó�� ���� �ʾҴٸ� 
	// ���� ������ �ʿ� ����� ���ڷ� ���� ������ ����
	// map �� ����, �迭�� ����ϰ� ����ϸ�
	// �������� ���� ��� .. ��.. ���� �ٽ� ����
	NextLevel = LevelMap[UpperName];
}

// �ʱ�ȭ�ÿ� ���� Start
void GameEngineCore::LevelInit(std::shared_ptr<GameEngineLevel> _Level)
{
	_Level->Start();
}