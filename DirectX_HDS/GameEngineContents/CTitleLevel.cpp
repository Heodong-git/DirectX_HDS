#include "PrecompileHeader.h"
#include "CTitleLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineCore/GameEngineCamera.h>

// TEST
#include <GameEngineBase/GameEngineTimeEvent.h>
#include "CTitleUIManager.h"

CTitleLevel::CTitleLevel()
{
}

CTitleLevel::~CTitleLevel()
{
}

void TestFunction(GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
{
	MsgTextBox("�׽�Ʈ�� �Լ� ȣ��ǳ�? ");
}

void TestF()
{

}

// �θ��Լ��� ������ �߱� ������ �̳༮�� ȣ���
void CTitleLevel::Start()
{
	GetMainCamera()->SetProjectionType(CameraType::Orthogonal);
	GetMainCamera()->GetTransform()->SetLocalPosition({ 0 , 0 , -1000.0f });

	// Ÿ��Ʋ ui�� �����ϴ� �Ŵ��� Ŭ���� 
	m_UIManager = CreateActor<CTitleUIManager>("TitleUIManager");
}

void CTitleLevel::Update(float _DeltaTime)
{
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