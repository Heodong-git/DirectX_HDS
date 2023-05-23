#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineSprite.h>

#include "TitleManager.h"
#include "TitleEditer.h"
#include "TitleBackGround.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	GetMainCamera()->SetSortType(0, SortType::YSort);

	ResourcesLoad();
	ActorLoad();
	SetState(BaseLevel::LevelState::WAIT);
	BaseLevel::Start();
}

void TitleLevel::Update(float _DeltaTime)
{
	/*if (true == GameEngineInput::IsDown("DebugChange_Tutorial"))
	{
		GameEngineCore::ChangeLevel("TutorialLevel");
		return;
	}*/

	BaseLevel::Update(_DeltaTime);
}

void TitleLevel::LevelChangeStart()
{
	/*m_GUI = GameEngineGUI::FindGUIWindowConvert<TitleEditer>("Title_Editer");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window�� nullptr �Դϴ�.");
		return;
	}
	
	m_GUI->On();*/
}

void TitleLevel::LevelChangeEnd()
{
	if (m_GUI != nullptr)
	{
		m_GUI->Off();
	}

	SetState(BaseLevel::LevelState::WAIT);
}

void TitleLevel::ResourcesLoad()
{
	// ���丮 Ŭ��������
	GameEngineDirectory NewDir;
	// ���ϴ� ������ ���� ���͸��� �̵�
	NewDir.MoveParentToDirectory("katanazero_resources");
	// �� ������ �̵�
	NewDir.Move("katanazero_resources");
	NewDir.Move("Texture");
	NewDir.Move("TitleLevel");

	// ���� ��ü�ε� 
	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", ".psd"});
	for (size_t i = 0; i < File.size(); i++)
	{
		GameEngineTexture::Load(File[i].GetFullPath());
	}

	if (nullptr == GameEngineSprite::Find("player_idle"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToDirectory("katanazero_resources");
		Dir.Move("katanazero_resources");
		Dir.Move("Texture");
		Dir.Move("TitleSub");

		GameEngineSprite::LoadFolder(Dir.GetPlusFileName("Plants_Anim").GetFullPath());
		std::vector<GameEngineFile> File = Dir.GetAllFile({ ".Png", });
	}
}

void TitleLevel::ActorLoad()
{
	// background ����, �������� + �޹��
	std::shared_ptr<TitleBackGround> NewBackGround = CreateActor<TitleBackGround>();

	// Title �� ��� UI �� ���� ��ǻ� �갡 ���ϴ°ɷ�
	m_TitleManager = CreateActor<TitleManager>();
	m_TitleManager->CreateRender();
}

/*
	// ���� : �̸��� ���� �Լ��� ������ִ� ���
	// �ΰ��� ���ڸ� �޴� function ��ü��
	// [](����)
	// {
	// }
	// �� ���·� �̸����� �Լ��� ����� ������ �� �ִ�. �ڵ��� ���ο� ������ �ڵ� �ۼ�
	// �̷� ���·� �̸� ���� �Լ��� ������ְ� ���ο��� ���𰡸� �ϰ� �����.
	//std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test =
	//	[=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
	//{
	//	MsgTextBox("����");

	//	_Manager->AddEvent(3.0f, TestFunction, false);
	//};

	//// ������ Ÿ���̺�Ʈ�� �Լ�ȣ��
	//// ���� �׽�Ʈ������ ���� Test �Լ��� ȣ�� �Ѱ�.
	//TimeEvent.AddEvent(5.0f, TestFunction, false);
*/