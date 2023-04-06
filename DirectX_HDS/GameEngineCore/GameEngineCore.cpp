#include "GameEngineCore.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include <GameEnginePlatform\GameEngineInput.h>
#include <GameEngineBase\GameEngineTime.h>

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
	// Core Init 
	CoreResourcesInit();

	if (nullptr == _ContentsStart)
	{
		MsgAssert("���� �������� �������� �ʽ��ϴ�.");
	}
	_ContentsStart();
}

// Loop , ������ ����Ǹ� �ݺ�����
void GameEngineCore::EngineUpdate()
{
	if (nullptr != NextLevel)
	{
		MainLevel = NextLevel;
	}

	if (nullptr == MainLevel)
	{
		MsgAssert("�ƹ��� ������ �������� �ʰ� �ֽ��ϴ�.");
		return;
	}

	float TimeDeltaTime = GameEngineTime::GlobalTime.TimeCheck();
	GameEngineInput::Update(TimeDeltaTime);
	// ���������Ʈ
	GameEngineSound::SoundUpdate();
	// Test? ������ Ÿ���̺�Ʈ�� ������Ʈ�� ����
	MainLevel->TimeEvent.Update(TimeDeltaTime);
	MainLevel->Update(TimeDeltaTime);
	MainLevel->Render(TimeDeltaTime);
}

void GameEngineCore::EngineEnd(std::function<void()> _ContentsEnd)
{
	if (nullptr == _ContentsEnd)
	{
		MsgAssert("�� �������� �������� �ʽ��ϴ�.");
	}

	_ContentsEnd();

	LevelMap.clear();

	// sharedptr �� ���� �޸𸮰� ���ŵǴ� �� �˰� ������. 
	CoreResourcesEnd();
}

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