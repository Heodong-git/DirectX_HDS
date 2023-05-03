#include "PrecompileHeader.h"
#include "CTitleLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTimeEvent.h>

#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineCoreWindow.h>

// TEST
#include "CTitleManager.h"
#include "CBackGround.h"

CTitleLevel::CTitleLevel()
{
}

CTitleLevel::~CTitleLevel()
{
}

// imgui �׽�Ʈ��
void CTitleLevel::TestFunction()
{
	std::shared_ptr<CBackGround> NewBackGround = CreateActor<CBackGround>();
}

// �θ��Լ��� ������ �߱� ������ �̳༮�� ȣ���
void CTitleLevel::Start()
{
	CKatanaZero_Level::Start();
	ResourcesLoad();
	ActorLoad();

	// imgui window ������ �������̽�, �����츦 �����ϰ� �Լ��� �Ѱ��ش�.
	// ������ �������� imgui �� ����� �Լ����� ���ε����ְ� ����Ѵ�. 
	// �� �Ѥ� 
	std::shared_ptr<GameEngineCoreWindow> Window = GameEngineGUI::FindGUIWindowConvert<GameEngineCoreWindow>("CoreWindow");

	if (nullptr == Window)
	{
		MsgAssert("�׽�Ʈ �ڵ� ���۵�");
		return;
	}

	Window->Test = std::bind(&CTitleLevel::TestFunction, this);
	Window->Test1 = std::bind(&CTitleLevel::TestFunction, this);
}

void CTitleLevel::Update(float _DeltaTime)
{
	CKatanaZero_Level::Update(_DeltaTime);
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
	std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });
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