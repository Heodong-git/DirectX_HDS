#include "CTitleLevel.h"
#include <GameEngineBase\GameEngineDebug.h>

// TEST
#include <GameEngineBase/GameEngineTimeEvent.h>

CTitleLevel::CTitleLevel()
{
}

CTitleLevel::~CTitleLevel()
{
}

void TestFunction(GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
{
	int a = 0;
}

// �θ��Լ��� ������ �߱� ������ �̳༮�� ȣ���
void CTitleLevel::Loading()
{
	// ���� : �̸��� ���� �Լ��� ������ִ� ���
	// �ΰ��� ���ڸ� �޴� function ��ü��
	// [](����)
	// {
	// }
	// �� ���·� �̸����� �Լ��� ����� ������ �� �ִ�. �ڵ��� ���ο� ������ �ڵ� �ۼ�
	// �̷� ���·� �̸� ���� �Լ��� ������ְ� ���ο��� ���𰡸� �ϰ� �����. 
	std::function<void(GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)> Test = 
		[=](GameEngineTimeEvent::TimeEvent& _Event, GameEngineTimeEvent* _Manager)
	{
		MsgTextBox("����");

		_Manager->AddEvent(3.0f, TestFunction, false);
	};

	// ������ Ÿ���̺�Ʈ�� �Լ�ȣ��
	// ���� �׽�Ʈ������ ���� Test �Լ��� ȣ�� �Ѱ�. 
	TimeEvent.AddEvent(5.0f, Test, false);
}

