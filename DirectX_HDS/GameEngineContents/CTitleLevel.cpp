#include "PrecompileHeader.h"
#include "CTitleLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTimeEvent.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineGUI.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include <GameEngineCore/GameEngineCore.h>

#include "CTitleManager.h"
#include "CTitleEditer.h"
#include "CBackGround.h"

CTitleLevel::CTitleLevel()
{
}

CTitleLevel::~CTitleLevel()
{
}

// imgui ��ư���� �������̽� , ��. 
// 1. ������ Ŭ��������Լ��� ����
// 2. �ھ������츦 ��ӹ��� Ŭ������ ���� �Ʒ�ó�� �Լ������͸� �Ѱ��ش�. 
// std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindowConvert<GameEngineCoreWindow>("CoreWindow");
// Window->Test = std::bind(&CTitleLevel::TestFunction, this);
// Window->Test1 = std::bind(&CTitleLevel::TestFunction, this);

// imgui �׽�Ʈ��
//void CTitleLevel::TestFunction()
//{
//	std::shared_ptr<CBackGround> NewBackGround = CreateActor<CBackGround>();
//}

void CTitleLevel::Start()
{
	if (false == GameEngineInput::IsKey("DebugChange_Tutorial"))
	{
		// GameEngineInput::CreateKey("DebugChange_Tutorial", VK_F1);
		GameEngineInput::CreateKey("DebugChange_Stage01", VK_F2);
	}

	ResourcesLoad();
	ActorLoad();
	SetState(ELEVEL_STATE::WAIT);
	CKatanaZero_Level::Start();
}

void CTitleLevel::Update(float _DeltaTime)
{
	/*if (true == GameEngineInput::IsDown("DebugChange_Tutorial"))
	{
		GameEngineCore::ChangeLevel("TutorialLevel");
		return;
	}*/

	if (true == GameEngineInput::IsDown("DebugChange_Stage01"))
	{
		GameEngineCore::ChangeLevel("StageLevel_01");
		return;
	}

	
	CKatanaZero_Level::Update(_DeltaTime);
}

void CTitleLevel::LevelChangeStart()
{
	m_GUI = GameEngineGUI::FindGUIWindowConvert<CTitleEditer>("Title_Editer");
	if (m_GUI == nullptr)
	{
		MsgAssert("GUI Window�� nullptr �Դϴ�.");
		return;
	}
	
	m_GUI->On();
}

void CTitleLevel::LevelChangeEnd()
{
	m_GUI->Off();
	SetState(ELEVEL_STATE::WAIT);
}

void CTitleLevel::ResourcesLoad()
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
}

void CTitleLevel::ActorLoad()
{
	// background ����, �������� + �޹��
	std::shared_ptr<CBackGround> NewBackGround = CreateActor<CBackGround>();

	// Title �� ��� UI 
	m_TitleManager = CreateActor<CTitleManager>("TitleUIManager");
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